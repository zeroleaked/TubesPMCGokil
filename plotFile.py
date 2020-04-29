import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

try :
    import subprocess
except:
    print("install subprocess")
    exit(0)
try :
    import Tkinter as Tk
except ImportError :
    import tkinter as Tk

class addFrame(Tk.Toplevel):
    def __init__(self, original, frameName):
        self.original_frame = original
        Tk.Toplevel.__init__(self)
        self.geometry("400x300")
        self.title(frameName) 
        self.Row = 0

    def onClose(self):
        self.destroy()
        self.original_frame.show()

    def getRow(self):
        self.Row += 1
        return (self.Row - 1)   

class showPlotClass(Tk.Toplevel):
    def __init__(self, original):
        """Constructor"""
        self.original_frame = original
        self.data = original.data
        self.Dict = original.Dict
        Tk.Toplevel.__init__(self)
        self.geometry("800x600")
        self.title("Show Plot")
        

        self.showPlotMenu()
       
        btn = Tk.Button(self, text="Close", command=self.onClose)
        btn.pack()          

    def onClose(self):
        self.destroy()
        self.original_frame.show()

        #plotting menu
    def showPlotMenu(self):
 
        total = 0
        for col in (self.data).columns:
            self.Dict[total] = col
            if (total != 0):
                Tk.Button(self,text = col,command=(lambda total = total:(self.showPlot(total)))).pack()
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