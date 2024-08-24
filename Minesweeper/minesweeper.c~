// Assignment 1 21T2 COMP1511: Minesweeper
// minesweeper.c
//
// This program was written by HARSH CHARU MURALI (z5361547)
// on 5/07/2021
//
// Version 1.0.0 (2021-06-19): Assignment released.

#include <stdio.h>
#include <stdlib.h>

// Possible square states.
#define VISIBLE_SAFE    0
#define HIDDEN_SAFE     1
#define HIDDEN_MINE     2

// The size of the starting grid.
#define SIZE              8

// The possible command codes.
#define DETECT_ROW      1
#define DETECT_SQUARE   2
#define REVEAL_CROSS    3
#define GAME_MODE       4
#define FLAG_MINE       5
#define DEFUSE          6

// Add any extra #defines here.
#define DETECT_MINES

void initialise_field(int minefield[SIZE][SIZE]);
void print_debug_minefield(int minefield[SIZE][SIZE]);

// Place your function prototyes here.

int main(void) {
    int minefield[SIZE][SIZE];
    int pairs;
    int counter = 0;
    int row1;
    int column1;
    int column_end1 = 0;
    
    initialise_field(minefield);
    printf("Welcome to minesweeper!\n");
    printf("How many mines? ");

    // TODO: Scan in the number of pairs of mines.
    scanf("%d", &pairs);

    printf("Enter pairs:\n");

    // TODO: Scan in the pairs of mines and place them on the grid.
    while (counter < pairs) {
        scanf("%d %d", &row1, &column1);
        if ((0 <= row1 && row1 <= SIZE) 
        && (0 <= column1 && column1 <= SIZE)) {
            minefield[row1][column1] = HIDDEN_MINE; 
        }
        counter = counter +1;
    }
    printf("Game Started\n");
    print_debug_minefield(minefield);


    // TODO: Scan in commands to play the game until the game ends.
    // A game ends when the player wins, loses, or enters EOF (Ctrl+D).
    // You should display the minefield after each command has been processed.
    
    int detect;    
                 
    while (scanf("%d", &detect) != EOF) { 
    
                 
        // Checks if the user inputs 1
        
        if (detect == DETECT_ROW) {

            
            scanf("%d %d %d", &row1, &column1, &column_end1);
            int count = 0;
            int i = 0;
            
            // Loops code till all the mines are detected
            
            while ((i <= column_end1-1) 
            &&(0 <= row1 && row1 <= 8) 
            && (0 <= column1 && column1 <= 8)
            && (0 <= column_end1 && column_end1 <= 8)
            && (column1 + column_end1 <9)) {
                if (minefield[row1][column1 + i] == 2 ) {
                    count++;
                }
                i++;
               
            }
           
            //Prints number of mines detected
           
            if ((0 <= row1 && row1 <= 8) 
            && (0 <= column1 && column1 <= 8)
            && (0 <= column_end1 && column_end1 <= 8)
            && (column1+i <= 8)
            && (i>0)) {
                printf("There are %d mine(s) in row %d, from column %d to %d\n", 
                count, row1, column1, column1 + i - 1);
                
                //Accounts for if coordinates are not in the map
                
            } else {
                printf("Coordinates not on map\n");
            }
            print_debug_minefield(minefield); 
        }
            
        //Checks if the user inputs 2
                            
        if (detect == DETECT_SQUARE) {
           
            int row2;
            int column2;
            int size;
            int mine = 0;
            
            
            scanf("%d %d %d", &row2, &column2, &size);
            
            // Stores maximum and minimum values for rows and columns
            
            int area = (size-1)/2;
            int column_start2 = column2 - area;
            int column_end2 = column2 + area;
            int row_start2 = row2 - area;
            int row_end2 = row2 + area;
            
            //Accounts for any discrepencies
            
            if (column_start2 < 0) {
                column_start2 = 0;
            }
            
            if (row_start2 < 0) {
                row_start2 = 0;
            }

            if (row_end2 >= SIZE) {
                row_end2 = SIZE - 1;
            }
            
            if (column_end2 >= SIZE) {
                column_end2 = SIZE - 1;
            }
            
            if ((row2 >= 0 && row2 < SIZE)
            && (column2 >= 0 && column2 < SIZE)) {
            
                // Starts checking for mines from top right corner to 
                //bottom left corner of the square
            
                int row_starting = row_start2;
                while (row_starting <= row_end2) {
                    int column_starting = column_start2;
                    while (column_starting <= column_end2) {
                        if (minefield[row_starting][column_starting] == HIDDEN_MINE) {
                            mine++;
                        }
                        column_starting++;
                    }
                    row_starting++;
                }
                
                // Results are displayed
                
                printf("There are %d mine(s) in the square centered at row %d, " 
                "column %d of size %d\n", mine, row2, column2, size); 
                print_debug_minefield(minefield);  
            } else {
                printf("Coordinates not on map\n");
                print_debug_minefield(minefield); 
            }
        }
        
                         
        
        if (detect == REVEAL_CROSS) {
        
            int row3;
            int column3;

            scanf("%d %d", &row3, &column3);
            
            // Tested code that didn't work
            /*
            
            if (row3 <= 0) {
                row3 = 0;
            }

            if (column3 <= 0) {
                column3 = 0;
            }
            
            if (row3 >= 7) {
                row3 = 7;
            }
            
            if (column3 >= 7) {
                column3 = 7;
            }
            
            int x = row3;
            int y = column3;


            while (((minefield[x][y]) == 1)
            && (y >= 0)
            && (y <= 7)
            && (0 <= x)
            && (x <= 7)) {

                // check top square
                while ((y >= 1)
                && (y <= 6)
                && (2 <= x)
                && (x <= 7)) {
                    if ((minefield[row3-2][column3-1])
                    &&(minefield[row3-2][column3])
                    &&(minefield[row3-2][column3+1])
                    &&(minefield[row3-1][column3-1])
                    &&(minefield[row3-1][column3])
                    &&(minefield[row3-1][column3+1])
                    &&(minefield[row3][column3-1])
                    &&(minefield[row3][column3])
                    &&(minefield[row3][column3+1]) != 2) {
                        (minefield[row3-1][column3]) = 0;
                    }
                }
                // check right square
                while ((y >= 0)
                && (y <= 5)
                && (1 <= x)
                && (x <= 6)) {
                    if ((minefield[row3-1][column3])
                    &&(minefield[row3-1][column3+1])
                    &&(minefield[row3-1][column3+2])
                    &&(minefield[row3][column3])
                    &&(minefield[row3][column3+1])
                    &&(minefield[row3][column3+2])
                    &&(minefield[row3+1][column3])
                    &&(minefield[row3+1][column3+1])
                    &&(minefield[row3 + 1][column3 + 2]) != 2) {
                        (minefield[row3][column3+1]) = 0;
                    }
                }
                // check bottom square
                while ((y >= 1)
                && (y <=6)
                && (0 <= x)
                && (x <= 5)) {
                    if ((minefield[row3][column3-1])
                    &&(minefield[row3][column3])
                    &&(minefield[row3][column3+1])
                    &&(minefield[row3+1][column3-1])
                    &&(minefield[row3+1][column3])
                    &&(minefield[row3+1][column3+1])
                    &&(minefield[row3+2][column3-1])
                    &&(minefield[row3+2][column3])
                    &&(minefield[row3+2][column3+1]) != 2) {
                        (minefield[row3+1][column3]) = 0;
                    }
                }
                // check left square
                while ((y >= 2)
                && (y <=7)
                && (1 <= x)
                && (x <= 6)) {
                    if ((minefield[row3-1][column3-2])
                    &&(minefield[row3-1][column3-1])
                    &&(minefield[row3-1][column3])
                    &&(minefield[row3][column3-2])
                    &&(minefield[row3][column3-1])
                    &&(minefield[row3][column3])
                    &&(minefield[row3+1][column3-2])
                    &&(minefield[row3+1][column3-1])
                    &&(minefield[row3+1][column3]) != 2) {
                        (minefield[row3][column3-1]) = 0;
                    }
                }
                if (((minefield[row3][column3]) == 1)
                && (y >= 0)
                && (y <= 8)
                && (0 <= x)
                && (x <= 8)) {
                    print_debug_minefield(minefield);
                    break;
                }
                
                else {
                    printf("Coordinates not on map\n");
                    print_debug_minefield(minefield); 
                    break;
            */
        }
    
    }
           
    return 0;
 
}       
  

// Set the entire minefield to HIDDEN_SAFE.
void initialise_field(int minefield[SIZE][SIZE]) {
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            minefield[i][j] = HIDDEN_SAFE;
            j++;
        }
        i++;
    }
}


// Print out the actual values of the minefield.
void print_debug_minefield(int minefield[SIZE][SIZE]) {
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            printf("%d ", minefield[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

 
