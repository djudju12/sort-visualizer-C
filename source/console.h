#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include <windows.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

//Retorna a quantidade buffers presentes na tela 
void get_size_window(int *col, int *row);

//Move o cursor para a coordenada X, Y
void GotoXY(int x, int y);

//Maxima a tela
void maximize_window();

//Oculta ou mostra o cursos
void ShowConsoleCursor(bool showFlag);

#endif
