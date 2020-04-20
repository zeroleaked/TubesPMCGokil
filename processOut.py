import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data = pd.read_csv("outfile.csv")
Dict = {}
total = 0
print('Data yang tersedia:')
for col in data.columns:
    Dict[total] = col
    print(total ,':' , col)
    total += 1

choice = int(input('Pilih  yang anda inginkan :'))
while choice != 0 :
    ax = plt.gca()
    data.plot(kind = 'line', x = 't', y = Dict[choice], ax = ax)
    plt.show()
    choice = int(input('Pilih  yang anda inginkan :'))
