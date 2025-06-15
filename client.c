#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include "questions.h"

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024 

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket < 0) {
        perror("Socket error");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection error");
        exit(1);
    }

    printf("Connected to the quiz server!\n\n");
    printf("Client expecting %d questions from NUM_QUESTIONS.\n\n", NUM_QUESTIONS); 

    for (int i = 0; i < NUM_QUESTIONS; i++) {
        memset(buffer, 0, sizeof(buffer));
        recv(clientSocket, buffer, sizeof(buffer), 0);
        printf("%s", buffer); 
        printf("\nNote: You have 10 seconds to answer.\n");
        printf("> ");
        fflush(stdout);
        char tempBuffer[BUFFER_SIZE] = {0};
        int answered = 0;
        char userAnswerChar = ' ';
        
        for (int secondsLeft = 10; secondsLeft >= 0; secondsLeft--) {
            fd_set set;
            struct timeval timeout;
            FD_ZERO(&set);
            FD_SET(STDIN_FILENO, &set);
            timeout.tv_sec = 1;
            timeout.tv_usec = 0;
            printf("\rTime remaining: %2d seconds. Answer:", secondsLeft);
            fflush(stdout);
            if (secondsLeft == 0) {
                break;
            }
            int rv = select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout);
            if (rv == -1) {
                perror("select");
                exit(1);
            } else if (rv > 0) {
                printf("\n");
                fflush(stdout);
                fgets(tempBuffer, sizeof(tempBuffer), stdin);
                if (strlen(tempBuffer) > 0 && (tempBuffer[0] == 'a' || tempBuffer[0] == 'b' || tempBuffer[0] == 'c' || tempBuffer[0] == 'd')) {
                    userAnswerChar = tempBuffer[0];
                    answered = 1;
                } else {
                    printf("Your answer is considered wrong because the character is not in the options (a, b, c, d).\n ");
                    int c;
                    userAnswerChar = 'x';
                    answered = 1;
                }
                break;
            }
        }
        if (!answered) {
            printf("\rTime's up! Moving to next question...\n");
            userAnswerChar = 'x';
        }
        memset(tempBuffer, 0, sizeof(tempBuffer));
        tempBuffer[0] = userAnswerChar;
        tempBuffer[1] = '\n';
        send(clientSocket, tempBuffer, strlen(tempBuffer), 0);
    }
    memset(buffer, 0, sizeof(buffer));
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("\n%s", buffer);
    int bytes_received;
    while ((bytes_received = recv(clientSocket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0'; 
        printf("%s", buffer); 
        fflush(stdout); 
        if (bytes_received < sizeof(buffer) - 1) {
            break;
        }
    }
    printf("\n");
    close(clientSocket);
    return 0;
}
