import random


def int_random(unique_list = []):
    while True:
        i = random.randint(0, 2147483647)
        if i not in unique_list:
            return i

def bigint_random(unique_list = []):
    while True:
        i = random.randint(0, 9223372036854775807)
        if i not in unique_list:
            return i

def char_random(length):
    s = ""

    for i in range(length):
        s += chr(random.randint(97, 122))

    return s

tab_name = input("Enter the name of the tab: ")

columns = []
"""
[
    {
        "name": "id",
        "type": "int",
    },
    {
        "name": "name",
        "type": "char",
        "length": 10,
    }
]
"""

print("="*20)

index = 1

while True:
    column_name = input("Enter the name of No.{} column('exit' to end): ".format(index))
    if column_name == "exit":
        break
    column_type = input("Enter the type of No.{} column: ".format(index))
    column = {
        "name": column_name,
        "type": column_type,
    }
    if column_type == 'char':
        column_length = input("Enter the length of No.{} column: ".format(index))
        column["length"] = column_length
    columns.append(column)

    index+=1

# print("Column you entered:", ", ".join([column["name"]+" "+column["type"] for column in columns]))

print(columns)

print("="*20)

unique_cols = []

uc_str = input("Enter the numbers of unique columns, separated by comma: ")

unique_cols = uc_str.split(",")

# convert to number
unique_cols = [int(col) for col in unique_cols]

print("Unique nums of columns:", unique_cols)

print("="*20)

amount = int(input("Enter the amount of data you want to generate: "))

filename = input("Enter the filename you want to save: ")

print("="*20)

print("Generating...")

# 删除文件

import os
import sys
import shutil

if os.path.exists(filename):
    os.remove(filename)

unique_cols_value_map = {}

for col in unique_cols:
    key = columns[col]["name"]

    unique_cols_value_map[key] = []

for i in range(amount):

    col_vals = []
    for col in columns:
        val = ''
        if col["type"] == "int":
            if col['name'] in unique_cols_value_map:
                val = int_random(unique_cols_value_map[col["name"]])
                unique_cols_value_map[col["name"]].append(val)
            else:
                val = int_random([])
        elif col["type"] == "bigint":
            if col['name'] in unique_cols_value_map:
                val = bigint_random(unique_cols_value_map[col["name"]])
                unique_cols_value_map[col["name"]].append(val)
            else:
                val = bigint_random([])
        elif col["type"] == "char":
            val = "'"+char_random(int(col["length"]))+"'"
        else:
            raise Exception("Unknown type: {}".format(col["type"]))
        
        col_vals.append(str(val))

    # print(col_vals)
    if i/amount*100 % 10 == 0:
        print("{}%".format(i/amount*100))
    
    sql = "INSERT INTO {} VALUES ({});".format(tab_name, ", ".join(col_vals))

    with open(filename, "a") as f:
        f.write(sql+"\n")