#pragma once
#include "objBase.h"

//角度がついた箱を書く
//(座標、箱の傾き、横幅、縦幅)
void FreeDrawBox(Point, Vector, int, int);

//角度がついた箱とまっすぐな箱との当たり判定
//(変座標、正座標、変ベクトル)
void HitCheckFreeBox(Point, Point, Vector);
