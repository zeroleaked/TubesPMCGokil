import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
try :
    import Tkinter as Tk
except ImportError :
    import tkinter as Tk
# https://www.blog.pythonlibrary.org/2012/07/26/tkinter-how-to-show-hide-a-window/

class showPlotClass(Tk.Toplevel):
    def __init__(self, original):
        """Constructor"""
        self.original_frame = original
        self.data = original.data
        self.Dict = original.Dict
        Tk.Toplevel.__init__(self)
        self.geometry("400x300")
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

class addComponentClass(Tk.Toplevel):
    def __init__(self, original):
        inputFile = "infile.txt"
        self.original_frame = original
        self.data = original.data
        self.Dict = original.Dict
        Tk.Toplevel.__init__(self)
        self.geometry("400x300")
        self.title("addComponentClass")        
        self.file = open(inputFile,"w+")

        btnres =Tk.Button(self, text="Add Resistance", command=self.addResistance)
        btnres.grid(row = 0) 

        btncap =Tk.Button(self, text="Add Capacitance", command=self.addCapacitance)
        btncap.grid(row = 1)                   
       
        btn = Tk.Button(self, text="Close", command=self.onClose)
        btn.grid(row = 2)          

    def onClose(self):
    	self.destroy()
        self.original_frame.show()

    #Add resistance Component
    def addResistance(self):
    	resValueEntry = Tk.Entry(self)
    	
        resNode1Entry = Tk.Entry(self)
    	
        resNode2Entry = Tk.Entry(self)

        rowStart = 3
        resValueLabel=Tk.Label(self,text = "Nilai resistor:").grid(row=rowStart, column = 1)
        resValueEntry.grid(row=rowStart, column = 2)
        resNode1Label=Tk.Label(self,text = "Nilai Node 1:").grid(row=rowStart+1, column = 1)
        resNode1Entry.grid(row=rowStart+1, column = 2)        
        resNode2Label=Tk.Label(self,text = "Nilai Node 2:").grid(row=rowStart+2, column = 1)
    	resNode2Entry.grid(row=rowStart+2, column = 2)    

    	submit = Tk.Button(self, text = "Submit")
    	cancel = Tk.Button(self, text = "Cancel")
    	submit['command'] =lambda binst =submit, binst2 = cancel:self.putResistance(1,resValueEntry,
    			resNode1Entry,resNode2Entry, binst, binst2)
    	cancel['command'] = lambda binst = cancel,  binst2 = submit:self.putResistance(0,resValueEntry,
    			resNode1Entry,resNode2Entry, binst, binst2)
    	cancel.pack(side = Tk.RIGHT, padx = 10, pady = 10)
    	submit.pack(side = Tk.RIGHT)

    def putResistance(self, state ,resValueEntry, resNode1Entry, resNode2Entry,binst, binst2):
    	if state == 1:
	    	self.file.write("R")
	    	self.file.write("\n")
	    	self.file.write(str(resValueEntry.get()))
	    	self.file.write("\n")    	
	    	self.file.write(str(resNode1Entry.get()))
	    	self.file.write("\n")    	
	    	self.file.write(str(resNode2Entry.get()))
	    	self.file.write("\n")

    	resValueEntry.destroy()
    	resNode1Entry.destroy()    	
    	resNode2Entry.destroy()    	
    	binst.destroy()   
    	binst2.destroy() 	
    	

    #Add Capacitor Component
    def addCapacitance(self):
    	capValueEntry = Tk.Entry(self)
    	capValueEntry.pack()
        capNode1Entry = Tk.Entry(self)
    	capNode1Entry.pack()    	
        capNode2Entry = Tk.Entry(self)
    	capNode2Entry.pack()    

    	submit = Tk.Button(self, text = "Submit")
    	submit.pack()
    	submit['command']=	lambda binst = submit :self.putCapacitance(capValueEntry,
    			capNode1Entry,capNode2Entry,binst)

    def putCapacitance(self, capValueEntry, capNode1Entry, capNode2Entry,binst):
    	self.file.write("C")
    	self.file.write("\n")
    	self.file.write(str(capValueEntry.get()))
    	self.file.write("\n")
    	capValueEntry.destroy()
    	self.file.write(str(capNode1Entry.get()))
    	self.file.write("\n")
    	capNode1Entry.destroy()    	
    	self.file.write(str(capNode2Entry.get()))
    	self.file.write("\n")
    	capNode2Entry.destroy()    	
    	binst.destroy()



    
class MyApp(object):
    
    def __init__(self, parent, fileName):
        self.root = parent
        self.root.title("Main Menu")
        self.frame = Tk.Frame(parent)
        self.frame.pack()        

        self.data = pd.read_csv(fileName)
        self.Dict = {}        
        
                
        btnShowPlot = Tk.Button(self.frame, text="Show Plot", command=self.showPlotInMenu)
        btnShowPlot.pack()
        btnAddComponent = Tk.Button(self.frame, text="Add Component", command=self.insertComponentInMenu)
        btnAddComponent.pack()

        # btnExit = Tk.Button(self.frame, text = "Exit", command = self.)
        
    def hide(self):
        self.root.withdraw()        
        
    def onCloseOtherFrame(self, otherFrame):
        otherFrame.destroy()
        self.show()
        
    def show(self):
        """"""
        self.root.update()
        self.root.deiconify()
    #showplot
    def showPlotInMenu(self):
        self.hide()
        subFrame = showPlotClass(self)   

    # insert component
    def insertComponentInMenu(self)   :
    	self.hide()
        subFrame = addComponentClass(self)


    # def insertResistor(self):


     
    
#----------------------------------------------------------------------
if __name__ == "__main__":
    root = Tk.Tk()
    root.geometry("800x600")
    app = MyApp(root, "outfile.csv")
    root.mainloop()