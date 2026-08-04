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

//角度
float GetAngle(Vector, Vector);
float GetAngle(Vector);

//角度で頂点座標を更新
//(更新する頂点座標、角度、ベクトルの長さ、ベクトルの始点)
void UpDateVectorRadian(Point*, int, float, Point);

//座標更新処理(画面端用)
void UpDateVertexPosition_Screen(BaseVector*);

//座標更新処理(オブジェクト用)
void UpDateVertexPosition_Object(BaseVector*, Vector);