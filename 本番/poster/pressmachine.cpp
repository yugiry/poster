#pragma once
#include "pressmachine.h"
#include "function.h"
#include "hitobj.h"
#include "scrap.h"

CPressmachine::CPressmachine()
{
	pos.x = 0;
	pos.y = 100;

	ImgWidth = 250;
	ImgHeight = 20;

	Top.x = Bottom.x = 0;
	Top.y = 400; Bottom.y = 570;

	Thit_Size.x = 250; Thit_Size.y = 20;
	Bhit_Size.x = 250; Bhit_Size.y = 20;
}

int CPressmachine::Action(vector<unique_ptr<BaseVector>>& base)
{
	//ƒvƒŒƒX‹@‚ð‰º‚°‚é
	if (CheckHitKey(KEY_INPUT_I) && !press_start && can_press)
	{
		press_start = true;
	}

	//“–‚½‚è”»’è
	{
		for (auto i = base.begin(); i != base.end(); i++)
		{
			if ((*i)->ID == BURNABLE || (*i)->ID == CRUMB || (*i)->ID == PLASTIC)
			{
				if ((*i)->radius == -1)
				{
					if (HitCheck_box(Bottom.x, Bottom.y, (*i)->pos.x, (*i)->pos.y, Bhit_Size.x, Bhit_Size.y, (*i)->ImgWidth, (*i)->ImgHeight))
					{
						bottom_hit = true;
					}
				}
				else if ((*i)->radius > 0)
				{
					if (HitCheck_box(Bottom.x, Bottom.y, (*i)->pos.x, (*i)->pos.y, Bhit_Size.x, Bhit_Size.y, (*i)->ImgWidth, (*i)->ImgHeight))
					{
						bottom_hit = true;
					}
				}
			}

			if ((*i)->ID == SCRAP)
			{
				if (HitCheck_box(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y, ImgWidth, ImgHeight, (*i)->ImgWidth, (*i)->ImgHeight))
				{
					reverse = true;
					more_press = false;
					vec.y = 0;
				}
			}
		}
		for (auto i = base.begin(); i != base.end(); i++)
		{
			if ((*i)->ID == BURNABLE || (*i)->ID == CRUMB || (*i)->ID == PLASTIC)
			{
				if ((*i)->radius == -1)
				{
					if (HitCheck_box(Top.x, Top.y, (*i)->pos.x, (*i)->pos.y, Thit_Size.x, Thit_Size.y, (*i)->ImgWidth, (*i)->ImgHeight) && bottom_hit)
					{
						can_press = true;
					}
				}
				else if ((*i)->radius > 0)
				{
					if (HitCheck_box(Top.x, Top.y, (*i)->pos.x, (*i)->pos.y, Thit_Size.x, Thit_Size.y, (*i)->ImgWidth, (*i)->ImgHeight) && bottom_hit)
					{
						can_press = true;
					}
				}
			}
		}
	}

	if (press_start)
	{
		if(HitCheck_box(pos.x,pos.y,Top.x,Top.y,ImgWidth,ImgHeight,Thit_Size.x,Thit_Size.y) && !more_press && !reverse)
		{
			more_press = true;
			Point p{ pos.x + 5,pos.y + ImgHeight + 10 };
			Vector v{ 0,0 };
			base.emplace_back((unique_ptr<BaseVector>)new CScrap(p));
			base.emplace_back((unique_ptr<BaseVector>)new CHitobj(Top, v, Thit_Size.x, Top.y + Bottom.y + Bhit_Size.y, 100, GDELETE));
		}
		if (!reverse)vec.y = speed;
		else vec.y = -speed;

		if (more_press)
		{
			vec.y = speed / 2;
		}
	}

	if (reverse && pos.y <= 100)
	{
		can_press = false;
		reverse = false;
		bottom_hit = false;
		pos.y = 100;
	}

	pos.y += vec.y;

	if (!bottom_hit)can_press = false;
	bottom_hit = false;

	return 0;
}

void CPressmachine::Draw()
{
	DrawBox(Top.x, Top.y, Top.x + Thit_Size.x, Top.y + Thit_Size.y, GetColor(255, 0, 0), false);

	DrawBox(Bottom.x, Bottom.y, Bottom.x + Bhit_Size.x, Bottom.y + Bhit_Size.y, GetColor(255, 0, 0), false);

	if (press_start)
		DrawBox(pos.x, pos.y, pos.x + ImgWidth, pos.y + ImgHeight, GetColor(0, 0, 255), false);
}