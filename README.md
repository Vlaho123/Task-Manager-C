CODE DOCUMENTATION FOR TASK MANAGER PROJECT


This program implements a simple task management system in C, where users can add, edit, delete, display, and save tasks to a file. 
The tasks are stored in a linked list and can be sorted by priority. 
The task manager supports basic operations for managing tasks and persists the tasks to a file (TASK_MANAGER.txt).


HEADER FILES

#include<stdio.h>         Standard I/O library for input and output operations.
#include<stdlib.h>        Standard library for memory allocation and process control.
#include<string.h>        String manipulation functions.
#include<malloc.h>        Memory allocation functions (alternative to stdlib.h).
#include<errno.h>         Provides error codes and related functions.
#include<stdbool.h>       Defines the `bool` type and true/false constants.


CONSTANTS

#define __STDC_WANT_LIB_EXT1__ 1  Enables some library extensions in some compilers.
#define _CRT_SECURE_NO_WARNINGS   Disables warnings related to insecure functions in MSVC.
#define MAX_SIZE_OF_TASKS 100     Maximum size for task-related strings like titles and descriptions.


TASK STRUCTURE DEFINITION

typedef struct Tasks *Task;
struct Tasks {
    int TaskID;                                 Task ID (unique identifier for the task).
    char TaskTitle[MAX_SIZE_OF_TASKS];          Task title (name of the task).
    char TaskDescription[MAX_SIZE_OF_TASKS];    Task description (details of the task).
    int TaskPriority;                           Task priority (1-High, 2-Medium, 3-Low).
    int IsCompleted;                            Task completion status (1 for completed, 0 for not completed).
    Task TaskNext;                              Pointer to the next task in the list.
};

FUNCTION DEFINITIONS

-- ReadFromFile(FILE* file, Task Tasks)

    Description: Reads tasks from a file (TASK_MANAGER.txt) and loads them into the linked list.
    Parameters:
            file: File pointer for the task file.
            Tasks: Pointer to the head task node of the linked list.
    Returns: None.
    Details: It reads each line from the file, parses the task data, and adds the task to the list sorted by priority.


-- AddTasksSortedByPriority(int TaskID, char* TaskTitle, char* TaskDescription, int TaskPriority, int isCompleted, Task TaskPosition)

    Description: Adds a new task to the linked list, sorted by priority.
    Parameters:
            TaskID: The unique ID of the new task.
            TaskTitle: Title of the new task.
            TaskDescription: Description of the new task.
            TaskPriority: Priority of the new task.
            isCompleted: Completion status (1 for completed, 0 for not completed).
            TaskPosition: Pointer to the task list where the new task should be inserted.
    Returns: None.
    Details: The function creates a new task and inserts it into the linked list in sorted order by priority.


-- isTaskIDUnique(int TaskID, Task TaskUniqueID)

    Description: Checks if a task ID is unique (not already used in the list).
    Parameters:
            TaskID: ID of the task to check.
            TaskUniqueID: Pointer to the task list to check against.
    Returns: 1 if the ID is unique, 0 if the ID already exists in the list.


-- TaskDisplay(Task DisplayTasks)
    
    Description: Displays all tasks in the terminal.
    Parameters:
            DisplayTasks: Pointer to the head of the task list to be displayed.
    Returns: None.
    Details: It iterates over the list of tasks and prints their details to the terminal.


-- DeleteAllTasks(Task DeleteTasks)
    
    Description: Deletes all tasks from the task list.
    Parameters:
            DeleteTasks: Pointer to the head of the task list to be deleted.
    Returns: None.
    Details: It frees memory for each task in the list.


-- FindTaskPrev(int TaskID, Task FindingTask)

    Description: Finds the task that precedes a specific task in the list based on the task ID.
    Parameters:
            TaskID: ID of the task to search for.
            FindingTask: Pointer to the task list.
    Returns: Pointer to the task that precedes the task with the given ID.
    Details: Traverses the list to find the task before the one with the matching ID.


-- FindTask(int TaskID, Task FindingTask)
    
    Description: Finds a task in the list by its ID.
    Parameters:
            TaskID: ID of the task to search for.
            FindingTask: Pointer to the task list.
    Returns: Pointer to the task if found, or NULL if not found.
    Details: Traverses the task list to find the task with the specified ID.


-- DeleteOneTask(int TaskID, Task DeletingOneTask)

    Description: Deletes a specific task from the task list.
    Parameters:
            TaskID: ID of the task to delete.
            DeletingOneTask: Pointer to the task list.
    Returns: None.
    Details: Finds and deletes a task with the given ID from the list.


-- SaveToFile(FILE* file, Task Tasks)

    Description: Saves all tasks from the list to a file (TASK_MANAGER.txt).
    Parameters:
            file: File pointer for the task file.
            Tasks: Pointer to the task list to save.
    Returns: None.
    Details: Iterates over the list of tasks and writes each task’s details to the file.


-- EditTask(int TaskID, Task EditingTask)

    Description: Allows the user to edit an existing task's details (ID, title, description, priority, or status).
    Parameters:
            TaskID: ID of the task to edit.
            EditingTask: Pointer to the head of the task list.
    Returns: None.
    Details: Prompts the user for new task details and updates the selected task in the list.

    
-- SortTasksByPriority(Task TaskSort)

    Description: Sorts the tasks in the list by their priority.
    Parameters:
            TaskSort: Pointer to the head of the task list to be sorted.
    Returns: None.
    Details: Uses the bubble sort algorithm to sort tasks in ascending order of priority (1-High, 2-Medium, 3-Low).


MAIN FUNCTION WORKFLOW

1. Initialization:

A head task (HeadTask) is created as the entry point for the linked list.
The program attempts to read the tasks from the file (TASK_MANAGER.txt) and displays them.

2. Menu Loop:

The user is presented with a menu of options to manage tasks.
Option 1: Add a new task.
Option 2: Edit an existing task.
Option 3: Delete a specific task.
Option 4: Delete all tasks.
Option 5: Display all tasks.
Option 6: Exit the program.

3. Task Operations:

For each operation, the program interacts with the linked list to modify or display tasks and saves the updated list to the file.


ERROR HANDLING

The program checks if files can be opened successfully. If a file cannot be opened, it prints an error message.
For task operations, the program ensures that task IDs are unique before adding or editing tasks.
The program provides feedback for invalid user input (e.g., invalid priority or status).


CONCLUSION

This program provides a simple but functional task management system with features like task addition, modification, deletion, and persistence via file storage. 
It leverages linked lists and includes basic sorting and error handling mechanisms for managing the tasks effectively.






















