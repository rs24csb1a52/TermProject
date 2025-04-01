Roll Numbers:
- 24CSB1A65 (Soan Sagar Terli)
- 24CSB1A57 (Sanjay Rao)
- 24CSB1A52 (Rajwardhan Singh)

Student Management System using AVL Trees

Project Contributors:
1. Soan Sagar Terli (24CSB1A65)
   - AVL Tree - Part 2
   - CourseInfo
   - FileHandler - Part 3

2. Sanjay Rao (24CSB1A57)
   - AVL Tree - Part 1
   - Node
   - FileHandler - Part 2

3. Rajwardhan Singh (24CSB1A52)
   - FileHandler - Part 1
   - Main (Handling argument input and passing)
   - Code Aggregation
   - Editing Makefile



--------------------------------------------------

Project Overview:
This project implements a Student Management System using AVL Trees for efficient storage and retrieval of student records. The system allows sorting based on CGPA or Roll Number and can be executed with different input modes.

--------------------------------------------------

Compilation and Execution:

Compilation:
Run the following command to compile the code:
make
This will generate an executable named student_records.

Execution:
Run the program with one of the following commands:

Sort by CGPA:
./student_records ./input.txt cgpa

Sort by Roll Number (Default):
./student_records ./input.txt rollno
or simply:
./student_records ./input.txt
If no sorting argument is provided, the program defaults to sorting by Roll Number.

--------------------------------------------------

File Descriptions:
- AVLTree - Implements AVL Tree data structure and its operations.
- Node - Defines the structure of each node in the AVL Tree.
- FileHandler - Handles file operations (reading input, writing output).
- CourseInfo - Manages student course-related information.
- Main - Controls argument handling and integrates the different modules.
- Makefile - Automates the compilation process.

--------------------------------------------------

Notes:
- Ensure input.txt exists and follows the correct format before execution.
- The program uses AVL Trees for efficient searching and sorting of student records.
- Default sorting is based on Roll Number unless specified otherwise.
- The complete source code is available on GitHub: https://github.com/rs24csb1a52/TermProject/

--------------------------------------------------

