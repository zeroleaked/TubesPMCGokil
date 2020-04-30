from __future__ import print_function
import numpy as np

outC = open('out.txt',"r")
outPython = open('outPython.txt', "r")

# for i in range (total):
#     n = int(infile.readline())
    
#     j = 0
#     mat = [[0 for x in range(n)] for y in range(n)]
#     for j in range(n):
#         kal = (infile.readline()).split()
#         for k in range(n):
#             mat[j][k] = (float)(kal[k])
#     inverse = np.linalg.inv(mat)
#     for j in range(n):
#         for k in range(n):
#             print(inverse[j][k], end = " ")
#         print()

for lineC in outC:
    lineP = outPython.readline()
    lineCList = lineC.split()
    linePList = lineP.split()
    for i in range(len(lineCList)):
        # print(str(float(lineCList[i]) - float(linePList[i])), end = " ")
        if abs(float(lineCList[i]) - float(linePList[i])) > 1.0e-10:
            print ("notPassed")
            exit(0)
    # print()
print("Passed")