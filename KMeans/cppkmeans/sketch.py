import numpy as np
import matplotlib.pyplot as plt
'''
text_file1 = open("RESULTX.txt", "r")
text_file2 = open("RESULTY.txt", "r")
text_file3 = open("RESULTc.txt", "r")
lines1 = text_file1.read().split(',')
lines2 = text_file2.read().split(',')
lines3 = text_file3.read().split(',')
'''

with open("my_output.txt") as f:
    content = f.readlines()
# you may also want to remove whitespace characters like `\n` at the end of each line
content = [x.strip() for x in content]
lines1 = []
lines2 = []
lines3 = []

for x in content:
    sp = x.split(' ')
    print (sp[0], sp[1], sp[2])
    lines1.append(sp[0])
    lines2.append(sp[1])
    lines3.append(sp[2])
    #print(x.split(' ')[0] + "haha")
print (len(lines1))
print (len(lines2))
print (len(lines3))

#lines1 = [1,2,3]
#lines2 = [1,2,3]
#colors = ['black','red','red']
colors = lines3
plt.scatter(lines1,lines2, color=colors)
plt.axis([0, 50, 0, 50])
plt.show()
