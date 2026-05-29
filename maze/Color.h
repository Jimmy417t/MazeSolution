#pragma once

#include <iostream>
#include <string>
using namespace std;

enum Color
{
    BLACK = 90, RED, GREEN, YELLOW, BLUE, PURPLE, DARK_BLUE, WHITE
};

void setColor(Color color);
void setColor(string type);

