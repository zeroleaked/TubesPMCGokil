import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import Tkinter as Tk
# https://www.blog.pythonlibrary.org/2012/07/26/tkinter-how-to-show-hide-a-window/

class OtherFrame(Tk.Toplevel):
    """"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        Tk.Toplevel.__init__(self)
        self.geometry("400x300")
        self.title("otherFrame")
    
class MyApp(object):
    
    def __init__(self, parent, fileName):
        self.root = parent
        self.root.title("Main Menu")
        self.frame = Tk.Frame(parent)
        self.frame.pack()        

        self.data = pd.read_csv(fileName)
        self.Dict = {}        
        
                
        btn = Tk.Button(self.frame, text="Show Plot", command=self.openFrame)
        btn.pack()
        
    def hide(self):
        self.root.withdraw()
        
    def openFrame(self):
        self.hide()
        subFrame = OtherFrame()
        handler = lambda: self.onCloseOtherFrame(subFrame)
        self.showPlotMenu(subFrame)
        btn = Tk.Button(subFrame, text="Close", command=handler)
        btn.pack()
        
    def onCloseOtherFrame(self, otherFrame):
        otherFrame.destroy()
        self.show()
        
    def show(self):
        """"""
        self.root.update()
        self.root.deiconify()


    #plotting menu
    def showPlotMenu(self, sub_frame):
        
        total = 0
        for col in (self.data).columns:
            self.Dict[total] = col
            if (total != 0):
                Tk.Button(sub_frame,text = col,command=(lambda total = total:(self.showPlot(total)))).pack()
            
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

    #insert component
        
    
#----------------------------------------------------------------------
if __name__ == "__main__":
    root = Tk.Tk()
    root.geometry("800x600")
    app = MyApp(root, "outfile.csv")
    root.mainloop()