#pragma once
#include "boxs.h"
#include "function.h"

CBoxs::CBoxs()
{
	ImgWidth = 300;
	ImgHeight = 80;

	pos.x = WINDOW_WIDTH / 2 - ImgWidth / 2;
	pos.y = WINDOW_HEIGHT / 2 - ImgHeight / 2;

	radian = 0;

	VW.x = cos(radian);
	VW.y = sin(radian);

	VW = Vector_SetLength(VW, ImgWidth);

	VH.x = VW.y;
	VH.y = VW.x;

	VH = Vector_SetLength(VH, ImgHeight);

	ID = B2;
}

int CBoxs::Action(vector<unique_ptr<BaseVector>>& base)
{
	vec.x = 0.0f; 
	vec.y = 0.0f;
	//vec.y += g;

	GetMousePoint(&x, &y);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) && !click)
	{
		ClickX = x; ClickY = y;
		click = true;
	}
	click = (GetMouseInput() & MOUSE_INPUT_LEFT);

	if (click)
	{

	}

	/*if (CheckHitKey(KEY_INPUT_U))
	{
		radian -= 6;
	}
	if (CheckHitKey(KEY_INPUT_I))
	{
		radian += 6;
	}*/

	pos.x += VW.x / 2 + VH.x / 2;
	pos.y += VW.y / 2 + VH.y / 2;

	VW.x = cos(RADIAN(radian));
	VW.y = sin(RADIAN(radian));

	VW = Vector_SetLength(VW, ImgWidth);

	VH.x = -VW.y;
	VH.y = VW.x;

	VH = Vector_SetLength(VH, ImgHeight);

	if (radian < 0)radian = 359;
	if (radian >= 360)radian = 0;

	pos.x -= VW.x / 2 + VH.x / 2;
	pos.y -= VW.y / 2 + VH.y / 2;

	//¶ã‚ª¶‰º‚æ‚è‰º‚É‚¢‚ê‚Î
	if (pos.y >= pos.y + VH.y)
	{
		//‰Eã‚ª¶ã‚æ‚è‰º‚É‚¢‚ê‚Î
		if (pos.y + VW.y > pos.y && pos.y + VW.y > WINDOW_HEIGHT)
		{
			pos.y = WINDOW_HEIGHT - VW.y;
			vec.y = -(vec.y * 0.4f);
		}

		if (pos.y > WINDOW_HEIGHT)
		{
			pos.y = WINDOW_HEIGHT;
			vec.y = -(vec.y * 0.4f);
		}
	}
	//¶‰º‚ª¶ã‚æ‚è‰º‚É‚¢‚ê‚Î
	else
	{
		//‰E‰º‚ª¶‰º‚æ‚è‰º‚É‚¢‚ê‚Î
		if (pos.y + VH.y + VW.y > pos.y + VH.y && pos.y + VH.y + VW.y > WINDOW_HEIGHT)
		{
			pos.y = WINDOW_HEIGHT - VW.y - VH.y;
			vec.y = -(vec.y * 0.4f);
		}
		if (pos.y + VH.y > WINDOW_HEIGHT)
		{
			pos.y = WINDOW_HEIGHT - VH.y;
			vec.y = -(vec.y * 0.4f);
		}
	}

	pos.x += vec.x;
	pos.y += vec.y;

	return 0;
}

void CBoxs::Draw()
{
	DrawLine(pos.x, pos.y, pos.x + VW.x, pos.y + VW.y, GetColor(255, 255, 255), true);
	DrawLine(pos.x, pos.y, pos.x + VH.x, pos.y + VH.y, GetColor(0, 255, 255), true);
	DrawLine(pos.x + VW.x + VH.x, pos.y + VW.y + VH.y, pos.x + VW.x, pos.y + VW.y, GetColor(255, 0, 255), true);
	DrawLine(pos.x + VW.x + VH.x, pos.y + VW.y + VH.y, pos.x + VH.x, pos.y + VH.y, GetColor(255, 255, 0), true);

	if (click)
	{
		DrawLine(x, y, ClickX, ClickY, GetColor(0, 255, 0), true);
	}
}
