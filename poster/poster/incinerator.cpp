#pragma once
#include "incinerator.h"

#include "function.h"

CIncinerator::CIncinerator()
{
	pos.x = 590;
	pos.y = 550;

	ImgWidth = 260;
	ImgHeight = 40;

	ID = INCINERATOR;
}

int CIncinerator::Action(vector<unique_ptr<BaseVector>>& base)
{
	//当たり判定
	for (auto i = base.begin(); i != base.end(); i++)
	{
		//燃えるゴミ
		{
			if ((*i)->ID == BURNABLE)
			{
				if ((*i)->radius == -1)
				{
					if (HitCheck_box(this, (*i).get()))
					{
						(*i)->FLAG = false;
						return 1;
					}
				}
				else if ((*i)->radius > 0)
				{
					if (HitCheck_Box_CircleB((*i).get(), this, (*i)->radius))
					{
						(*i)->FLAG = false;
						return 1;
					}
				}
			}
		}
		//鉄ごみ
		{
			if ((*i)->ID == CRUMB)
			{
				if ((*i)->radius == -1)
				{
					if (HitCheck_box(this, (*i).get()))
					{
						(*i)->FLAG = false;
						return 2;
					}
				}
				else if ((*i)->radius > 0)
				{
					if (HitCheck_Box_CircleB((*i).get(), this, (*i)->radius))
					{
						(*i)->FLAG = false;
						return 2;
					}
				}
			}
		}
		//プラスティック
		{
			if ((*i)->ID == PLASTIC)
			{
				if ((*i)->radius == -1)
				{
					if (HitCheck_box(this, (*i).get()))
					{
						(*i)->FLAG = false;
						return 2;
					}
				}
				else if ((*i)->radius > 0)
				{
					if (HitCheck_Box_CircleB((*i).get(), this, (*i)->radius))
					{
						(*i)->FLAG = false;
						return 2;
					}
				}
			}
		}
	}

	return 0;
}

void CIncinerator::Draw()
{
	DrawBox(pos.x, pos.y, pos.x + ImgWidth, pos.y + ImgHeight, GetColor(255, 0, 0), false);
}