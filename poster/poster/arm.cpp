#pragma once
#include "arm.h"
#include "function.h"
#include "hitobj.h"

constexpr bool OPEN = true;		//�A�[�����J���Ă���
constexpr bool CLOSE = false;	//�A�[�������Ă���

CArm::CArm()
{
	//�A�[���̏����ʒu
	pos.x = 0;
	pos.y = 20;

	//�A�[���̉摜�T�C�Y
	ImgWidth = 64;
	ImgHeight = 64;

	arm_state = CLOSE;

	//�{�^����������Ă��邩����̏�����
	for (int i = 0; i < HBEND; i++)
	{
		Click_Check[i] = false;
	}
}

int CArm::Action(vector<unique_ptr<BaseVector>>& base)
{
	//�A�[�����܂��Ă��鎞
	if (arm_state == CLOSE)
	{
		//����͂ޔ�����o��
		base.emplace_back((unique_ptr<BaseVector>)new CHitobj(pos));
	}

	//�ړ��x�N�g���̃��Z�b�g
	vec.x = vec.y = 0;

	//�A�[���������Ă���
	if (move_time == 0)
	{
		move_time--;
		arm_state = CLOSE;
	}
	if (move_time > 0)
	{
		move_time--;
	}

	//�A�[�����J��
	if (arm_open == 0)
	{
		arm_open--;
		arm_state = OPEN;
		arm_down = true;
	}
	if (arm_open > 0)
	{
		arm_open--;
	}

	//�A�[����������
	if (CheckHitKey(KEY_INPUT_F) && !Click_Check[F] && !arm_down && pos.y == 20)
	{
		arm_open = 30;
	}

	//�A�[�����������Ă��Ȃ���
	if (!arm_down && pos.y <= 20 && move_time < 0)
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

					}
				}
				else if ((*i)->radius > 0)
				{
					if (HitCheck_Box_CircleB((*i).get(), this, (*i)->radius))
					{
						arm_down = false;
						move_time = GRAP_TIME;
						vec.y -= 4.0f;
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

				}
				else if ((*i)->radius > 0)
				{

				}
			}
		}
		//�v���X�e�B�b�N
		{
			if ((*i)->ID == PLASTIC)
			{
				if ((*i)->radius == -1)
				{

				}
				else if ((*i)->radius > 0)
				{

				}
			}
		}
	}

	//���W�X�V
	pos.x += vec.x;
	pos.y += vec.y;

	//���E�Ɉړ��ł���͈͎w��
	if (pos.x < 0)pos.x = 0;
	if (pos.x > GAME_WIDTH -ImgWidth)pos.x = GAME_WIDTH - ImgWidth;

	return 0;
}

void CArm::Draw()
{
	DrawBox(pos.x, pos.y, pos.x + ImgWidth, pos.y + ImgHeight, GetColor(255, 0, 0), true);
}