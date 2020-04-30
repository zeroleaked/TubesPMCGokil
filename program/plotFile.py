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
        self.data = pd.read_csv(original.fileOutputName)
        self.Dict ={}
        Tk.Toplevel.__init__(self)
        self.frame = Tk.Frame(self)
        self.frame.grid(padx=10, pady=10)

        # self.geometry("800x600")
        self.title("Show Plot")

        title = Tk.Label(self.frame, text="Show Plot")
        title.grid(row=0, column=1, padx=5, pady=5, sticky="NESW")

        self.showPlotMenu()
        print self.data.shape[1]

        btn = Tk.Button(self.frame, text="Close", command=self.onClose)
        btn.grid(row=self.data.shape[1], column=1, padx=5, pady=5)

    def onClose(self):
        self.destroy()
        self.original_frame.show()

        #plotting menu
    def showPlotMenu(self):
        total = 0
        last = 'n'
        offset = 0
        i = 0
        for col in self.data.columns:
            self.Dict[total] = col
            if (total != 0):
                if last != col[0]:
                    offset += 1
                    i = 1
                Tk.Button(
                    self.frame,
                    text = col,
                    command=(lambda total = total:(self.showPlot(total)))
                ).grid(row=i, column=offset, padx=5, pady=5, sticky="NESW")
                last = col[0]
            total += 1
            i += 1

    def showPlot(self, choice_show):
        plt.close()
        # figure = plt.Figure()
        # ax[choice_show] = plt.gca()
        print(choice_show)
        print(self.Dict.get(choice_show))
        # (self.data).plot(kind = 'line', x = 't', y = ((self.Dict).get(choice_show)), ax = ax[choice_show])
        (self.data).plot(kind = 'line', x = 't', y = ((self.Dict).get(choice_show)))
        plt.grid()
        plt.show()
