#ifndef WSBOARD_H
#define WSBOARD_H

#include <vector>
#include <iostream>
#include <typeinfo>
#include <windows.h>

enum color{RED, YELLOW, NONE};
struct letterData {//stores a letter along with it's index within the row/colum/diag vectors
    char letter;//letter
    int rowX, rowY;//row index
    int columX, columY;//comum index
    int DRdiagX, DRdiagY;//DRdiag index
    int DLdiagX, DLdiagY;//DLdiag index
    color colorMark = NONE;//RED if first letter of a word, YELLOW if non-first letter of a word
};

enum dir{LEFT, RIGHT, UP, DOWN, DR, DL, UR, UL};//used to specify a direction on the puzzle board

class ws_board{
private:
    int w, h;//width and height of the puzzle

    std::vector<letterData> letters;//stores the individual letters/characters in whe wordsearch problem
    int sz;//size of letters vector

    std::vector<std::vector <std::vector<letterData>::iterator>> rows;//a vector of vectors representing each row in the wordsearch puzzle, each containing iterators to its respective contents in the letters vector
    std::vector<std::vector <std::vector<letterData>::iterator>> colums;//a vector of vectors representing each colum in the wordsearch puzzle, each containing iterators to its respective contents in the letters vector
    std::vector<std::vector <std::vector<letterData>::iterator>> DRdiag;//a vector of vectors representing each downwards-right diagonal row in the wordsearch puzzle, each containing iterators to its respective contents in the letters vector
    std::vector<std::vector <std::vector<letterData>::iterator>> DLdiag;//a vector of vectors representing each downwards-left diagonal row in the wordsearch puzzle, each containing iterators to its respective contents in the letters vector

    void set_row(std::vector<letterData>::iterator letter, int rowNum);//adds a row to the rows vector using specified row number, and fills it starting at the passed in itterator
    void adjust_clums(std::vector<letterData>::iterator letter, int rowNum);//adds elements to the colums vector using the iterator to the first character in a row and moving forward
    void adjust_diag(std::vector<letterData>::iterator letter, int rowNum);//adds elements to DRdiag and DL diag vectors using the iterator to the first character in a row and it's row number and moving forward

    bool check_direction(letterData& letter, dir direction, std::string word);//checks letters in a specific direction, returns true if specified word was found

    void set_color (int c){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
    }
public:
    ws_board(int wi, int hi);
    void fill_board();
    
    bool find_word(std::string word);//finds word within the puzzle, marking the first letter to be colored red, and the rest yellow; returns true if word was forund, false if otherwise

    void print_board();//prints board with found words colored appropriately

    void test(){//for debugging purposes only
        std::cout << letters.size();
    }
};

#endif // WSBOARD_H