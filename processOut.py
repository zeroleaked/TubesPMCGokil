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


class addComponentClass(Tk.Toplevel):
    def __init__(self, original):
        inputFile = "infile.txt"
        self.original_frame = original
        self.data = original.data
        self.Dict = original.Dict
        self.Row = 0
        Tk.Toplevel.__init__(self)
        self.geometry("800x600")
        self.title("addComponentClass")        
        self.file = open(inputFile,"w+")

        btnres =Tk.Button(self, text="Add Resistance", command=self.addResistance)
        btnres.grid(row = self.getRow()) 

        btncap =Tk.Button(self, text="Add Capacitance", command=self.addCapacitance)
        btncap.grid(row = self.getRow())

        btnind =Tk.Button(self, text="Add Inductance", command=self.addInductance)
        btnind.grid(row = self.getRow())                           

        btnvolt =Tk.Button(self, text="Add Voltage Source", command=self.addVoltageSource)
        btnvolt.grid(row = self.getRow())                                   

        btncurr =Tk.Button(self, text="Add Current Source", command=self.addCurrentSource)
        btncurr.grid(row = self.getRow())         

        btngrou =Tk.Button(self, text="Add Ground", command=self.addGround)
        btngrou.grid(row = self.getRow())                         
       
        btn = Tk.Button(self, text="Close", command=self.onClose)
        btn.grid(row = self.getRow())          

    def hide(self):
        self.withdraw()
    def show(self):
        """"""
        self.update()
        self.deiconify()    

    def onClose(self):
        self.destroy()
        self.original_frame.show()

    def getRow(self):
        self.Row += 1
        return (self.Row - 1)

    #Add resistance Component
    def addResistance(self):
        self.hide()
        otherFrame = addFrame(self, "addResistance")
        resValueEntry = Tk.Entry(otherFrame)
        
        resNode1Entry = Tk.Entry(otherFrame)
        
        resNode2Entry = Tk.Entry(otherFrame)

        rowStart = otherFrame.getRow()
        resValueLabel=Tk.Label(otherFrame,text = "Nilai resistor:")        
        resNode1Label=Tk.Label(otherFrame,text = "Nilai Node 1:")
        resNode2Label=Tk.Label(otherFrame,text = "Nilai Node 2:")

        resValueLabel.grid(row=rowStart, column = 1)
        resNode1Label.grid(row=rowStart+1, column = 1)        
        resNode2Label.grid(row=rowStart+2, column = 1)

        resNode1Entry.grid(row=rowStart+1, column = 2)        
        resValueEntry.grid(row=rowStart, column = 2)
        resNode2Entry.grid(row=rowStart+2, column = 2)    

        submit = Tk.Button(otherFrame, text = "Submit")
        cancel = Tk.Button(otherFrame, text = "Cancel")
        submit['command'] =lambda binst =submit, binst2 = cancel:self.putResistance(1,resValueEntry,
                resNode1Entry,resNode2Entry, resValueLabel, resNode1Label, resNode2Label, binst, binst2, otherFrame)
        cancel['command'] = lambda binst = cancel,  binst2 = submit:self.putResistance(0,resValueEntry,
                resNode1Entry,resNode2Entry, resValueLabel, resNode1Label, resNode2Label, binst, binst2, otherFrame)
        cancel.grid(row = rowStart+4, column = 4)
        submit.grid(row = rowStart+4, column = 5)

    def putResistance(self, state ,resValueEntry, resNode1Entry, resNode2Entry, resValueLabel, resNode1Label, resNode2Label,binst, binst2, otherFrame):
        if state == 1:
            self.file.write("R")
            self.file.write("\n")
            self.file.write(str(resValueEntry.get()))
            self.file.write("\n")       
            self.file.write(str(resNode1Entry.get()))
            self.file.write("\n")       
            self.file.write(str(resNode2Entry.get()))
            self.file.write("\n")
   
        otherFrame.onClose()
        

    #Add Capacitor Component
    def addCapacitance(self):
        self.hide()
        otherFrame = addFrame(self, "addResistance")
        capValueEntry = Tk.Entry(otherFrame)
        
        capNode1Entry = Tk.Entry(otherFrame)
        
        capNode2Entry = Tk.Entry(otherFrame)

        rowStart = otherFrame.getRow()
        capValueLabel=Tk.Label(otherFrame,text = "Nilai capacitor:")        
        capNode1Label=Tk.Label(otherFrame,text = "Nilai Node 1:")
        capNode2Label=Tk.Label(otherFrame,text = "Nilai Node 2:")

        capValueLabel.grid(row=rowStart, column = 1)
        capNode1Label.grid(row=rowStart+1, column = 1)        
        capNode2Label.grid(row=rowStart+2, column = 1)

        capNode1Entry.grid(row=rowStart+1, column = 2)        
        capValueEntry.grid(row=rowStart, column = 2)
        capNode2Entry.grid(row=rowStart+2, column = 2)    

        submit = Tk.Button(otherFrame, text = "Submit")
        cancel = Tk.Button(otherFrame, text = "Cancel")
        submit['command'] =lambda binst =submit, binst2 = cancel:self.putCapacitance(1,capValueEntry,
                capNode1Entry,capNode2Entry, capValueLabel, capNode1Label, capNode2Label, binst, binst2, otherFrame)
        cancel['command'] = lambda binst = cancel,  binst2 = submit:self.putCapacitance(0,capValueEntry,
                capNode1Entry,capNode2Entry, capValueLabel, capNode1Label, capNode2Label, binst, binst2, otherFrame)
        cancel.grid(row = rowStart+4, column = 4)
        submit.grid(row = rowStart+4, column = 5)

    def putCapacitance(self, state ,capValueEntry, capNode1Entry, capNode2Entry, capValueLabel, capNode1Label, capNode2Label,binst, binst2, otherFrame):
        if state == 1:
            self.file.write("C")
            self.file.write("\n")
            self.file.write(str(capValueEntry.get()))
            self.file.write("\n")       
            self.file.write(str(capNode1Entry.get()))
            self.file.write("\n")       
            self.file.write(str(capNode2Entry.get()))
            self.file.write("\n")

        capValueEntry.destroy()
        capNode1Entry.destroy()     
        capNode2Entry.destroy()  
        capValueLabel.destroy()
        capNode1Label.destroy()     
        capNode2Label.destroy()          

        binst.destroy()   
        binst2.destroy() 
        otherFrame.onClose()

    def addInductance(self):
        self.hide()
        otherFrame = addFrame(self, "addResistance")
        indValueEntry = Tk.Entry(otherFrame)
        
        indNode1Entry = Tk.Entry(otherFrame)
        
        indNode2Entry = Tk.Entry(otherFrame)

        rowStart = otherFrame.getRow()
        indValueLabel=Tk.Label(otherFrame,text = "Nilai induktor:")        
        indNode1Label=Tk.Label(otherFrame,text = "Nilai Node 1:")
        indNode2Label=Tk.Label(otherFrame,text = "Nilai Node 2:")

        indValueLabel.grid(row=rowStart, column = 1)
        indNode1Label.grid(row=rowStart+1, column = 1)        
        indNode2Label.grid(row=rowStart+2, column = 1)

        indNode1Entry.grid(row=rowStart+1, column = 2)        
        indValueEntry.grid(row=rowStart, column = 2)
        indNode2Entry.grid(row=rowStart+2, column = 2)    

        submit = Tk.Button(otherFrame, text = "Submit")
        cancel = Tk.Button(otherFrame, text = "Cancel")
        submit['command'] =lambda binst =submit, binst2 = cancel:self.putInductance(1,indValueEntry,
                indNode1Entry,indNode2Entry, indValueLabel, indNode1Label, indNode2Label, binst, binst2, otherFrame)
        cancel['command'] = lambda binst = cancel,  binst2 = submit:self.putInductance(0,indValueEntry,
                indNode1Entry,indNode2Entry, indValueLabel, indNode1Label, indNode2Label, binst, binst2, otherFrame)
        cancel.grid(row = rowStart+4, column = 4)
        submit.grid(row = rowStart+4, column = 5)


    def putInductance(self, state ,indValueEntry, indNode1Entry, indNode2Entry, indValueLabel, indNode1Label, indNode2Label,binst, binst2, otherFrame):
        if state == 1:
            self.file.write("L")
            self.file.write("\n")
            self.file.write(str(indValueEntry.get()))
            self.file.write("\n")       
            self.file.write(str(indNode1Entry.get()))
            self.file.write("\n")       
            self.file.write(str(indNode2Entry.get()))
            self.file.write("\n")

        indValueEntry.destroy()
        indNode1Entry.destroy()     
        indNode2Entry.destroy()  
        indValueLabel.destroy()
        indNode1Label.destroy()     
        indNode2Label.destroy()          

        binst.destroy()   
        binst2.destroy()  
        otherFrame.onClose()

    def addVoltageSource(self):
        self.hide()
        otherFrame = addFrame(self, "Add VOltage Source")
        voltValueEntry = Tk.Entry(otherFrame)
        
        voltNode1Entry = Tk.Entry(otherFrame)
        
        voltNode2Entry = Tk.Entry(otherFrame)

        rowStart = otherFrame.getRow()
        voltValueLabel=Tk.Label(otherFrame,text = "Nilai Sumber Tegangan:")        
        voltNode1Label=Tk.Label(otherFrame,text = "Nilai Node 1:")
        voltNode2Label=Tk.Label(otherFrame,text = "Nilai Node 2:")

        voltValueLabel.grid(row=rowStart, column = 1)
        voltNode1Label.grid(row=rowStart+1, column = 1)        
        voltNode2Label.grid(row=rowStart+2, column = 1)

        voltNode1Entry.grid(row=rowStart+1, column = 2)        
        voltValueEntry.grid(row=rowStart, column = 2)
        voltNode2Entry.grid(row=rowStart+2, column = 2)    

        submit = Tk.Button(otherFrame, text = "Submit")
        cancel = Tk.Button(otherFrame, text = "Cancel")
        submit['command'] =lambda binst =submit, binst2 = cancel:self.putVoltageSource(1,voltValueEntry,
                voltNode1Entry,voltNode2Entry, voltValueLabel, voltNode1Label, voltNode2Label, binst, binst2, otherFrame)
        cancel['command'] = lambda binst = cancel,  binst2 = submit:self.putVoltageSource(0,voltValueEntry,
                voltNode1Entry,voltNode2Entry, voltValueLabel, voltNode1Label, voltNode2Label, binst, binst2, otherFrame)
        cancel.grid(row = rowStart+4, column = 4)
        submit.grid(row = rowStart+4, column = 5)

    def putVoltageSource(self, state ,voltValueEntry, voltNode1Entry, voltNode2Entry, voltValueLabel, voltNode1Label, voltNode2Label,binst, binst2, otherFrame):
        if state == 1:
            self.file.write("V")
            self.file.write("\n")
            self.file.write(str(voltValueEntry.get()))
            self.file.write("\n")       
            self.file.write(str(voltNode1Entry.get()))
            self.file.write("\n")       
            self.file.write(str(voltNode2Entry.get()))
            self.file.write("\n")

        otherFrame.onClose()

    def addCurrentSource(self):
        self.hide()
        otherFrame = addFrame(self, "Add Current Source")
        currValueEntry = Tk.Entry(otherFrame)
        
        currNode1Entry = Tk.Entry(otherFrame)
        
        currNode2Entry = Tk.Entry(otherFrame)

        rowStart = otherFrame.getRow()
        currValueLabel=Tk.Label(otherFrame,text = "Nilai Sumber Arus:")        
        currNode1Label=Tk.Label(otherFrame,text = "Nilai Node 1:")
        currNode2Label=Tk.Label(otherFrame,text = "Nilai Node 2:")

        currValueLabel.grid(row=rowStart, column = 1)
        currNode1Label.grid(row=rowStart+1, column = 1)        
        currNode2Label.grid(row=rowStart+2, column = 1)

        currNode1Entry.grid(row=rowStart+1, column = 2)        
        currValueEntry.grid(row=rowStart, column = 2)
        currNode2Entry.grid(row=rowStart+2, column = 2)    

        submit = Tk.Button(otherFrame, text = "Submit")
        cancel = Tk.Button(otherFrame, text = "Cancel")
        submit['command'] =lambda binst =submit, binst2 = cancel:self.putCurrentSource(1,currValueEntry,
                currNode1Entry,currNode2Entry, currValueLabel, currNode1Label, currNode2Label, binst, binst2, otherFrame)
        cancel['command'] = lambda binst = cancel,  binst2 = submit:self.putCurrentSource(0,currValueEntry,
                currNode1Entry,currNode2Entry, currValueLabel, currNode1Label, currNode2Label, binst, binst2, otherFrame)
        cancel.grid(row = rowStart+4, column = 4)
        submit.grid(row = rowStart+4, column = 5)

    def putCurrentSource(self, state ,currValueEntry, currNode1Entry, currNode2Entry, currValueLabel, currNode1Label, currNode2Label,binst, binst2, otherFrame):
        if state == 1:
            self.file.write("I")
            self.file.write("\n")
            self.file.write(str(currValueEntry.get()))
            self.file.write("\n")       
            self.file.write(str(currNode1Entry.get()))
            self.file.write("\n")       
            self.file.write(str(currNode2Entry.get()))
            self.file.write("\n")

        otherFrame.onClose()

    def addGround(self):
        self.hide()
        otherFrame = addFrame(self, "Add Ground")
        grouValueEntry = Tk.Entry(otherFrame)

        rowStart = otherFrame.getRow()
        grouValueLabel=Tk.Label(otherFrame,text = "Nilai Node Ground:")        

        grouValueLabel.grid(row=rowStart, column = 1)

        grouValueEntry.grid(row=rowStart, column = 2)

        submit = Tk.Button(otherFrame, text = "Submit")
        cancel = Tk.Button(otherFrame, text = "Cancel")
        submit['command'] =lambda binst =submit, binst2 = cancel:self.putgrouentSource(1,grouValueEntry,otherFrame)
        cancel['command'] = lambda binst = cancel,  binst2 = submit:self.putgrouentSource(0,grouValueEntry otherFrame)
        cancel.grid(row = rowStart+4, column = 4)
        submit.grid(row = rowStart+4, column = 5)

    def putGround(self, state ,grouValueEntry, otherFrame):
        if state == 1:
            self.file.write("G")
            self.file.write("\n")
            self.file.write(str(grouValueEntry.get()))
            self.file.write("\n")

        otherFrame.onClose()

    
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