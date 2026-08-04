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

//角度
float GetAngle(Vector A, Vector B)
{
	float dot = A.x * B.x + A.y * B.y;

	float cross = A.x * B.y - A.y * B.x;

	float angle = atan2(cross, dot) * 180.0f / M_PI;

	if (angle < 0.0f)angle += 360.0f;

	return angle;
}

float GetAngle(Vector A)
{
	return GetAngle(A, base_angle);
}

//角度で頂点座標を更新
//(更新する頂点座標、角度、ベクトルの長さ、ベクトルの始点)
void UpDateVectorRadian(Point* V, int r, float l, Point s)
{
	if (r >= 360.0f)r -= 360.0f;
	if (r < 0)r += 360.0f;
	float rad = r * (M_PI / 180.0f);
	Vector vertex_vec = { (float)cos(rad),-(float)sin(rad) };
	vertex_vec = Vector_SetLength(vertex_vec, l);
	V->x = s.x + vertex_vec.x;
	V->y = s.y + vertex_vec.y;
}

//座標更新処理(画面端用)
void UpDateVertexPosition_Screen(BaseVector* _obj)
{
	//移動処理
	_obj->pos.x += _obj->vec.x;
	_obj->pos.y += _obj->vec.y;

	Vector return_vec{ 0,0 };
	for (int i = 0; i < _obj->vertex_num; i++)
	{
		int j = i + 1;
		if (j == _obj->vertex_num)j = 0;

		Vector vertex_vec;
		float length, a, rad;

		_obj->tri[i].vertex[0] = { _obj->pos.x,_obj->pos.y };

		UpDateVectorRadian(&_obj->tri[i].vertex[1], _obj->tri[i].angle[1] + _obj->angle, Vector_Length(_obj->vertexs_vec[i]), _obj->pos);

		UpDateVectorRadian(&_obj->tri[i].vertex[2], _obj->tri[i].angle[2] + _obj->angle, Vector_Length(_obj->vertexs_vec[j]), _obj->pos);



		if (_obj->tri[i].vertex[1].y > WINDOW_HEIGHT)
		{
			return_vec.y = WINDOW_HEIGHT - _obj->tri[i].vertex[1].y;
			_obj->vec.y = 0;
		}
		else if (_obj->tri[i].vertex[2].y > WINDOW_HEIGHT)
		{
			return_vec.y = WINDOW_HEIGHT - _obj->tri[i].vertex[2].y;
			_obj->vec.y = 0;
		}
	}

	_obj->pos.x += return_vec.x;
	_obj->pos.y += return_vec.y;
}

//座標更新処理(オブジェクト用)
void UpDateVertexPosition_Object(BaseVector* _obj, Vector vec)
{
	//移動処理
	_obj->pos.x += vec.x;
	_obj->pos.y += vec.y;

	Vector return_vec{ 0,0 };
	for (int i = 0; i < _obj->vertex_num; i++)
	{
		int j = i + 1;
		if (j == _obj->vertex_num)j = 0;

		Vector vertex_vec;
		float length, a, rad;

		_obj->tri[i].vertex[0] = { _obj->pos.x,_obj->pos.y };

		UpDateVectorRadian(&_obj->tri[i].vertex[1], _obj->tri[i].angle[1] + _obj->angle, Vector_Length(_obj->vertexs_vec[i]), _obj->pos);

		UpDateVectorRadian(&_obj->tri[i].vertex[2], _obj->tri[i].angle[2] + _obj->angle, Vector_Length(_obj->vertexs_vec[j]), _obj->pos);

	}

	_obj->pos.x += return_vec.x;
	_obj->pos.y += return_vec.y;
}
