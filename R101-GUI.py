import tkinter
from tkinter import *
import customtkinter
import serial
import threading

# Define the serial port and baud rate.
# Ensure the 'COM#' corresponds to what was seen in the Windows Device Manager
ser = serial.Serial('COM5', 9600)
customtkinter.set_appearance_mode("dark")  # Modes: system (default), light, dark
customtkinter.set_default_color_theme("green")  # Themes: blue (default), dark-blue, green

app = customtkinter.CTk()
app.geometry("1000x700")
app.title("Robotics 101 GUI")

targetStr = StringVar()
targetStr.set("Current Target: ")
def up():
    print("Up Pressed")
    ser.write(b'u')
def down():
    print("Down Pressed")
    ser.write(b'd')
button_up = customtkinter.CTkButton(master=app,
                                 width=120,
                                 height=32,
                                 border_width=0,
                                 corner_radius=8,
                                 text="Up Button",
                                 command = up)
button_up.place(relx=0.5, rely=0.25, anchor=tkinter.CENTER)
button_down = customtkinter.CTkButton(master=app,
                                 width=120,
                                 height=32,
                                 border_width=0,
                                 corner_radius=8,
                                 text="Down Button",
                                 command=down)
button_down.place(relx=0.5, rely=0.5, anchor=tkinter.CENTER)
targetLab = Label(app, textvariable=targetStr, background='#333333', fg="white")
targetLab.grid(column=0, row=1, sticky="we", padx=5, pady=5)

def arduino_handler():
    data = ser.readline().decode('utf-8').strip()
    targetStr.set("Current Progress: " + str(data))
    print(data)
    
threading.Thread(target=arduino_handler, daemon=True).start()
app.mainloop()