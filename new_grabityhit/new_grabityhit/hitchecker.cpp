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

		for (int i = 0; i < _poly2->vertexs_vec.size(); i++)
		{
			for (int j = i + 1; j < _poly2->vertexs_vec.size(); j++)
			{
				Point first = { _poly2->pos.x + vertexs_vec[i].x,_poly2->pos.y + vertexs_vec[i].y };
				Point end = { _poly2->pos.x + vertexs_vec[j].x,_poly2->pos.y + vertexs_vec[j].y };

				//頂点から一番近い線分上の点を出す
				Point pos_on_line = Near_Point_Line(p, first, end);
				vertexs_vec.push_back(Sub_Point_Point(pos_on_line, p));
			}
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
