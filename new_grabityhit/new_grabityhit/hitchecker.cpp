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
			BaseVector* a = base[i].get();
			BaseVector* b = base[j].get();
			
			if (a->ID > b->ID)swap(a, b);

			if (a->ID == (int)ObjID::POLYGON && b->ID == (int)ObjID::POLYGON)
			{
				HitCheck_PP(a, b);
			}
			if (a->ID == (int)ObjID::CIRCLE && b->ID == (int)ObjID::CIRCLE)
			{

			}
			if (a->ID == (int)ObjID::POLYGON && b->ID == (int)ObjID::CIRCLE)
			{

			}
		}
	}

	if (object_hit)
		DrawString(0, 20, "hit", 0xff0000, true);

	return 0;
}

//多角形と多角形の当たり判定処理
void HitChecker::HitCheck_PP(BaseVector* _poly1, BaseVector* _poly2)
{
	bool poly1_hit = false, poly2_hit = false;

	//_poly1のポリゴン分調べる
	for (int polygon1 = 0; polygon1 < _poly1->tri.size(); polygon1++)
	{
		//現在のポリゴンの頂点ずつ
		for (int vertex1 = 1; vertex1 < THREE; vertex1++)
		{
			Point p = _poly1->tri[polygon1].vertex[vertex1];//現在調べている頂点

			//Point p = _poly1->tri[0].vertex[1];//左上...?

			//_poly2のポリゴン分調べる
			for (int polygon2 = 0; polygon2 < _poly2->tri.size(); polygon2++)
			{
				//int polygon2 = 0;
				/*if (CheckInPolygon(_poly2->tri[polygon2].vertex, p));
				{
					poly1_hit = true;
					break;
				}*/

				float cross[THREE];

				//頂点が_poly2のポリゴン内に入っているか調べる
				for (int i = 0; i < THREE; i++)
				{
					int j = i + 1;
					if (j == THREE)j = 0;

					Vector v1 = Sub_Point_Point(_poly2->tri[polygon2].vertex[j], _poly2->tri[polygon2].vertex[i]);
					Vector v2 = Sub_Point_Point(p, _poly2->tri[polygon2].vertex[j]);

					cross[i] = v1.x * v2.y - v1.y * v2.x;
				}
				if ((cross[0] > 0 && cross[1] > 0 && cross[2] > 0) || (cross[0] < 0 && cross[1] < 0 && cross[2] < 0))
				{
					poly1_hit = true;
					break;
				}
			}
		}
	}

	//_poly2のポリゴン分調べる
	for (int polygon2 = 0; polygon2 < _poly2->tri.size(); polygon2++)
	{
		//aポリゴンの頂点ずつ
		for (int vertex2 = 1; vertex2 < THREE; vertex2++)
		{
			Point p = _poly2->tri[polygon2].vertex[vertex2];//現在調べている頂点

			//_poly1のポリゴン分調べる
			for (int polygon1 = 0; polygon1 < _poly1->tri.size(); polygon1++)
			{
				float cross[THREE];

				//頂点が_poly1のポリゴン内に入っているか調べる
				for (int i = 0; i < THREE; i++)
				{
					int j = i + 1;
					if (j == THREE)j = 0;

					Vector v1 = Sub_Point_Point(_poly1->tri[polygon1].vertex[j], _poly1->tri[polygon1].vertex[i]);
					Vector v2 = Sub_Point_Point(p, _poly1->tri[polygon1].vertex[j]);

					cross[i] = v1.x * v2.y - v1.y * v2.x;
				}
				if ((cross[0] > 0 && cross[1] > 0 && cross[2] > 0) || (cross[0] < 0 && cross[1] < 0 && cross[2] < 0))
				{
					poly2_hit = true;
					break;
				}
			}
		}
	}

	//当たった後の動き
	_poly1->vertex_hit = poly1_hit;
	_poly2->vertex_hit = poly2_hit;
}

//円と円の当たり判定処理
void HitChecker::HitCheck_CC(BaseVector* _cir1, BaseVector* _cir2)
{

}

//多角形と円の当たり判定処理
void HitChecker::HitCheck_PC(BaseVector* _poly, BaseVector* _cir)
{

}

void HitChecker::Draw()
{
	if (object_hit)
	{
		DrawString(0, 15, "hit", 0xff0000, true);
	}
}

//点がポリゴンの中にいるかどうか調べる
//(始点、終点、頂点)
bool HitChecker::CheckInPolygon(vector<Point> vsp, Point vp)
{
	float cross[THREE];
	//頂点が_poly1のポリゴン内に入っているか調べる
	for (int i = 0; i < THREE; i++)
	{
		int j = i + 1;
		if (j == THREE)j = 0;

		Vector v1 = Sub_Point_Point(vsp[j], vsp[i]);
		Vector v2 = Sub_Point_Point(vp, vsp[j]);

		cross[i] = v1.x * v2.y - v1.y * v2.x;
	}
	if ((cross[0] > 0 && cross[1] > 0 && cross[2] > 0) || (cross[0] < 0 && cross[1] < 0 && cross[2] < 0))
	{
		return true;
	}

	return false;
}