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
	//�����蔻��
	for (auto i = base.begin(); i != base.end(); i++)
	{
		//�R����S�~
		{
			if ((*i)->ID == BURNABLE)
			{
				if ((*i)->radius == -1)
				{
					if (HitCheck_box(this, (*i).get()))
					{
						(*i)->FLAG = false;
						break;
					}
				}
				else if ((*i)->radius > 0)
				{
					if (HitCheck_Box_CircleB((*i).get(), this, (*i)->radius))
					{
						(*i)->FLAG = false;
						break;
					}
				}
			}
		}
		//�S����
		{
			if ((*i)->ID == CRUMB)
			{
				if ((*i)->radius == -1)
				{
					if (HitCheck_box(this, (*i).get()))
					{
						(*i)->FLAG = false;
						break;
					}
				}
				else if ((*i)->radius > 0)
				{
					if (HitCheck_Box_CircleB((*i).get(), this, (*i)->radius))
					{
						(*i)->FLAG = false;
						break;
					}
				}
			}
		}
		//�v���X�e�B�b�N
		{
			if ((*i)->ID == PLASTIC)
			{
				if ((*i)->radius == -1)
				{
					if (HitCheck_box(this, (*i).get()))
					{
						(*i)->FLAG = false;
						break;
					}
				}
				else if ((*i)->radius > 0)
				{
					if (HitCheck_Box_CircleB((*i).get(), this, (*i)->radius))
					{
						(*i)->FLAG = false;
						break;
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