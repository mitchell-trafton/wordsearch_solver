#include <iostream>
#include "board/wordsearch.h"
#include "board/wordsearch.cpp"
#include "board/rcd.cpp"

int main(){
    //declair vars
    ws_board* board;//wordsearch board object
    std::vector<std::string> words;//stores words
    std::vector<std::string> notFound;//words not found in puzzle
    int wordLen;//number of words
    int w, h;//width and height of puzzl

    //collect length and width and save to board
    std::cout << "Width: ";
    std::cin >> w;
    std::cout << "Height: ";
    std::cin >> h;
    board = new ws_board(w, h);

    //fill board with letters
    std::cout << "\nEnter the letters for each line with no spaces:\n";
    board->fill_board();

    //collect words
    std::cout << "\nHow many words?: ";
    std::cin >> wordLen;
    for (size_t i = 1; i <= wordLen; ++i){
        std::string wordIN;//user input for word

        std::cout << "Word " << i << ": ";
        std::cin >> wordIN;
        while (wordIN.length() <= 1){
            std::cout << "Words must be atleast 2 characters long. Try Again, or enter '\\\\' to skip word.\n:";
            std::cin >> wordIN;
        }
        if (wordIN == "\\\\") continue;
        words.push_back(wordIN);
    }

    //find words and put words not found in the notFound in the notFound vector
    std::cout << "\nFinding words...\n";
    for (std::string w : words){
        if (!board->find_word(w)){
            notFound.push_back(w);
        }
    }

    board->print_board();
    if (notFound.size() > 0){
        std::cout << "\nNot Found: \n";
        for (std::string n : notFound){
            std::cout << n << "\n";
        }
    }
}