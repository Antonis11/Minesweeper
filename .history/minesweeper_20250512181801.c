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

void panel(void);
double select_dif(void);
void create_level(void);
void check_surround(int i, int j);
void show_level(void);

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

int main(void) {
    int win;
    double multi;

    do {
        printf("Give Rows and Columns\n");
        scanf("%d %d", &ROWS, &COLUMNS);
        if ( (ROWS * COLUMNS * 0.1 < 1) || ROWS>15 || COLUMNS>15 ) 
            printf("INVALID DIMENSIONS GIVEN!\n");
    }while( (ROWS * COLUMNS * 0.1 < 1) || ROWS>15 || COLUMNS>15 );
    multi = select_dif();
    
    panel();
    open_squares = 0;
    win = (ROWS * COLUMNS) - mine_count;
    create_level();
    

    return 0;


}