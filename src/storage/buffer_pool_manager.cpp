/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "buffer_pool_manager.h"

/**
 * @description: 从free_list或replacer中得到可淘汰帧页的 *frame_id
 * @return {bool} true: 可替换帧查找成功 , false: 可替换帧查找失败
 * @param {frame_id_t*} frame_id 帧页id指针,返回成功找到的可替换帧id
 */
bool BufferPoolManager::find_victim_page(frame_id_t* frame_id) {
    // Todo:

    
    // 1 使用BufferPoolManager::free_list_判断缓冲池是否已满需要淘汰页面

    // 1.1 未满获得frame
    if (!free_list_.empty()) {
        *frame_id = free_list_.front();
        free_list_.pop_front();
        return true;
    }

    // 1.2 已满使用lru_replacer中的方法选择淘汰页面

    else {
        if (!replacer_->victim(frame_id)) {
            return false;
        }

        // 将淘汰的page写入磁盘

        Page* page = &pages_[*frame_id];
        
        if (page->is_dirty_) {
            disk_manager_->write_page(page->id_.fd, page->id_.page_no, page->get_data(), PAGE_SIZE);
            page->is_dirty_ = false;
        }

        return true;
    }
}

/**
 * @description: 更新页面数据, 如果为脏页则需写入磁盘，再更新为新页面，更新page元数据(data, is_dirty, page_id)和page table
 * @param {Page*} page 写回页指针
 * @param {PageId} new_page_id 新的page_id
 * @param {frame_id_t} new_frame_id 新的帧frame_id
 */
void BufferPoolManager::update_page(Page *page, PageId new_page_id, frame_id_t new_frame_id) {
    // Todo:

    // 1 如果是脏页，写回磁盘，并且把dirty置为false

    if (page->is_dirty_) {
        disk_manager_->write_page(page->id_.fd, page->id_.page_no, page->get_data(), PAGE_SIZE);
        //page->is_dirty_ = false;
    }

    // 2 更新page table

    page_table_.erase(page->id_);
    page_table_[new_page_id] = new_frame_id;

    // 3 重置page的data，更新page id

    page->reset_memory();
    page->id_ = new_page_id;

    page->pin_count_ = 0;
    page->is_dirty_ = false;
}

/**
 * @description: 从buffer pool获取需要的页。
 *              如果页表中存在page_id（说明该page在缓冲池中），并且pin_count++。
 *              如果页表不存在page_id（说明该page在磁盘中），则找缓冲池victim page，将其替换为磁盘中读取的page，pin_count置1。
 * @return {Page*} 若获得了需要的页则将其返回，否则返回nullptr
 * @param {PageId} page_id 需要获取的页的PageId
 */
Page* BufferPoolManager::fetch_page(PageId page_id) {
    //Todo:

    std::scoped_lock lock{latch_};

    // 1.     从page_table_中搜寻目标页

    auto it = page_table_.find(page_id);

    // 1.1    若目标页有被page_table_记录，则将其所在frame固定(pin)，并返回目标页。

    if (it != page_table_.end()) {
        Page* page = &pages_[it->second];
        page->pin_count_ += 1;

        if (page->pin_count_ == 1) {
            replacer_->pin(it->second);
        }

        return page;
    }

    // 1.2    否则，尝试调用find_victim_page获得一个可用的frame，若失败则返回nullptr
    
    else {
        frame_id_t frame_id;

        if (!find_victim_page(&frame_id)) {
            return nullptr;
        }

        Page* page = &pages_[frame_id];

        // 2.  若获得的可用frame存储的为dirty page，则须调用updata_page将page写回到磁盘
        
        update_page(page, page_id, frame_id);

        // 3.  调用disk_manager_的read_page读取目标页到frame

        disk_manager_->read_page(page_id.fd, page_id.page_no, page->get_data(), PAGE_SIZE);

        // 4.  固定目标页，更新pin_count_

        page->pin_count_ += 1;

        if (page->pin_count_ == 1) {
            replacer_->pin(frame_id);
        }

        // 5  返回目标页

        return page;
    }
}

/**
 * @description: 取消固定pin_count>0的在缓冲池中的page
 * @return {bool} 如果目标页的pin_count<=0则返回false，否则返回true
 * @param {PageId} page_id 目标page的page_id
 * @param {bool} is_dirty 若目标page应该被标记为dirty则为true，否则为false
 */
bool BufferPoolManager::unpin_page(PageId page_id, bool is_dirty) {
    // Todo:
    // 0. lock latch

    std::scoped_lock lock{latch_};

    // 1. 尝试在page_table_中搜寻page_id对应的页P

    auto it = page_table_.find(page_id);

    // 1.1 P在页表中不存在 return false

    if (it == page_table_.end()) {
        return false;
    }

    // 1.2 P在页表中存在，获取其pin_count_
    
    else {
        int pin_count = pages_[it->second].pin_count_;

        // 2.1 若pin_count_已经等于0，则返回false

        if (pin_count == 0) {
            return false;
        }

        // 2.2 若pin_count_大于0，则pin_count_自减一
        
        else {
            pages_[it->second].pin_count_ -= 1;

            // 2.2.1 若自减后等于0，则调用replacer_的Unpin

            if (pages_[it->second].pin_count_ == 0) {
                replacer_->unpin(it->second);
            }
            // 3 根据参数is_dirty，更改P的is_dirty_
            if (is_dirty) {
                pages_[it->second].is_dirty_ = true;
            }
        }
        return true;
    }
}

/**
 * @description: 将目标页写回磁盘，不考虑当前页面是否正在被使用
 * @return {bool} 成功则返回true，否则返回false(只有page_table_中没有目标页时)
 * @param {PageId} page_id 目标页的page_id，不能为INVALID_PAGE_ID
 */
bool BufferPoolManager::flush_page(PageId page_id) {
    // Todo:
    // 0. lock latch

    std::scoped_lock lock{latch_};

    assert(page_id.page_no != INVALID_PAGE_ID);

    // 1. 查找页表,尝试获取目标页P

    auto it = page_table_.find(page_id);

    // 1.1 目标页P没有被page_table_记录 ，返回false

    if (it == page_table_.end()) {
        return false;
    }

    // 2. 无论P是否为脏都将其写回磁盘。
    
    Page* page = &pages_[it->second];

    disk_manager_->write_page(page_id.fd, page_id.page_no, page->get_data(), PAGE_SIZE);

    // 3. 更新P的is_dirty_

    page->is_dirty_ = false;
   
    return true;
}

/**
 * @description: 创建一个新的page，即从磁盘中移动一个新建的空page到缓冲池某个位置。
 * @return {Page*} 返回新创建的page，若创建失败则返回nullptr
 * @param {PageId*} page_id 当成功创建一个新的page时存储其page_id
 */
Page* BufferPoolManager::new_page(PageId* page_id) {
    // 1.   获得一个可用的frame，若无法获得则返回nullptr

    std::scoped_lock lock{latch_};

    frame_id_t frame_id;

    if (!find_victim_page(&frame_id)) {
        return nullptr;
    }

    // 2.   在fd对应的文件分配一个新的page_id

    Page* page = &pages_[frame_id];

    *page_id = {page_id->fd, disk_manager_->allocate_page(page_id->fd)};
    // page->id_ = *page_id; // done by update_page

    update_page(page, *page_id, frame_id);

    // 3.   将frame的数据写回磁盘

    disk_manager_->write_page(page_id->fd, page_id->page_no, page->get_data(), PAGE_SIZE);
    // 4.   固定frame，更新pin_count_

    page->pin_count_ += 1;

    if (page->pin_count_ == 1) {
        replacer_->pin(frame_id);
    }

    // 5.   返回获得的page
   return page;
}

/**
 * @description: 从buffer_pool删除目标页
 * @return {bool} 如果目标页不存在于buffer_pool或者成功被删除则返回true，若其存在于buffer_pool但无法删除则返回false
 * @param {PageId} page_id 目标页
 */
bool BufferPoolManager::delete_page(PageId page_id) {
    // 1.   在page_table_中查找目标页，若不存在返回true

    std::scoped_lock lock{latch_};

    auto it = page_table_.find(page_id);

    if (it == page_table_.end()) {
        return true;
    }

    // 2.   若目标页的pin_count不为0，则返回false
    
    if (pages_[it->second].pin_count_ != 0) {
        return false;
    }

    // 3.   将目标页数据写回磁盘，从页表中删除目标页，重置其元数据，将其加入free_list_，返回true
    if (pages_[it->second].is_dirty_) {
        disk_manager_->write_page(page_id.fd, page_id.page_no, pages_[it->second].get_data(), PAGE_SIZE);
        pages_[it->second].is_dirty_ = false;
    }

    page_table_.erase(it);

    pages_[it->second].reset_memory();

    free_list_.push_back(it->second);
    
    pages_[it->second].pin_count_ = 0;

    return true;
}

/**
 * @description: 将buffer_pool中的所有页写回到磁盘
 * @param {int} fd 文件句柄
 */
void BufferPoolManager::flush_all_pages(int fd) {

    std::scoped_lock lock{latch_};

    // 遍历page_table_

    for (auto it = page_table_.begin(); it != page_table_.end(); ++it) {
        // 若page的fd与参数fd相同，则将其写回磁盘
        if (it->first.fd == fd) {
            Page* page = &pages_[it->second];

            disk_manager_->write_page(page->id_.fd, page->id_.page_no, page->get_data(), PAGE_SIZE);

            page->is_dirty_ = false;
        }
    }
}

void BufferPoolManager::delete_all_pages(int fd) {
    std::scoped_lock lock{latch_};
    std::vector<PageId> to_be_deleted;
    for(auto& [page_id, frame] : page_table_) {
        if(page_id.fd == fd) {
            to_be_deleted.push_back(page_id);
        }
    }

    for(auto page_id : to_be_deleted) {
        auto frame = page_table_[page_id];  
        // 如果该页面还没有unpin，则unpin
        replacer_->unpin(frame);
        // 从页表中删除该页面并添加到free_list中
        Page *page = &(pages_[frame]);
        page->reset_memory();
        page->is_dirty_ = false;
        page->pin_count_ = 0;

        page_table_.erase(page_id);
        free_list_.emplace_back(frame);
    }
}