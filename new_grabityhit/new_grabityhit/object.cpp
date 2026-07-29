#include "object.h"

CObject::CObject(int _type)
{
	switch (_type)
	{
	case 0:
		pos.x = WINDOW_WIDTH / 2;
		pos.y = WINDOW_HEIGHT / 2 - 150;

		ImgWidth = 100;
		ImgHeight = 300;
		can = true;
		break;
	case 1:
		pos.x = WINDOW_WIDTH / 2;
		pos.y = WINDOW_HEIGHT - 100;

		ImgWidth = 300;
		ImgHeight = 100;
		break;
	case 2:
		pos.x = pos.y = 0;

		ImgWidth = ImgHeight = 50;
		break;
	}

	rc = 0.5f;
	vertex_num = 4;

	//í∏ì_ÇÃèâä˙âª
	Vector v = { -ImgWidth / HALF, -ImgHeight / HALF };
	vertexs_vec.push_back(v);
	v = { ImgWidth / HALF, -ImgHeight / HALF };
	vertexs_vec.push_back(v);
	v = { ImgWidth / HALF,ImgHeight / HALF };
	vertexs_vec.push_back(v);
	v = { -ImgWidth / HALF,ImgHeight / HALF };
	vertexs_vec.push_back(v);

	for (int i = 0; i < vertex_num; i++)
	{
		int j = i + 1;
		if (j == vertex_num)j = 0;

		Poly poly;

		Point p = { pos.x,pos.y };
		poly.vertex.push_back(p);
		p = { pos.x + vertexs_vec[i].x,pos.y + vertexs_vec[i].y };
		poly.vertex.push_back(p);
		p = { pos.x + vertexs_vec[j].x,pos.y + vertexs_vec[j].y };
		poly.vertex.push_back(p);

		tri.push_back(poly);
	}

	ID = (int)ObjID::POLYGON;
}

int CObject::Action(const ObjList& base, ObjList& add_list)
{
	if (can)
	{
		vec.x = 0.0f; vec.y += g;

		if (CheckHitKey(KEY_INPUT_W))vec.y = -5.0f;
		if (CheckHitKey(KEY_INPUT_S))vec.y = 5.0f;
		if (CheckHitKey(KEY_INPUT_A))vec.x = -5.0f;
		if (CheckHitKey(KEY_INPUT_D))vec.x = 5.0f;

		//à⁄ìÆèàóù
		pos.x += vec.x;
		pos.y += vec.y;

		{
			Vector return_vec{ 0,0 };
			for (int i = 0; i < vertex_num; i++)
			{
				int j = i + 1;
				if (j == vertex_num)j = 0;

				tri[i].vertex[0] = { pos.x,pos.y };
				tri[i].vertex[1] = { pos.x + vertexs_vec[i].x,pos.y + vertexs_vec[i].y };
				tri[i].vertex[2] = { pos.x + vertexs_vec[j].x,pos.y + vertexs_vec[j].y };

				if (tri[i].vertex[1].y > WINDOW_HEIGHT)
				{
					return_vec.y = WINDOW_HEIGHT - tri[i].vertex[1].y;
					vec.y = 0;
				}
				else if (tri[i].vertex[2].y > WINDOW_HEIGHT)
				{
					return_vec.y = WINDOW_HEIGHT - tri[i].vertex[2].y;
					vec.y = 0;
				}
			}

			pos.x += return_vec.x;
			pos.y += return_vec.y;
		}
	}

	return 0;
}

void CObject::Draw()
{
	DrawCircle(pos.x, pos.y, 1, 0xff0000, true);

	/*for (int i = 0; i < vertexs_vec.size(); i++)
	{
		int j = i + 1;
		if (j == vertexs_vec.size())j = 0;
		DrawLine(pos.x + vertexs_vec[i].x, pos.y + vertexs_vec[i].y, pos.x + vertexs_vec[j].x, pos.y + vertexs_vec[j].y, 0xffffff, true);
	}*/
	for (int i = 0; i < tri.size(); i++)
	{
		DrawLine(tri[i].vertex[0].x, tri[i].vertex[0].y, tri[i].vertex[1].x, tri[i].vertex[1].y, 0xffffff, true);
		DrawLine(tri[i].vertex[1].x, tri[i].vertex[1].y, tri[i].vertex[2].x, tri[i].vertex[2].y, 0xffffff, true);
		DrawLine(tri[i].vertex[2].x, tri[i].vertex[2].y, tri[i].vertex[0].x, tri[i].vertex[0].y, 0xffffff, true);
	}

	switch ((int)ImgWidth)
	{
	case 100:
		DrawFormatString(WINDOW_WIDTH / 2, 0, 0xffffff, "%f:%f", tri[0].vertex[1].x, tri[0].vertex[1].y);
		if (vertex_hit)
			DrawString(0, 20, "ècìñÇΩÇ¡ÇΩ", 0xffffff);
		DrawFormatString(0, 40, 0xffffff, "%f", vec.y);
		break;
	case 300:
		DrawFormatString(WINDOW_WIDTH / 2, 20, 0xffffff, "%f:%f", tri[0].vertex[1].x, tri[0].vertex[1].y);
		if (vertex_hit)
			DrawString(0, 40, "â°ìñÇΩÇ¡ÇΩ", 0xffffff);
		break;
	}
}
