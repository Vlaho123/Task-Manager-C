#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<errno.h>
#include<stdbool.h>
#define __STDC_WANT_LIB_EXT1__ 1

#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE_OF_TASKS 100
//struct Tasks
//Represents a structure of a single task
//Task consists of an ID, title, description, priority and status


typedef struct Tasks *Task;
struct Tasks {

	int TaskID;
	char TaskTitle[MAX_SIZE_OF_TASKS];
	char TaskDescription[MAX_SIZE_OF_TASKS];
	int TaskPriority;  //Can be 1-High, 2-Medium,  3-Low
	int IsCompleted;    //1 for Yes, 0 for No
	Task TaskNext;
};

void ReadFromFile(FILE* file, Task Tasks);  //Read Tasks From Existing File
void AddTasksSortedByPriority(int TaskID, char* TaskTitle, char* TaskDescription, int TaskPriority, int isCompleted, Task TaskPosition); //Sort Tasks By Priority
void TaskDisplay(Task DisplayTasks);  //Display Tasks In Terminal
void DeleteAllTasks(Task DeleteTasks);  //Delete All Tasks
Task FindTaskPrev(int TaskID, Task FindingTask);  //Find Task That Is Previous To The One You Want To Delete
Task FindTask(int TaskID, Task FindingTask); //Finding Task - Needed For Editing A Task
void DeleteOneTask(int TaskID, Task DeletingOneTask);  //Delete One Specific Task
void SaveToFile(FILE* file, Task Tasks);	//Save All Tasks To File
void SortTasksByPriority(Task TaskSort); //Task Sorting
void EditTask(int TaskID, Task EditingTask);  //Editing Task
int isTaskIDUnique(int TaskID, Task* TaskUniqueID);  //Checking if task ID is unique

int main()
{
	struct Tasks HeadTask;
	HeadTask.TaskNext = NULL;
	FILE* fileToReadFrom = NULL;
	FILE* fileToSaveTo = NULL;
	Task Find_Task;
	ReadFromFile(fileToReadFrom, &HeadTask);
	TaskDisplay(HeadTask.TaskNext);
	printf("\n\n");

	int number;

	while (true)
	{
		printf("\n\nChoose from available options:\n");
		printf("Press number 1 if you want to add task to the task manager.\n");
		printf("Press number 2 if you want to edit existing task from the task manager.\n");
		printf("Press number 3 if you want to delete specific task from the task manager.\n");
		printf("Press number 4 if you want to delete all tasks from the task manager.\n");
		printf("Press number 5 if you want to display all tasks from the task manager.\n");
		printf("Press number 6 for exiting the option manager.\n");


		printf("\nYour Option: ");
		scanf_s("%d", &number);

		//switch case for choosing on of the 6 options 

		switch (number)
		{
		case 1:
		{
			printf("Task adding option\n\n");
			int IDTask, PriorityTask, TaskIsCompleted;
			char setTaskTitle[MAX_SIZE_OF_TASKS], setTaskDescription[MAX_SIZE_OF_TASKS];

			printf("Enter task ID (number): ");
			scanf_s("%d", &IDTask);

			if (!isTaskIDUnique(IDTask, HeadTask.TaskNext)) {
				printf("Error: Task with ID %d already exists. Please enter a unique ID.\n", IDTask);
				break;
			}

			getchar(); //Consume the newline left in the buffer by scanf_s()

			printf("Enter task title: ");
			fgets(setTaskTitle, sizeof(setTaskTitle), stdin);
			setTaskTitle[strcspn(setTaskTitle, "\n")] = 0; //Remove newline at the end

			printf("Enter task description: ");
			fgets(setTaskDescription, sizeof(setTaskDescription), stdin);
			setTaskDescription[strcspn(setTaskDescription, "\n")] = 0; //Remove newline at the end

			printf("Enter task priority (1-High, 2-Medium, 3-Low): ");
			scanf_s("%d", &PriorityTask);

			printf("Enter task status (1-Completed, 0-Not Completed): ");
			scanf_s("%d", &TaskIsCompleted);

			AddTasksSortedByPriority(IDTask, setTaskTitle, setTaskDescription, PriorityTask, TaskIsCompleted, &HeadTask);
			SaveToFile(fileToSaveTo, HeadTask.TaskNext);
			printf("Task successfully added.\n");

			break;
		}

		case 2:
		{
			int IDTask;


			printf("\nTask editing option\n");
			printf("Enter ID of a task you want to edit: ");
			scanf_s("%d", &IDTask);
			EditTask(IDTask, &HeadTask);
			SortTasksByPriority(&HeadTask);
			SaveToFile(SaveToFile, HeadTask.TaskNext);
			break;
		}
		case 3:
		{
			int TaskIDToDelete;
			printf("\nYou clicked number 3 (Deleting Specific Task). \nEnter ID of a task you want to delete: ");
			scanf_s("%d", &TaskIDToDelete);
			DeleteOneTask(TaskIDToDelete, &HeadTask);
			SaveToFile(fileToSaveTo, HeadTask.TaskNext);
			break;
		}
		case 4:
		{
			printf("\nYou clicked number 4 (Deleting All Tasks).\n");
			DeleteAllTasks(&HeadTask);
			SaveToFile(fileToSaveTo, HeadTask.TaskNext);
			printf("\nAll tasks successfully deleted. Press display option to ensure it is all deleted or check TASK_MANAGER.txt file.\n");
			break;
		}
		case 5:
		{
			printf("\nYou clicked number 5 (Displaying All Tasks).\n");
			TaskDisplay(HeadTask.TaskNext);
			break;
		}
		case 6:
		{
			printf("Exiting options manager\n");

			return 0;
		}
	
		default: {
			printf("You pressed the wrong number. You must press numbers from 1-6 in order to pick an option. Try again or press 6 for exit.");
			break;
				}
			
		}
	}
	return 0;
}

// Collecting Tasks From Existing File called "TASKS.txt"
void ReadFromFile(FILE* file, Task Tasks)
{
	int TaskID, TaskPriority, IsCompleted;
	char line[MAX_SIZE_OF_TASKS * 3];  
	char TaskTitle[MAX_SIZE_OF_TASKS] = { 0 };
	char TaskDescription[MAX_SIZE_OF_TASKS] = { 0 };


	//Gives us feedback about opening the file. 
	//If zero, file opened, if 2, file cannot be opened.
	errno_t error_code = fopen_s(&file, "TASK_MANAGER.txt", "r");
	if (error_code != 0)
	{
		printf("Can't open file. Error: %d\n", errno);
		return;
	}

	//Gets every single line from the file.
	while (fgets(line, sizeof(line), file))
	{
		
		if (sscanf_s(line, "%d\t%[^\t]\t%[^\t]\t%d\t%d",
			&TaskID,
			TaskTitle, (unsigned)_countof(TaskTitle),
			TaskDescription, (unsigned)_countof(TaskDescription),
			&TaskPriority,
			&IsCompleted) == 5)
		{
			//Adds tasks to the list and sorts them by priority
			AddTasksSortedByPriority(TaskID, TaskTitle, TaskDescription, TaskPriority, IsCompleted, Tasks);
		}
	}

	fclose(file);
}


//Adding Tasks To A List and Sorting Them By Priority
void AddTasksSortedByPriority(int TaskID, char* TaskTitle, char* TaskDescription, int TaskPriority, int isCompleted, Task TaskPosition) {
	Task newTask = NULL;
	newTask = (Task)malloc(sizeof(struct Tasks));

	newTask->TaskID = TaskID;
	strcpy_s(newTask->TaskTitle, sizeof newTask->TaskTitle, TaskTitle);
	strcpy_s(newTask->TaskDescription, sizeof newTask->TaskDescription, TaskDescription);
	newTask->TaskPriority = TaskPriority;
	newTask->IsCompleted = isCompleted;
	newTask->TaskNext = NULL;

	
	Task CurrentTask = TaskPosition;
	while (CurrentTask->TaskNext != NULL && CurrentTask->TaskNext->TaskPriority <= TaskPriority) {
		CurrentTask = CurrentTask->TaskNext;
	}

	newTask->TaskNext = CurrentTask->TaskNext;
	CurrentTask->TaskNext = newTask;
	
}
//Checking if IDs are unique

int isTaskIDUnique(int TaskID, Task TaskUniqueID) {
	Task CurrentTask = TaskUniqueID;
	while (CurrentTask != NULL) {
		if (CurrentTask->TaskID == TaskID) {
			return 0;
		}
		CurrentTask = CurrentTask->TaskNext;
	}
	return 1;
}
// Displaying All Tasks To The Terminal

void TaskDisplay(Task DisplayTasks) {

	printf("\nTASK MANAGER\n");
	while (DisplayTasks != NULL)
	{
		printf("Task identification number: %d", DisplayTasks->TaskID);
		printf("\tTask title: %s", DisplayTasks->TaskTitle);
		printf("\tTask description: %s", DisplayTasks->TaskDescription);
		printf("\tTask priority: %d", DisplayTasks->TaskPriority);
		printf("\tTask status: %d", DisplayTasks->IsCompleted);

		printf("\n");
		DisplayTasks = DisplayTasks->TaskNext;
	}
}

// Deleting All Tasks
void DeleteAllTasks(Task DeleteTasks) {

	Task TemporaryTask = NULL;
	
	while (DeleteTasks->TaskNext != NULL)
	{
		TemporaryTask = DeleteTasks->TaskNext;
		DeleteTasks->TaskNext = TemporaryTask->TaskNext;
		free(TemporaryTask);
	}

}

//Find Task That Is Previous To The One You Want To Delete
Task FindTaskPrev(int TaskID, Task FindingTask) {

	while (FindingTask->TaskNext!= NULL && FindingTask->TaskNext->TaskID != TaskID)
	{
		FindingTask = FindingTask->TaskNext;
	}
	if (FindingTask != NULL)
		return FindingTask;
	else
		return 0;
}

//Find Specific Task 
Task FindTask(int TaskID, Task FindingTask) {

	while (FindingTask != NULL && FindingTask->TaskID != TaskID)
	{
		FindingTask = FindingTask->TaskNext;
	}
	if (FindingTask != NULL)
		return FindingTask;
	else
		return NULL;
}


//Delete One Specific Task

void DeleteOneTask(int TaskID, Task DeletingOneTask) {

	Task PreviousTask = NULL;

	PreviousTask = FindTaskPrev(TaskID, DeletingOneTask);
	if (PreviousTask->TaskNext == NULL)
	{
		printf("Task with that ID does not exist.");
		return 0;
	}
	//Previous task used to link up with the task next to the one we are searching for
	Task TemporaryTask = NULL;
	TemporaryTask = PreviousTask->TaskNext;
	PreviousTask->TaskNext = TemporaryTask->TaskNext;
	free(TemporaryTask);
	printf("\nTask successfully deleted. Press display option to ensure it is deleted or check TASK_MANAGER.txt file.\n");
}

//Save All Tasks To The File Called "TASK_MANAGER.txt"
void SaveToFile(FILE* file, Task Tasks) {

	errno_t error_code;
	error_code = fopen_s(&file, "TASK_MANAGER.txt", "w");
	if (error_code != 0)
	{
		printf("Can't open file. Error: %d", errno);
		return 0;
	}

	while (Tasks != NULL)
	{
		fprintf_s(file, "%d\t%s\t%s\t%d\t%d\n", Tasks->TaskID, Tasks->TaskTitle, Tasks->TaskDescription, Tasks->TaskPriority, Tasks->IsCompleted);
		Tasks = Tasks->TaskNext;
	}
	fclose(file);
}
//Editing Task

void EditTask(int TaskID, Task EditingTask) {

	Task TemporaryTask = EditingTask;
	while (EditingTask != NULL && EditingTask->TaskID != TaskID) {
		EditingTask = EditingTask->TaskNext;
	}
	if (EditingTask == NULL)
	{
		printf("Task with that ID does not exist.");
		return 0;
	}
	else
	{
		printf("Task with that ID found.\n");
	}
	//X is used so that we can remember our position in a list
	Task X = EditingTask;
	//Reseting EditingTask
	EditingTask = TemporaryTask;
	int EditOption;

	while (true)
	{
		printf("\nPress number 1 if you want to edit task ID.\n");
		printf("Press number 2 if you want to edit task title.\n");
		printf("Press number 3 if you want to edit task description.\n");
		printf("Press number 4 if you want to edit task priority.\n");
		printf("Press number 5 if you want to edit task status.\n");
		printf("Press number 6 for exiting options manager.\n");

		printf("\nYour option: ");
		scanf_s("%d", &EditOption);

		switch (EditOption)
		{
		case 1:
		{
			int newID;
			printf("New Task ID: ");
			scanf_s("%d", &newID);
			//Reset EditingTask in order to search same IDs within our list of tasks
			if (!isTaskIDUnique(newID, EditingTask)) {
				printf("Error: Task ID %d already exists. Choose a different ID.\n", newID);
				break;
			}
			else {
				EditingTask = X;
				EditingTask->TaskID = newID;
			}
			break;
		}
		case 2:
		{
			char newTitle[MAX_SIZE_OF_TASKS];
			printf("New Task Title: ");
			scanf_s("%s", newTitle, (unsigned int)sizeof(newTitle));
			EditingTask = X;
			strcpy_s(EditingTask->TaskTitle, sizeof(EditingTask->TaskID), newTitle);
			break;
		}
		case 3:
		{
			char newDescription[MAX_SIZE_OF_TASKS];
			printf("New Task Description: ");
			scanf_s("%s", newDescription, (unsigned int)sizeof(newDescription));
			EditingTask = X;
			strcpy_s(EditingTask->TaskDescription, sizeof(EditingTask->TaskDescription), newDescription);
			break;
		}
		case 4:
		{
			int newPriority;
			printf("New Task Priority(1-High, 2-Medium, 3-Low): ");
			scanf_s("%d", &newPriority);
			if (newPriority > 3 || newPriority < 1)
			{
				printf("You entered wrong priority number. Try again or exit the edit options manager.\n");
				break;
			}
			EditingTask = X;
			EditingTask->TaskPriority = newPriority;
			break;
		}
		case 5:
		{
			int newStatus;
			printf("New Task Status(1-Completed, 0-Not completed): ");
			scanf_s("%d", &newStatus);
			if (newStatus < 0 || newStatus>1)
			{
				printf("You entered wrong status number. Try again or exit the edit options manager.\n");
				break;
			}
			EditingTask = X;
			EditingTask->IsCompleted = newStatus;
			break;
		}
		case 6:
		{
			printf("Exiting Edit Task optins manager.\n");
			return 0;
		}
		default:
		{
			printf("You pressed the wrong number. Choose options from 1-6.");
			break;
		}
		}
		printf("\nTask successfully modified. Press display option to ensure it is modified or check TASK_MANAGER.txt file\n");

			}
	
}

/* Task Sorting */
void SortTasksByPriority(Task TaskSort) {

		Task X = NULL;
		Task PreviousTask = NULL;
		Task TemporaryTask = NULL;
		Task End = NULL;

		while (TaskSort->TaskNext != End)
		{
			PreviousTask = TaskSort;
			X = TaskSort->TaskNext;
			while (X->TaskNext != End)
			{

				if ((X->TaskPriority)>(X->TaskNext->TaskPriority))
				{
					TemporaryTask = X->TaskNext;
					PreviousTask->TaskNext = TemporaryTask;
					X->TaskNext = TemporaryTask->TaskNext;
					TemporaryTask->TaskNext = X;

					X = TemporaryTask;
				}
				PreviousTask = X;
				X = X->TaskNext;

			}
			End = X;
		}

}
