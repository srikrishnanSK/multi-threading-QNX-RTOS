@author Srikrishnan Venkatasubramanian
## Muti-threading with REALTIME OPERATING SYSTEMS (RTOS)
Before deep diving into the installation procedure and usage of the above source code understanding the below terminologies are very important.

#### General Purpose Operating system
A general purpose computer that can be used to solve multiple problem required by the user. Solution to the problem is provided in the form of service and a problem
can have multiple soultions in the form of services.

#### Embedded System
A microcomputer part of a larger system that has been designed to solve a specific problem by providing one or two dedicated service.

#### Realtime Operating System (RTOS)
As the name specifies it is an operating system that is used for time-intended applications that is required to process data and perform some actions without any delays.

#### Soft deadlines
A deadline if not met would not lead to catastrophic consquences. A general purpose computer is a great example for such deadlines.

#### Hard deadlines
A deadline if not met would lead to catastrophic consquences. An embedded system is a great example for such deadlines.

### Description
Majority of the world is full of electronic devices that are used to perform a specific task **(embedded system)**. If we take a car, it will have an embedded system 
with sensors that are used to monitor various parameters such as brake, vehicle speed, inner temperature, oil temperature etc. The processing and reporting of such 
data without any delays is higly essential when it comes to such systems. Thus usage of RTOS for this purpose is very important. This project has been developed 
to gather data from multiple sensors of an embedded system , process it and display them to the user in Realtime using muti-threaded processing. Since we dont
have the actual sensor, the provided datset is to be used to emulate the process. Based on the given requirements the following have been achieved:-
* A thread to read data from the provided dataset every 1 second.
* 8 threads for each parameter updating the defined structure at their respective defined intervals.
* Use main thread to display the parameters to the console every 500ms.

Posix threads and timers have been used for this purpose and the program has been developed in C++.

### Installation
1. The project has been implemented on QNX RTOS. In order to launch the project and test the application in RTOS create a QNX account, request for a license or choose
the 30-day trial.
2. Download the QNX software center and install Momentix IDE followed by the same version QNX SDP on your system.
3. After the installtion, open momentix IDE and click on symbol i on the top right corner of the screen (should open the target perspective).
4. On the left hand pane right click and choose create new virutal machine.
5. Give a name and choose the software for the virtual machine to be created with (Vmware,Vbox,qemu).
6. Once the virtual machine has been spun the target should be succesfully connected through Momentix IDE.

### Running the project
1. Extract the source files in your workspace and open them in Momentix IDE.
2. Build the project.
3. click on symbol i on the top right corner of the screen (should open the target perspective).
4. Click on the target and open the Target file system navigator. 
5. Copy paste the dataset.csv file in the tmp directory **(Will not allow you to put files anywhere else)**.
6. Run the project on the target.


