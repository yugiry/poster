#pragma once
#include "objBase.h"

//点の座標、線の始点、線の終点
Point Near_Point_Line(Point, Point, Point);

//点と四角形それぞれの辺の近い距離を調べる
//(点の座標、四角形の座標、四角形の横幅、四角形の縦幅)
BoxLine Near_Point_BoxLine(Point, Point, Vector, Vector);

//長さの配列を短い順に揃える
void Fix_Length(float*, BoxLine*);

//二つのベクトルのなす角を求める
float Twe_Vector_Angle(Vector, Vector);
