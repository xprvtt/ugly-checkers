#include <iostream>
//#include <iso646.h>

using namespace std;


int main() {

    // тарица игрового поля
    // 1 строка и 1 столбец используюя для обозначения координат
    // последующие цифры 1 и 2 определяют игрока

    int Matrix[9][9] = {
    { 0, 1, 2, 3, 4, 5, 6, 7, 8 },
    { 1, 0, 1, 0, 1, 0, 1, 0, 1 },
    { 2, 1, 0, 1, 0, 1, 0, 1, 0 },
    { 3, 0, 1, 0, 1, 0, 1, 0, 1 },
    { 4, 9, 0, 9, 0, 9, 0, 9, 0 },
    { 5, 0, 9, 0, 9, 0, 9, 0, 9 },
    { 6, 2, 0, 2, 0, 2, 0, 2, 0 },
    { 7, 0, 2, 0, 2, 0, 2, 0, 2 },
    { 8, 2, 0, 2, 0, 2, 0, 2, 0 },
    };

    for (bool Win = false; Win == false; ) {

        setlocale(LC_ALL, "Ru");

        
        int Point1 = 0;
        int Point2 = 0;

        for (int i = 1; i < 9; i++) {
            for (int j = 1; j < 9; j++) {
                if (Matrix[i][j] == 1) {
                    Point1 += 1;
                }
                else if (Matrix[i][j] == 2) {
                    Point2 += 1;
                }
            }
        }

        if (Point1 == 0) {
            cout << "выиграл игрок 2" << endl;
            Win = true;
            break;
        }
        else if (Point2 == 0) {
            cout << "выиграл игрок 1" << endl;
            Win = true;
            break;
        }

        cout << Point1 << " " << Point2 << endl;

        // стандартное начало, ходит игрок 1

        for (bool rightMove = false; rightMove == false; ) {
            int row, col, row_re, col_re;

            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    cout << Matrix[i][j] << "   ";
                }
                cout << endl << endl;
            }

            cout << "ходит игрок 1" << endl << "введите начальную координату шашки(ряд столбец)" << endl;

            int forceMove[48][2]{ {0} };
            int x = 0;

            // проверка обязательных ходов
            for (int i = 1; i < 9; i++) {
                for (int j = 1; j < 9; j++) {
                    if (Matrix[i][j] == 1) {
                        if (Matrix[i + 1][j + 1] == 2 and Matrix[i + 2][j + 2] == 9) {
                            x++;
                            forceMove[x][0] = i;
                            forceMove[x][1] = j;
                            cout << "вы должны срубить шашку на координатах " << i + 1 << " " << j + 1 << endl;
                        }
                        else if (Matrix[i + 1][j - 1] == 2 and Matrix[i + 2][j - 2] == 9) {
                            x++;
                            forceMove[x][0] = i;
                            forceMove[x][1] = j;
                            cout << "вы должны срубить шашку на координатах " << i + 1 << " " << j - 1 << endl;
                        }
                        else if (Matrix[i - 1][j + 1] == 2 and Matrix[i - 2][j + 2] == 9) {
                            x++;
                            forceMove[x][0] = i;
                            forceMove[x][1] = j;
                            cout << "вы должны срубить шашку на координатах " << i - 1 << " " << j + 1 << endl;
                        }
                        else if (Matrix[i - 1][j - 1] == 2 and Matrix[i - 2][j - 2] == 9) {
                            x++;
                            forceMove[x][0] = i;
                            forceMove[x][1] = j;
                            cout << "вы должны срубить шашку на координатах " << i - 1 << " " << j - 1 << endl;
                        }
                    }
                }
            }

            int sum = 0;
            for (int i = 0; i < 48; i++) {
                for (int j = 0; j < 2; j++) {
                    sum += forceMove[i][j];
                }
            }

            // условия когда мы не можем ходить любой шашкой, т.к. вынужены срубить
            if (sum == 0) {
                for (bool r_Checker = false; r_Checker == false; ) {
                    cin >> row >> col;
                    if (Matrix[row + 1][col + 1] != 9 and Matrix[row + 1][col - 1] != 9 and Matrix[row - 1][col + 1] != 9 and Matrix[row - 1][col - 1] != 9) {
                        cout << "вы не можете выбрать эту шашку" << endl;

                    }
                    else {
                        r_Checker = true;
                    }
                }
            }
            else {

                for (bool rightForceMove = false; rightForceMove == false;) {

                    cout << "доступные шашки для хода: " << endl;;

                    for (int i = 0; i < 48; i++) {
                        if (forceMove[i][0] != 0 and forceMove[i][1] != 0) {
                            cout << forceMove[i][0] << " " << forceMove[i][1] << endl;
                        }

                    }

                    cout << endl;

                    for (bool checker = false; checker == false;) {

                        cin >> row >> col;

                        for (int i = 0; i < 48; i++) {
                            if (row == forceMove[i][0] and col == forceMove[i][1]) {
                                rightForceMove = true;
                            }

                        }

                        if (rightForceMove == true) {
                            cout << "теперь срубите шашку противника" << endl;
                            checker = true;
                        }
                        else if (Matrix[row][col] == 0) {
                            cout << "тут нет шашки" << endl;
                        }
                        else {
                            cout << "ошибка";
                        }
                        cout << Matrix[row + 1][col + 1] << Matrix[row + 1][col - 1] << Matrix[row - 1][col + 1] << Matrix[row - 1][col - 1];
                    }
                }
            }

            // действие игрока 1

            if (Matrix[row][col] == 1) {
                for (bool endMove = false; endMove == false;) {

                    cout << "введите конечную координату своей шашки" << endl;
                    cin >> row_re >> col_re;

                    // стандартная проверка куда возможно сходить

                    if (row_re == row + 1) {

                        switch (Matrix[row_re][col_re]) {
                        case 9:
                            Matrix[row][col] = 9;
                            Matrix[row_re][col_re] = 1;
                            cout << "вы никого не срубили" << endl << endl;
                            endMove = rightMove = true;
                            break;
                        case 1:
                            cout << "нельзя поставить на свою шашку" << endl << endl;
                            break;
                        case 0:
                            cout << "нельзя сюда передвинуть" << endl << endl;
                            break;
                        default:
                            cout << "нельзя поставить сюда!" << endl << endl;

                        }
                    }

                    else if (row_re == row + 2 and col_re == col + 2 and Matrix[row + 1][col + 1] == 2 and Matrix[row_re][col_re] != 2) {
                        Matrix[row][col] = 9;
                        Matrix[row + 1][col + 1] = 9;
                        Matrix[row_re][col_re] = 1;
                        cout << "игрок 1 срубил шашку" << endl;
                        endMove = true;
                    }
                    else if (row_re == row + 2 and col_re == col - 2 and Matrix[row + 1][col - 1] == 2 and Matrix[row_re][col_re] != 2) {
                        Matrix[row][col] = 9;
                        Matrix[row + 1][col - 1] = 9;
                        Matrix[row_re][col_re] = 1;
                        cout << "вы срубили 1 пешку" << endl;
                        endMove = true;
                    }
                    else {
                        cout << "нельзя поставить сюда!!" << endl << endl;
                    }
                }

                // проверка возможных обязательных ходов
                for (int i = 1; rightMove == false; ) {

                    int pick = 0;
                    if (Matrix[row_re + i][col_re + i] == 2 and Matrix[row_re + i + i][col_re + i + i] == 9) {
                        cout << "этой же пешкой вы должны срубить еще 1 шашку ниже и правее, на координате " << row_re + i << " " << col_re + i << " направление >> 1" << endl;
                        pick += 1;
                    }
                    if (Matrix[row_re + i][col_re - i] == 2 and Matrix[row_re + i + i][col_re - i - i] == 9) {
                        cout << "этой же пешкой вы должны срубить еще 1 шашку ниже и левее, на координате " << row_re + i << " " << col_re - i << " направление >> 2" << endl;
                        pick += 1;
                    }
                    if (Matrix[row_re - i][col_re + i] == 2 and Matrix[row_re - i - i][col_re + i + i] == 9) {
                        cout << "этой же пешкой вы должны срубить еще 1 шашку выше и правее, на координате " << row_re - i << " " << col_re + i << " направление >> 3" << endl;
                        pick += 1;
                    }
                    if (Matrix[row_re - i][col_re - i] == 2 and Matrix[row_re - i - i][col_re - i - i] == 9) {
                        cout << "этой же пешкой вы должны срубить еще 1 шашку выше и левее, на координате " << row_re - i << " " << col_re - i << " направление >> 4" << endl;
                        pick += 1;
                    }
                    if (pick == 0) {
                        cout << "ход закончен" << endl << endl;
                        rightMove = true;
                    }
                    else {

                        for (int i = 0; i < 9; i++) {
                            for (int j = 0; j < 9; j++) {
                                cout << Matrix[i][j] << "   ";
                            }
                            cout << endl << endl;
                        }

                        cout << "снова ходит игрок 1" << endl << "напишите номер направления которое хотите выбрать " << endl;
                        cin >> pick;

                        // в случае если одной пешкой можно выбрать несколько вариантов вынужденного хода
                        switch (pick) {

                        case 1:
                            cout << "игрок 1 рубит еще одну шашку находящуюся ниже и правее, на координате " << row_re + i << " " << col_re + i << endl;
                            Matrix[row_re][col_re] = 9;
                            Matrix[row_re + i][col_re + i] = 9;
                            Matrix[row_re + i * 2][col_re + i * 2] = 1;
                            row_re += i * 2;
                            col_re += i * 2;
                            break;
                        case 2:
                            cout << "игрок 1 рубит еще одну шашку находящуюся ниже и левее, на координате " << row_re + i << " " << col_re - i << endl;
                            Matrix[row_re][col_re] = 9;
                            Matrix[row_re + i][col_re - i] = 9;
                            Matrix[row_re + i * 2][col_re - i * 2] = 1;
                            row_re += i * 2;
                            col_re -= i * 2;
                            break;
                        case 3:
                            cout << "игрок 1 рубит еще одну шашку находящуюся выше и правее, на координате " << row_re - i << " " << col_re + i << endl;
                            Matrix[row_re][col_re] = 9;
                            Matrix[row_re - i][col_re + i] = 9;
                            Matrix[row_re - i * 2][col_re + i * 2] = 1;
                            row_re -= i * 2;
                            col_re += i * 2;
                            break;
                        case 4:
                            cout << "игрок 1 рубит еще одну шашку находящуюся выше и левее, на координате " << row_re - i << " " << col_re - i << endl;
                            Matrix[row_re][col_re] = 9;
                            Matrix[row_re - i][col_re - i] = 9;
                            Matrix[row_re - i * 2][col_re - i * 2] = 1;
                            row_re -= i * 2;
                            col_re -= i * 2;
                            break;
                        default:
                            cout << "ошибка" << endl;
                        }


                    }

                }
            }
            else {
                cout << "тут нет шашки" << endl << endl;
            }
        };


        //              
        // 
        //
        //              действия игрокa 2 
        //
        //
        //             абсолютно идентичны
        //
        //


        for (bool rightMove = false; rightMove == false; ) {
            int row, col, row_re, col_re;

            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    cout << Matrix[i][j] << "   ";
                }
                cout << endl << endl;
            }

            cout << "ходит игрок 2" << endl << "введите начальную координату шашки(ряд столбец)" << endl;

            int forceMove[48][2]{ {0} };
            int x = 0;

            for (int i = 1; i < 9; i++) {
                for (int j = 1; j < 9; j++) {
                    if (Matrix[i][j] == 2) {
                        if (Matrix[i + 1][j + 1] == 1 and Matrix[i + 2][j + 2] == 9) {
                            x++;
                            forceMove[x][0] = i;
                            forceMove[x][1] = j;
                            cout << "вы должны срубить шашку на координатах " << i + 1 << " " << j + 1 << endl;
                        }
                        else if (Matrix[i + 1][j - 1] == 1 and Matrix[i + 2][j - 2] == 9) {
                            x++;
                            forceMove[x][0] = i;
                            forceMove[x][1] = j;
                            cout << "вы должны срубить шашку на координатах " << i + 1 << " " << j - 1 << endl;
                        }
                        else if (Matrix[i - 1][j + 1] == 1 and Matrix[i - 2][j + 2] == 9) {
                            x++;
                            forceMove[x][0] = i;
                            forceMove[x][1] = j;
                            cout << "вы должны срубить шашку на координатах " << i - 1 << " " << j + 1 << endl;
                        }
                        else if (Matrix[i - 1][j - 1] == 1 and Matrix[i - 2][j - 2] == 9) {
                            x++;
                            forceMove[x][0] = i;
                            forceMove[x][1] = j;
                            cout << "вы должны срубить шашку на координатах " << i - 1 << " " << j - 1 << endl;
                        }
                    }
                }
            }

            int sum = 0;
            for (int i = 0; i < 48; i++) {
                for (int j = 0; j < 2; j++) {
                    sum += forceMove[i][j];
                }
            }

            if (sum == 0) {
                for (bool r_Checker = false; r_Checker == false; ) {
                    cin >> row >> col;
                    if (Matrix[row + 1][col + 1] != 9 and Matrix[row + 1][col - 1] != 9 and Matrix[row - 1][col + 1] != 9 and Matrix[row - 1][col - 1] != 9) {
                        cout << "вы не можете выбрать эту шашку" << endl;

                    }
                    else {
                        r_Checker = true;
                    }
                }
            }
            else {

                for (bool rightForceMove = false; rightForceMove == false;) {

                    cout << "доступные шашки для хода: " << endl;;

                    for (int i = 0; i < 48; i++) {
                        if (forceMove[i][0] != 0 and forceMove[i][1] != 0) {
                            cout << forceMove[i][0] << " " << forceMove[i][1] << endl;
                        }

                    }

                    cout << endl;

                    for (bool checker = false; checker == false;) {

                        cin >> row >> col;

                        for (int i = 0; i < 48; i++) {
                            if (row == forceMove[i][0] and col == forceMove[i][1]) {
                                rightForceMove = true;
                            }

                        }

                        if (rightForceMove == true) {
                            cout << "теперь срубите шашку противника" << endl;
                            checker = true;
                        }
                        else if (rightForceMove == false and Matrix[row][col] == 0) {
                            cout << "тут нет шашки" << endl;
                        }

                        else if (rightForceMove == false) {
                            cout << "вы не можете выбрать эту шашку" << endl;
                        }
                        else {
                            cout << "ошибка";
                        }
                    }
                }
            }

            if (Matrix[row][col] == 2) {
                for (bool endMove = false; endMove == false;) {

                    cout << "введите конечную координату своей шашки" << endl;
                    cin >> row_re >> col_re;

                    if (row_re == row - 1) {

                        switch (Matrix[row_re][col_re]) {
                        case 9:
                            Matrix[row][col] = 9;
                            Matrix[row_re][col_re] = 2;
                            cout << "вы никого не срубили" << endl << endl;
                            endMove = rightMove = true;
                            break;
                        case 2:
                            cout << "нельзя поставить на свою шашку" << endl << endl;
                            break;
                        case 0:
                            cout << "нельзя сюда передвинуть" << endl << endl;
                            break;
                        default:
                            cout << "нельзя поставить сюда!" << endl << endl;

                        }
                    }
                    else if (row_re == row - 2 and col_re == col + 2 and Matrix[row - 1][col + 1] == 1 and Matrix[row_re][col_re] != 1) {
                        Matrix[row][col] = 9;
                        Matrix[row - 1][col + 1] = 9;
                        Matrix[row_re][col_re] = 2;
                        cout << "игрок 1 срубил шашку" << endl;
                        endMove = true;
                    }
                    else if (row_re == row - 2 and col_re == col - 2 and Matrix[row - 1][col - 1] == 1 and Matrix[row_re][col_re] != 1) {
                        Matrix[row][col] = 9;
                        Matrix[row - 1][col - 1] = 9;
                        Matrix[row_re][col_re] = 2;
                        cout << "вы срубили 1 пешку" << endl;
                        endMove = true;
                    }
                    else {
                        cout << "нельзя поставить сюда!!" << endl << endl;
                    }
                }

                for (int i = 1; rightMove == false; ) {

                    int pick = 0;
                    if (Matrix[row_re + i][col_re + i] == 2 and Matrix[row_re + i + i][col_re + i + i] == 9) {
                        cout << "этой же пешкой вы должны срубить еще 1 шашку ниже и правее, на координате " << row_re + i << " " << col_re + i << " направление >> 1" << endl;
                        pick += 1;
                    }
                    if (Matrix[row_re + i][col_re - i] == 2 and Matrix[row_re + i + i][col_re - i - i] == 9) {
                        cout << "этой же пешкой вы должны срубить еще 1 шашку ниже и левее, на координате " << row_re + i << " " << col_re - i << " направление >> 2" << endl;
                        pick += 1;
                    }
                    if (Matrix[row_re - i][col_re + i] == 2 and Matrix[row_re - i - i][col_re + i + i] == 9) {
                        cout << "этой же пешкой вы должны срубить еще 1 шашку выше и правее, на координате " << row_re - i << " " << col_re + i << " направление >> 3" << endl;
                        pick += 1;
                    }
                    if (Matrix[row_re - i][col_re - i] == 2 and Matrix[row_re - i - i][col_re - i - i] == 9) {
                        cout << "этой же пешкой вы должны срубить еще 1 шашку выше и левее, на координате " << row_re - i << " " << col_re - i << " направление >> 4" << endl;
                        pick += 1;
                    }
                    if (pick == 0) {
                        cout << "ход закончен" << endl << endl;
                        rightMove = true;
                    }
                    else {

                        for (int i = 0; i < 9; i++) {
                            for (int j = 0; j < 9; j++) {
                                cout << Matrix[i][j] << "   ";
                            }
                            cout << endl << endl;
                        }

                        cout << "снова ходит игрок 2" << endl << "напишите номер направления которое хотите выбрать " << endl;
                        cin >> pick;

                        switch (pick) {

                        case 1:
                            cout << "игрок 1 рубит еще одну шашку находящуюся ниже и правее, на координате " << row_re + i << " " << col_re + i << endl;
                            Matrix[row_re][col_re] = 9;
                            Matrix[row_re + i][col_re + i] = 9;
                            Matrix[row_re + i * 2][col_re + i * 2] = 2;
                            row_re += i * 2;
                            col_re += i * 2;
                            break;
                        case 2:
                            cout << "игрок 1 рубит еще одну шашку находящуюся ниже и левее, на координате " << row_re + i << " " << col_re - i << endl;
                            Matrix[row_re][col_re] = 9;
                            Matrix[row_re + i][col_re - i] = 9;
                            Matrix[row_re + i * 2][col_re - i * 2] = 2;
                            row_re += i * 2;
                            col_re -= i * 2;
                            break;
                        case 3:
                            cout << "игрок 1 рубит еще одну шашку находящуюся выше и правее, на координате " << row_re - i << " " << col_re + i << endl;
                            Matrix[row_re][col_re] = 9;
                            Matrix[row_re - i][col_re + i] = 9;
                            Matrix[row_re - i * 2][col_re + i * 2] = 2;
                            row_re -= i * 2;
                            col_re += i * 2;
                            break;
                        case 4:
                            cout << "игрок 1 рубит еще одну шашку находящуюся выше и левее, на координате " << row_re - i << " " << col_re - i << endl;
                            Matrix[row_re][col_re] = 9;
                            Matrix[row_re - i][col_re - i] = 9;
                            Matrix[row_re - i * 2][col_re - i * 2] = 2;
                            row_re -= i * 2;
                            col_re -= i * 2;
                            break;
                        default:
                            cout << "ошибка" << endl;
                        }


                    }

                }
            }
            else {
                cout << "тут нет шашки" << endl << endl;
            }
        };

    }
};

