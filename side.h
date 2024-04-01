//
// Created by Полина Шевцова on 25.05.23.
//

#ifndef CUBICRUBIC_SIDE_H
#define CUBICRUBIC_SIDE_H
#include <iostream>
#include <fstream>
enum Color {
    white = 0,
    red = 1,
    blue = 2,
    green = 3,
    yellow = 4,
    orange = 5,
    undef = -1,
};
int ChangeToNum(char c){
    switch(c){
        case 'w':{
            return 0;
            break;
        }case 'r':{
            return 1;
            break;
        }case 'b':{
            return 2;
            break;
        }case 'g':{
            return 3;
            break;
        }case 'y':{
            return 4;
            break;
        }case 'o':{
            return 5;
            break;
        } default:
            return -1;
            break;
    }
}
char ChangeToLett(int num){
    switch(num){
        case 0:{
            return 'w';
            break;
        }case 1:{
            return 'r';
            break;
        }case 2:{
            return 'b';
            break;
        }case 3:{
            return 'g';
            break;
        }case 4:{
            return 'y';
            break;
        }case 5:{
            return 'o';
            break;
        } default:
            return '*';
            break;
    }
}
class Side{
private:
    int n = 3;
public:
    Side* down_side;
    Side* right_side;
    Side* up_side;
    Side* left_side;
    int side[3][3];
    Side(){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                side[i][j] = undef;
            }
        }
    }
    Side(int clr,  Side* down, Side* right, Side* up, Side* left){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                side[i][j] = clr;
            }
        }
        down_side = down;
        right_side = right;
        up_side = up;
        left_side = left;

    }
    Side(int **clrs, Side* down, Side* right, Side* up, Side* left){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                side[i][j] = clrs[i][j];
            }
        }
        down_side = down;
        right_side = right;
        up_side = up;
        left_side = left;
    }
    void print(std::string s, std::ofstream& output){
        for(int i = 0; i < 3; i++){
            output << s;
            for(int j = 0; j < 3; j++){
                output << ChangeToLett(side[i][j]) << " ";
            }
            output << '\n';
        }
    }
    void printBack(std::string s, std::ofstream& output){
        for(int i = 2; i > -1; i--){
            output << s;
            for(int j = 0; j < 3; j++){
                output << ChangeToLett(side[i][j]) << " ";
            }
            output << '\n';
        }
    }
    void TurnRight(){ //поворот кубика в руках вправо
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < i; j++) {
                std::swap(side[i][j], side[j][i]); //Транспонируем матрицу
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n/2; j++) {
                std::swap(side[i][j], side[i][n - j - 1]); //Переворачиваем столбцы
            }
        }
    }
    void TurnLeft(){
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                std::swap(side[i][j], side[j][i]); //Транспонируем матрицу
            }
        }
        for (int j = 0; j < n; j++) { //Переворачиваем столбцы
            for (int i = 0; i < n / 2; i++) {
                std::swap(side[i][j], side[n-i-1][j]);
            }
        }
    }
};
#endif //CUBICRUBIC_SIDE_H
