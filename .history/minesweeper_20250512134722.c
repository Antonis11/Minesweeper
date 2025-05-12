#include <stdio.h>

int ROWS,COLUMNS;
int mine_count;

double select_dif(void);

double select_dif(void)
{
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

int main(void) {
    double multi;

    do {
        printf("Give Rows and Columns\n");
        scanf("%d %d", &ROWS, &COLUMNS);
        if ( (ROWS * COLUMNS * 0.1 < 1) || ROWS>15 || COLUMNS>15 ) 
            printf("INVALID DIMENSIONS GIVEN!\n");
    }while( (ROWS * COLUMNS * 0.1 < 1) || ROWS>15 || COLUMNS>15 );
    multi = select_dif();

    return 0;

}