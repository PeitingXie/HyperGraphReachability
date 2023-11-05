n = 15
file_names = []
file_name = 'hyperedge-amazon-reviews'
for i in range(1,n+1):
    file_names.append(f'{file_name}{i}.txt')
    

for i in file_names:
    print(i)

# file_names = ['file1.txt', 'file2.txt', 'file3.txt', 'file4.txt', ...]

# # 创建一个新文件，命名为 "file"
output_file_name = file_name
with open(output_file_name + 'merged.txt', 'w') as output_file:
    for file_name in file_names:
        with open(file_name, 'r') as input_file:
            output_file.write(input_file.read())

print(f'合并完成，结果保存在 {output_file_name}.txt')