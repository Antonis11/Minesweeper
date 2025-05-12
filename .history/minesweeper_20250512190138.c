#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define Mine '@'
#define Marked Mine+1

int ROWS,COLUMNS;
int **array_main, **array_visible;
int mine_count;
int open_squares;
int moves = 0;

void panel(void);
double select_dif(void);
void create_level(void);
void check_surround(int i, int j);
void show_level(void);
int open(int x,int y);
void mark(int x, int y);
void cheat(int x, int y);
int end_game(void);
void read_text(char str[], int size, int flag);

void panel(void) {
    int i,j;

    array_main=(int**) malloc(ROWS*sizeof(int*));
    for(i=0; i<ROWS; i++) {
        array_main[i]=(int*) malloc(COLUMNS*sizeof(int));
        if(array_main[i]==NULL) {
            printf("No memory available!!!\n");
            exit(1);
        }
    }

    array_visible=(int**) malloc(ROWS*sizeof(int*));
    for(i=0; i<ROWS; i++) {
        array_visible[i]=(int*) malloc(COLUMNS*sizeof(int));
        if(array_main[i]==NULL) {
            printf("No memory available!!!\n");
            exit(1);
        }
    }

    for(i=0; i<ROWS ;i++) {
        for(j=0; j<COLUMNS ;j++) {
            array_main[i][j]=0;
        }
    }

    for(i=0; i<ROWS ;i++) {
        for(j=0; j<COLUMNS ;j++) {
        array_visible[i][j] = '#';
        }
    }
}

double select_dif(void) {
    int level;
    
    printf("Choose difficulty\n");
    printf("1-Easy\n");
    printf("2-Medium\n");
    printf("3-Hard\n");
    printf("4-Impossible\n");

    do{
        printf("Choice: ");
        scanf("%d",&level);
        if(level<1 || level>4)
            printf("INVALID NUMBER SELECTED!\n");
    }while(level<1 || level>4);
    getchar();
    switch(level){
    case 1:
        mine_count = ROWS * COLUMNS * 0.10;
    return 0.1;
    case 2:
        mine_count = ROWS * COLUMNS * 0.15;
    return 0.15;
    case 3:
        mine_count = ROWS * COLUMNS * 0.20;
    return 0.20;
    case 4:
        mine_count = ROWS * COLUMNS * 0.25;
    return 0.25;
    }

    printf("Level: %d Mine_count: %d\n",level,mine_count);
}

void create_level(void) {
    int i,j;
    int rand_index_1,rand_index_2;

    srand(time(NULL));
    for(i=0; i<mine_count; i++) {
        rand_index_1=rand() % ROWS;
        rand_index_2=rand() % COLUMNS;
        if(array_main[rand_index_1][rand_index_2] != Mine)
            array_main[rand_index_1][rand_index_2] = Mine;
        else
            mine_count++;
        }

        printf("\n\n");
        for(i=0; i<ROWS; i++) {
            for(j=0; j<COLUMNS; j++) {
                if(array_main[i][j] != Mine)
                    check_surround(i, j);
        printf("%3d", array_main[i][j]);
            }
        printf("\n");
        }
        printf("\n\n");

    printf("%5c", ' ');
    for(j=0; j<COLUMNS; j++) {
        printf("%3d", j+1);
    }
    printf("\n");

    for(i=0; i<COLUMNS*4; i++) {
        printf("-");
    }
    printf("\n");

    for(i=0; i<ROWS; i++)
    {
        printf("%d |  ", i+1);
        for(j=0; j<COLUMNS; j++) {
            printf("%3c", array_visible[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("%d blocks are open\n",open_squares);
}

void check_surround(int i, int j) {
    int k,l;

    for(k=i-1; k<i+2; k++) {
        for(l=j-1; l<j+2; l++) {
            if(k>=0 && l>=0 && k<ROWS && l<COLUMNS && array_main[k][l] == Mine)
                array_main[i][j]++;
            }
        }
    }

void show_level(void) {
    int i,j;

    system("clear");

    printf("%5c", ' ');
    for(j=0; j<COLUMNS; j++) {
        printf("%3d", j+1);
    }
    printf("\n");

    for(i=0; i<COLUMNS*4; i++) {
        printf("-");
    }
    printf("\n");

    for (i = 0; i < ROWS; i++) {
        printf("%d |  ", i+1);
        for (j = 0; j < COLUMNS; j++)
        {
        if(array_visible[i][j] > 0 && array_visible[i][j] < 9)
            printf("%3d", array_visible[i][j]);
        else if(array_visible[i][j] == Marked)
            printf("%3c", Mine);
        else     
            printf("%3c", array_visible[i][j]);
        }
    printf("\n");
    }
}

int open(int x, int y) { 
    int over = 0;

    if(x<0 || y<0 || x>=ROWS || y>=COLUMNS)
        return 0;

    if(array_visible[x][y] == Mine + 1 || array_visible[x][y] == '#')
        array_visible[x][y] = array_main[x][y];
    else
        return 0;

    if(moves == 0) {
        if(array_visible[x][y] == Mine) {
            array_visible[x][y] = '#';
            return 0;
        }
    }

    open_squares++;
    moves++;
    if(array_visible[x][y] == Mine)
        over = 1;
    else if (array_visible[x][y] == 0) {
        int k,l; 
        array_visible[x][y] = '.';

    for(k=x-1; k <= x+1; k++) {
        for(l=y-1; l <= y+1; l++){
            open(k,l);
        }
    }
}
    show_level();
    if(over) {
        printf("\n GAME OVER!!!\n");
        exit(1);
    }

    return 1;
}

void mark(int x, int y) {
    if(x<0 || y<0 || x>=ROWS || y>=COLUMNS) {
        printf("INVALID DIMENSIONS GIVEN!\n");
        return;
    }  
    else if(array_visible[x][y] != '#') {
        printf("Square already opened!\n");
        return;
    }
    array_visible[x][y] = Marked;
    show_level();
    return; 
}

void cheat(int x, int y) {

    if((x<0)|| (y<0) || (x>=ROWS) || (y>=COLUMNS) ) {
        printf("INVALID DIMENSIONS GIVEN!\n");
        return;
    }
    else if(array_visible[x][y] != '#') {
        printf("Square already opened!\n");
        return;
    }

    if(array_main[x][y] == Mine)
        printf("Mine Here!!\n");
    else if(array_main[x][y] == 0)
        printf("Empty Square\n");
    else
        printf("%d Mine Around\n", array_main[x][y]);
}

int end_game(void) {
    char ch;

    do {
        printf("Are you sure?[y or n]\n");
        ch = getchar();
        if(ch != '\n') {
            if(ch == 'y') {
                printf("Closing the game.\n");
                return 0;
            }
        }
    }while(ch != 'n'  && getchar() != EOF);

    getchar();
    return 1;
}

void read_text(char str[], int size, int flag) {
    int len;
    if(fgets(str, size, stdin) == NULL) {
        printf("ERROR: fgets() failed\n");
        exit(1);
    }

    len = strlen(str);
    if(len > 0) {
        if(flag && str[len-1] == '\n')
            str[len-1] = '\0';
    }
    else {
        printf("ERROR: No input\n");
        exit(1);
    }
}    

int main(void) {
    int i,row,col,x,y,s,z;
    char str[15];
    int win;
    double multi;

    do {
        printf("Give Rows and Columns\n");
        scanf("%d %d", &ROWS, &COLUMNS);
        if ( (ROWS * COLUMNS * 0.1 < 1) || ROWS>15 || COLUMNS>15 ) 
            printf("INVALID DIMENSIONS GIVEN!\n");
    }while( (ROWS * COLUMNS * 0.1 < 1) || ROWS>15 || COLUMNS>15 );
    multi = select_dif();

    while(1) {
        panel();
        open_squares = 0;
        win = (ROWS * COLUMNS) - mine_count;
        create_level();
        
        while(open_squares != win) { 
            printf("Write commands: ");
            read_text(str, sizeof(str), 1);

            if(!strncmp(str, "open", 4)) {
                if( (str[5] >= '1' && str[5] <='9')  && (str[6]>= '0' && str[6]<= '9') && (str[8] >= '1' && str[8] <='9')  && (str[9]>= '0' && str[9]<= '9') ) {  //e.g open(XX,YY)
                    x = str[5] - '0';
                    y = str[6] - '0';
                    row = x * 10 + y;

                    s = str[8] - '0';
                    z = str[9] - '0';
                    col= s * 10 + z;
                }
                else if( (str[5] >= '1' && str[5] <='9')  && (str[6]>= '0' && str[6]<= '9') ) { //e.g open(XX,Y)
                    x = str[5] - '0';
                    y = str[6] - '0';
                    row = x * 10 + y;

                    col= str[8] - '0';
                }
                else if( (str[7] >= '1' && str[7] <='9')  && (str[8]>= '0' && str[8]<= '9')) { //e.g open(X,YY)
                    row = str[5] - '0';

                    s = str[7] - '0';
                    z = str[8] - '0';
                    col= s * 10 + z;
                }
                else if( (str[5] >= '1' && str[5] <= '9') && (str[7] >= '1' && str[7] <= '9') ) {  //e.g open(X,Y)    
                    row = str[5] - '0';
                    col = str[7] - '0';
                }
                else
                    printf("NO VALID COMMAND!\n");

                if(!open(row-1,col-1))
                    printf("INVALID DIMENSIONS GIVEN!!!\n");
            }
            else if(!strncmp(str, "mark", 4)) {
                if( (str[5] >= '1' && str[5] <='9')  && (str[6]>= '0' && str[6]<= '9') && (str[8] >= '1' && str[8] <='9')  && (str[9]>= '0' && str[9]<= '9') ) { //e.g mark(XX,YY)
                    x = str[5] - '0';
                    y = str[6] - '0';
                    row = x * 10 + y;

                    s = str[8] - '0';
                    z = str[9] - '0';
                    col= s * 10 + z;
                }
                else if( (str[5] >= '1' && str[5] <='9')  && (str[6]>= '0' && str[6]<= '9') ) { //e.g mark(XX,Y)         
                    x = str[5] - '0';
                    y = str[6] - '0';
                    row = x * 10 + y;

                    col= str[8] - '0';
                }
                else if( (str[7] >= '1' && str[7] <='9')  && (str[8]>= '0' && str[8]<= '9') ) { //e.g mark(X,YY)
                    row = str[5] - '0';

                    s = str[7] - '0';
                    z = str[8] - '0';
                    col= s * 10 + z;
                }
                else if( (str[5] >= '1' && str[5] <= '9') && (str[7] >= '1' && str[7] <= '9') ) { //e.g mark(X,Y)      
                row = str[5] - '0';
                col = str[7] - '0';
                }
                else
                    printf("NO VALID COMMAND!\n");

                mark(row-1,col-1);
            }
            else if(!strncmp(str, "cheat", 5)) {
            if( (str[6] >= '1' && str[6] <='9')  && (str[7]>= '0' && str[7]<= '9') && (str[9] >= '1' && str[9] <='9')  && (str[10]>= '0' && str[10]<= '9') ) { //e.g cheat(XX,YY)
                x = str[6] - '0';
                y = str[7] - '0';
                row = x * 10 + y;

                s = str[9] - '0';
                z = str[10] - '0';
                col= s * 10 + z;
            }
            else if( (str[6] >= '1' && str[6] <='9')  && (str[7]>= '0' && str[7]<= '9') ) { //e.g cheat(XX,Y)
                x = str[6] - '0';
                y = str[7] - '0';
                row = x * 10 + y;

                col= str[9] - '0';
            }
            else if( (str[8] >= '1' && str[8] <='9')  && (str[9]>= '0' && str[9]<= '9') ) { //e.g cheat(X,YY)
                row = str[6] - '0';

                s = str[8] - '0';
                z = str[9] - '0';
                col= s * 10 + z;
            }
            else if( (str[6] >= '1' && str[6] <= '9') && (str[8] >= '1' && str[8] <= '9') ) { //e.g cheat(X,Y)
                row = str[6] - '0';
                col = str[8] - '0';
            }
            else
                printf("NO VALID COMMAND!\n");

            cheat(row-1,col-1);
            }
            else if(!strcmp(str, "exit")) {
                if(!end_game())
                return 0;
            }    
        }
    }  
        return 0;
}