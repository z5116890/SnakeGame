#include <iostream>
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>

using namespace std;
bool gameOver;
const int width = 30;
const int height = 15;