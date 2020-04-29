import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
try :
    import subprocess
except:
    print("install subprocess")
    exit(0)

try :
    import subprocess
except:
    print("install subprocess")
    exit(0)
try :
    import Tkinter as Tk
    from Tkinter import ttk
except ImportError :
    import tkinter as Tk
    from tkinter import ttk

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

    
class showComponentClass(Tk.Toplevel):
    def __init__(self, original):
        self.original_frame = original
        Tk.Toplevel.__init__(self)
        self.Row = 0
        canvas = Tk.Canvas(self)
        scroll_y = Tk.Scrollbar(self, orient = "vertical", command = canvas.yview)

        frame = Tk.Frame(canvas)
        
        self.geometry("800x200")
        self.title("addComponentClass")        
        self.file = open(original.inputFile, "r")

        self.r_list = []
        self.l_list = []
        self.c_list = []
        self.v_list = []
        self.i_list = []
        self.w_list = []
        self.j_list = []

        self.readInputFile()
        Tk.Label(frame, text = "Daftar R").grid(row = self.getRow())
        row_now = self.getRow()
        Tk.Label(frame, text = "Nilai (Ohm)").grid(row = row_now, column = 0)
        Tk.Label(frame, text = "Node 1").grid(row = row_now, column = 1)
        Tk.Label(frame, text = "Node 2").grid(row = row_now, column = 2)
        for i in range (len(self.r_list)):
            row_now = self.getRow()
            for j in range (3):
                Tk.Label(frame, text = str(self.r_list[i][j])).grid(row = row_now, column = j)

        Tk.Label(frame, text = "Daftar L").grid(row = self.getRow())
        row_now = self.getRow()
        Tk.Label(frame, text = "Nilai (H)").grid(row = row_now, column = 0)
        Tk.Label(frame, text = "Node 1").grid(row = row_now, column = 1)
        Tk.Label(frame, text = "Node 2").grid(row = row_now, column = 2)
        Tk.Label(frame, text = "Nilai arus awal").grid(row = row_now, column = 3)
        for i in range (len(self.l_list)):
            row_now = self.getRow()
            for j in range (4):
                Tk.Label(frame, text = str(self.l_list[i][j])).grid(row = row_now, column = j)

        Tk.Label(frame, text = "Daftar C").grid(row = self.getRow())
        row_now = self.getRow()
        Tk.Label(frame, text = "Nilai (Farad)").grid(row = row_now, column = 0)
        Tk.Label(frame, text = "Node 1").grid(row = row_now, column = 1)
        Tk.Label(frame, text = "Node 2").grid(row = row_now, column = 2)
        Tk.Label(frame, text = "Nilai tegangan awal").grid(row = row_now, column = 3)
        for i in range (len(self.c_list)):
            row_now = self.getRow()
            for j in range (4):
                Tk.Label(frame, text = str(self.c_list[i][j])).grid(row = row_now, column = j)
        
        Tk.Label(frame, text = "Daftar Sumber Tegangan").grid(row = self.getRow())
        row_now = self.getRow()
        Tk.Label(frame, text = "Nilai (Volt)").grid(row = row_now, column = 0)
        Tk.Label(frame, text = "Node 1").grid(row = row_now, column = 1)
        Tk.Label(frame, text = "Node 2").grid(row = row_now, column = 2)
        for i in range (len(self.v_list)):
            row_now = self.getRow()
            for j in range (3):
                Tk.Label(frame, text = str(self.v_list[i][j])).grid(row = row_now, column = j)

        Tk.Label(frame, text = "Daftar Sumber Arus").grid(row = self.getRow())
        row_now = self.getRow()
        Tk.Label(frame, text = "Nilai (Ampere)").grid(row = row_now, column = 0)
        Tk.Label(frame, text = "Node 1").grid(row = row_now, column = 1)
        Tk.Label(frame, text = "Node 2").grid(row = row_now, column = 2)
        for i in range (len(self.i_list)):
            row_now = self.getRow()
            for j in range (3):
                Tk.Label(frame, text = str(self.i_list[i][j])).grid(row = row_now, column = j)

        Tk.Label(frame, text = "Daftar Sumber Tegangan AC").grid(row = self.getRow())
        row_now = self.getRow()
        Tk.Label(frame, text = "Amplitude (Volt)").grid(row = row_now, column = 0)
        Tk.Label(frame, text = "Node 1").grid(row = row_now, column = 1)
        Tk.Label(frame, text = "Node 2").grid(row = row_now, column = 2)
        Tk.Label(frame, text = "Type").grid(row = row_now, column = 3)
        Tk.Label(frame, text = "Freq (Hz)").grid(row = row_now, column = 4)
        Tk.Label(frame, text = "Time Shift(s)").grid(row = row_now, column = 5)
        for i in range (len(self.w_list)):
            row_now = self.getRow()
            for j in range (6):
                if (j == 3):
                    if int(self.w_list[i][3]) == 0:
                        Tk.Label(frame, text = "Sinus").grid(row = row_now, column = j)
                    else:
                        Tk.Label(frame, text = "Kotak").grid(row = row_now, column = j)
                    continue
                Tk.Label(frame, text = str(self.w_list[i][j])).grid(row = row_now, column = j)

        Tk.Label(frame, text = "Daftar Sumber Arus AC").grid(row = self.getRow())
        row_now = self.getRow()
        Tk.Label(frame, text = "Amplitude (Ampere)").grid(row = row_now, column = 0)
        Tk.Label(frame, text = "Node 1").grid(row = row_now, column = 1)
        Tk.Label(frame, text = "Node 2").grid(row = row_now, column = 2)
        Tk.Label(frame, text = "Type").grid(row = row_now, column = 3)
        Tk.Label(frame, text = "Freq (Hz)").grid(row = row_now, column = 4)
        Tk.Label(frame, text = "Time Shift(s)").grid(row = row_now, column = 5)
        for i in range (len(self.j_list)):
            row_now = self.getRow()
            for j in range (6):
                if (j == 3):
                    if int(self.j_list[i][3]) == 0:
                        Tk.Label(frame, text = "Sinus").grid(row = row_now, column = j)
                    else:
                        Tk.Label(frame, text = "Kotak").grid(row = row_now, column = j)
                    continue
                Tk.Label(frame, text = str(self.j_list[i][j])).grid(row = row_now, column = j)

        print self.w_list
        print self.j_list


        btn = Tk.Button(frame, text="Close", command=self.onClose)
        btn.grid(row = self.getRow())          

        canvas.create_window(0,0,anchor='nw',window = frame)       
        canvas.update_idletasks()

        canvas.configure(scrollregion=canvas.bbox('all'),
        yscrollcommand = scroll_y.set)

        canvas.pack(fill='both', expand=True, side='left')
        scroll_y.pack(fill='y', side='right')

    def hide(self):
        self.withdraw()
    def show(self):
        """"""
        self.update()
        self.deiconify()    

    def onClose(self):
        self.file.close()
        self.destroy()
        self.original_frame.show()

    def getRow(self):
        self.Row += 1
        return (self.Row - 1)

    def readN(self,list,k, n) :
        temp_list = []
        for i in range (n):
            s = list[k+i+1]
            # print("momo = "+s)
            temp_list.append(s)
        return temp_list
        
    
    def readInputFile(self):
        list = self.file.read().splitlines()
        for k in range (len (list)):
            ch = list[k]
            
            if ch == "R":
                self.r_list.append(self.readN(list,k,3))
            elif ch == 'L':
                self.l_list.append(self.readN(list,k,4))
            elif ch == 'C':
                self.c_list.append(self.readN(list,k,4))
            elif ch == 'V':
                self.v_list.append(self.readN(list,k,3))
            elif ch == 'I':
                self.i_list.append(self.readN(list,k,3))
            elif ch == 'J':
                self.j_list.append(self.readN(list,k,6))
            elif ch == 'W':
                self.w_list.append(self.readN(list,k,6))
            elif ch == '':
                break
        
        


    

