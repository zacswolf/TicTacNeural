import csv 
import sys #used for passing in the argument

def rotate(a):
    return [a[6], a[3], a[0], a[7], a[4], a[1], a[8], a[5], a[2]]

rot = {     6:0,  3:1,  0:2,  7:3,  4:4,  1:5,  8:6,  5:7,  2:8}

if len(sys.argv) < 2:
    file_name = "../TrainingData.csv"
else:
    file_name = sys.argv[1] #filename is argument 1
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
        A, B, C = r[2:11], r[11:20], r[20:29]
        r = r[:2]
        for i in range(4):
            r[0] = rot[r[0]]
            A = rotate(A)
            B = rotate(B)
            C = rotate(C)

            val = r + A + B + C
            write.write(','.join([str(x) for x in val]))
            write.write('\n') 

p1.close()
p2.close()
