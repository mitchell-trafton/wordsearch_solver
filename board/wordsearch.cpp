#include "wordsearch.h"
#include <iostream>
#include <vector>
#include <string>

//local functions/////////////////////////////////////////////////////////////////
std::vector<letterData>::iterator load_row (int w, std::string content, std::vector<letterData>& letters, int rowNum){
    std::vector<letterData>::iterator firstInRow;//iterator to first letter in current row
    //insert first letter from row into letters vector, and save it's itterator
    letters[rowNum * w].letter = content.at(0);
    firstInRow = letters.begin() + rowNum * w;

    for (size_t i = 1; i < w; ++i){
        //load rest of chars into letters vector
        letters[rowNum * w + i].letter = content.at(i);
    }

    return firstInRow;
}

//ws_board functions//////////////////////////////////////////////////////////////
ws_board::ws_board(int wi, int hi){
    letters.resize(wi * hi);

    w = wi;
    h = hi;
    sz = wi * hi;
}

void ws_board::fill_board(){
    std::string rowContent;//stores input characters in each as a single string
    std::vector<letterData>::iterator currentChar;//stores iterator current char in letters vector that is being used
    int currentRow;//index of current row in rows vector being worked on

    for (size_t i = 0; i < h; ++i){
        std::cout << ": ";
        std::cin >> rowContent;

        while (rowContent.length() != w){
            std::cout << "There must be " << w << " letters in a row. Try again: ";
            std::cin >> rowContent;
        }
        currentChar = load_row(w, rowContent, letters, i);

        set_row(currentChar, i);
        adjust_clums(currentChar, i);
        adjust_diag(currentChar, i);
    }
}

bool ws_board::find_word(std::string word){
    //find first letter
    for (letterData l : letters){
        if (l.letter == word.at(0)){
            //if first letter found check surrounding letters
            if (check_direction(l, RIGHT, word)||
                check_direction(l, LEFT, word)||
                check_direction(l, UP, word)||
                check_direction(l, DOWN, word)||
                check_direction(l, DR, word)||
                check_direction(l, UL, word)||
                check_direction(l, DL, word)||
                check_direction(l, UR, word)) return true;
        }
    }
    return false;
}

bool ws_board::check_direction(letterData& firstLetter, dir direction, std::string word){
    std::vector<std::vector<letterData>::iterator>::iterator currentLetterIT;//iterator to iterator to current letter being checked 
    std::vector<std::vector<letterData>::iterator>* line;//line being checked from
    int increment;//1 if incrementing forward in a vector, -1 if incrementing backwards in a vector
    bool wordFound = false;//true if a word was found
    int currentLetterIN = 0;//index of current letter in word being searched for

    switch (direction){
    case RIGHT:
        currentLetterIT = rows[firstLetter.rowX].begin() + firstLetter.rowY;
        line = &rows[firstLetter.rowX];
        increment = 1;
        break;
    case LEFT:
        currentLetterIT = rows[firstLetter.rowX].begin() + firstLetter.rowY;
        line = &rows[firstLetter.rowX];
        increment = -1;
        break;
    case UP:
        currentLetterIT = colums[firstLetter.columX].begin() + firstLetter.columY;
        line = &colums[firstLetter.columX];
        increment = -1;
        break;
    case DOWN:
        currentLetterIT = colums[firstLetter.columX].begin() + firstLetter.columY;
        line = &colums[firstLetter.columX];
        increment = 1;
        break;
    case DR:
        currentLetterIT = DRdiag[firstLetter.DRdiagX].begin() + firstLetter.DRdiagY;
        line = &DRdiag[firstLetter.DRdiagX];
        increment = 1;
        break;
    case UL:
        currentLetterIT = DRdiag[firstLetter.DRdiagX].begin() + firstLetter.DRdiagY;
        line = &DRdiag[firstLetter.DRdiagX];
        increment = -1;
        break;
    case DL:
        currentLetterIT = DLdiag[firstLetter.DLdiagX].begin() + firstLetter.DLdiagY;
        line = &DLdiag[firstLetter.DLdiagX];
        increment = 1;
        break;
    case UR:
        currentLetterIT = DLdiag[firstLetter.DLdiagX].begin() + firstLetter.DLdiagY;
        line = &DLdiag[firstLetter.DLdiagX];
        increment = -1;
        break;
    }

    //check letters in specified drection to see if specified word can be formed
    currentLetterIT += increment;
    while(!((currentLetterIT < line->begin()) || (currentLetterIT == line->end()))){//don't let the letter iterator being checked be outside it's respective vector
        currentLetterIN++;
        
        if((*currentLetterIT)->letter != word.at(currentLetterIN)){//if a letter doesn't match its corresponding char in word, break whle loop
            break;
        }
        
        else if (currentLetterIN == (word.length() - 1)){//word found by virtue of length of word being reached without troubles
            currentLetterIT -= (word.length() - 1) * increment;
            (*currentLetterIT)->colorMark = RED;
            for (size_t i = 1; i < word.length(); ++i){
                currentLetterIT += increment;
                if ((*currentLetterIT)->colorMark != RED) (*currentLetterIT)->colorMark = YELLOW;
            }
            return true;//word found
        }

        currentLetterIT += increment;
    }
    return false;//word not found
}

void ws_board::print_board(){
    int lineCtr = 0;//counts number of elements in line
    for (letterData l : letters){
        if (l.colorMark == RED) set_color(4);
        else if (l.colorMark == YELLOW) set_color(6);

        std::cout << l.letter << " ";

        set_color(7);

        lineCtr++;
        if (lineCtr >= w){
            lineCtr = 0;
            std::cout << std::endl;
        }
    }
}