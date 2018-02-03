#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char inputChar()
{
    //To generate random input char, get an integer between 
    int code;
    char c;

    code = rand() % 14;

    switch(code) {
        case 0:
            c = '[';
            break;
        case 1:
            c = '(';
            break;
        case 2:
            c = '{';
            break;
        case 3:
            c = ' ';
            break;
        case 4:
            c = 'a';
            break;
        case 5:
            c = 'x';
            break;
        case 6:
            c = '}';
            break;
        case 7:
            c = ')';
            break;
        case 8:
            c = 'r';
            break;
        case 9:
            c = 'e';
            break;
        case 10:
            c = 's';
            break;
        case 11:
            c = 't';
            break;
        case 12:
            c = '\0';
            break;
        default: 
            c = ']';
            break;
    }

    return c;
}

char* string = NULL;

char *inputString()
{
    int i;
    if(string != NULL) {
        free(string);    
    }
    string = malloc(7 * sizeof(char));

    for(i = 0; i < 6; i++) {
        string[i] = inputChar();
    } 
    string[6] = '\0'; //Make sure the string is null terminated

    return string;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  clock_t begin;
  clock_t end;
  double time_spent;

  begin = clock();
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      end = clock();
      time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
      printf("\nTime spent until full coverage: %f\n", time_spent);
      printf("error ");

      if(string != NULL) {
        free(string); 
      }

      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();

    return 0;
}
