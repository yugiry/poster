#include "hitchecker.h"
#include "function.h"
#include <cmath>
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
				HitCheck_PW_Axis(a, b);//軸判定関数
				//HitCheck_PW(a,b);
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

//軸判定関数
void HitChecker::HitCheck_PW_Axis(BaseVector* _poly, BaseVector* _wall)
{
	//_polyの三角形と_wallの三角形を調べる(頂点ごとの処理を省き、辺同士の交差を求める)

	//_polyのポリゴン数
	for (int polygon1 = 0; polygon1 < _poly->tri.size(); polygon1++)
	{
		//_wallのポリゴン数
		for (int polygon2 = 0; polygon2 < _wall->tri.size(); polygon2++)
		{
			float min_overlap = 1.0e30f;//重なりの最小判定範囲、値は10^30乗に設定し一番高い数字にする

			bool collision = true;//衝突判定、初期判定はtrueでfor文を回す
			Vector axis = { 0.0f,0.0f };//方向
			Vector axis_result = { 0.0f,0.0f };//最終的な計算された方向
			Point edge_start;//辺の始点
			Point edge_end;//辺の終点
			Vector poly_center{ 0.0f,0.0f };//polyの中点
			Vector wall_center{ 0.0f,0.0f };//wallの中点

			//各三角形の辺から垂直なベクトルを作成し、分離軸を使って調べる
			//調べる三角形の数
			for (int shape = 0; shape < 2 && collision; shape++)
			{
				//調べる辺の数
				for (int edge = 0; edge < THREE; edge++)
				{
					int next_edge = edge + 1;
					if (next_edge == THREE)
						next_edge = 0;


					//各三角形の辺を設定
					if (shape == 0)
					{
						edge_start = _poly->tri[polygon1].vertex[edge];
						edge_end = _poly->tri[polygon1].vertex[next_edge];
					}
					else
					{
						edge_start = _wall->tri[polygon2].vertex[edge];
						edge_end = _wall->tri[polygon2].vertex[next_edge];
					}

					//辺に垂直な軸の作成
					axis.x = -(edge_end.y - edge_start.y);
					axis.y = edge_end.x - edge_start.x;

					//軸の長さ
					float axis_length = Vector_Length(axis);

					//一応長さが0である辺は無視
					if (axis_length <= 0.000001f)
						continue;

					//垂直な軸を長さで割る
					axis.x /= axis_length;
					axis.y /= axis_length;

					//_poly,_wallの三角形に辺の最小値、最大値を設定
					float poly_min = _poly->tri[polygon1].vertex[0].x * axis.x +
						_poly->tri[polygon1].vertex[0].y * axis.y;
					float poly_max = poly_min;

					float wall_min = _wall->tri[polygon2].vertex[0].x * axis.x +
						_wall->tri[polygon2].vertex[0].y * axis.y;
					float wall_max = wall_min;

					//それぞれの頂点から垂直な軸を投影して範囲を調べる
					for (int i = 1; i < THREE; i++)
					{
						//_poly
						float projection =
							_poly->tri[polygon1].vertex[i].x * axis.x +
							_poly->tri[polygon1].vertex[i].y * axis.y;

						//範囲内ならその位置まで狭める
						if (projection < poly_min) poly_min = projection;
						if (projection > poly_max) poly_max = projection;

						//_wall
						projection =
							_wall->tri[polygon2].vertex[i].x * axis.x +
							_wall->tri[polygon2].vertex[i].y * axis.y;

						if (projection < wall_min) wall_min = projection;
						if (projection > wall_max) wall_max = projection;

					}

					//重なりを計算
					float overlap = (poly_max < wall_max ? poly_max : wall_max) -
						(poly_min > wall_min ? poly_min : wall_min);

					//軸上で離れていれば衝突していないと判定しスキップする
					if (overlap <= 0.0001f)
					{
						collision = false;
						break;
					}


					// 押し戻しが最小になる場所を更新
					if (overlap < min_overlap)
					{
						min_overlap = overlap;
						axis_result.x = axis.x;
						axis_result.y = axis.y;
					}
				}
			}

			//当たっていなければスキップ
			if (!collision)
			{
				continue;
			}


			//poly,wallの中心を求める
			//それぞれの頂点位置を加算してそれを3で割り各ポリゴンの中点を計算
			for (int i = 0; i < THREE; i++)
			{
				poly_center.x += _poly->tri[polygon1].vertex[i].x;
				poly_center.y += _poly->tri[polygon1].vertex[i].y;
				wall_center.x += _wall->tri[polygon2].vertex[i].x;
				wall_center.y += _wall->tri[polygon2].vertex[i].y;
			}
			poly_center.x /= THREE;
			poly_center.y /= THREE;
			wall_center.x /= THREE;
			wall_center.y /= THREE;

			//それぞれの中心点からpoly-wallの法線を作成
			Vector center{ 0.0f,0.0f };
			center.x = poly_center.x - wall_center.x;
			center.y = poly_center.y - wall_center.y;

			if (center.x * axis_result.x + center.y * axis_result.y < 0.0f)
			{
				axis_result.x = -axis_result.x;
				axis_result.y = -axis_result.y;
			}

			//押し戻す量を成分毎に設定
			Vector pushback =
			{
				axis_result.x * (min_overlap + 0.001f),
				axis_result.y * (min_overlap + 0.001f)
			};

			//重心から衝突点までのベクトル
			Point contact_point{ 0.0f,0.0f };

			for (int i = 0; i < THREE; i++)
			{
				contact_point.x += _poly->tri[polygon1].vertex[i].x;
				contact_point.y += _poly->tri[polygon1].vertex[i].y;
			}
			contact_point.x /= THREE;
			contact_point.y /= THREE;

			//近似してその差を計算
			float rx = contact_point.x - poly_center.x;
			float ry = contact_point.y - poly_center.y;

			float vn = _poly->vec.x * axis_result.x + _poly->vec.y * axis_result.y;


			if (vn < 0.0f && _poly->inertia > 0.000001f)
			{
				// 法線方向の力積の大きさ
				float impulse =
					-(1.0f + _poly->rc) * vn * _poly->mass;
				// 角速度の変化
				_poly->angle_velocity +=
					(rx * axis_result.y - ry * axis_result.x)
					* impulse / _poly->inertia;
				_poly->angle += _poly->angle_velocity;
			}
			UpDateVertexPosition_Object(_poly, pushback);

			// 壁に向かっている速度だけ反射させる
			float vec_refrection =
				_poly->vec.x * axis_result.x +
				_poly->vec.y * axis_result.y;

			if (vec_refrection < 0.0f)
			{
				_poly->vec.x -=
					(1.0f + _poly->rc) * vec_refrection * axis_result.x;

				_poly->vec.y -=
					(1.0f + _poly->rc) * vec_refrection * axis_result.y;
			}

			return;
		}
	}
}


//多角形と壁の当たり判定処理
void HitChecker::HitCheck_PW(BaseVector* _poly, BaseVector* _wall)
{
	//_polyのポリゴン分調べる
	for (int polygon1 = 0; polygon1 < _poly->tri.size(); polygon1++)
	{
		//現在のポリゴンの頂点ずつ
		for (int vertex1 = 0; vertex1 < THREE; vertex1++)
		{
			Point p = _poly->tri[polygon1].vertex[vertex1];//現在調べている頂点

			//_wallのポリゴン分調べる
			for (int polygon2 = 0; polygon2 < _wall->tri.size(); polygon2++)
			{

				float cross[THREE];

				Vector dot[THREE];
				Vector Dist[THREE];//点同士の距離
				Point old_pos;
				//頂点が_wallのポリゴン内に入っているか調べる
				for (int i = 0; i < THREE; i++)
				{
					int j = i + 1;
					if (j == THREE)j = 0;

					//あたった相手の面のベクトル
					Vector v1 = Sub_Point_Point(_wall->tri[polygon2].vertex[j], _wall->tri[polygon2].vertex[i]);
					//当たった自分の頂点から面までのベクトル
					Vector v2 = Sub_Point_Point(p, _wall->tri[polygon2].vertex[j]);

					//求めたベクトルから外積を使って調べる
					cross[i] = v1.x * v2.y - v1.y * v2.x;

					//内積
					Vector d1 = Sub_Point_Point(p, _wall->tri[polygon2].vertex[i]);
					Vector d2 = Sub_Point_Point(p, _wall->tri[polygon2].vertex[j]);
					Vector v3 = Sub_Point_Point(_wall->tri[polygon2].vertex[i], _wall->tri[polygon2].vertex[j]);

					dot[i].x = d1.x * v1.x + d1.y * v1.y;
					dot[i].y = d2.x * v3.x + d2.y * v3.y;

					//点同士が重なった時
					Dist[i].x = (d1.x * d1.x) + (d1.y * d1.y);
					Dist[i].y = (d2.x * d2.x) + (d2.y * d2.y);


				}

				if ((cross[0] > 0 && cross[1] > 0 && cross[2] > 0) || (cross[0] < 0 && cross[1] < 0 && cross[2] < 0))
				{
					//重力加速をリセット
					_poly->vec.y = -(_poly->vec.y * _poly->rc);
					_poly->vec.x = -(_poly->vec.x);
					_poly->pos.x += _poly->vec.x;_poly->pos.y += _poly->vec.y;

					//当たった位置まで戻す
					Point near_pos = Near_Point_Line(p, _wall->tri[polygon2].vertex[1], _wall->tri[polygon2].vertex[2]);
					Vector return_vec = { near_pos.x - p.x,near_pos.y - p.y };
					UpDateVertexPosition_Object(_poly, return_vec);

					return;
				}
				if ((dot[0].x >= 0.0f && dot[0].y >= 0.0f) && (dot[1].x >= 0.0f && dot[1].y >= 0.0f) && (dot[2].x >= 0.0f && dot[2].y >= 0.0f) &&
					cross[0] == 0.0f && cross[1] == 0.0f && cross[2] == 0.0f)
				{
					//重力加速をリセット
					_poly->vec.y = -(_poly->vec.y * _poly->rc);
					_poly->vec.x = -(_poly->vec.x);
					_poly->pos.x += _poly->vec.x;_poly->pos.y += _poly->vec.y;

					//当たった位置まで戻す
					Point near_pos = Near_Point_Line(p, _wall->tri[polygon2].vertex[1], _wall->tri[polygon2].vertex[2]);
					Vector return_vec = { near_pos.x - p.x,near_pos.y - p.y };
					UpDateVertexPosition_Object(_poly, return_vec);

					return;
				}
				//点同士のあたり判定
				if (Dist[0].x <= 12 || Dist[1].x <= 12 || Dist[2].x <= 12 ||
					Dist[0].y <= 12 || Dist[1].y <= 12 || Dist[2].y <= 12)
				{
					//重力加速度をリセット
					_poly->vec.y = -(_poly->vec.y);
					_poly->vec.x = -(_poly->vec.x);_poly->vec.y = -(_poly->vec.y);
					_poly->pos.x += _poly->vec.x;_poly->pos.y += _poly->vec.y;

					//当たった位置まで戻す
					Point near_pos = Near_Point_Line(p, _wall->tri[polygon2].vertex[1], _wall->tri[polygon2].vertex[2]);
					Vector return_vec = { p.x - near_pos.x,p.y - near_pos.y };
					UpDateVertexPosition_Object(_poly, return_vec);

					return;
				}
			}
		}
	}

	//_wallのポリゴン分調べる
	for (int polygon1 = 0; polygon1 < _wall->tri.size(); polygon1++)
	{
		//現在のポリゴンの頂点ずつ
		for (int vertex1 = 0; vertex1 < THREE; vertex1++)
		{
			Point p = _wall->tri[polygon1].vertex[vertex1];//現在調べている頂点

			//_polyのポリゴン分調べる
			for (int polygon2 = 0; polygon2 < _poly->tri.size(); polygon2++)
			{
				float cross[THREE];//外積

				Vector dot[THREE];
				Vector Dist[THREE];//点同士の距離
				//頂点が_polyのポリゴン内に入っているか調べる
				for (int i = 0; i < THREE; i++)
				{
					int j = i + 1;
					if (j == THREE)j = 0;

					//外積
					Vector v1 = Sub_Point_Point(_poly->tri[polygon2].vertex[j], _poly->tri[polygon2].vertex[i]);
					Vector v2 = Sub_Point_Point(p, _poly->tri[polygon2].vertex[j]);
					cross[i] = v1.x * v2.y - v1.y * v2.x;
					//内積
					Vector d1 = Sub_Point_Point(p, _poly->tri[polygon2].vertex[i]);
					Vector d2 = Sub_Point_Point(p, _poly->tri[polygon2].vertex[j]);
					Vector v3 = Sub_Point_Point(_poly->tri[polygon2].vertex[i], _poly->tri[polygon2].vertex[j]);

					dot[i].x = d1.x * v1.x + d1.y * v1.y;
					dot[i].y = d2.x * v3.x + d2.y * v3.y;

					//点同士が重なった時
					Dist[i].x = (d1.x * d1.x) + (d1.y * d1.y);
					Dist[i].y = (d2.x * d2.x) + (d2.y * d2.y);

				}
				//外積判定
				if ((cross[0] > 0 && cross[1] > 0 && cross[2] > 0) || (cross[0] < 0 && cross[1] < 0 && cross[2] < 0))
				{
					//重力加速度をリセット
					_poly->vec.y = -(_poly->vec.y * _poly->rc);

					//当たった位置まで戻す
					Point near_pos = Near_Point_Line(p, _poly->tri[polygon2].vertex[1], _poly->tri[polygon2].vertex[2]);
					Vector return_vec = { p.x - near_pos.x,p.y - near_pos.y };

					UpDateVertexPosition_Object(_poly, return_vec);

					break;
				}
				if ((dot[0].x >= 0.0f && dot[0].y >= 0.0f) && (dot[1].x >= 0.0f && dot[1].y >= 0.0f) && (dot[2].x >= 0.0f && dot[2].y >= 0.0f) &&
					cross[0] == 0.0f && cross[1] == 0.0f && cross[2] == 0.0f)
				{
					//重力加速をリセット
					_poly->vec.y = -(_poly->vec.y * _poly->rc);

					//当たった位置まで戻す
					Point near_pos = Near_Point_Line(p, _poly->tri[polygon2].vertex[1], _poly->tri[polygon2].vertex[2]);
					Vector return_vec = { near_pos.x - p.x,near_pos.y - p.y };

					UpDateVertexPosition_Object(_poly, return_vec);
					break;
				}
				//点同士のあたり判定
				if (Dist[0].x <= 12 || Dist[1].x <= 12 || Dist[2].x <= 12 ||
					Dist[0].y <= 12 || Dist[1].y <= 12 || Dist[2].y <= 12)
				{
					//重力加速度をリセット
					_poly->vec.y = -(_poly->vec.y);
					_poly->vec.x = -(_poly->vec.x);_poly->vec.y = -(_poly->vec.y);
					_poly->pos.x += _poly->vec.x;_poly->pos.y += _poly->vec.y;

					//当たった位置まで戻す
					Point near_pos = Near_Point_Line(p, _poly->tri[polygon2].vertex[1], _poly->tri[polygon2].vertex[2]);
					Vector return_vec = { p.x - near_pos.x,p.y - near_pos.y };
					UpDateVertexPosition_Object(_poly, return_vec);

					return;
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