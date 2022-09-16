file1 = open("log", "r")
file2 = open("rightlog", "r")

lines1 = file1.readlines()
lines2 = file2.readlines()

for i in range(len(lines1)):
    vals1 = lines1[i].split(', ')
    vals2 = lines2[i].split(', ')
    for j in range(len(vals1)):
        if(vals1[j] != vals2[j]):
            print(f"diffrence at line: {i+1}, {vals1[j]} : {vals2[j]}")

