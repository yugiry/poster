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

			if (a->ID == (int)ObjID::POLYGON && b->ID == (int)ObjID::WALL)
			{
				HitCheck_PW(a, b);
			}
			if (a->ID == (int)ObjID::CIRCLE && b->ID == (int)ObjID::WALL)
			{

			}
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

//多角形と壁の当たり判定処理
void HitChecker::HitCheck_PW(BaseVector* _poly, BaseVector* _wall)
{
	//_poly1のポリゴン分調べる
	for (int polygon1 = 0; polygon1 < _poly->tri.size(); polygon1++)
	{
		//現在のポリゴンの頂点ずつ
		for (int vertex1 = 1; vertex1 < THREE; vertex1++)
		{
			Point p = _poly->tri[polygon1].vertex[vertex1];//現在調べている頂点

			//_poly2のポリゴン分調べる
			for (int polygon2 = 0; polygon2 < _wall->tri.size(); polygon2++)
			{
				float cross[THREE];

				//頂点が_poly2のポリゴン内に入っているか調べる
				for (int i = 0; i < THREE; i++)
				{
					int j = i + 1;
					if (j == THREE)j = 0;

					Vector v1 = Sub_Point_Point(_wall->tri[polygon2].vertex[j], _wall->tri[polygon2].vertex[i]);
					Vector v2 = Sub_Point_Point(p, _wall->tri[polygon2].vertex[j]);

					cross[i] = v1.x * v2.y - v1.y * v2.x;
				}
				if ((cross[0] > 0 && cross[1] > 0 && cross[2] > 0) || (cross[0] < 0 && cross[1] < 0 && cross[2] < 0))
				{
					//重力加速をリセット
					_poly->vec.y = 0;

					//当たった位置まで戻す
					Point near_pos = Near_Point_Line(p, _wall->tri[polygon2].vertex[1], _wall->tri[polygon2].vertex[2]);
					Vector return_vec = { near_pos.x - p.x,near_pos.y - p.y };

					UpDateVertexPosition_Object(_poly, return_vec);

					break;
				}
			}
		}
	}
}

//円と壁の当たり判定処理
void HitChecker::HitCheck_CW(BaseVector* _cir, BaseVector* _wall)
{

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

			//_poly2のポリゴン分調べる
			for (int polygon2 = 0; polygon2 < _poly2->tri.size(); polygon2++)
			{
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
					//重力加速をリセット
					_poly1->vec.y = 0;

					//当たった位置まで戻す
					Point near_pos = Near_Point_Line(p, _poly2->tri[polygon2].vertex[1], _poly2->tri[polygon2].vertex[2]);
					Vector return_vec = { near_pos.x - p.x,near_pos.y - p.y };

					UpDateVertexPosition_Object(_poly1, return_vec);

					break;
				}
			}
		}
	}

	//_poly2のポリゴン分調べる
	//for (int polygon2 = 0; polygon2 < _poly2->tri.size(); polygon2++)
	//{
	//	//aポリゴンの頂点ずつ
	//	for (int vertex2 = 1; vertex2 < THREE; vertex2++)
	//	{
	//		Point p = _poly2->tri[polygon2].vertex[vertex2];//現在調べている頂点

	//		//_poly1のポリゴン分調べる
	//		for (int polygon1 = 0; polygon1 < _poly1->tri.size(); polygon1++)
	//		{
	//			float cross[THREE];

	//			//頂点が_poly1のポリゴン内に入っているか調べる
	//			for (int i = 0; i < THREE; i++)
	//			{
	//				int j = i + 1;
	//				if (j == THREE)j = 0;

	//				Vector v1 = Sub_Point_Point(_poly1->tri[polygon1].vertex[j], _poly1->tri[polygon1].vertex[i]);
	//				Vector v2 = Sub_Point_Point(p, _poly1->tri[polygon1].vertex[j]);

	//				cross[i] = v1.x * v2.y - v1.y * v2.x;
	//			}
	//			if ((cross[0] > 0 && cross[1] > 0 && cross[2] > 0) || (cross[0] < 0 && cross[1] < 0 && cross[2] < 0))
	//			{
	//				poly2_hit = true;
	//				break;
	//			}
	//		}
	//	}
	//}

	//当たった後の動き
	//_poly1->vertex_hit = poly1_hit;
	//_poly2->vertex_hit = poly2_hit;
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