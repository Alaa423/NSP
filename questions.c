#include "questions.h"
#include <string.h>

void loadQuestions(struct Question q[]) {
    strcpy(q[0].question, "According to the course, what structure is used by the `gethostbyname()` function to return information about a host?");
    strcpy(q[0].options[0], "a) struct sockaddr");
    strcpy(q[0].options[1], "b) struct in_addr");
    strcpy(q[0].options[2], "c) struct hostent");
    strcpy(q[0].options[3], "d) struct servent");
    q[0].correct = 'c';

    strcpy(q[1].question, "In the `sockaddr_in` structure, which field stores the port number in network format?");
    strcpy(q[1].options[0], "a) sin_family");
    strcpy(q[1].options[1], "b) sin_port");
    strcpy(q[1].options[2], "c) sin_addr");
    strcpy(q[1].options[3], "d) sin_zero");
    q[1].correct = 'b';

    strcpy(q[2].question, "What is the value of the `type` parameter to create a datagram socket (UDP) with the `socket()` function?");
    strcpy(q[2].options[0], "a) SOCK_STREAM");
    strcpy(q[2].options[1], "b) SOCK_RAW");
    strcpy(q[2].options[2], "c) SOCK_DGRAM");
    strcpy(q[2].options[3], "d) SOCK_SEQPACKET");
    q[2].correct = 'c';

    strcpy(q[3].question, "According to the course, what function is used by a server to bind a socket to a specific IP address and port number?");
    strcpy(q[3].options[0], "a) listen()");
    strcpy(q[3].options[1], "b) connect()");
    strcpy(q[3].options[2], "c) bind()");
    strcpy(q[3].options[3], "d) accept()");
    q[3].correct = 'c';

    strcpy(q[4].question, "Which Unix function is used to create a new process by duplicating the calling process?");
    strcpy(q[4].options[0], "a) exec()");
    strcpy(q[4].options[1], "b) fork()");
    strcpy(q[4].options[2], "c) system()");
    strcpy(q[4].options[3], "d) pthread_create()");
    q[4].correct = 'b';

    strcpy(q[5].question, "After a successful call to `fork()`, what is the return value of `fork()` in the child process?");
    strcpy(q[5].options[0], "a) The parent's PID"); 
    strcpy(q[5].options[1], "b) The child's PID"); 
    strcpy(q[5].options[2], "c) 0");
    strcpy(q[5].options[3], "d) -1");
    q[5].correct = 'c';

    strcpy(q[6].question, "According to the course, what is the IPC mechanism that allows two or more processes to access the same section of RAM?");
    strcpy(q[6].options[0], "a) Pipes");
    strcpy(q[6].options[1], "b) Message Queues");
    strcpy(q[6].options[2], "c) Shared Memory"); 
    strcpy(q[6].options[3], "d) Sockets");
    q[6].correct = 'c';

    strcpy(q[7].question, "What is the main reason for using semaphores or mutexes with shared memory?");
    strcpy(q[7].options[0], "a) To transfer data between processes.");  
    strcpy(q[7].options[1], "b) To synchronize access to shared memory and avoid race conditions."); 
    strcpy(q[7].options[2], "c) To create larger memory segments."); 
    strcpy(q[7].options[3], "d) To free shared memory after use.");
    q[7].correct = 'b';

    strcpy(q[8].question, "What is another common name used for a 'Named Pipe' in Unix systems?");
    strcpy(q[8].options[0], "a) Socket");
    strcpy(q[8].options[1], "b) File System Pipe");
    strcpy(q[8].options[2], "c) FIFO (First-In, First-Out)"); 
    strcpy(q[8].options[3], "d) Anonymous Pipe");
    q[8].correct = 'c';

    strcpy(q[9].question, "Unlike anonymous pipes, where are named pipes (FIFOs) created and accessed?");
    strcpy(q[9].options[0], "a) Only in RAM.");                            
    strcpy(q[9].options[1], "b) In the kernel only.");                     
    strcpy(q[9].options[2], "c) As special files in the file system.");    
    strcpy(q[9].options[3], "d) Via random file descriptors.");            
    q[9].correct = 'c';
}
