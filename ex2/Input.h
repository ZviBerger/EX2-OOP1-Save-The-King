#pragma once

#include"Structures.h"
#include<iostream>
#include <thread>       // for sleep

const int KB_ESCAPE = 27;
const int SPECIAL_KEY = 224;
const int KB_UP = 72;
const int KB_DOWN = 80;
const int KB_LEFT = 75;
const int KB_RIGHT = 77;
const int KB_P = 112;
const int KB_SPACE = 32;


class Input
{
public:
Input();
KEYS getNextKey() const;
private:
KEYS getSpecialKey() const;
};

