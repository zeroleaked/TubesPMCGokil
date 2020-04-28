import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from Tkinter import *
# import matplotlib
# matplotlib.use("TkAgg")
# from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
# from matplotlib.figure import Figure

class AppS:
    def __init__(self, master=None, fileName = None):
        self.master = master
        master.title("APP")


        self.data = pd.read_csv(fileName)

        self.Dict = {}
        total = 0
        for col in (self.data).columns:
            self.Dict[total] = col
            if (total != 0):
                Button(master,text = col,command=(lambda total = total:(self.showPlot(total)))).pack()
            
            total += 1
    
    def showPlot(self, choice_show):
    	plt.close()
    	# figure = plt.Figure()
        # ax[choice_show] = plt.gca()
        print(choice_show)
        print(self.Dict.get(choice_show))
        # (self.data).plot(kind = 'line', x = 't', y = ((self.Dict).get(choice_show)), ax = ax[choice_show])
        (self.data).plot(kind = 'line', x = 't', y = ((self.Dict).get(choice_show)))
        plt.show()
    def hello(self):
    	print "hellod"



    
        
root = Tk()
app = AppS(master=root, fileName = "outfile.csv")
root.mainloop()

# data = pd.read_csv("outfile.csv")h
# Dict = {}
# total = 0

# def showPlot(choice_show):
#     ax = plt.gca()
#     data.plot(kind = 'line', x = 't', y = Dict[choice_show], ax = ax)
#     plt.show()
#     # choice = int(input('Pilih  yang anda inginkan :'))


# root = Tk()
# root.geometry("600x800")

# # print('Data yang tersedia:')
# for col in data.columns:
#     if (total != 0):
#         Button(window,text = col,command=showPlot(total))
#         Button.pack()
#         #print str(total),"-" , str(col)
#     Dict[total] = col
    
#     total += 1

# # choice = int(input('Pilih  yang anda inginkan :'))
# root.mainloop()

    
