import random
import string

# 定义三种规则
SEQUENCE = '顺序'
RANDOM = '随机但不去重'
RANDOM_UNIQUE = '随机并去重'

rules = []
start_points = []

# 为了生成随机字符串
def random_string(length):
    return ''.join(random.choice(string.ascii_letters) for i in range(length))

# 描述一个列的信息
class Column:
    def __init__(self, name, ctype, length=None):
        self.name = name
        self.ctype = ctype
        self.length = length if ctype == 'char' else None

# 生成指定类型和规则的数据
def generate_data(column, rule, sequence_value=1, generated_set=set()):
    if column.ctype == 'char':
        return f"'{random_string(column.length)}'"
    else:
        if rule == SEQUENCE:
            return str(sequence_value)
        elif rule == RANDOM:
            return str(random.randint(1, 10000000))  # 这里设定随机生成1-1000的整数
        else:  # RANDOM_UNIQUE
            unique_value = random.randint(1, 10000000)
            while unique_value in generated_set:
                unique_value = random.randint(1, 10000000)
            generated_set.add(unique_value)
            return str(unique_value)

# 生成SQL语句
def generate_sql(tablename, columns, mode, num, filename, condition_column=None, condition_rule=None, condition_start_point=1):
    with open(filename, 'w') as f:
        sequence_values = {col.name: start_points[i] for i, col in enumerate(columns)} if mode == 'insert' else {condition_column.name: condition_start_point}
        generated_values_set = {col.name: set() for col in columns}
        
        for _ in range(num):
            if mode == 'insert':
                values = ', '.join(generate_data(column, rules[i], sequence_values[column.name], generated_values_set[column.name]) for i, column in enumerate(columns))
                f.write(f'insert into {tablename} values ({values});\n')
                for i, column in enumerate(columns):
                    if rules[i] == SEQUENCE:
                        sequence_values[column.name] += 1
            else:  # delete or select
                condition_value = generate_data(condition_column, condition_rule, sequence_values[condition_column.name], generated_values_set[condition_column.name])
                sym = ""
                if mode == "select":
                    sym = " *"
                f.write(f'{mode}{sym} from {tablename} where {condition_column.name}={condition_value};\n')
                if condition_rule == SEQUENCE:
                    sequence_values[condition_column.name] += 1

# 主函数，用于与用户交互和指导程序流程
def main():
    global rules, start_points

    tablename = input('请输入表名：')
    
    columns = []
    column_number = int(input('请输入列的数量：'))
    for i in range(column_number):
        name = input(f'请输入第{i+1}列的名称：')
        ctype = input(f'请输入第{i+1}列的类型（int, bigint, char）：')
        length = int(input(f'请输入第{i+1}列的长度（如果类型是char）：')) if ctype == 'char' else None
        columns.append(Column(name, ctype, length))
        
    mode = input('请输入模式（insert, delete, select）：')
    if mode == 'insert':
        rules = []
        for i in range(column_number):
            rule = input(f'请输入第{i+1}列的生成规则（顺序, 随机但不去重, 随机并去重）：')
            rules.append(rule)
            if rule == SEQUENCE:
                start_points.append(int(input(f'请输入第{i+1}列的顺序起始点：')))
            else:
                start_points.append(1)
    else:
        condition_column_name = input('请输入条件的列的名称：')
        condition_column = next((col for col in columns if col.name == condition_column_name), None)
        if not condition_column:
            print(f'列名{condition_column_name}在表{tablename}中不存在.')
            return
        condition_rule = input('请输入条件的生成规则（顺序, 随机但不去重, 随机并去重）：')
        if condition_rule == SEQUENCE:
            condition_start_point = int(input(f'请输入条件列的顺序起始点：'))
        else:
            condition_start_point = 1
        
    num = int(input('请输入需要生成的语句的数量：'))
    filename = input('请输入文件名：')
    
    if mode == 'insert':
        generate_sql(tablename, columns, mode, num, filename)
    else:
        generate_sql(tablename, columns, mode, num, filename, condition_column, condition_rule, condition_start_point)

if __name__ == '__main__':
    main()
