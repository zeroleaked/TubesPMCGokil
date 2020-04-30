# import numpy as np
# infile = open('in.txt',"r")
# total = int(infile.readline())

# for i in range (total):
#     n = int(infile.readline())
    
#     j = 0
#     mat = [[0 for x in range(n)] for y in range(n)]
#     for j in range(n):
#         kal = (infile.readline()).split()
#         for k in range(n):
#             mat[j][k] = (float)(kal[k])
#     print np.linalg.det(mat)
from __future__ import print_function
import numpy as np

infile = open('in.txt',"r")
total = int(infile.readline())

for i in range (total):
    n = int(infile.readline())
    
    j = 0
    mat = [[0 for x in range(n)] for y in range(n)]
    for j in range(n):
        kal = (infile.readline()).split()
        for k in range(n):
            mat[j][k] = (float)(kal[k])
    inverse = np.linalg.inv(mat)
    for j in range(n):
        for k in range(n):
            print(inverse[j][k], end = " ")
        print()



