#include "box.h"

CBox::CBox()
{
	pos.x = WINDOW_WIDTH / 2;
	pos.y = WINDOW_HEIGHT / 2;

	ImgWidth = 100;
	ImgHeight = 100;

	rc = 0.5f;
	vertex_num = 4;

	//í∏ì_ÇÃèâä˙âª
	Point p = { pos.x - ImgWidth / 2,pos.y - ImgHeight / 2 };
	vertexs.push_back(p);
	p = { pos.x + ImgWidth / 2,pos.y - ImgHeight / 2 };
	vertexs.push_back(p);
	p = { pos.x + ImgWidth / 2,pos.y + ImgHeight / 2 };
	vertexs.push_back(p);
	p = { pos.x - ImgWidth / 2,pos.y + ImgHeight / 2 };
	vertexs.push_back(p);
}

int CBox::Action(const ObjList& base, ObjList& add_list)
{


	return 0;
}

void CBox::Draw()
{
	DrawCircle(pos.x, pos.y, 1, 0xff0000, true);

	for (int i = 0; i < vertexs.size(); i++)
	{
		int j = i + 1;
		if (j == vertexs.size())j = 0;
		DrawLine(vertexs[i].x, vertexs[i].y, vertexs[j].x, vertexs[j].y, 0xffffff, true);
	}
}