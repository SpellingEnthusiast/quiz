#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//R00172226 - Quiz

int count_questions(const char* filepath){
    FILE *file;
    file = fopen(filepath, "r");
    char chr;
    int count_lines = 0;

    chr = getc(file);
    while (chr != EOF)
    {
        if (chr == '\n')
        {
            count_lines = count_lines + 1;
        }
        chr = getc(file);
    }
    rewind(file);
    fclose(file);
    return count_lines;
}

int read_questions(const char* filepath, char (*array)[1000], int count){
    int i;
    FILE *f = fopen(filepath, "r");

    int line = 0;
    char input[1000];
    char *p;

    while (fgets(input, 1000, f)){
//        printf("%d. %s", line, input);
        p = strtok(input, "|");

        if(p){
               strcpy(array[line++], p);
        }
    }

    fclose(f);
}

int read_answers(const char* filepath, char (*array)[1000], int count){
    int i;
    FILE *f = fopen(filepath, "r");
    char *p;
    int line = 0;
    char input[1000];

    while (fgets(input, 1000, f)){
//        printf("%d. %s", line, input);
        p = strtok(input, "|");
        p = strtok (NULL, "\n");

        if(p){
               strcpy(array[line++], p);
        }

    }

    fclose(f);
}

char ask_question(char (*Qarray)[1000], char (*Aarray)[1000], int count, char argv[]){
    char answer[100];
    char chosen[count];
    int correct = 0;
    int wrong = 0;
    int questionsasked = 0;
    int i;
    int j;
    int r;
    int x;

    for(x=0; x<count; x++){
        chosen[count] = 0;
    }

    for (i = 0; i < count; i++) {
        srand(time(NULL));
        r = rand() % count;
        while (chosen[r] == 1){
            r = rand() % count;
        }

        printf("Q: %s", Qarray[r]);
        questionsasked++;

        if (strcmp(argv, "1") == 0){
            printf("\nClue: ?");
        }

        if (strcmp(argv, "2") == 0){
            printf("\nClue: ");
            for (j = 0; j < strlen(Aarray[r]); j++){
                printf("- ");
            }
        }

        if (strcmp(argv, "3") == 0){
            printf("\nClue: ");
            char c;
            int index = 0;
            c = Aarray[r][0];
            printf("%c", c);
            for (j = 0; j < strlen(Aarray[r]) - 2; j++){
                printf(" - ");
                index++;
            }
            c = Aarray[r][index + 1];
            printf("%c", c);
        }

        if (strcmp(argv, "4") == 0){
            printf("\nClue: ");
            char c;
            int index = 0;
            int a;
            int b;
            int x;
            int status = 0;
            while (status == 0){
                    a = rand() % strlen(Aarray[r]);
                    b = rand() % strlen(Aarray[r]);
                    while (a == b){
                            a = rand() % strlen(Aarray[r]);
                            b = rand() % strlen(Aarray[r]);
                    }

                    for (x = 0; x < strlen(Aarray[r]); x++){
                            if (a == x){
                                c = Aarray[r][a];
                                printf("%c", c);
                            }
                            else if (b == x){
                               c = Aarray[r][b];
                               printf("%c", c);
                           }
                            else{
                                printf(" - ");
                            }
                    }
                    status = 1;
            }

        }

        if (strcmp(argv, "5") == 0){
            char c;
            int x;
            int ran;
            int answerLetterCount;
            answerLetterCount = strlen(Aarray[r]);
            char chosenLetters[answerLetterCount];
                for(x=0; x<answerLetterCount; x++){
                        chosenLetters[count] = 0;
                }

            printf("\nClue: ");
            for (j = 0; j < strlen(Aarray[r]); j++){
                    ran = rand() % strlen(Aarray[r]);

                    while (chosenLetters[ran] == 1){
                        ran = rand() % strlen(Aarray[r]);
                    }

                    c = Aarray[r][ran];

                printf("%c", c);

                chosenLetters[ran] = 1;
            }
        }

        printf("\nEnter answer: \n");
        scanf("%s", &answer);

        if (strcmp(answer, Aarray[r]) == 0){
            printf("Correct!\n");
            correct++;
            printf("Score: %d / %d\n", correct, questionsasked);
        }

        else{
            printf("Incorrect!\n");
            wrong++;
            printf("Score: %d / %d\n", correct, questionsasked);
        }

        chosen[r] = 1;

     }
}


int main(int argc, char *argv[])
{
    int i = 0;
    int count_lines = 0;
    count_lines = count_questions(argv[1]);
    printf("Number of questions in this quiz: %d\n", count_lines);
    char questions[1000][1000];
    char answers[1000][1000];

    read_questions(argv[1], questions, count_lines);
    read_answers(argv[1], answers, count_lines);
    ask_question(questions, answers, count_lines, argv[2]);


    return 0;
}
