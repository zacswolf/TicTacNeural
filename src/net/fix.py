import csv 
import sys #used for passing in the argument
file_name = sys.argv[1] #filename is argument 1
if len(sys.argv < 2):
    file_name = "../TrainingData.csv"
i = -1

p1 = open("player1.csv", "w")
p2 = open("player2.csv", "w")

with open(file_name, 'rU') as f:  #opens PW file
    reader = csv.reader(f)
    for row in reader:
        i += 1
        if i == 0:
            continue
        if len(row) != 30:
            continue
        r = [int(x) for x in row]
        if r[29] == 1:
            write = p1
        else:
            write = p2
        del r[29]
        r = [r[28]] + r[:-1]
        write.write(','.join([str(x) for x in r]))
        write.write('\n') 

p1.close()
p2.close()
