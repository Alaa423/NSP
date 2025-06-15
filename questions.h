#ifndef QUESTIONS_H
#define QUESTIONS_H

#define NUM_QUESTIONS 10

struct Question {
    char question[256];
    char options[4][100];
    char correct;  
};

void loadQuestions(struct Question q[]);

#endif
