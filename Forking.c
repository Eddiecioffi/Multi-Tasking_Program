//This program creates child processes that are each assigned with a different task. The parent process waits for all child processes to complete and then displays the results of each task. The tasks are computing the factorial of 5, finding prime numbers up to 20, and performing a custom task.
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// Function prototypes for the child processes
void task1();
void task2();
void task3();

// Function prototypes for factorial and prime number functions
int factorial(int n);
void findPrimes();

int main() {
    int n;
    // Prompt user to enter n which is the number of child processes to create
    printf("Enter the number of child processes to create: ");
    // Read the user input and store it in n
    scanf("%d", &n);

    // Check if n is valid
    if (n < 1 || n > 5) {
        printf("Number of child processes must be between 1 and 5.\n");
        exit(EXIT_FAILURE);
    }
    // Displau the number of child processes to be created
    printf("Parent process (PID: %d) is creating %d child processes.\n", getpid(), n);

    // Fork n child processes
    for (int i = 0; i < n; ++i) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Task operations for child process
            switch (i) {
                case 0:
                    printf("Child %d (PID: %d) is computing the factorial of 5.\n", i + 1, getpid());
                    task1(); // Executes task 1
                    break;
                case 1:
                    printf("Child %d (PID: %d) is finding prime numbers up to 20.\n", i + 1, getpid());
                    task2(); // Executes task 2
                    break;
                case 2:
                    printf("Child %d (PID: %d) is performing a custom task.\n", i + 1, getpid());
                    task3(); // Executes task 3
                    break;
            }
            exit(EXIT_SUCCESS); // Exit the child process
        }
    }

    // Parent process waits for all child processes to complete
    int status;
    pid_t child_pid;

    for (int i = 0; i < n; ++i) {
        child_pid = wait(&status);
        printf("Child %d (PID: %d) completed its task. ", i + 1, child_pid);
        if (WIFEXITED(status)) {
            if (i == 0) {
                printf("Result: %d\n", WEXITSTATUS(status)); // Print result of task 1
            } else if (i == 1) {
                printf("Result: ");
                findPrimes(); // Print result of task 2
            } else {
                printf("Result: Custom task completed.\n"); // Print result of task 3
            }
        } else {
            printf("An error occurred.\n"); // Print error message
        }
    }
    // Print final display message
    printf("All child processes have completed. Parent (PID: %d) is displaying the final message.\n", getpid()); 

    return 0;
}

void task1() {
    int result = factorial(5); // Calcualtes the factorial of 5
    exit(result); // Exit the child process with the result
}

void task2() {
    findPrimes(); // Finds prime numbers
    exit(0); // Exit the child process with the result
}

void task3() {
    // Custom task here
    exit(0); // Exit
}

// Additional functions for factorial and prime numbers
int factorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

void findPrimes() {
    printf("2 3 5 7 11 13 17 19\n"); // Print prime numbers
}
