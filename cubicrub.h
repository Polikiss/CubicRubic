//
// Created by Полина Шевцова on 25.05.23.
//

#ifndef CUBICRUBIC_CUBICRUB_H
#define CUBICRUBIC_CUBICRUB_H
#include "side.h"
#include <fstream>

enum Position{
    up = 0,
    front = 1,
    right = 2,
    back = 3,
    left = 4,
    down = 5,
};

class CubicRubic{
private:
    std::ifstream input;
    void MakeSolveSides(){
        cubic[up] = Side(yellow, &cubic[front], &cubic[right], &cubic[back], &cubic[left]);
        cubic[left] = Side (green, &cubic[down], &cubic[front], &cubic[up], &cubic[back]);
        cubic[front] = Side(orange, &cubic[down], &cubic[right], &cubic[up], &cubic[left]);
        cubic[right] = Side(blue, &cubic[down], &cubic[back], &cubic[up], &cubic[front]);
        cubic[down] = Side(white, &cubic[back], &cubic[right], &cubic[front], &cubic[left]);
        cubic[back] = Side(red, &cubic[up], &cubic[left], &cubic[down], &cubic[right]);
    }
    void ReadInputSIdes(){
        cubic = new Side[6];
        int** inputSide = new int*[3];
        int** inputSide1 = new int*[3];
        int** inputSide2 = new int*[3];
        int** inputSide3 = new int*[3];
        for(int i = 0; i < 3; i++){
            inputSide[i] = new int[3];
            inputSide1[i] = new int[3];
            inputSide2[i] = new int[3];
            inputSide3[i] = new int[3];
        }
        ReadSide(inputSide, input);
        cubic[up] = Side(inputSide, &cubic[front], &cubic[right], &cubic[back], &cubic[left]);
        Read3Side(inputSide1, inputSide2, inputSide3, input);
        cubic[left] = Side(inputSide1, &cubic[down], &cubic[front], &cubic[up], &cubic[back]);
        cubic[front] = Side(inputSide2, &cubic[down], &cubic[right], &cubic[up], &cubic[left]);
        cubic[right] = Side(inputSide3, &cubic[down], &cubic[back], &cubic[up], &cubic[front]);
        ReadSide(inputSide, input);
        cubic[down] = Side(inputSide, &cubic[back], &cubic[right], &cubic[front], &cubic[left]);
        ReadBackSide(inputSide, input);
        cubic[back] = Side (inputSide, &cubic[up], &cubic[left], &cubic[down], &cubic[right]);

        for(int i = 0; i < 3; i++){
            delete [] inputSide[i];
            delete [] inputSide1[i];
            delete [] inputSide2[i];
            delete [] inputSide3[i];
        }
        delete []inputSide;
        delete [] inputSide1;
        delete [] inputSide2;
        delete [] inputSide3;

    }
    void ReadBackSide(int **input_side, std::ifstream& input){
        char c = ' ';
        for(int i = 2; i > -1; i--){
            for(int j = 0; j < 3; j++){
                while(c == ' ' || c == '\n'){
                    input.get(c);
                }
                input_side[i][j] = ChangeToNum(c);
                c = ' ';
            }
        }
    }
    void Read3Side(int **input_side1, int **input_side2, int **input_side3, std::ifstream& input){
        char c = ' ';
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                while(c == ' ' || c == '\n'){
                    input.get(c);
                }
                input_side1[i][j] = ChangeToNum(c);
                c = ' ';
            }
            for(int j = 0; j < 3; j++){
                while(c == ' ' || c == '\n'){
                    input.get(c);
                }
                input_side2[i][j] = ChangeToNum(c);
                c = ' ';
            }
            for(int j = 0; j < 3; j++){
                while(c == ' ' || c == '\n'){
                    input.get(c);
                }
                input_side3[i][j] = ChangeToNum(c);
                c = ' ';
            }
        }
    }
    void ReadSide(int **input_side, std::ifstream& input){
        char c = ' ';
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                while(c == ' ' || c == '\n'){
                    input.get(c);
                }
                input_side[i][j] = ChangeToNum(c);
                c = ' ';
            }


        }
    }
    void ChooseMove(int num){
        switch(num){
            case 0:{
                R();
                return;
                break;
            }case 1:{
                R_();
                return;
                break;
            }case 2:{
                L();
                return;
                break;
            }case 3:{
                L_();
                return;
                break;
            }case 4:{
                U();
                return;
                break;
            }case 5:{
                U_();
                return;
                break;
            }case 6: {
                D();
                return;
                break;
            }case 7: {
                D_();
                return;
                break;
            }case 8: {
                F();
                return;
                break;
            }case 9: {
                F_();
                return;
                break;
            }case 10: {
                B();
                return;
                break;
            }case 11: {
                B_();
                return;
                break;
            }

        }
    }
    void CorrectCubic(){
        int redCol = 0;
        int blueCol = 0;
        int yellCol = 0;
        int oranCol  = 0;
        int whitCol = 0;
        int greenCol = 0;
    }

public:
    Side* cubic;
    CubicRubic(){
        output.open("output.txt");
        if(!output.is_open()){
            std::cout<< "Wrong output file path";
            exit(154);
        }
        cubic = new Side[6];
        MakeSolveSides();
    }
    CubicRubic(bool flag){
        input.open("input.txt");
        if(!input.is_open()){
            std::cout<< "Wrong input file path";
            exit(168);
        }
        output.open("output.txt");
        if(!output.is_open()){
            std::cout<< "Wrong output file path";
            exit(173);
        }
        ReadInputSIdes();
        input.close();
    }

    void print (){
        std::string s = "      ";
        cubic[up].print(s, output);
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                output << ChangeToLett(cubic[left].side[i][j]) << " ";
            }
            for(int j = 0; j < 3; j++){
                output << ChangeToLett(cubic[front].side[i][j]) << " ";
            }

            for(int j = 0; j < 3; j++){
                output << ChangeToLett(cubic[right].side[i][j]) << " ";
            }
            output << '\n';
        }
        cubic[down].print(s, output);
        cubic[back].printBack(s, output);
        output <<  "\n";
    }
    void R(){
        Side* s = &cubic[front];
        int *cur_edge = new int[3];
        int* next_edge = new int[3];
        s->right_side->TurnRight();
        Side* sDown = s->up_side;
        for(int i =0; i< 3; i++){
            cur_edge[i] = s->side[i][2];
        }
        for(int j = 0; j < 4; j++){
            for(int i =0; i< 3; i++){
                next_edge[i] = sDown->side[i][2];
            }
            if(sDown == &cubic[back]){
                std::swap(next_edge[0], next_edge[2]);
                std::swap(cur_edge[0], cur_edge[2]);
            }
            for(int i = 0; i < 3; i++){
                sDown->side[i][2] = cur_edge[i];
            }
            for(int i = 0; i < 3; i++){
                cur_edge[i] = next_edge[i];
            }
            s = sDown;
            sDown = s->up_side;
        }

        delete [] cur_edge;
        delete [] next_edge;
    }
    void R_(){
        Side* s = &cubic[front];
        int *cur_edge = new int[3];
        int* next_edge = new int[3];
        s->right_side->TurnLeft();
        Side* sDown = s->down_side;
        for(int i =0; i< 3; i++){
            cur_edge[i] = s->side[i][2];
        }
        for(int j = 0; j < 4; j++){
            for(int i =0; i< 3; i++){
                next_edge[i] = sDown->side[i][2];
            }
            if(sDown == &cubic[back]){
                std::swap(next_edge[0], next_edge[2]);
                std::swap(cur_edge[0], cur_edge[2]);
            }
            for(int i = 0; i < 3; i++){
                sDown->side[i][2] = cur_edge[i];
            }
            for(int i = 0; i < 3; i++){
                cur_edge[i] = next_edge[i];
            }
            s = sDown;
            sDown = s->down_side;
        }

        delete [] cur_edge;
        delete [] next_edge;
    }
    void L(){
        Side* s = &cubic[front];
        int *cur_edge = new int[3];
        int* next_edge = new int[3];
        s->left_side->TurnRight();
        Side* sDown = s->down_side;
        for(int i =0; i< 3; i++){
            cur_edge[i] = s->side[i][0];
        }
        for(int j = 0; j < 4; j++){
            for(int i =0; i< 3; i++){
                next_edge[i] = sDown->side[i][0];
            }
            if(sDown == &cubic[back]){
                std::swap(next_edge[0], next_edge[2]);
                std::swap(cur_edge[0], cur_edge[2]);
            }
            for(int i = 0; i < 3; i++){
                sDown->side[i][0] = cur_edge[i];
            }
            for(int i = 0; i < 3; i++){
                cur_edge[i] = next_edge[i];
            }
            s = sDown;
            sDown = s->down_side;
        }

        delete [] cur_edge;
        delete [] next_edge;
    }
    void L_(){
        Side* s = &cubic[front];
        int *cur_edge = new int[3];
        int* next_edge = new int[3];
        s->left_side->TurnLeft();
        Side* sDown = s->up_side;
        for(int i =0; i< 3; i++){
            cur_edge[i] = s->side[i][0];
        }
        for(int j = 0; j < 4; j++){
            for(int i =0; i< 3; i++){
                next_edge[i] = sDown->side[i][0];
            }
            if(sDown == &cubic[back]){
                std::swap(next_edge[0], next_edge[2]);
                std::swap(cur_edge[0], cur_edge[2]);
            }
            for(int i = 0; i < 3; i++){
                sDown->side[i][0] = cur_edge[i];
            }
            for(int i = 0; i < 3; i++){
                cur_edge[i] = next_edge[i];
            }
            s = sDown;
            sDown = s->up_side;
        }
        delete [] cur_edge;
        delete [] next_edge;
    }
    void U(){
        Side* s = &cubic[front];
        int *cur_edge = new int[3];
        int* next_edge = new int[3];
        s->up_side->TurnRight();
        Side* sLeft = s->left_side;
        for(int i =0; i< 3; i++){
            cur_edge[i] = s->side[0][i];
        }
        for(int j = 0; j < 4; j++){
            for(int i =0; i< 3; i++){
                next_edge[i] = sLeft->side[0][i];
            }
            if(sLeft == &cubic[back]){
                std::swap(next_edge[0], next_edge[2]);
                std::swap(cur_edge[0], cur_edge[2]);
            }
            for(int i = 0; i < 3; i++){
                sLeft->side[0][i] = cur_edge[i];
            }
            for(int i = 0; i < 3; i++){
                cur_edge[i] = next_edge[i];
            }
            s = sLeft;
            sLeft = s->left_side;
        }
        delete [] cur_edge;
        delete [] next_edge;
    }
    void U_(){
        Side* s = &cubic[front];
        int *cur_edge = new int[3];
        int* next_edge = new int[3];
        s->up_side->TurnLeft();
        Side* sRight = s->right_side;
        for(int i =0; i< 3; i++){
            cur_edge[i] = s->side[0][i];
        }
        for(int j = 0; j < 4; j++){
            for(int i =0; i< 3; i++){
                next_edge[i] = sRight->side[0][i];
            }
            if(sRight == &cubic[back]){
                std::swap(next_edge[0], next_edge[2]);
                std::swap(cur_edge[0], cur_edge[2]);
            }
            for(int i = 0; i < 3; i++){
                sRight->side[0][i] = cur_edge[i];
            }
            for(int i = 0; i < 3; i++){
                cur_edge[i] = next_edge[i];
            }
            s = sRight;
            sRight = s->right_side;
        }

        delete [] cur_edge;
        delete [] next_edge;
    }
    void D(){
        Side* s = &cubic[front];
        int *cur_edge = new int[3];
        int* next_edge = new int[3];
        s->down_side->TurnRight();
        Side* sRight = s->right_side;
        for(int i =0; i< 3; i++){
            cur_edge[i] = s->side[2][i];
        }
        for(int j = 0; j < 4; j++){
            for(int i =0; i< 3; i++){
                next_edge[i] = sRight->side[2][i];
            }
            if(sRight == &cubic[back]){
                std::swap(next_edge[0], next_edge[2]);
                std::swap(cur_edge[0], cur_edge[2]);
            }
            for(int i = 0; i < 3; i++){
                sRight->side[2][i] = cur_edge[i];
            }
            for(int i = 0; i < 3; i++){
                cur_edge[i] = next_edge[i];
            }
            s = sRight;
            sRight = s->right_side;
        }
        delete [] cur_edge;
        delete [] next_edge;
    }
    void D_(){
        Side* s = &cubic[front];
        int *cur_edge = new int[3];
        int* next_edge = new int[3];
        s->down_side->TurnLeft();
        Side* sRight = s->left_side;
        for(int i =0; i< 3; i++){
            cur_edge[i] = s->side[2][i];
        }
        for(int j = 0; j < 4; j++){
            for(int i =0; i< 3; i++){
                next_edge[i] = sRight->side[2][i];
            }
            if(sRight == &cubic[back]){
                std::swap(next_edge[0], next_edge[2]);
                std::swap(cur_edge[0], cur_edge[2]);
            }
            for(int i = 0; i < 3; i++){
                sRight->side[2][i] = cur_edge[i];
            }
            for(int i = 0; i < 3; i++){
                cur_edge[i] = next_edge[i];
            }
            s = sRight;
            sRight = s->left_side;
        }
        delete [] cur_edge;
        delete [] next_edge;
    }
    void B(){
        Side* s = &cubic[back];
        int *cur_edge = new int[3];
        int* next_edge = new int[3];
        s->TurnLeft();
        for(int i =0; i < 3; i++){
            cur_edge[i] = cubic[right].side[i][2];
        }
        for(int i =0; i < 3; i++){
            next_edge[i] = cubic[up].side[0][i];
        }
        for(int i =0; i < 3; i++){
            cubic[up].side[0][i] =  cur_edge[i];
        }


        for(int i =0; i < 3; i++){
            cur_edge[i] = next_edge[i];
        }
        for(int i =0; i < 3; i++){
            next_edge[i] = cubic[left].side[i][0];
        }
        std::swap(cur_edge[0], cur_edge[2]);
        for(int i =0; i < 3; i++){
            cubic[left].side[i][0] = cur_edge[i];
        }


        for(int i =0; i < 3; i++){
            cur_edge[i] = next_edge[i];
        }
        for(int i =0; i < 3; i++){
            next_edge[i] = cubic[down].side[2][i];
        }
        for(int i =0; i < 3; i++){
            cubic[down].side[2][i] = cur_edge[i];
        }

        for(int i =0; i < 3; i++){
            cur_edge[i]  = next_edge[i];
        }
        std::swap(cur_edge[0], cur_edge[2]);
        for(int i =0; i < 3; i++){
            cubic[right].side[i][2] = cur_edge[i];
        }
        delete [] cur_edge;
        delete [] next_edge;
    }
    void B_(){
        Side* s = &cubic[back];
        int *cur_edge = new int[3];
        int* next_edge = new int[3];
        s->TurnRight();
        for(int i =0; i < 3; i++){
            cur_edge[i] = cubic[right].side[i][2];
        }
        for(int i =0; i < 3; i++){
            next_edge[i] = cubic[down].side[2][i];
        }
        std::swap(cur_edge[0], cur_edge[2]);
        for(int i =0; i < 3; i++){
            cubic[down].side[2][i] = cur_edge[i];
        }



        for(int i =0; i < 3; i++){
            cur_edge[i] = next_edge[i];
        }
        for(int i =0; i < 3; i++){
            next_edge[i] = cubic[left].side[i][0];
        }
        for(int i =0; i < 3; i++){
            cubic[left].side[i][0] = cur_edge[i];
        }


        for(int i =0; i < 3; i++){
            cur_edge[i] = next_edge[i];
        }
        for(int i =0; i < 3; i++){
            next_edge[i] = cubic[up].side[0][i];
        }
        std::swap(cur_edge[0], cur_edge[2]);
        for(int i =0; i < 3; i++){
            cubic[up].side[0][i] =  cur_edge[i];
        }

        for(int i =0; i < 3; i++){
            cur_edge[i]  = next_edge[i];
        }
        for(int i =0; i < 3; i++){
            cubic[right].side[i][2] = cur_edge[i];
        }
        delete [] cur_edge;
        delete [] next_edge;
    }
    void F(){
        Side* s = &cubic[front];
        int *cur_edge = new int[3];
        int* next_edge = new int[3];
        s->TurnRight();
        for(int i =0; i < 3; i++){
            cur_edge[i] = cubic[right].side[i][0];
        }
        for(int i =0; i < 3; i++){
            next_edge[i] = cubic[down].side[0][i];
        }
        std::swap(cur_edge[0], cur_edge[2]);
        for(int i =0; i < 3; i++){
            cubic[down].side[0][i] = cur_edge[i];
        }



        for(int i =0; i < 3; i++){
            cur_edge[i] = next_edge[i];
        }
        for(int i =0; i < 3; i++){
            next_edge[i] = cubic[left].side[i][2];
        }
        for(int i =0; i < 3; i++){
            cubic[left].side[i][2] = cur_edge[i];
        }


        for(int i =0; i < 3; i++){
            cur_edge[i] = next_edge[i];
        }
        for(int i =0; i < 3; i++){
            next_edge[i] = cubic[up].side[2][i];
        }
        std::swap(cur_edge[0], cur_edge[2]);
        for(int i =0; i < 3; i++){
            cubic[up].side[2][i] =  cur_edge[i];
        }

        for(int i =0; i < 3; i++){
            cur_edge[i]  = next_edge[i];
        }
        for(int i =0; i < 3; i++){
            cubic[right].side[i][0] = cur_edge[i];
        }
        delete [] cur_edge;
        delete [] next_edge;
    }
    void F_(){
        Side* s = &cubic[front];
        int *cur_edge = new int[3];
        int* next_edge = new int[3];
        s->TurnLeft();
        for(int i =0; i < 3; i++){
            cur_edge[i] = cubic[right].side[i][0];
        }
        for(int i =0; i < 3; i++){
            next_edge[i] = cubic[up].side[2][i];
        }
        for(int i =0; i < 3; i++){
            cubic[up].side[2][i] =  cur_edge[i];
        }



        for(int i =0; i < 3; i++){
            cur_edge[i] = next_edge[i];
        }
        for(int i =0; i < 3; i++){
            next_edge[i] = cubic[left].side[i][2];
        }
        std::swap(cur_edge[0], cur_edge[2]);
        for(int i =0; i < 3; i++){
            cubic[left].side[i][2] = cur_edge[i];
        }


        for(int i =0; i < 3; i++){
            cur_edge[i] = next_edge[i];
        }
        for(int i =0; i < 3; i++){
            next_edge[i] = cubic[down].side[0][i];
        }
        for(int i =0; i < 3; i++){
            cubic[down].side[0][i] = cur_edge[i];
        }


        for(int i =0; i < 3; i++){
            cur_edge[i]  = next_edge[i];
        }
        std::swap(cur_edge[0], cur_edge[2]);
        for(int i =0; i < 3; i++){
            cubic[right].side[i][0] = cur_edge[i];
        }
        delete [] cur_edge;
        delete [] next_edge;
    }

    void R(int side){
        if(side == right){
            B();
            return;
        }else if(side == left){
            F();
            return;
        }
        else if(side == back){
            L();
            return;
        }
        else if(side == front || side == up || side == down){
            R();
            return;
        }
    }
    void R_(int side){
        if(side == right){
            B_();
            return;
        }else if(side == left){
            F_();
            return;
        }else if(side == back){
            L_();
            return;
        }
        else if(side == front || side == up || side == down){
            R_();
            return;
        }
    }
    void L(int side){
        if(side == right){
            F();
            return;
        }else if(side == left){
            B();
            return;
        }else if(side == back){
            R();
            return;
        }
        else if(side == front || side == up || side == down){
            L();
            return;
        }
    }
    void L_(int side){
        if(side == right){
            F_();
            return;
        }else if(side == left){
            B_();
            return;
        }else if(side == back){
            R_();
            return;
        }
        else if(side == front || side == up || side == down){
            L_();
            return;
        }
    }
    void U(int side){
        if(side == up){
            B();
            return;
        }else if(side == down){
            F();
            return;
        }
        else if(side == front || side == left || side == right || side == back){
            U();
            return;
        }
        //добавить try-catch
    }
    void U_(int side){
        if(side == up){
            B_();
            return;
        }else if(side == down){
            F_();
            return;
        }
        else if(side == front || side == left || side == right || side == back){
            U_();
            return;
        }
        //добавить try-catch
    }
    void D(int side){
        if(side == up){
            F();
            return;
        }else if(side == down){
            B();
            return;
        }
        else if(side == front || side == left || side == right || side == back){
            D();
            return;
        }
        //добавить try-catch
    }
    void D_(int side){
        if(side == up){
            F_();
            return;
        }else if(side == down){
            B_();
            return;
        }
        else if(side == front || side == left || side == right || side == back){
            D_();
            return;
        }
        //добавить try-catch
    }
    void B(int side){
        switch(side){
            case front:{
                B();
                return;
                break;
            }case back:{
                F();
                return;
                break;
            }case up:{
                D();
                return;
                break;
            }case down:{
                U();
                return;
                break;
            }case right:{
                L();
                return;
                break;
            }case left:{
                R();
                return;
                break;
            }
        }
    }
    void B_(int side){
        switch(side){
            case front:{
                B_();
                return;
                break;
            }case back:{
                F_();
                return;
                break;
            }case up:{
                D_();
                return;
                break;
            }case down:{
                U_();
                return;
                break;
            }case right:{
                L_();
                return;
                break;
            }case left:{
                R_();
                return;
                break;
            }
        }
    }
    void F(int side){
        switch(side){
            case front:{
                F();
                return;
                break;
            }case back:{
                B();
                return;
                break;
            }case up:{
                U();
                return;
                break;
            }case down:{
                D();
                return;
                break;
            }case right:{
                R();
                return;
                break;
            }case left:{
                L();
                return;
                break;
            }
        }
    }
    void F_(int side){
        switch(side){
            case front:{
                F_();
                return;
                break;
            }case back:{
                B_();
                return;
                break;
            }case up:{
                U_();
                return;
                break;
            }case down:{
                D_();
                return;
                break;
            }case right:{
                R_();
                return;
                break;
            }case left:{
                L_();
                return;
                break;
            }
        }
    }

    void PiphPaph(int side){
        R(side);
        U(side);
        R_(side);
        U_(side);
    }
    void LeftPiphPaph(int side){
        L_(side);
        U_(side);
        L(side);
        U(side);
    }
    void Random(){
        srand((unsigned) time(NULL));
        int count = rand()%40;
        for(int i = 0; i <count; i++){
            int num = rand()%12;
            ChooseMove(num);
        }
        print();
        return;
    }
    std::ofstream output;
};

#endif //CUBICRUBIC_CUBICRUB_H
