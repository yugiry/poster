#include "Myfunction.h"
#include "2D_function.h"

//座標更新(オブジェクト)
void PositionUpdate(BaseVector* object)
{
	object->pos.x += object->vec.x;
	object->pos.y += object->vec.y;
}

//点から直線までの最短距離を調べる
//(点、直線の始点、直線の終点)
Point Near_Point_Line(Point P, Point A, Point B)
{
	Point Q{ 0,0 };//直線上の点
	Vector n{ B.x - A.x,B.y - A.y };//直線の方向ベクトル
	Vector AP{ P.x - A.x,P.y - A.y };//始点からの点までのベクトル
	float t = (AP.x * n.x + AP.y * n.y) / (n.x * n.x + n.y * n.y);//投影係数
	if (t < 0)t = 0;//0より小さい場合は始点値
	if (t > 1)t = 1.0f;//1より大きい場合は終点値
	Q = Add_Point_Vector(A, Mul_Vector_Scaler(n, t));

	return Q;
}

//点がポリゴンの中にいるかどうか調べる
//(最短距離の座標、最短距離の長さ、ポリゴン)
bool CheckInPolygon(vector<Point> _short_pos, vector<float> _length, BaseVector* _poly)
{
	for (int i = 0; i < _poly->vertex_num; i++)
	{
		int j = i + 1;
		if (j == _poly->vertex_num)j = 0;


	}

	return  false;
}
