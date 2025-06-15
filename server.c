#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "questions.h"

#define PORT 8080
#define MAX_CLIENTS 1
#define BUFFER_SIZE 1024

void handleClient(int clientSocket, struct sockaddr_in clientAddr) {
    struct Question quiz[NUM_QUESTIONS];
    char buffer[BUFFER_SIZE];
    int score = 0;
    char incorrect_answers_details[BUFFER_SIZE * 5];
    memset(incorrect_answers_details, 0, sizeof(incorrect_answers_details));
    int has_incorrect_answers = 0; 
    loadQuestions(quiz);
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "Q%d: %s\n%s\n%s\n%s\n%s\nYour answer (a/b/c/d): ",
                i + 1,
                quiz[i].question,
                quiz[i].options[0],
                quiz[i].options[1],
                quiz[i].options[2],
                quiz[i].options[3]);

        send(clientSocket, buffer, strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        recv(clientSocket, buffer, sizeof(buffer), 0);

        if (buffer[0] == quiz[i].correct) {
            score++;
        } else {
            has_incorrect_answers = 1;
            char temp_correction_str[512]; 
            int correct_option_index = quiz[i].correct - 'a';
            sprintf(temp_correction_str, "\nQ%d: '%s'\n   Your answer was incorrect. The correct answer is '%c) %s'\n",
                    i + 1,
                    quiz[i].question,
                    quiz[i].correct,
                    quiz[i].options[correct_option_index]);
            strcat(incorrect_answers_details, temp_correction_str);
        }
    }

    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "Quiz complete! Your score is %d out of %d.\n", score, NUM_QUESTIONS);
    send(clientSocket, buffer, strlen(buffer), 0);

    char final_corrections_message[BUFFER_SIZE * 5]; 
    memset(final_corrections_message, 0, sizeof(final_corrections_message));

    if (has_incorrect_answers) {
        strcat(final_corrections_message, "\nCorrections for incorrect answers \n");
        strcat(final_corrections_message, incorrect_answers_details); 
    } else {
        strcat(final_corrections_message, "\nExcellent! All your answers are correct..\n");
    }

    send(clientSocket, final_corrections_message, strlen(final_corrections_message), 0);

    FILE *logFile = fopen("results.txt", "a");
    if (logFile) {
        fprintf(logFile, "Client %s scored %d/%d\n", inet_ntoa(clientAddr.sin_addr), score, NUM_QUESTIONS);
        fclose(logFile);
    }

    close(clientSocket);
    printf("Client disconnected: %s\n", inet_ntoa(clientAddr.sin_addr));
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size = sizeof(clientAddr);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Socket error");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind error");
        exit(1);
    }

    if (listen(serverSocket, MAX_CLIENTS) < 0) {
        perror("Listen error");
        exit(1);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addr_size);
        if (clientSocket < 0) {
            perror("Accept error");
            continue;
        }

        printf("Client connected: %s\n", inet_ntoa(clientAddr.sin_addr));
        handleClient(clientSocket, clientAddr);
    }

    close(serverSocket);
    return 0;
}
