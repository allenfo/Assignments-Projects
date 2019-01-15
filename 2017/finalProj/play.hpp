#include"map.hpp"
#include"character.hpp"
#include"boss.hpp"
#ifndef PLAY_HPP
#define PLAY_HPP

int menu();
void play(Map*, Character*);
int bossBattle(Boss* , Character*);

#endif
