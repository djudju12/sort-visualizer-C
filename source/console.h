#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include <windows.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

//retorna o tamanho do console
void get_size_window(int *col, int *row);

//move o cursor para a coordenada X, Y
void GotoXY(int x, int y);

//maxima a tela no inicio do programa
void maximize_window();

//esconde o cursor
void ShowConsoleCursor(bool showFlag);

#endif
