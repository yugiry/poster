#pragma once
#include "pressmachine.h"
#include "function.h"

CPressmachine::CPressmachine()
{
	pos.x = 0;
	pos.y = 350;

	ImgWidth = 250;
	ImgHeight = 20;
}

int CPressmachine::Action(vector<unique_ptr<BaseVector>>& base)
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
						break;
					}
				}
				else if ((*i)->radius > 0)
				{
					if (HitCheck_Box_CircleB((*i).get(), this, (*i)->radius))
					{
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
						break;
					}
				}
				else if ((*i)->radius > 0)
				{
					if (HitCheck_Box_CircleB((*i).get(), this, (*i)->radius))
					{
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
						break;
					}
				}
				else if ((*i)->radius > 0)
				{
					if (HitCheck_Box_CircleB((*i).get(), this, (*i)->radius))
					{
						break;
					}
				}
			}
		}
	}

	return 0;
}

void CPressmachine::Draw()
{
	DrawBox(pos.x, pos.y, pos.x + ImgWidth, pos.y + ImgHeight, GetColor(255, 0, 0), false);
}