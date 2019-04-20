# ag-mech-clemson

This is the code repository for the Mechatronic Agriculture CI at Clemson University. It contains the main code run on the Arduino for controlling the system along with a couple other utilities.


brain - Contains the main code for the system

endstop_print - Contains Arduino code to print out the state of each enstop to make sure that they are plugged into the correct pin (make sure that pins.h is up to date) (this is actually also a mode inside of brain)

power - Contains a simple program for toggling the Pi pin that turns the PSU on and off

testing - Contains a generic Arduino folder for general testing



---------- MAIN CODE DOCUMENTATION ----------
The code is designed to be as modular as possible, and the main focus has been on creating utilities that can be used by later semesters to accomplish higher-level tasks. There is a single ".ino" file (brain.ino) that the Arduino automatically runs, and that file uses all of the other ".cpp" files. There are a couple ".h" files for general #defines (pins.h, globals.h, etc.), but most of the files have one ".cpp" file and one ".h" file with function prototypes and other info.

While testing different code, I found myself wanted to run in a few different "modes". For instance, sometimes I wanted to be able to control the robot using the push-button controller, and sometimes I wanted to have the robot try to water all of the plants. I accomplished this by making the brain.ino basically just setup code and then a switch statement between the different modes. The mode that it runs is controlled by a "#define" at the top of the brain.ino code.

< MAIN CODE >
brain.ino: Root Arduino file. Includes all of the other files. Switches between "modes"

definitions.h: Header file for general definitions. Can be used by all files.

pins.h: Defines all pins on the Arduino. Can be used by all files.

gloabls.h: Defines global variables (mainly tracking position). Can be used by all files

<MODULES>
init(.h/.cpp): Runs initialization code to set pin modes and to calibrate the number of steps using the endstops (make sure that it won't hit anything at max x and max y when it goes down to calibrate min z)

move(.h/.cpp): Contains the lower level code for moving each motor, going to a certain (x,y,z), turning on the vacuum and water pump, and a few other things.

box_logic(.h/.cpp): Contains the logic for going to a certain cell in a box. Takes box origin, size, and number of cells, then allows you to navigate using cell numbers instead of (x,y,z). Should be expanded to store more information and have more functions. This should probably be moved to the Pi

loss_test(.h/.cpp): code that bounces the machine back and forth between endstops and prints its count each time. can be used to count how many steps have been dropped, but it hasn't been used in a while, so it should be updated to be a mode

<MODES>
print_endstops(.h/.cpp): simple arduino code to print out the value of each endstop to ensure pins.h is correct

print_pos(.h/.cpp): code that takes the input from the push-button controller to move the robot and control the pumps. This can be run after the initialization to give (x,y,z) values for each point for getting coordinates, or can be run without initialization for simple mechanical debugging

box_logic_test(.h/.cpp): code to test out the box_logic object and make sure it works

normal_run(.h/.cpp): currently unimplemented, but this will be the code that we run on startup to monitor plants and whatnot