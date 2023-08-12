/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "sm_manager.h"

#include <sys/stat.h>
#include <unistd.h>

#include <fstream>

#include "index/ix.h"
#include "record/rm.h"
#include "record_printer.h"

/**
 * @description: 判断是否为一个文件夹
 * @return {bool} 返回是否为一个文件夹
 * @param {string&} db_name 数据库文件名称，与文件夹同名
 */
bool SmManager::is_dir(const std::string& db_name) {
    struct stat st;
    return stat(db_name.c_str(), &st) == 0 && S_ISDIR(st.st_mode);
}

/**
 * @description: 创建数据库，所有的数据库相关文件都放在数据库同名文件夹下
 * @param {string&} db_name 数据库名称
 */
void SmManager::create_db(const std::string& db_name) {
    if (is_dir(db_name)) {
        throw DatabaseExistsError(db_name);
    }
    //为数据库创建一个子目录
    std::string cmd = "mkdir " + db_name;
    if (system(cmd.c_str()) < 0) {  // 创建一个名为db_name的目录
        throw UnixError();
    }
    if (chdir(db_name.c_str()) < 0) {  // 进入名为db_name的目录
        throw UnixError();
    }
    //创建系统目录
    DbMeta *new_db = new DbMeta();
    new_db->name_ = db_name;

    // 注意，此处ofstream会在当前目录创建(如果没有此文件先创建)和打开一个名为DB_META_NAME的文件
    std::ofstream ofs(DB_META_NAME);

    // 将new_db中的信息，按照定义好的operator<<操作符，写入到ofs打开的DB_META_NAME文件中
    ofs << *new_db;  // 注意：此处重载了操作符<<

    delete new_db;

    // 创建日志文件
    disk_manager_->create_file(LOG_FILE_NAME);

    // 回到根目录
    if (chdir("..") < 0) {
        throw UnixError();
    }
}

/**
 * @description: 删除数据库，同时需要清空相关文件以及数据库同名文件夹
 * @param {string&} db_name 数据库名称，与文件夹同名
 */
void SmManager::drop_db(const std::string& db_name) {
    if (!is_dir(db_name)) {
        throw DatabaseNotFoundError(db_name);
    }
    std::string cmd = "rm -r " + db_name;
    if (system(cmd.c_str()) < 0) {
        throw UnixError();
    }
}

/**
 * @description: 打开数据库，找到数据库对应的文件夹，并加载数据库元数据和相关文件
 * @param {string&} db_name 数据库名称，与文件夹同名
 */
void SmManager::open_db(const std::string& db_name) {
    // 检查是否存在db_name/目录
    if (!is_dir(db_name)) {
        throw DatabaseNotFoundError(db_name);
    }
    // 进入db_name/目录
    if (chdir(db_name.c_str()) < 0) {
        throw UnixError();
    }

    // 读取数据库元数据
    std::ifstream ifs(DB_META_NAME);
    ifs >> db_;

    // 加载表元数据
    for (auto &entry : db_.tabs_) {
        auto &tab = entry.second;
        fhs_.emplace(tab.name, rm_manager_->open_file(tab.name));

        // 打开表文件
        // fhs_[tab.name] = rm_manager_->open_file(tab.name);

        // TODO: 加载索引
        for (auto &ix_meta : tab.indexes) {
            ihs_.emplace(ix_manager_->get_index_name(tab.name, ix_meta.cols), ix_manager_->open_index(tab.name, ix_meta.cols));
        }
    }
}

/**
 * @description: 把数据库相关的元数据刷入磁盘中
 */
void SmManager::flush_meta() {
    // 默认清空文件
    std::ofstream ofs(DB_META_NAME);
    ofs << db_;
}

/**
 * @description: 关闭数据库并把数据落盘
 */
void SmManager::close_db() {
    // flush所有脏page
    for (auto &rm_file : fhs_) {
        buffer_pool_manager_->flush_all_pages(rm_file.second->GetFd());
    }
    // 刷新元数据
    flush_meta();

    // 回到根目录

    if (chdir("..") < 0) {
        throw UnixError();
    }

    // 关闭所有表文件

    for (auto &rm_file : fhs_) {
        rm_manager_->close_file(rm_file.second.get());
    }
    fhs_.clear();

    //TODO: 关闭日志文件

    
}

/**
 * @description: 显示所有的表,通过测试需要将其结果写入到output.txt,详情看题目文档
 * @param {Context*} context 
 */
void SmManager::show_tables(Context* context) {
    std::fstream outfile;
    
    outfile.open("output.txt", std::ios::out | std::ios::app);
    outfile << "| Tables |\n";
    RecordPrinter printer(1);
    printer.print_separator(context);
    printer.print_record({"Tables"}, context);
    printer.print_separator(context);
    for (auto &entry : db_.tabs_) {
        auto &tab = entry.second;
        printer.print_record({tab.name}, context);
        outfile << "| " << tab.name << " |\n";
    }
    printer.print_separator(context);
    outfile.close();
}

/**
 * @description: 显示表的元数据
 * @param {string&} tab_name 表名称
 * @param {Context*} context 
 */
void SmManager::desc_table(const std::string& tab_name, Context* context) {
    TabMeta &tab = db_.get_table(tab_name);

    std::vector<std::string> captions = {"Field", "Type", "Index"};
    RecordPrinter printer(captions.size());
    // Print header
    printer.print_separator(context);
    printer.print_record(captions, context);
    printer.print_separator(context);
    // Print fields
    for (auto &col : tab.cols) {
        std::vector<std::string> field_info = {col.name, coltype2str(col.type), col.index ? "YES" : "NO"};
        printer.print_record(field_info, context);
    }
    // Print footer
    printer.print_separator(context);
}

/**
 * @description: 创建表
 * @param {string&} tab_name 表的名称
 * @param {vector<ColDef>&} col_defs 表的字段
 * @param {Context*} context 
 */
void SmManager::create_table(const std::string& tab_name, const std::vector<ColDef>& col_defs, Context* context) {
    if (db_.is_table(tab_name)) {
        throw TableExistsError(tab_name);
    }
    // Create table meta
    int curr_offset = 0;
    TabMeta tab;
    tab.name = tab_name;
    for (auto &col_def : col_defs) {
        ColMeta col = {.tab_name = tab_name,
                       .name = col_def.name,
                       .type = col_def.type,
                       .len = col_def.len,
                       .offset = curr_offset,
                       .index = false};
        curr_offset += col_def.len;
        tab.cols.push_back(col);
    }
    // Create & open record file
    int record_size = curr_offset;  // record_size就是col meta所占的大小（表的元数据也是以记录的形式进行存储的）
    rm_manager_->create_file(tab_name, record_size);
    db_.tabs_[tab_name] = tab;
    // fhs_[tab_name] = rm_manager_->open_file(tab_name);
    fhs_.emplace(tab_name, rm_manager_->open_file(tab_name));

    if(context != nullptr) {
        context->lock_mgr_->lock_exclusive_on_table(context->txn_, fhs_[tab_name]->GetFd());
    }

    flush_meta();
}

/**
 * @description: 删除表
 * @param {string&} tab_name 表的名称
 * @param {Context*} context
 */
void SmManager::drop_table(const std::string& tab_name, Context* context) {

    if(context != nullptr) {
        context->lock_mgr_->lock_exclusive_on_table(context->txn_, fhs_[tab_name]->GetFd());
    }
    
    // 检查
    if (!db_.is_table(tab_name)) {
        throw TableNotFoundError(tab_name);
    }
    // 删除索引
    
    for (auto it = db_.tabs_[tab_name].indexes.begin(); it != db_.tabs_[tab_name].indexes.end(); it++) {
        // buffer_pool_manager_->delete_all_pages(ih->fd_);
        // ix_manager_->destroy_index(tab_name, it->cols);
        // //drop_index(tab_name, it->cols, context);
        // ix_manager_->destroy_index(ihs_.at(index_name).get(), tab_name, col_names);

        auto index_name = ix_manager_->get_index_name(tab_name, it->cols);
        ix_manager_->close_index(ihs_.at(index_name).get());
        //ix_manager_->destroy_index(ihs_.at(index_name).get(), tab_name, col_names);
        buffer_pool_manager_->delete_all_pages(ihs_.at(index_name).get()->get_fd());
        ix_manager_->destroy_index(tab_name, it->cols);
    }

    // 2. 删除db_中的对应的tabs_
    db_.tabs_.erase(tab_name);

    // 3. 删除buffer pool中的pages
    auto rm_file_hdl = fhs_.at(tab_name).get();
    buffer_pool_manager_->delete_all_pages(rm_file_hdl->GetFd());

    // 4. 记录管理器删除表中的数据文件
    rm_manager_->destroy_file(tab_name);
    fhs_.erase(tab_name);

    flush_meta();
}

/**
 * @description: 创建索引
 * @param {string&} tab_name 表的名称
 * @param {vector<string>&} col_names 索引包含的字段名称
 * @param {Context*} context
 */
void SmManager::create_index(const std::string& tab_name, const std::vector<std::string>& col_names, Context* context) {
    
    if(context != nullptr) {
        context->lock_mgr_->lock_shared_on_table(context->txn_, fhs_[tab_name]->GetFd());
    }

    // 检查表名
    if (!db_.is_table(tab_name)) {
        throw TableNotFoundError(tab_name);
    }

    // 检查字段名
    auto &tab = db_.get_table(tab_name);

    for (auto &col_name : col_names) {
        if (!tab.is_col(col_name)) {
            throw ColumnNotFoundError(col_name);
        }
    }
    
    // 检查索引是否存在
    if (ix_manager_->exists(tab_name, col_names)) {
        throw IndexExistsError(tab_name, col_names);
    }

    std::string ix_file_name = tab_name;

    // 构建colMeta的vector
    std::vector<ColMeta> cols;

    IndexMeta ix_meta;
    ix_meta.tab_name = tab_name;
    ix_meta.col_tot_len = 0;
    ix_meta.col_num = col_names.size();

    for (auto &col_name : col_names) {

        ColMeta &col = tab.get_col(col_name)[0];
        //ColMeta &col = *db_.get_table(tab_name).get_col(col_name);

        col.index = true;

        ix_meta.col_tot_len += col.len;
        ix_meta.cols.push_back(col);
        cols.push_back(col);
    }

    // 创建索引
    ix_manager_->create_index(ix_file_name, cols);

    // ihs_.emplace(ix_manager_->get_index_name(tab_name, col_names), ix_manager_->open_index(ix_file_name, cols));

    // 添加到TabMeta中
    tab.indexes.push_back(ix_meta);

    std::string index_name = ix_manager_->get_index_name(tab_name,col_names);
      // 4. 更新TableMeta
    int fd = disk_manager_->open_file(index_name);

    auto page = buffer_pool_manager_->fetch_page(PageId{fd,IX_FILE_HDR_PAGE});

    IxFileHdr ix_file_hdl;
    ix_file_hdl.deserialize(page->get_data());
    // ix_meta.col_tot_len = ix_file_hdl.col_tot_len_;
    // ix_meta.col_num = ix_file_hdl.col_num_;
    // for(auto &col_meta : cols) {
    //     ix_meta.cols.push_back(col_meta);
    // }
    //db_.get_table(tab_name).indexes.push_back(ix_meta);

    char* key = new char[ix_meta.col_tot_len];

    buffer_pool_manager_->unpin_page(page->get_page_id(),false);
    disk_manager_->close_file(fd);

    // 更新sm_manager
    // auto ix_hdl = ix_manager_->open_index(tab_name,col_names);
    ihs_.emplace(index_name, ix_manager_->open_index(tab_name,col_names));
    auto ix_hdl = ihs_.at(index_name).get();
    
    // 将表已存在的record创建索引
    // auto tab = db_.get_table(tab_name);
    auto file_hdl = fhs_.at(tab_name).get();

    try{
        for (RmScan rm_scan(file_hdl); !rm_scan.is_end(); rm_scan.next()) {
            auto rec = file_hdl->get_record(rm_scan.rid(), context);  
            int offset = 0;
            for(size_t i = 0; i < ix_meta.col_num; ++i) {
                    memcpy(key + offset, rec->data + ix_meta.cols[i].offset, ix_meta.cols[i].len);
                    offset += ix_meta.cols[i].len;
                }
            ix_hdl->insert_entry(key, rm_scan.rid(), context->txn_);
        }
    }catch(InternalError &error) {
            drop_index(tab_name, col_names, context);
            //throw InternalError("Non-unique index!");
            std::cout<<"create index fail"<<std::endl;
        }

    flush_meta();

    std::cout<<"create index success"<<std::endl;
}

/**
 * @description: 删除索引
 * @param {string&} tab_name 表名称
 * @param {vector<string>&} col_names 索引包含的字段名称
 * @param {Context*} context
 */
void SmManager::drop_index(const std::string& tab_name, const std::vector<std::string>& col_names, Context* context) {

    if(context != nullptr) {
        context->lock_mgr_->lock_shared_on_table(context->txn_, fhs_[tab_name]->GetFd());
    }

    // 检查表名
    if (!db_.is_table(tab_name)) {
        throw TableNotFoundError(tab_name);
    }

    // 存在性检查
    if (!ix_manager_->exists(tab_name, col_names)) {
        throw IndexNotFoundError(tab_name, col_names);
    }

        // 判断索引是否正确
    TabMeta &tab = db_.tabs_[tab_name];
    for(auto col_name : col_names) {
        auto col = tab.get_col(col_name);
        if(tab.is_col_to_index(col->name)){
            col->index = false;
        }
    }

    // // 删除索引文件
    // ix_manager_->destroy_index(tab_name, col_names);

    // // 删除TabMeta中的索引
    // for (auto it = db_.get_table(tab_name).indexes.begin(); it != db_.get_table(tab_name).indexes.end(); it++) {
    //     if (it->tab_name == tab_name && it->col_num == col_names.size()) {
    //         bool flag = true;
    //         for (int i = 0; i < col_names.size(); i++) {
    //             if (it->cols[i].name != col_names[i]) {
    //                 flag = false;
    //                 break;
    //             }
    //         }
    //         if (flag) {
    //             db_.get_table(tab_name).indexes.erase(it);
    //             break;
    //         }
    //     }
    // }

    // ihs_.erase(ix_manager_->get_index_name(tab_name, col_names));

    // 删除索引
    auto index_name = ix_manager_->get_index_name(tab_name, col_names);
    ix_manager_->close_index(ihs_.at(index_name).get());
    ix_manager_->destroy_index(ihs_.at(index_name).get(), tab_name, col_names);
    
    auto ix_meta = db_.get_table(tab_name).get_index_meta(col_names);
    db_.get_table(tab_name).indexes.erase(ix_meta);
    ihs_.erase(index_name);

    flush_meta();

    std::cout<<"drop index success"<<std::endl;
}

/**
 * @description: 显示索引
 * @param {string&} tab_name 表名称
 * @param {Context*} context
 */
void SmManager::show_index(const std::string& tab_name, Context* context) {
    std::cout<<"show index called"<<std::endl;

    // 检查表名
    if (!db_.is_table(tab_name)) {
        throw TableNotFoundError(tab_name);
    }

    TabMeta &tab = db_.get_table(tab_name);

    std::fstream outfile;

    outfile.open("output.txt", std::ios::out | std::ios::app);

    RecordPrinter printer(3);

    printer.print_separator(context);
    printer.print_record({"Table", "Unique", "Column_names"}, context);
    printer.print_separator(context);

    // for 所有索引
    for (auto &ix_meta : tab.indexes) {
        // 打印表名
        outfile << "| " << tab_name << " ";

        // 是否唯一
        outfile << "| unique " ; 

        // 打印字段名
        outfile << "| (";
        outfile << ix_meta.cols[0].name;
        std::string col_name = "("+ix_meta.cols[0].name;
        for (int i = 1; i < ix_meta.col_num; i++) {
            outfile << "," << ix_meta.cols[i].name;
            col_name += ","+ix_meta.cols[i].name;
        }
        col_name += ")";
        printer.print_record({tab_name, "unique", col_name}, context);
        outfile << ") |\n";
        // // 打印索引名
        // outfile << "| " << ix_manager_->get_index_name(tab_name, ix_meta.cols) << " |\n";
    }
    printer.print_separator(context);
    outfile.close();
}

/**
 * @description: 删除索引
 * @param {string&} tab_name 表名称
 * @param {vector<ColMeta>&} 索引包含的字段元数据
 * @param {Context*} context
 */
void SmManager::drop_index(const std::string& tab_name, const std::vector<ColMeta>& cols, Context* context) {
    // 直接提取字段名
    std::vector<std::string> col_names;

    for (auto &col : cols) {
        col_names.push_back(col.name);
    }

    drop_index(tab_name, col_names, context);
    // 我真是天才
}