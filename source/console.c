#include "console.h"

void get_size_window(int *col, int *row){
    CONSOLE_SCREEN_BUFFER_INFO cmd;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cmd);
    *col = cmd.srWindow.Right - cmd.srWindow.Left +1;
    *row = cmd.srWindow.Bottom - cmd.srWindow.Top +1;
}

void GotoXY(int x, int y){
    HANDLE out; //handle para std_output
    COORD coordenadas; //estrutura para coordenadas
    
    fflush(stdout);
    coordenadas.X = x;
    coordenadas.Y = y;
    out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(out,coordenadas); //seta a posicao do cursos na posicao x,y no std_output
}

void maximize_window(){
    HWND consoleWindow = GetConsoleWindow(); //Handle para a janela
    ShowWindow(consoleWindow, SW_MAXIMIZE);
}

void ShowConsoleCursor(bool showFlag){
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); //handle para std_output 

    CONSOLE_CURSOR_INFO cursorInfo; 

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; //seta a visibilidade do cursos
    SetConsoleCursorInfo(out, &cursorInfo);
}

