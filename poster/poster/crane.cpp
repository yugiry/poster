#pragma once
#include "crane.h"
#include "function.h"
#include "hitobj.h"

constexpr bool OPEN = true;		//�A�[�����J���Ă���
constexpr bool CLOSE = false;	//�A�[�������Ă���

CCrane::CCrane()
{
	//�A�[���̏����ʒu
	pos.x = 0;
	pos.y = 20;

	//�A�[���̉摜�T�C�Y
	ImgWidth = 64;
	ImgHeight = 48;

	arm_state = CLOSE;

	//�{�^����������Ă��邩����̏�����
	for (int i = 0; i < HBEND; i++)
	{
		Click_Check[i] = false;
	}

	Point p;
	p.x = pos.x + 8; p.y = pos.y + ImgHeight;
	Larm = new CArm(p);
	p.x = pos.x + ImgWidth - 8;
	Rarm = new CArm(p);
}

int CCrane::Action(vector<unique_ptr<BaseVector>>& base)
{
	//�A�[�����܂��Ă��鎞
	if (arm_state == CLOSE)
	{
		Point p{ pos.x,pos.y + ImgHeight };
		//����͂ޔ�����o��
		base.emplace_back((unique_ptr<BaseVector>)new CHitobj(p, vec, ImgWidth, 32, 1, ARM));
	}

	//�ړ��x�N�g���̃��Z�b�g
	vec.x = vec.y = 0;

	//�A�[���������Ă���
	if (move_time == 0)
	{
		move_time--;
	}
	if (move_time > 0)
	{
		move_time--;
	}

	if (close_time == 0)
	{
		close_time--;
		Click_Check[R] = false;
	}
	if (close_time > 0)
	{
		close_time--;
		arm_state = CLOSE;
	}

	//�A�[�����J��
	if (arm_open == 0 && Click_Check[F])
	{
		arm_open--;
		arm_down = true;
		Click_Check[F] = false;
	}
	if (arm_open == 0 && Click_Check[R])
	{
		arm_open--;
		close_time = 30;
	}
	if (arm_open > 0)
	{
		arm_open--;
		arm_state = OPEN;
	}

	//�A�[����������
	if (CheckHitKey(KEY_INPUT_J) && !arm_down && pos.y == 20)
	{
		arm_open = 30;
		Click_Check[F] = true;
	}
	//�A�[�����J��
	if (CheckHitKey(KEY_INPUT_U) && !Click_Check[R])
	{
		arm_open = 30;
		Click_Check[R] = true;
	}

	//�A�[�����������Ă��Ȃ���
	if (!arm_down && pos.y <= 20 && move_time < 0 && arm_open < 0)
	{
		//���E�ړ�
		if (CheckHitKey(KEY_INPUT_A) && !Click_Check[A])
		{
			vec.x = -3.0f;
		}
		if (CheckHitKey(KEY_INPUT_D) && !Click_Check[D])
		{
			vec.x = 3.0f;
		}
	}

	//�A�[����������
	if (arm_down)
	{
		vec.y = 4.0f;
	}
	//�A�[����������
	if (!arm_down && pos.y > 20 && move_time < 0)
	{
		vec.y = -4.0f;
	}

	//�����蔻��
	for (auto i = base.begin(); i != base.end(); i++)
	{
		//��
		if ((*i)->ID == WALL)
		{
			Point late{ pos.x,pos.y + vec.y };
			if (HitCheck_box(late.x, late.y, (*i)->pos.x, (*i)->pos.y, ImgWidth, ImgHeight, (*i)->ImgWidth, (*i)->ImgHeight))
			{
				arm_down = false;
				move_time = GRAP_TIME;
				vec.y -= 4.0f;
				arm_state = CLOSE;
			}
		}

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
						arm_down = false;
						move_time = GRAP_TIME;
						vec.y -= 4.0f;
						pos.y += vec.y;
						Larm->pos.y += vec.y;
						Rarm->pos.y += vec.y;
						arm_state = CLOSE;
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
						arm_down = false;
						move_time = GRAP_TIME;
						vec.y -= 4.0f;
						pos.y += vec.y;
						Larm->pos.y += vec.y;
						Rarm->pos.y += vec.y;
						arm_state = CLOSE;
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

	//���W�X�V
	pos.x += vec.x;
	pos.y += vec.y;
	Larm->pos.x += vec.x;
	Larm->pos.y += vec.y;
	Rarm->pos.x += vec.x;
	Rarm->pos.y += vec.y;

	//���E�Ɉړ��ł���͈͎w��
	if (pos.x < 0)pos.x = 0;
	if (pos.x > GAME_WIDTH -ImgWidth)pos.x = GAME_WIDTH - ImgWidth;

	Larm->pos.x = pos.x + 8;
	Larm->pos.y = pos.y + ImgHeight;
	Rarm->pos.x = pos.x + ImgWidth - 8;
	Rarm->pos.y = pos.y + ImgHeight;

	Larm->Action(base);
	Rarm->Action(base);

	return 0;
}

void CCrane::Draw()
{
	DrawBox(pos.x, pos.y, pos.x + ImgWidth, pos.y + ImgHeight, GetColor(255, 0, 0), true);

	Larm->Draw();
	Rarm->Draw();
}