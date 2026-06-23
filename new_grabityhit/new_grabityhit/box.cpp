#include "box.h"
#include "function.h"

CBox::CBox()
{
	pos.x = WINDOW_WIDTH / 2;
	pos.y = WINDOW_HEIGHT / 2;

	ImgWidth = 100;
	ImgHeight = 100;

	rc = 0.5f;
	vertex_num = 4;

	//頂点の初期化
	Vector v = { -ImgWidth / HALF, -ImgHeight / HALF };
	vertexs_vec.push_back(v);
	v = { ImgWidth / HALF, -ImgHeight / HALF };
	vertexs_vec.push_back(v);
	v = { ImgWidth / HALF,ImgHeight / HALF };
	vertexs_vec.push_back(v);
	v = { -ImgWidth / HALF,ImgHeight / HALF };
	vertexs_vec.push_back(v);

	ID = (int)ObjID::POLYGON;

	can_move = true;
}

CBox::CBox(Point _p)
{
	pos = _p;

	ImgWidth = WINDOW_WIDTH;
	ImgHeight = 100;

	rc = 0.0f;
	vertex_num = 4;

	//頂点の初期化
	Vector v = { -ImgWidth / HALF, -ImgHeight / HALF };
	vertexs_vec.push_back(v);
	v = { ImgWidth / HALF, -ImgHeight / HALF };
	vertexs_vec.push_back(v);
	v = { ImgWidth / HALF,ImgHeight / HALF };
	vertexs_vec.push_back(v);
	v = { -ImgWidth / HALF,ImgHeight / HALF };
	vertexs_vec.push_back(v);

	ID = (int)ObjID::POLYGON;
}

int CBox::Action(const ObjList& base, ObjList& add_list)
{
	if (can_move)
	{
		vec.x = vec.y = 0.0f;

		if (CheckHitKey(KEY_INPUT_W))vec.y = -4.0f;
		if (CheckHitKey(KEY_INPUT_S))vec.y = 4.0f;
		if (CheckHitKey(KEY_INPUT_A))vec.x = -4.0f;
		if (CheckHitKey(KEY_INPUT_D))vec.x = 4.0f;

		//座標更新
		PositionUpdate(this);
	}

	return 0;
}

void CBox::Draw()
{
	DrawCircle(pos.x, pos.y, 1, 0xff0000, true);

	for (int i = 0; i < vertexs_vec.size(); i++)
	{
		int j = i + 1;
		if (j == vertexs_vec.size())j = 0;
		DrawLine(pos.x + vertexs_vec[i].x, pos.y + vertexs_vec[i].y, pos.x + vertexs_vec[j].x, pos.y + vertexs_vec[j].y, 0xffffff, true);
	}
}