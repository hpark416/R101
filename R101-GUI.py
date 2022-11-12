import tkinter
from tkinter import *
import customtkinter
import serial
# Define the serial port and baud rate.
# Ensure the 'COM#' corresponds to what was seen in the Windows Device Manager
ser = serial.Serial('COM5', 9600)
customtkinter.set_appearance_mode("dark")  # Modes: system (default), light, dark
customtkinter.set_default_color_theme("green")  # Themes: blue (default), dark-blue, green

app = customtkinter.CTk()
app.geometry("1000x700")
app.title("Robotics 101 GUI")

def onKeyPress(event):
    if event.char == 'w':
        up()
    if event.char == 'd':
        left()
    if event.char == 's':
        down()
    if event.char == 'a':
        right()
    if event.char == 'x':
        stop()
def up():
    print("Up Pressed")
    ser.write(b'u')
def down():
    print("Down Pressed")
    ser.write(b'd')
def right():
    print("right")
    ser.write(b'r')
def left():
    print("left")
    ser.write(b'l')
def climb():
    print("climb")
    ser.write(b'c')
def climbdown():
    print("climb-down")
    ser.write(b'x')
def stop():
    print("stopped")
    ser.write(b's')
button_up = customtkinter.CTkButton(master=app,
                                 width=120,
                                 height=32,
                                 border_width=0,
                                 corner_radius=8,
                                 text="Up Button",
                                 command = up)
button_up.place(relx=0.5, rely=0.25, anchor=tkinter.CENTER)
button_stop = customtkinter.CTkButton(master=app,
                                 width=120,
                                 height=32,
                                 border_width=0,
                                 corner_radius=8,
                                 text="Stop Button",
                                 command = stop)
button_stop.place(relx=0.1, rely=0.1, anchor=tkinter.CENTER)
button_down = customtkinter.CTkButton(master=app,
                                 width=120,
                                 height=32,
                                 border_width=0,
                                 corner_radius=8,
                                 text="Down Button",
                                 command=down)
button_down.place(relx=0.5, rely=0.7, anchor=tkinter.CENTER)
button_right = customtkinter.CTkButton(master=app,
                                 width=120,
                                 height=32,
                                 border_width=0,
                                 corner_radius=8,
                                 text="Right Button",
                                 command = right)
button_right.place(relx=0.75, rely=0.5, anchor=tkinter.CENTER)
button_left = customtkinter.CTkButton(master=app,
                                 width=120,
                                 height=32,
                                 border_width=0,
                                 corner_radius=8,
                                 text="Left Button",
                                 command = left)
button_left.place(relx=0.25, rely=0.5, anchor=tkinter.CENTER)
button_climb = customtkinter.CTkButton(master=app,
                                 width=120,
                                 height=32,
                                 border_width=0,
                                 corner_radius=8,
                                 text="Climb Up Button",
                                 command = climb)
button_climb.place(relx=0.5, rely=0.45, anchor=tkinter.CENTER)
button_climbdown = customtkinter.CTkButton(master=app,
                                 width=120,
                                 height=32,
                                 border_width=0,
                                 corner_radius=8,
                                 text="Climb Down Button",
                                 command = climbdown)
button_climbdown.place(relx=0.5, rely=0.55, anchor=tkinter.CENTER)
# def keyboard_movement():
#     if keyboard.read_key() == "w":
#         up()
#     if keyboard.read_key() == 'd':
#         left()
#     if keyboard.read_key() == 's':
#         down()
#     if keyboard.read_key() == 'a':
#         right()
#     if keyboard.press('space'):
#         stop()
    
app.bind('<KeyPress>', onKeyPress)
app.mainloop()