#pragma once
#include "objBase.h"

//座標更新(オブジェクト)
void PositionUpdate(BaseVector*);

//点から直線までの最短距離を調べる
//(点、直線の始点、直線の終点)
Point Near_Point_Line(Point, Point, Point);

//点がポリゴンの中にいるかどうか調べる
//(頂点、)
bool CheckInPolygon(Point, vector<Point>, BaseVector*);