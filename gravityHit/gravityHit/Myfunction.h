#pragma once
#include "objBase.h"

//点の座標、線の始点、線の終点
Point Near_Point_Line(Point, Point, Point);

//四角形の当たり判定(座標、横幅ベクトル、縦幅ベクトル)
void HitLeft_Window(BaseVector*);
void HitRight_Window(BaseVector*);
void HitUp_Window(BaseVector*);
void HitDown_Window(BaseVector*);