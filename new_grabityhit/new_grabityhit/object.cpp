#include "object.h"

CObject::CObject(int _type)
{
	switch (_type)
	{
	case 0:
		pos.x = WINDOW_WIDTH / 2;
		pos.y = WINDOW_HEIGHT / 2;

		ImgWidth = 100;
		ImgHeight = 100;
		break;
	case 1:
		pos.x = WINDOW_WIDTH / 2;
		pos.y = WINDOW_HEIGHT - 50;

		ImgWidth = WINDOW_WIDTH;
		ImgHeight = 100;
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

		poly.vertex[0] = { pos.x,pos.y };
		poly.vertex[1] = { pos.x + vertexs_vec[i].x,pos.y + vertexs_vec[i].y };
		poly.vertex[2] = { pos.x + vertexs_vec[j].x,pos.y + vertexs_vec[j].y };

		tri.push_back(poly);
	}

	ID = (int)ObjID::POLYGON;
}

int CObject::Action(const ObjList& base, ObjList& add_list)
{
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
		DrawLine(tri[i].vertex[2].x, tri[i].vertex[2].y, tri[i].vertex[1].x, tri[i].vertex[1].y, 0xffffff, true);
	}
}
