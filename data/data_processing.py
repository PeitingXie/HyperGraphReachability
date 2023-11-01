count = 0
with open('colored-MAG_raw.txt', 'r') as file:
    line = file.readline()
    while (line):
        data1 = line.split(' ')
        data2 = data1[0].replace(',', ' ')
        data2 += "\n"
        
        with open('colored-MAG.txt', 'a') as file2:
            file2.write(data2)
        
        line = file.readline()
        count += 1
        if (count % 100 == 0) :
            print(count)