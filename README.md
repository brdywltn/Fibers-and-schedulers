# Advanced Systems Programming - Assignment

## Table of Contents

1. [Introduction](#introduction)
2. [Task 1 - Part One](#task-1---part-one)
3. [Task 1 - Part Two](#task-1---part-two)
4. [Task 2](#task-2)
5. [Task 2 - Extended](#task-2---final-part)


## Introduction
This project, written in c++, implements a simple runtime that supports different fibers running within a single thread along with a basic scheduler to manage their execution. 

## Task 1 - Part One
This part explores the basics and implements a program that uses the provided context library to save and restore execution state and allows control flow to transfer between different function calls. It also demonstrates correct memory alignment and layout in accordance with the System V ABI.

The code is contained within the [task one pt 1](task_one.cpp) file.

To build, run the following command whilst inside the directory containing the task_one_pt2.cpp file:

```bash
clang++ -std=c++17 -I./context -o taskone context/context.o task_one.cpp
```

and then execute with:

```bash
./taskone
```

Here is the displayed output of the compiled file:

![Task One - Part One Output](screenshots/taskoneoutput.jpg)

## Task 1 - Part Two
This task further builds upon the first task to include another function and demonstrates the creation of fibers with their own memory stacks and continues to demonstrate the correct memory alignment and layout in accordance with the System V ABI.

The code is contained within the [task one pt 2](task_one_pt2.cpp) file.

To build, run the following command whilst inside the directory containing the task_one_pt2.cpp file:

```bash
clang++ -std=c++17 -I./context -o taskonept2 context/context.o task_one_pt2.cpp
```

and then execute with:

```bash
./taskonept2
```

Here is the displayed output of the compiled file:

![Task One - Part Two Output](screenshots/taskonept2output.jpg)

## Task 2
This task is primarily focussed around creating distinct classes to handle both the fibers functionality, and an additional class which handles a new implementation: the Scheduler. The scheduler enables fibers to be added to a queue, using spawn, and then those fibers can be executed in a round-robin fashion with the do_it method.

The main features of this task are:

![fiber class](screenshots/fiber.jpg)
![scheduler class](screenshots/scheduler.jpg)

and the code is contained within the [fiber header](fiber.hpp), [fiber implementation](fiber.cpp), [scheduler header](scheduler.hpp), [scheduler implementation](scheduler.cpp) and the [task two](task_two.cpp) files.

To build, run the following commands whilst inside the directory containing the task_one_pt2.cpp file:

```bash
clang++ fiber.cpp -o fiber.o
clang++ scheduler.cpp -o scheduler.o
clang++ -std=c++17 -I./context task_two.cpp fiber.o scheduler.o context/context.o -o tasktwo
```

and then execute with:

```bash
./tasktwo
```

Here is the displayed output of the compiled file:

![Task Two Output](screenshots/tasktwooutput.jpg)

## Task 2 - Final part
This small extension to the work completed as part of task 2 adds the passing of a second arguement on fiber creation, which is a pointer to an integer. As required by the specs, the fibers themselves use the function get_data to access the pointer that was passed in at creation.

The main features of this task are the following extended classes:

![extended fiber class](screenshots/fiber2.jpg)
![extended scheduler class](screenshots/scheduler2.jpg)

To build this task, use the run the following commands while inside the [task2_final](task2_final/) directory:

```bash
clang++ -c fiber.cpp -o fiber.o
clang++ -c scheduler.cpp -o scheduler.o
clang++ -c main.cpp -o main.o
clang++ -I.../context/context.o fiber.o scheduler.o main.o ../context/context.o -o program
```

and then execute with:

```bash
./program
```

Here is the displayed output of the compiled file:

![Task Two extended output](screenshots/task2finaloutput.jpg)