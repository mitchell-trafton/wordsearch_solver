//contains functions for filling the row/colum/dig vectors within the ws_board class

#include "wordsearch.h"
#include <iostream>

//local functions//////////////////////////////////////////////////////////
enum insertType {ROW, COLUM, DRDIAG, DLDIAG};//used to indicate a row/colum/diag vector
void insert_element
    (std::vector<std::vector<std::vector<letterData>::iterator>>& insertTo,
    int insertAt, insertType inType, std::vector<letterData>::iterator& element, bool increment, int y = -1){
        //inserts an iterator into the specified vector at the specified index
        //increment=true if iterator increments afterwards, false if decrements
        //y only needs a value if a row is passed in
        insertTo[insertAt].push_back(element);
        switch (inType){
        case ROW:
            element->rowX = insertAt;
            element->rowY = y;
            break;
        case COLUM:
            element->columX = insertAt;
            element->columY = insertTo[insertAt].size() - 1;
            break;
        case DRDIAG:
            element->DRdiagX = insertAt;
            element->DRdiagY = insertTo[insertAt].size() - 1;
            break;
        case DLDIAG:
            element->DLdiagX = insertAt;
            element->DLdiagY = insertTo[insertAt].size() - 1;
            break;
        }
        if (increment) ++element;
        else --element;
    }

//class functions//////////////////////////////////////////////////////////
void ws_board::set_row(std::vector<letterData>::iterator letterIT, int rowNum){
    rows.resize(rows.size() + 1);
    
    for (size_t i = 0; i < w; ++i){
        insert_element(rows, rowNum, ROW, letterIT, true, i);
    }
}

void ws_board::adjust_clums(std::vector<letterData>::iterator letterIT, int rowNum){
    if (rowNum == 0){//size colums vector appropriately if this is the first row
        colums.resize(w);
    }

    for (size_t i = 0; i < w; ++i){
        insert_element(colums, i, COLUM, letterIT, true);
    }
}

void ws_board::adjust_diag(std::vector<letterData>::iterator letterIT, int rowNum){
    std::vector<letterData>::iterator letterITrev = letterIT + (w - 1);//reverse of letterIT, used for DLdiag, begins at end of row
    
    if (rowNum == 0){//new diag rows are created for each letter in the first horizontal row
        for (size_t i = 0; i < w; ++i){
            //DRdiag
            DRdiag.resize(DRdiag.size() + 1);
            insert_element(DRdiag, i, DRDIAG, letterIT, true);
            //DLdiag
            DLdiag.resize(DLdiag.size() + 1);
            insert_element(DLdiag, i, DLDIAG, letterITrev, false);
        }        
    }
    else{
        //create new DR and DL row for first and last letters in each line, respectively
        //DRdiag
        DRdiag.resize(DRdiag.size() + 1);
        insert_element(DRdiag, rowNum + w - 1, DRDIAG, letterIT, true);
        //DLdiag
        DLdiag.resize(DLdiag.size() + 1);
        insert_element(DLdiag, rowNum + w - 1, DLDIAG, letterITrev, false);

        //which diagonal rows to insert the next letters into depends on their particular
        //horizontal row
        //
        //if the horizontal row number (base 0) is less than the width of the puzzle, the diagonal
        //row to insert each subsequent letter into will be one one less than the previous, 
        //up until the number of the diagonal row is greater than the width, after that, 
        //each letter wil be inserted into each diagonal row in ascending order starting
        //with row 0, lasting until the end of the horizontal row
        //
        //if the horizontal row number (base 0) is greater than or equal to the puzzle's width,
        //the diagonal row to insert each subsequent letter into will be one less than the
        //previous, lasting until the end of the horizontal row
        for (size_t i = 1; (i <= (rowNum - 1)) && (i < w); ++i){
            //DRdiag
            insert_element(DRdiag, (rowNum + w - 1) - i, DRDIAG, letterIT, true);
            //DLdiag
            insert_element(DLdiag, (rowNum + w - 1) - i, DLDIAG, letterITrev, false);
        }
        if (rowNum < w){
            for (size_t i = rowNum; i < w; ++i){
                //DRdiag
                insert_element(DRdiag, i - rowNum, DRDIAG, letterIT, true);
                //DLdiag
                insert_element(DLdiag, i - rowNum, DLDIAG, letterITrev, false);
            }
        }
    }
}