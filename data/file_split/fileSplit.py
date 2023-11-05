fileName = 'hyperedge-amazon-reviews'
with open(fileName + '.txt', 'r') as input_file:
    file_number = 1
    line_count = 0
    output_file = None

    for line in input_file:
        if line_count % 300000 == 0:
            if output_file:
                output_file.close()
            output_file = open(f'{fileName}{file_number}.txt', 'w')
            file_number += 1
        output_file.write(line)
        line_count += 1

    if output_file:
        output_file.close()