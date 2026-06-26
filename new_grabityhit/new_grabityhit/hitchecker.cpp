#include "hitchecker.h"
#include "function.h"

//コンストラクタ
HitChecker::HitChecker()
{

}

//当たり判定の更新処理
int HitChecker::CheckerUpdate(const ObjList& base)
{
	for (int i = 0; i < base.size(); i++)
	{
		for (int j = i + 1; j < base.size(); j++)
		{
			if (base[i]->ID == (int)ObjID::POLYGON || base[j]->ID == (int)ObjID::POLYGON)
			{
				HitCheck_PP(base[i].get(), base[j].get());
			}
			if (base[i]->ID == (int)ObjID::CIRCLE || base[j]->ID == (int)ObjID::CIRCLE)
			{

			}
		}
	}

	return 0;
}

//多角形と多角形の当たり判定処理
void HitChecker::HitCheck_PP(BaseVector* _poly1, BaseVector* _poly2)
{
	//_poly1の頂点の分判定を取る
	for (int a = 0; a < _poly1->vertexs_vec.size(); a++)
	{
		//現在調べている頂点からそれぞれの変までの最短距離を調べる
		Vector v = _poly1->vertexs_vec[a];						//現在調べている頂点までのベクトルを記録
		Point p = { _poly1->pos.x + v.x,_poly1->pos.y + v.y };	//現在調べている頂点のワールド座標

		vector<Point> shortrang_pos;
		vector<Vector> shortrang_vec;

		//_poly1の頂点からの最短距離を_poly2の線分の分調べる
		for (int i = 0; i < _poly2->vertexs_vec.size(); i++)
		{
			int j = i + 1;
			if (j == _poly2->vertexs_vec.size())j = 0;
			Point first = { _poly2->pos.x + _poly2->vertexs_vec[i].x,_poly2->pos.y + _poly2->vertexs_vec[i].y };
			Point end = { _poly2->pos.x + _poly2->vertexs_vec[j].x,_poly2->pos.y + _poly2->vertexs_vec[j].y };

			Point pos_on_line = Near_Point_Line(p, first, end);//頂点から一番近い線分上の点を出す
			Vector near_line = Sub_Point_Point(pos_on_line, p);//頂点から線分上の点までのベクトル
			shortrang_pos.push_back(pos_on_line);
			shortrang_vec.push_back(near_line);
		}
		//最短距離の長さを保存
		vector<float>  length;
		for (int b = 0; b < shortrang_vec.size(); b++)
			length.push_back(Vector_Length(shortrang_vec[b]));

		//頂点が_poly2の中にいるかどうか判定
		//if (CheckInPolygon(shortrang_pos, length, _poly2))
		{

		}
	}
}

//円と円の当たり判定処理
void HitChecker::HitCheck_CC(BaseVector* _cir1, BaseVector* _cir2)
{

}

//多角形と円の当たり判定処理
void HitChecker::HitCheck_PC(BaseVector* _poly, BaseVector* _cir)
{

}
