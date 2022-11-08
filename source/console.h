#ifndef CONSOLE_H
#define CONSOLE_H

//retorna o tamanho do console
void get_size_window(int *col, int *row){
    CONSOLE_SCREEN_BUFFER_INFO cmd;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cmd);
    *col = cmd.srWindow.Right - cmd.srWindow.Left +1;
    *row = cmd.srWindow.Bottom - cmd.srWindow.Top +1;
}

//move o cursor para a coordenada X, Y
void GotoXY(int x, int y){
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
}

//maxima a tela no inicio do programa
void maximize_window(){
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_MAXIMIZE);
}

//esconde o cursor
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

#endif
