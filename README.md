# Patient Indexing System

## Overview
The **Patient Indexing System** is a C-based program that organizes patient records using an **AVL Tree** structure. It allows users to efficiently store, retrieve, and manage patient information based on **Body Mass Index (BMI)** while maintaining balanced search performance.

## Features
- **AVL Tree Implementation**: Ensures balanced insertion and efficient searching.
- **Patient Data Management**: Stores patient details including name, birth date, height, weight, and BMI.
- **File-Based Data Loading**: Reads patient data from `patients.txt` and constructs the AVL Tree.
- **Patient Lookup by BMI**: Allows searching for patients with a specific BMI.
- **Youngest Patient Finder**: Identifies the youngest patient in the database.
- **Patient List Display**: Displays all patients in sorted order based on BMI.

## Files
### 1. `avltree.h`
Defines the **AVL tree structure** and function prototypes.

### 2. `indexingpatients.c`
Contains the core **AVL tree operations**, including:
- Tree creation, insertion, and balancing.
- Data loading from file.
- Searching patients by BMI.
- Identifying the youngest patient.
- Displaying stored patient records.

### 3. `main.c`
Handles **user interaction**, providing a menu-driven system to:
1. Display all patients.
2. Search for patients by BMI.
3. Identify the youngest patient.

## How to Compile and Run
### Compilation:
```bash
gcc main.c indexingpatients.c -o patient_indexing
```
### Execution:
```bash
./patient_indexing
```
## Input File Format (`patients.txt`)
The system expects patient data in the following format:
```
Name;Surname;Date of birth;Height;Weight;BMI
Alex;Black;20/02/2000;1.80;85;26.2
John;Brown;18/08/2004;1.80;85;26.2
Brainy;Smurf;04/05/1980;1.75;170;55.5
Clumsy;Smurf;18/02/2000;1.80;45;13.9
```
## Future Improvements
- Store birth dates as integers for **faster comparisons**.
- Optimize data storage using **dynamic arrays** instead of linked lists.
- Implement **file-based data persistence** for saving modified records.

## Author
**Berrak Yıldırım**
Student ID: 2690964

