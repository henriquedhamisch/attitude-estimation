# Roll/Pitch Angle Estimator

This project implements an estimator for roll and pitch angles using a set of data from the [MMA8451 accelerometer](https://www.nxp.com/docs/en/data-sheet/MMA8451Q.pdf).
For each sample, the roll and pitch angles are computed according to the mathematics described in the [Application Note AN3461](https://www.nxp.com/docs/en/application-note/AN3461.pdf) and recorded in an output file.

## Detailed description
This project has been developed based in the information provided by the application note AN3461 (link above), which describes the procedures to compute the roll and pitch angles of an object according to data taken from an accelerometer.
In this demonstration, the data consists in a set of samples extracted from the MMA8451 accelerometer (link above).

Regarding the software structure, it was decided to keep it in a single file because of its relative simplicity and its script-like nature.
The code can be divided in three main parts: reading the log file, estimating the angles and saving the results in the output file.

For the file manipulation (both input and output), the 'fstream' class was included to retain the file object and perform basic procedures (open, close, read, write).
The strategy used to get the data from the log file is to first extract a given line, store it in another stream object, and then extract the four elements from the line.

Concerning the estimation of the angles, the complete equations 37 and 38 (see AN3461) - which compensate for the regions of instabilty - were used because they provide a more reliable output.
The parameter 'mi' was set to 0.01, since it showed to produce an accurate result according to note AN3461 (but it can be easily changed).
Also, the 'atan2' function was used to compute the angles according to the parameters' signals.

The output file shows, for each sample, three values: the timestamp (in seconds), the roll angle (in degrees) and the pitch angle (in degrees).

## Running the software

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Cloning the repository
First of all, you need to clone the git repository into your local machine.
Please make sure you have git environment installed in your machine (see detailed information [here](https://git-scm.com/)).

To clone the repository, open the terminal, move to a desired directory and run:
```
git clone https://github.com/henriquedhamisch/attitude-estimation.git
```
This will copy the project folder to the directory you selected.

### Compiling and running the software

In order to be able to compile and run the software, you must have the GCC compiler installed in your machine.

To check if you have it installed, open the terminal and run:
```
gcc --version
```
If your machine has it, you will see an output showing the version of your gcc compiler. In this case, please proceed to "Compiling".

If you don't have it, follow the installation information below, according to your operational system.

#### Windows
* Go to [MinGW website](https://osdn.net/projects/mingw/releases/) and download the installer
* Follow the installation notes detailed [here](http://www.mingw.org/wiki/Getting_Started)

#### Linux
* Open the terminal
* Run the command ```sudo apt-get install build-essential```

After the installation is done, you are ready to compile and run the software.

#### Compiling
To compile the software, open the terminal, move to the project folder in your machine and run:

```
g++ main.cpp -o main
```
This compiles the source code and generates the executable file.

#### Running 
To run the software after compiling, simply run in the terminal (again in the project folder):

* Windows: ```main```
* Linux: ```./main```

A file called "result.log" will be created in the project folder, contaning the estimated roll and pitch angles for each input sample (as well as the timestamp).
You can open the file and see the results.
