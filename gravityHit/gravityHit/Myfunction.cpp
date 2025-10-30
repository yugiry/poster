#pragma once
#include "function.h"

Point Near_Point_Line(Point P, Point A, Point B)
{
	Point Q{ 0,0 };//������̓_
	Vector n{ B.x - A.x,B.y - A.y };//�����̕����x�N�g��
	Vector AP{ P.x - A.x,P.y - A.y };//�n�_����̓_�܂ł̃x�N�g��
	float t = (AP.x * n.x + AP.y * n.y) / (n.x * n.x + n.y * n.y);//���e�W��
	if (t < 0)t = 0;//0��菬�����ꍇ�͎n�_�l
	if (t > 1)t = 1.0f;//1���傫���ꍇ�͏I�_�l
	Q = Add_Point_Vector(A, Mul_Vector_Scaler(n, t));

	return Q;
}

//�l�p�`�̓����蔻��(���W�A�����x�N�g���A�c���x�N�g��)
void HitLeft(BaseVector* b)
{
	//���オ������荶�ɂ����
	if (b->pos.x <= b->pos.x + b->VH.x)
	{
		//�E�オ�����荶�ɂ����
		if (b->pos.x + b->VW.x < b->pos.x && b->pos.x + b->VW.x < 0);

		if (b->pos.x < 0);
		
	}
	//�����������荶�ɂ����
	else
	{
		//�E����������荶�ɂ����
		if (b->pos.x + b->VH.x + b->VW.x < b->pos.x + b->VH.x && b->pos.x + b->VH.x + b->VW.x < 0);
		if (b->pos.x + b->VH.x < 0);
	}

	//�����������Ă��Ȃ����
	return;
}
void HitRight(BaseVector* b)
{
	//���オ�������E�ɂ����
	if (b->pos.x >= b->pos.x + b->VH.x)
	{
		//�E�オ������E�ɂ����
		if (b->pos.x + b->VW.x > b->pos.x && b->pos.x + b->VW.x > WINDOW_WIDTH);

		if (b->pos.x > WINDOW_WIDTH);

	}
	//������������E�ɂ����
	else
	{
		//�E�����������E�ɂ����
		if (b->pos.x + b->VH.x + b->VW.x > b->pos.x + b->VH.x && b->pos.x + b->VH.x + b->VW.x > WINDOW_WIDTH);
		if (b->pos.x + b->VH.x > WINDOW_WIDTH);
	}

	//�����������Ă��Ȃ����
	return;
}
void HitUp(BaseVector* b)
{
	//���オ������荶�ɂ����
	if (b->pos.y <= b->pos.y + b->VH.y)
	{
		//�E�オ�����荶�ɂ����
		if (b->pos.y + b->VW.y < b->pos.y && b->pos.y + b->VW.y < 0);

		if (b->pos.y < 0);

	}
	//�����������荶�ɂ����
	else
	{
		//�E����������荶�ɂ����
		if (b->pos.y + b->VH.y + b->VW.y < b->pos.y + b->VH.y && b->pos.y + b->VH.y + b->VW.y < 0);
		if (b->pos.y + b->VH.y < 0);
	}

	//�����������Ă��Ȃ����
	return;
}
void HitDown(BaseVector* b)
{
	//���オ�������E�ɂ����
	if (b->pos.y >= b->pos.y + b->VH.y)
	{
		//�E�オ������E�ɂ����
		if (b->pos.y + b->VW.y > b->pos.y && b->pos.y + b->VW.y > WINDOW_HEIGHT)
		{
			b->pos.y = WINDOW_HEIGHT - b->VW.y;
			b->vec.y = 0;
			return;
		}

		if (b->pos.y > WINDOW_HEIGHT)
		{
			b->pos.y = WINDOW_HEIGHT;
			b->vec.y = 0;
			return;
		}

	}
	//������������E�ɂ����
	else
	{
		//�E�����������E�ɂ����
		if (b->pos.y + b->VH.y + b->VW.y > b->pos.y + b->VH.y && b->pos.y + b->VH.y + b->VW.y > WINDOW_HEIGHT)
		{
			b->pos.y = WINDOW_HEIGHT - b->VW.y - b->VH.y;
			b->vec.y = 0; 
			return;
		}
		if (b->pos.y + b->VH.y > WINDOW_HEIGHT)
		{
			b->pos.y = WINDOW_HEIGHT - b->VH.y;
			b->vec.y = 0;
			return;
		}
	}

	//�����������Ă��Ȃ����
	return;
}
