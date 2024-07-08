# STM_Praktikum Sensor D6T-32L-01A
/// overview

## Getting started
The components used for this project are:
* A D6T-32L-01A IR Sensor that was connected to 
* A STM32F412G-Discovery board using  
* A Qwiic to 4-male jumper pin cable.
THough not required for the use of this application, the Data-sheets for the sensor and the controler can be found at [Datasheet D6T]() and [Datasheet STM32]() respectively.

### Wireing
On the side of the sensor apart from pushing the cable in the box below the board untill a click can be heared no wireing is needed. 
At the evaluation board the external I2C port can be found as a black box with eight square holes on the far right edge of the board next to the micro usb connector that is used to connect the board to the computer or power source. To see which cable from the sensor matches wich which pin on the sensor follow the graphic below:
![Pin connection between sensor and Controller](file:./images/hardware_pinout)

### Loading the software to the evaluation board
For this project, I used the under the XY License published free to use software STMCubeIDE. Within this software you can write the software of an opened project onto a evaluation board that is connected with usb by pressing the play button on the top middle of the Screen. At the first time the IDE will ask you about saving before running which you can accept. THe software will be written to to your board and executed immediatly. 

### Resetting the software
1. Restart Sensor by pulling ground cable and repluging it in
2. Press reset button (img)


## Software Architecture and Design decisions
The presentated software to read the sensor data has been moved to a Folder called `/Core/.../sensor/` to enable the construction of different logically seperated components. This folder has an access point for the main method called `d6t.h` in which the main streamline of the constructed methods were executed. These method have been seperated into two files:
1. `.../sensor/communication.h/c` in the communication files the methods focus on getting the raw data from the sensor and interpret it in a way that it fits to a for Humans readable value in °C. Even thoug the task requests iso units, I chose not to comply as the stepsize between Kelvin and Celsius are identical and a calculation to Kelvin would only take more space on the small Display as the numbers are 272.15 bigger that Celsius's system. I decided the conversion is easy enough that it is not worth the extra space.
2. `.../sensor/render.h/c` contains the code used to visualize the data we got from the sensor on the evaluation board screen. ... /// how and why like this



## Authors
Yannick Pahlke 1841500 (@Reskuzo on Github)
# Todo
* Watchdog timer
* Interrupts to fasten up
* option to switch between sensor models (not able to test though)
* Regelung/Glättung der Daten
  