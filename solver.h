//
// Created by Полина Шевцова on 25.05.23.
//

#ifndef CUBICRUBIC_SOLVER_H
#define CUBICRUBIC_SOLVER_H
#include "cubicrub.h"
#include <vector>
class algorithm{
private:
    CubicRubic cube;
    bool isChamomile(){
        if(cube.cubic[up].side[0][1] == white && cube.cubic[up].side[2][1] == white){
            if(cube.cubic[up].side[1][0] == white && cube.cubic[up].side[1][2] == white){
                return true;
            }
        }
        return false;
    }
    void turnIfWhite(int x, int y){
        if(cube.cubic[up].side[x][y] == white){
            cube.U();
            first.push_back("U ");
            turnIfWhite(x, y);
            return;
        }
        return;
    }
    void chamomile(){
        int count = 0;
        while(!isChamomile() && count < 80){
            count++;
            Side* s = &cube.cubic[front];
            if(s->side[1][0] == white){
                turnIfWhite(1, 0);
                first.push_back("L' ");
                cube.L_();
                continue;
            }
            if(s->side[1][2] == white){
                turnIfWhite(1, 2);
                first.push_back("R ");
                cube.R();
                continue;
            }
            if(s->side[0][1] == white || s->side[2][1] == white){
                turnIfWhite(0, 1);
                cube.F();
                first.push_back("F ");
                continue;
            }

            s = &cube.cubic[back];
            if(s->side[1][0] == white){
                turnIfWhite(1, 0);
                first.push_back("L ");
                cube.L();
                continue;
            }
            if(s->side[1][2] == white){
                turnIfWhite(1, 2);
                first.push_back("R' ");
                cube.R_();
                continue;
            }
            if(s->side[0][1] == white || s->side[2][1] == white){
                turnIfWhite(2, 1);
                first.push_back("B ");
                cube.B();
                continue;
            }

            s = &cube.cubic[left];
            if(s->side[1][0] == white){
                turnIfWhite(0, 1);
                first.push_back("B_ ");
                cube.B_();
                continue;
            }
            if(s->side[1][2] == white){
                turnIfWhite(2, 1);
                first.push_back("F ");
                cube.F();
                continue;
            }
            if(s->side[0][1] == white || s->side[2][1] == white){
                turnIfWhite(1, 0);
                first.push_back("L ");
                cube.L();
                continue;
            }

            s = &cube.cubic[right];
            if(s->side[1][0] == white){
                turnIfWhite(2, 1);
                first.push_back("F ");
                cube.F();
                continue;
            }
            if(s->side[1][2] == white){
                turnIfWhite(0, 1);
                first.push_back("B' ");
                cube.B_();
                continue;
            }
            if(s->side[0][1] == white || s->side[2][1] == white){
                turnIfWhite(1, 2);
                first.push_back("R ");
                cube.R();
                continue;
            }

            s = &cube.cubic[down];
            if(s->side[1][0] == white){
                turnIfWhite(1, 0);
                first.push_back("L2 ");
                cube.L();
                cube.L();
                continue;
            }
            if(s->side[1][2] == white){
                turnIfWhite(1, 2);
                first.push_back("R2 ");
                cube.R();
                cube.R();
                continue;
            }
            if(s->side[0][1] == white || s->side[2][1] == white){
                first.push_back("D ");
                cube.D();
                continue;
            }
        }
    }
    void whiteSide(){
        Side* yel = &cube.cubic[up];
        Side* s = &cube.cubic[right];
        while(s->side[0][1] != blue || yel->side[1][2] != white){
            first2.push_back("U ");
            cube.U();
        }
        first2.push_back("R2 ");
        cube.R();
        cube.R();

        s = &cube.cubic[front];
        while(s->side[0][1] != orange || yel->side[2][1] != white){
            first2.push_back("U ");
            cube.U();
        }
        first2.push_back("F2 ");
        cube.F();
        cube.F();

        s = &cube.cubic[left];
        while(s->side[0][1] != green || yel->side[1][0] != white){
            first2.push_back("U ");
            cube.U();
        }
        first2.push_back("L2 ");
        cube.L();
        cube.L();

        s = &cube.cubic[back];
        while(s->side[0][1] != red || yel->side[0][1] != white){
            first2.push_back("U ");
            cube.U();
        }
        first2.push_back("B2 ");
        cube.B();
        cube.B();
    }

    bool isWhiteComplete(){
        Side *s = &cube.cubic[down];
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(s->side[i][j] != white){
                    return false;
                }
            }
        }
        s = &cube.cubic[front];
        for(int i = 0; i <3; i++){
            if(s->side[2][i] != orange){
                return false;
            }
        }
        s = &cube.cubic[right];
        for(int i = 0; i <3; i++){
            if(s->side[2][i] != blue){
                return false;
            }
        }
        s = &cube.cubic[left];
        for(int i = 0; i <3; i++){
            if(s->side[2][i] != green){
                return false;
            }
        }
        s = &cube.cubic[back];
        for(int i = 0; i <3; i++){
            if(s->side[2][i] != red){
                return false;
            }
        }
        return true;
    };
    bool secondUp(){
        Side* s = &cube.cubic[up];
        if(s->side[0][0] == white){
            if(cube.cubic[back].side[0][0] == green){
                second.push_back("y y ");
                for(int i = 0; i < 3; i++){
                    cube.PiphPaph(back);
                    second.push_back("R U R' U'");
                }
                second.push_back("y y\n");
            }else{
                second.push_back("U ");
                cube.U();
                return 0;
            }
            return 1;
        }

        if(s->side[2][2] == white){
            if(cube.cubic[front].side[0][2] == blue){
                for(int i = 0; i < 3; i++){
                    cube.PiphPaph(front);
                    second.push_back("R U R' U' ");
                }
                second.push_back("\n");
            }else{
                second.push_back("U ");
                cube.U();
                return 0;
            }
            return 1;
        }
        if(s->side[0][2] == white){
            if(cube.cubic[right].side[0][2] == red){
                second.push_back("y");
                for(int i = 0; i < 3; i++){
                    cube.PiphPaph(right);
                    second.push_back("R U R' U' ");
                }
                second.push_back("y'\n");
            }else{
                second.push_back("U ");
                cube.U();
                return 0;
            }
            return 1;
        }

        if(s->side[2][0] == white){
            if(cube.cubic[left].side[0][2] == orange){
                second.push_back("y'");
                for(int i = 0; i < 3; i++){
                    cube.PiphPaph(left);
                    second.push_back("R U R' U' ");
                }
                second.push_back("y\n");
            }else{
                second.push_back("U ");
                cube.U();
                return 0;
            }
            return 1;
        }
        return 0;
    }
    bool secondFront(){
        Side* s = &cube.cubic[front];
        Side* r = &cube.cubic[right];
        Side* l = &cube.cubic[left];
        if(s->side[0][2] == white){
            if(r->side[0][0] == blue){
                for(int i = 0; i < 5; i++){
                    cube.PiphPaph(front);
                    second.push_back("R U R' U' ");
                }
                second.push_back("\n");
            }else{
                second.push_back("U ");
                cube.U();
                return 0;
            }
            return 1;
        }
        if(s->side[0][0] == white){
            if(l->side[0][2] == green){
                cube.PiphPaph(left);
                second.push_back("y' R U R' U' y\n ");
            }else{
                second.push_back("U ");
                cube.U();
                return 0;
            }
            return 1;
        }

        if(s->side[2][0] == white) {
            cube.PiphPaph(left);
            second.push_back("y' R U R' U' y ");
            return 1;
        }
        if( s->side[2][2] == white){
            cube.PiphPaph(front);
            second.push_back("R U R' U' ");
            return 1;
        }
        return 0;
    }
    int secondRight(){
        Side* s = &cube.cubic[right];
        Side* r = &cube.cubic[back];
        Side* l = &cube.cubic[front];
        if(s->side[0][2] == white){
            if(r->side[0][2] == red){
                second.push_back("y ");
                for(int i = 0; i < 5; i++){
                    cube.PiphPaph(right);
                    second.push_back("y R U R' U' y' ");
                }
                second.push_back("y'\n");
            }else{
                second.push_back("U ");
                cube.U();
                return 2;
            }
            return 1;
        }
        if(s->side[0][0] == white){
            if(l->side[0][2] == orange){
                cube.PiphPaph(front);
                second.push_back(" R U R' U'\n");
            }else{
                second.push_back("U ");
                cube.U();
                return 2;
            }
            return 1;
        }

        if(s->side[2][0] == white) {
            cube.PiphPaph(front);
            second.push_back("R U R' U ");
            return 1;
        }
        if( s->side[2][2] == white){
            cube.PiphPaph(right);
            second.push_back("y R U R' U' y' ");
            return 1;
        }
        return 0;
    }
    bool secondLeft(){
        Side* s = &cube.cubic[left];
        Side* r = &cube.cubic[front];
        Side* l = &cube.cubic[back];
        if(s->side[0][2] == white){
            if(r->side[0][0] == orange){
                second.push_back("y' ");
                for(int i = 0; i < 5; i++){
                    cube.PiphPaph(left);
                    second.push_back("R U R' U' ");
                }
                second.push_back("y\n");
            }else{
                second.push_back("U ");
                cube.U();
                return 0;
            }
            return 1;
        }
        if(s->side[0][0] == white){
            if(l->side[0][0] == red){
                cube.PiphPaph(back);
                second.push_back("y y R U R' U' y' y'\n");
            }else{
                second.push_back("U ");
                cube.U();
                return 0;
            }
            return 1;
        }
        if(s->side[2][0] == white) {
            cube.PiphPaph(back);
            second.push_back("y y L' U' L U y' y' ");
            return 1;
        }
        if( s->side[2][2] == white){
            cube.PiphPaph(left);
            second.push_back("y' R U R' U' y ");
            return 1;
        }
        return 0;
    }
    bool secondBack(){
        Side* s = &cube.cubic[back];
        Side* r = &cube.cubic[right];
        Side* l = &cube.cubic[left];
        if(s->side[0][0] == white){
            if(l->side[0][0] == green){
                second.push_back("y y ");
                for(int i = 0; i < 5; i++){
                    cube.PiphPaph(back);
                    second.push_back("R U R' U' ");
                }
                second.push_back("y y\n");
            }else{
                second.push_back("U ");
                cube.U();
                return 0;
            }
            return 1;
        }
        if(s->side[0][2] == white){
            if(r->side[0][2] == blue){
                cube.PiphPaph(right);
                second.push_back("y R U R' U' y'\n");
            }else{
                second.push_back("U ");
                cube.U();
                return 0;
            }
            return 1;
        }
        if(s->side[2][0] == white) {
            cube.PiphPaph(back);
            second.push_back("y y L' U' L U y' y' ");
            return 1;
        }
        if( s->side[2][2] == white){
            cube.PiphPaph(right);
            second.push_back("y R U R' U' y' ");
            return 1;
        }
        return 0;
    }
    void secondDown(){
        Side* s = &cube.cubic[down];
        if(s->side[0][0] == white && (cube.cubic[front].side[2][0] != orange || cube.cubic[left].side[2][2] != green)) {
            cube.PiphPaph(left);
            second.push_back("y' R U R' U' y ");
            return;
        }

        if(s->side[0][2] == white  && (cube.cubic[front].side[2][2] != orange || cube.cubic[right].side[2][0] != blue)){
            cube.PiphPaph(front);
            second.push_back("R U R' U' ");
            return;
        }

        if(s->side[2][0] == white  && (cube.cubic[back].side[2][0] != red || cube.cubic[left].side[2][2] != green)){
            cube.LeftPiphPaph(back);
            second.push_back("y y R U R' U' y' y' ");
            return;
        }

        if(s->side[2][2] == white && (cube.cubic[back].side[2][2] != red || cube.cubic[right].side[2][0] != blue)){
            cube.PiphPaph(left);
            second.push_back("y R U R' U' y' ");
            return;
        }

    }

    bool isSecondLayerCompleted(){
        Side* s = &cube.cubic[front];
        for(int i = 0; i< 3; i++){
            if(s->side[1][i] != orange){
                return false;
            }
        }
        s =  &cube.cubic[left];
        for(int i = 0; i< 3; i++){
            if(s->side[1][i] != green){
                return false;
            }
        }
        s =  &cube.cubic[back];
        for(int i = 0; i< 3; i++){
            if(s->side[1][i] != red){
                return false;
            }
        }
        s =  &cube.cubic[right];
        for(int i = 0; i< 3; i++){
            if(s->side[1][i] != blue){
                return false;
            }
        }
        return true;
    }
    bool thirdUp(){
        bool flag = 0;
        Side* u = &cube.cubic[up];
        Side* s = &cube.cubic[front];
        if(s->side[0][1] != yellow && u->side[2][1] != yellow){
            if(s->side[0][1] == s->side[1][1]){
                if(u->side[2][1] == blue){
                    cube.U();
                    cube.PiphPaph(front);
                    cube.LeftPiphPaph(right);
                    third.push_back("U R U R' U' y L' U' L U y'\n");
                    return 1;
                }else if(u->side[2][1] == green){
                    cube.U_();
                    cube.LeftPiphPaph(front);
                    cube.PiphPaph(left);
                    third.push_back("U' L' U' L U y' U R U R' U' y\n");
                    return 1;
                }
            }else{
                cube.U();
                third.push_back("U ");
                flag = 1;
            }
        }
        s = &cube.cubic[left];
        if(s->side[0][1] != yellow && u->side[1][0] != yellow){
            if(s->side[0][1] == s->side[1][1]){
                third.push_back("y' ");
                if(u->side[1][0] == orange){
                    cube.U();
                    cube.PiphPaph(left);
                    cube.LeftPiphPaph(front);
                    third.push_back("U R U R' U' y L' U' L U y' y\n");
                    return 1;
                }else if(u->side[1][0] == red){
                    cube.U_();
                    cube.LeftPiphPaph(left);
                    cube.PiphPaph(back);
                    third.push_back("U' L' U' L U y' U R U R' U' y y\n");
                    return 1;
                }
            }else{
                cube.U();
                third.push_back("U ");
                flag = 1;
            }
        }

        s = &cube.cubic[back];
        if(s->side[0][1] != yellow && u->side[0][1] != yellow){
            if(s->side[0][1] == s->side[1][1]){
                third.push_back("y y ");
                if(u->side[0][1] == green){
                    cube.U();
                    cube.PiphPaph(back);
                    cube.LeftPiphPaph(left);
                    third.push_back("U R U R' U' y L' U' L U y' y y\n");
                    return 1;
                }else if(u->side[0][1] == blue){
                    cube.U_();
                    cube.LeftPiphPaph(back);
                    cube.PiphPaph(right);
                    third.push_back("U' L' U' L U y' U R U R' U' y y\n");
                    return 1;
                }
            }else{
                cube.U();
                third.push_back("U ");
                flag = 1;
            }
        }
        s = &cube.cubic[right];
        if(s->side[0][1] != yellow && u->side[1][2] != yellow){
            if(s->side[0][1] == s->side[1][1]){
                third.push_back("y ");
                if(u->side[1][2] == red){
                    cube.U();
                    cube.PiphPaph(right);
                    cube.LeftPiphPaph(back);
                    third.push_back("U R U R' U' y L' U' L U y' y\n");
                    return 1;
                }else if(u->side[1][2] == orange){
                    cube.U_();
                    cube.LeftPiphPaph(right);
                    cube.PiphPaph(front);
                    third.push_back("U' L' U' L U y' U R U R' U' y\n");
                    return 1;
                }
            }else{
                cube.U();
                third.push_back("U ");
                flag = 1;
            }
        }
        return flag;

    }
    void thirdCenter(){
        Side* s = &cube.cubic[front];
        if(s->side[1][2] != yellow || cube.cubic[right].side[1][0] != yellow ){
            if(s->side[1][2] != orange || cube.cubic[right].side[1][0] != blue){
                cube.PiphPaph(front);
                cube.LeftPiphPaph(right);
                third.push_back("U R U R' U' y L' U' L U y'\n");
                return;
            }
        }

        s = &cube.cubic[left];
        if(s->side[1][2] != yellow && cube.cubic[front].side[1][0] != yellow){
            if(s->side[1][2] != green && cube.cubic[front].side[1][0] != orange){
                cube.PiphPaph(left);
                cube.LeftPiphPaph(front);
                third.push_back("y' U R U R' U' y L' U' L U y' y\n");
                return;
            }
        }

        s = &cube.cubic[back];
        if(s->side[1][0] != yellow && cube.cubic[left].side[1][0] != yellow){
            if(s->side[1][0] != red ){
                if(cube.cubic[left].side[1][0] != green){
                    cube.PiphPaph(back);
                    cube.LeftPiphPaph(left);
                    third.push_back("y y U R U R' U' y L' U' L U y' y y\n");
                    return;
                }
            }

        }
        s = &cube.cubic[right];
        if(s->side[1][2] != yellow && cube.cubic[back].side[1][2] != yellow){
            if(s->side[1][2] != blue && cube.cubic[back].side[1][2] != red){
                cube.PiphPaph(right);
                cube.LeftPiphPaph(back);
                third.push_back("y U R U R' U' y L' U' L U y' y'\n");
                return;
            }
        }
        return;

    }

    bool isYellowCross(){
        Side* s = &cube.cubic[up];
        if(s->side[0][1]!= yellow){
            return false;
        }
        if(s->side[2][1]!= yellow){
            return false;
        }
        if(s->side[1][0]!= yellow){
            return false;
        }
        if(s->side[1][2]!= yellow){
            return false;
        }
        return true;
    }
    void stick(int side){
        cube.F(side);
        cube.PiphPaph(side);
        cube.F_(side);
        fourth.push_back("F R U R' U' F' ");
    }
    void checkMark(int side){
        cube.F(side);
        cube.PiphPaph(side);
        cube.PiphPaph(side);
        cube.F_(side);
        fourth.push_back("F R U R' U' R U R' U' F' ");
    }
    bool findStick(){
        Side* s = &cube.cubic[up];
        if(s->side[1][0] == yellow && s->side[1][2] == yellow){
            stick(front);
            return true;
        }
        if(s->side[0][1] == yellow && s->side[2][1] == yellow){
            fourth.push_back("y' ");
            stick(left);
            fourth.push_back("y ");
            return true;
        }
        return false;
    }
    bool findCheckMark(){
        Side* s = &cube.cubic[up];
        if(s->side[1][0] == yellow && s->side[0][1] == yellow){
            checkMark(front);
            return true;
        }
        if(s->side[0][1] == yellow && s->side[1][2] == yellow){
            fourth.push_back("y' ");
            checkMark(left);
            fourth.push_back("y ");
            return true;

        }
        if(s->side[1][2] == yellow && s->side[2][1] == yellow){
            fourth.push_back("y y ");
            checkMark(back);
            fourth.push_back("y y ");
            return true;
        }
        if(s->side[2][1] == yellow && s->side[1][0] == yellow){
            fourth.push_back("y ");
            checkMark(right);
            fourth.push_back("y' ");
            return true;
        }
        return false;
    }

    bool isRightYellowCross(){
        if(cube.cubic[front].side[0][1] != orange){
            return false;
        }
        if(cube.cubic[left].side[0][1] != green){
            return false;
        }
        if(cube.cubic[right].side[0][1] != blue){
            return false;
        }
        if(cube.cubic[back].side[0][1] != red){
            return false;
        }
        return true;
    }
    void fifthNear(int side){
        cube.R(side);
        cube.U(side);
        cube.R_(side);
        cube.U(side);
        cube.R(side);
        cube.U(side);
        cube.U(side);
        cube.R_(side);
        cube.U(side);
        fifth.push_back("R U R' U R U2 R' U ");
    }
    void fifthOpposite(int side){
        cube.R(side);
        cube.U(side);
        cube.R_(side);
        cube.U(side);
        cube.R(side);
        cube.U(side);
        cube.U(side);
        cube.R_(side);
        fifth.push_back("R U R' U R U2 R' ");
    }
    bool isNear(){
        if(cube.cubic[front].side[0][1] == orange){
            if(cube.cubic[left].side[0][1] == green){
                fifth.push_back("y y ");
                fifthNear(back);
                fifth.push_back("y y\n");
                return 1;
            }
            if(cube.cubic[right].side[0][1] == blue){
                fifth.push_back("y' ");
                fifthNear(left);
                fifth.push_back("y\n");
                return 1;
            }
        }
        if(cube.cubic[back].side[0][1] == red){
            if(cube.cubic[right].side[0][1] == blue){
                fifthNear(front);
                fifth.push_back("\n");
                return 1;
            }
            if(cube.cubic[left].side[0][1] == green){
                fifth.push_back("y ");
                fifthNear(right);
                fifth.push_back("y'\n");
                return 1;
            }
        }
        return 0;

    }
    bool isOpposite(){
        if(cube.cubic[front].side[0][1] == orange){
            if(cube.cubic[back].side[0][1] == red){
                fifthOpposite(front);
                fifth.push_back("\n");
                return 1;
            }
        }
        if(cube.cubic[left].side[0][1] == green){
            if(cube.cubic[right].side[0][1] == blue){
                fifth.push_back("y ");
                fifthOpposite(left);
                fifth.push_back("y'\n");
                return 1;
            }
        }
        return 0;
    }

    int angleinRightPlaces(){
        int count = 0;
        int c1 = cube.cubic[front].side[0][2];
        int c2 = cube.cubic[right].side[0][0];
        int c3 = cube.cubic[up].side[2][2];
        if(c1 == yellow || c1 == blue || c1 == orange){
            if(c2 == yellow || c2 == blue || c2 == orange){
                if(c3 == yellow || c3 == blue || c3 == orange){
                    count+=2;
                }
            }
        }
        c1 = cube.cubic[left].side[0][2];
        c2 = cube.cubic[front].side[0][0];
        c3 = cube.cubic[up].side[2][0];
        if(c1 == yellow || c1 == green || c1 == orange){
            if(c2 == yellow || c2 == green || c2 == orange){
                if(c3 == yellow || c3 == green || c3 == orange){
                    count++;
                }
            }
        }
        if(count == 3){
            return 5;
        }else if(count == 2){
            yellowAndgle(right);
            return count;
        }else if(count == 1){
            yellowAndgle(front);
            return count;
        }

        c1 = cube.cubic[back].side[0][0];
        c2 = cube.cubic[left].side[0][0];
        c3 = cube.cubic[up].side[0][0];
        if(c1 == yellow || c1 == green || c1 == red){
            if(c2 == yellow || c2 == green || c2 == red){
                if(c3 == yellow || c3 == green || c3 == red){
                    count++;
                }
            }
        }
        if(count){
            yellowAndgle(back);
            return count;
        }

        c1 = cube.cubic[right].side[0][2];
        c2 = cube.cubic[down].side[0][2];
        c3 = cube.cubic[up].side[0][2];
        if(c1 == yellow || c1 == green || c1 == orange){
            if(c2 == yellow || c2 == green || c2 == orange){
                if(c3 == yellow || c3 == green || c3 == orange){
                    count++;
                }
            }
        }
        if(count){
            yellowAndgle(left);
            return count;
        }
        return count;
    }
    void yellowAndgle(int side){
        cube.R(side);
        cube.U_(side);
        cube.L_(side);
        cube.U(side);
        cube.R_(side);
        cube.U_(side);
        cube.L(side);
        cube.U(side);
        sixth.push_back("R U' L' U R' U' L U ");
    }
    void noYellowAngle(){
        cube.R();
        cube.U_();
        cube.L_();
        cube.U();
        cube.R_();
        cube.U_();
        cube.L();
        cube.U();
        sixth.push_back("R U' L' U R' U' L U ");
    }

    void turnUpSideDown(){
        for(int i = 0; i< 3; i++){
            for(int j = 0; j< 3; j++){
                std::swap(cube.cubic[up].side[i][j], cube.cubic[down].side[2-i][2-j]);
            }
        }
        cube.cubic[front].TurnRight();
        cube.cubic[front].TurnRight();
        cube.cubic[left].TurnRight();
        cube.cubic[left].TurnRight();
        cube.cubic[back].TurnRight();
        cube.cubic[back].TurnRight();
        cube.cubic[right].TurnRight();
        cube.cubic[right].TurnRight();
        for(int i = 0; i< 3; i++){
            for(int j = 0; j< 3; j++){
                std::swap(cube.cubic[left].side[i][j], cube.cubic[right].side[i][j]);
            }
        }
    }
    void turnAngles(int side){
        cube.R(side);
        cube.U(side);
        cube.R_(side);
        cube.U_(side);
        seventh.push_back("R U R_ U_ ");
    }
public:
    std::vector<std::string> first;
    std::vector<std::string> first2;;
    std::vector<std::string> second;
    std::vector<std::string> third;
    std::vector<std::string> fourth;
    std::vector<std::string> fifth;
    std::vector<std::string> sixth;
    std::vector<std::string> seventh;
    algorithm(){
        cube = CubicRubic();
        cube.Random();
    }
    algorithm(CubicRubic* input){
        cube = input;
        cube.print();
    }
    void firstStep(){
        chamomile();
        whiteSide();
    }
    void secondStep(){
        int count = 0;
        int i = 4;
        while(!isWhiteComplete() && count < 40){
            count++;
            if (secondFront() && i){
                i--;
                continue;
            }
            if (secondLeft()){
                continue;
            }
            if (secondLeft()){
                continue;
            }
            if (secondBack()){
                continue;
            }
            int i = secondRight();
            if(i == 2){
                secondStep();
                break;
            }
            if(i){
                continue;
            }
            if (secondUp()){
                continue;
            }
            secondDown();
            i = 4;
        }
    }
    void thirdStep(){
        int count = 40;
        while(!isSecondLayerCompleted() && count){
            count--;
            while(thirdUp()&& count){
                count--;
            };
            thirdCenter();
        }
    }
    void fourthStep(){
        fourth.push_back("\n");
        if(!isYellowCross()){
            if(!findStick()){
                if(!findCheckMark()){
                    stick(front);
                    cube.U();
                    cube.U();
                    fourth.push_back("2U ");
                    checkMark(front);
                }
            }

        }
    }
    void fifthStep(){
        bool flag = 0;
        while(!flag){
            flag = isRightYellowCross();
            if(!flag){
                flag = isNear();
                if(!flag){
                    if(!isOpposite()){
                        cube.U();
                        fifth.push_back("U ");
                    }
                }
            }
        }

    }
    void sixthStep(){
        int count = angleinRightPlaces();
        while(count < 5){
            if(!count) {
                noYellowAngle();
            }
            count = angleinRightPlaces();
        }

    }
    void seventhStep(){
        turnUpSideDown();
        seventh.push_back("Turn cube upside down\n");
        cube.print();
        if((cube.cubic[down].side[0][2] != yellow ||
            cube.cubic[front].side[2][2] != cube.cubic[front].side[2][1] ||
            cube.cubic[right].side[2][0] != cube.cubic[right].side[2][1])){
            for(int i = 0; i < 4; i++){
                while((cube.cubic[down].side[0][2] != yellow ||
                       cube.cubic[front].side[2][2] != cube.cubic[front].side[2][1] ||
                       cube.cubic[right].side[2][0] != cube.cubic[right].side[2][1]) ){
                    turnAngles(front);
                }
                cube.D_();
            }
        }
        if((cube.cubic[down].side[0][0] != yellow
            || cube.cubic[left].side[2][2] != cube.cubic[left].side[2][1]
            || cube.cubic[front].side[2][0] != cube.cubic[front].side[2][1])){
            for(int i = 0; i < 4; i++){
                int j = 6;
                while((cube.cubic[down].side[0][0] != yellow
                       || cube.cubic[left].side[2][2] != cube.cubic[left].side[2][1]
                       || cube.cubic[front].side[2][0] != cube.cubic[front].side[2][1]) && j){
                    turnAngles(left);
                }
                cube.D_();
                cube.print();
                j--;
            }
        }

        if(cube.cubic[down].side[0][2] != yellow
           || cube.cubic[back].side[0][2] != cube.cubic[back].side[0][1]
           || cube.cubic[left].side[2][0] != cube.cubic[left].side[2][1]){
            for(int i = 0; i < 4; i++){
                while(cube.cubic[down].side[0][2] != yellow
                      || cube.cubic[back].side[0][2] != cube.cubic[back].side[0][1]
                      || cube.cubic[left].side[2][0] != cube.cubic[left].side[2][1]){
                    turnAngles(back);
                }
                cube.D_();
            }
        }

        if(cube.cubic[down].side[0][2] != yellow
           || cube.cubic[front].side[2][2] != cube.cubic[front].side[2][1]
           || cube.cubic[right].side[2][0] != cube.cubic[right].side[2][1]){
            for(int i = 0; i < 4; i++){
                while(cube.cubic[down].side[0][2] != yellow
                      || cube.cubic[front].side[2][2] != cube.cubic[front].side[2][1]
                      || cube.cubic[right].side[2][0] != cube.cubic[right].side[2][1]){
                    turnAngles(right);
                }
                cube.D_();
            }
        }

        turnUpSideDown();
        seventh.push_back("\nTurn cube upside down\n");

    }

    void Solver(){
        firstStep();
        cube.print();
        for(int i = 0; i< first.size(); i++){
            std::cout << first[i];
        }
        std::cout << "\n\n";
        for(int i = 0; i< first2.size(); i++){
            std::cout << first2[i];
        }
        std::cout << "\n\n";
        secondStep();
        cube.print();
        for(int i = 0; i< second.size(); i++){
            std::cout << second[i];
        }
        std::cout << "\n\n";
        thirdStep();
        cube.print();
        for(int i = 0; i< third.size(); i++){
            std::cout << third[i];
        }
        fourthStep();
        cube.print();
        for(int i = 0; i< fourth.size(); i++){
            std::cout << fourth[i];
        }
        std::cout << "\n\n";
        fifthStep();
        cube.print();
        for(int i = 0; i< fifth.size(); i++){
            std::cout << fifth[i];
        }
        std::cout << "\n\n";
        sixthStep();
        cube.print();
        for(int i = 0; i< sixth.size(); i++){
            std::cout << sixth[i];
        }
        std::cout << "\n\n";
        seventhStep();
        cube.print();
        for(int i = 0; i< seventh.size(); i++){
            std::cout << seventh[i];
        }

    }
};
#endif //CUBICRUBIC_SOLVER_H
