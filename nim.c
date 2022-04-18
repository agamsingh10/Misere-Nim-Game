#include "nim.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int *new_board(int board_size){
    int *boardArray = malloc(sizeof(int) * board_size); //mallocing an array of board_size integers

    if (boardArray == NULL) {             //if malloc fails, print error message
        fprintf(stderr, "ERROR\n");
        exit(-1);
    }
    return boardArray;                         //return the pointer to  the array
}

struct node *mk_nim_hash(int max_hash, int board_size, int *start_board){
    struct node *initialize = malloc(sizeof(struct node) * max_hash); //  mallocing an array of size max_hash struct node

    if (initialize == NULL){               //if malloc fails, print error message

        fprintf(stderr, "ERROR\n");
        exit(-1);
    }


    for (int i = 0; i < max_hash; i++) {      // initialise all the variables

        initialize[i].moves = -1;
        initialize[i].nimsum = -1;
        initialize[i].move = NULL;
        initialize[i].board = hash2board(board_size, start_board, i);
    }
    return initialize;
}

//function to free the memory of board array
void free_board(int *board){
    free(board);
}

void free_nim_hash(int max_hash, struct node *nim_hash){

    //free each move array and each board array
    for (int i = 0; i < max_hash; i++) {
        free(nim_hash[i].move);
        free(nim_hash[i].board);
    }
    free(nim_hash);                                 //free nim_hash
}

//Function to create a new board
int *board_from_argv(int board_size, char **argv){
    int *new_board = malloc(sizeof(int) *board_size);

    for (int i = 0; i < board_size; i++) {
        new_board[i] = atoi(argv[i]);            //iniitalizing it with the integer equivalents of string array argv
    }
    return new_board;
}

int *copy_board(int board_size, int *board){
    //create the copy the original board
    int *initialisedBoard = new_board(board_size);

    for (int i = 0; i < board_size; i++)    {       //initialising each value one by one with board values
        initialisedBoard[i] = board[i];
    }
    return initialisedBoard;                       //return the new board
}

int game_over(int board_size, int *board){
    int count = 0;

    for (int i = 0; i < board_size; i++) {
        count = count + board[i];           //count the total matches present in the board
    }
    if (count == 1) {                          //return 1 if one match is left

        return 1;
    }
    else{
    return 0;
  }
}

void join_graph(struct node *nim_hash, int hash, int board_size, int *start_board)
{
    if (nim_hash[hash].moves != -1)         //check whether the moves variable is -1 and exit if completed
    {
        return;
    }
        int totalMoves = 0, moove = 0;                                                       //variable for incrementing move
        int * tempCopy = NULL;

        for (int i = 0; i <= board_size - 1; i++)  //get total number of possible moves that can be made for the given board
        {
            totalMoves = totalMoves + nim_hash[hash].board[i];
        }
        nim_hash[hash].moves = totalMoves;
        nim_hash[hash].move = malloc(sizeof(struct move) * totalMoves);     //allocate a move array within the node to store those moves

        for (int row = 0; row < board_size; row++)
        {
            for (int j = 1; j <=nim_hash[hash].board[row]; j++)
            {
                nim_hash[hash].move[moove].matches = j ;                    //initialization with appropriate match
                nim_hash[hash].move[moove].row = row;                       //initialization with appropriate row
                tempCopy = copy_board(board_size, nim_hash[hash].board);          //store the temporary copy
                tempCopy[row] =   tempCopy[row]-j;                                    //remove j matches
                nim_hash[hash].move[moove].hash = board2hash(board_size, start_board, tempCopy);
                moove++;                                                                        //increment the move variable
                nim_hash[hash].nimsum = compute_nimsum(board_size, nim_hash[hash].board);      //nimsum is assigned the sum value that is calculated
                join_graph(nim_hash, board2hash(board_size, start_board, tempCopy), board_size, start_board);  //calling itself recursively on each destination node
            }
        }

    }


int compute_nimsum(int board_size, int *board)
{
    int flag = 0, nimSum = 0;
    for (int i = 0; i < board_size; i++){    //interate through the board array
      nimSum  = nimSum  ^ board[i];
      }

    for (int j = 0; j < board_size; j++){    //interate through the board array

        if (board[j] > 1){                  //if number of matches > 1

            flag = 1;                        //if any one row with matches greater than 1 is found
            break;
        }
    }
      if (flag == 0){
        if (nimSum  != 0){
            nimSum  = 0;
        }
        else {
          nimSum  = 1;
        }
    }
    return nimSum ;
}
