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
		printfDx("aaaa\n");

	return 0;
}

//多角形と多角形の当たり判定処理
void HitChecker::HitCheck_PP(BaseVector* _poly1, BaseVector* _poly2)
{
	//_poly1のポリゴン分調べる
	for (int polygon1 = 0; polygon1 < _poly1->tri.size(); polygon1++)
	{
		//aポリゴンの頂点ずつ
		for (int vertex1 = 0; vertex1 < THREE; vertex1++)
		{
			Point p = _poly1->tri[polygon1].vertex[vertex1];		//現在調べている頂点

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

					cross[i] = v1.x * v2.y - v1.y * v1.x;
				}
				if ((cross[0] > 0 && cross[1] > 0 && cross[2] > 0) || (cross[0] < 0 && cross[1] < 0 && cross[2] < 0))
				{
					object_hit = true;
					break;
				}
			}

		}
	}

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
		for (int i = 0; i < shortrang_vec.size(); i++)
			length.push_back(Vector_Length(shortrang_vec[i]));

		//頂点が_poly2の中にいるか
		{
			int x = 0;

			for (int i = 0; i < _poly2->vertex_num; i++)
			{
				int j = i + 1;
				if (j == _poly2->vertex_num)j = 0;


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

void HitChecker::Draw()
{
	if (object_hit)
	{
		DrawString(0, 15, "hit", 0xff0000, true);
	}
}