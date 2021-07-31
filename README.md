# Assignment 4

## Title: CP386 Assignment 4 
## `Banker's Algorithm`

***********************************
 ***Authors:***
  - **Fatima Omar** 
      - **Student ID#:** 191815080 
      - **Github Username:** FatimaOmarZ
  - **Mohammad Al Zouabi**
      - **Student ID#:** 190977620
      - **Github Username:** M-Alzouabi
***********************************
***Motivation:***
  - This code was developed and created as part of a course assignment.

***Installation:***
  - This code includes a makefile which is used to compile and test the code.
  - The makefile is made up of multiple commands:
      - CC = gcc
      - CFLAGS = -Wall -g -std=gnu99
      - LDFLAGS = -lrt -lpthread
      - TARGET = Question1  
      - OBJFILES = Question1.o 
      - runq1: the command that compile the the file Question1.c and run it


***ScreenShots:***

![image](https://user-images.githubusercontent.com/87793706/127729563-f3ad3f18-8f2b-4494-94cf-ded3e6845084.png)
![image](https://user-images.githubusercontent.com/87793706/127729584-bee5cfbd-54f6-407e-ab41-a978db5d6448.png)
![image](https://user-images.githubusercontent.com/87793706/127729601-0df28d6c-0a9b-44d7-96aa-484bc4db8856.png)
![image](https://user-images.githubusercontent.com/87793706/127729626-21fdf5e6-3146-4ffe-bcbd-e1f2552db205.png)
![image](https://user-images.githubusercontent.com/87793706/127729635-046b740c-f227-4f03-9746-7bbc1d409b26.png)

***Individual Contribution:***
  - Most functions were done as a group, the rest that were done indiviually are listed below.
  - **Mohammad AL Zouabi**
     - Release Resources
     - Print Current Status
  - **Fatima Omar**
     - Request Resources
     - Safety Algorithm
     - User input and file handling

***Features:***
- User can enter commands multiple commands such as:
      -<RQ [int customer_number] [int Resource 1] [int Resource 2] [int Resource 3] [int Resource 4]> which is used for requesting resource. If the request leaves the system unsafe it will be denied. If the system state is safe, the resources would be allocated and a message “State is safe, and request is satisfied” would be printed.
      -<RL [int customer_number] [int Resource 1] [int Resource 2] [int Resource 3] [int Resource 4]> which will release the resources and data structures would be updated accordingly. It would print “The resources have been released successfully”.
      -<Status>: ‘Status’ command prints all arrays and matrices used (available, maximum, allocation, and remaining need)
      -<Run>: ‘Run’ command prints the safe sequence first and then executes customers as threads in a safe sequence. Each thread requests the resources it needs, releases them, and lets the next thread in the sequence run.
      -<Exit>: The ‘Exit’ command is used to exit the loop and the program.

***Credits:***
  - Code from assignments two and three were refered to in the process of completing this assignment.
     - Assignment two was used to help with file handling.
     - Assignment three was used to help with mutex and thread manupilation  
  - Operating System Concepts - 10th Edition. [TextBook Link](https://codex.cs.yale.edu/avi/os-book/OS10/index.html)
     - Textbook and lecture slides were referred in order to better understand different concepts and alogrithms used in this code such as; Requesting Resource  and Safety Algorithm.

***License:***

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
