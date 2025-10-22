#pragma once
#include "library_function.h"
#include <random>

//�I�u�W�F�N�g�\�[�g�֐�(vector)
int Pivot(vector<unique_ptr<BaseVector>>& base, int low, int hight) {
	int pivot = base[hight]->pri;//�Ō��pri�l���s�{�b�g�ɂ���
	int i = low - 1;//�������v�f�C���f�b�N�X

	for (int j = low; j < hight; j++) {
		if (base[j]->pri < pivot) {
			i++;
			swap(base[i], base[j]);//�v�f�̓���ւ�
		}
	}
	swap(base[i + 1], base[hight]);
	return i + 1;
}
void ObjSort_Quick(vector<unique_ptr<BaseVector>>& base, int low, int hight) {
	if (low < hight) {
		int pivot_position = Pivot(base, low, hight);
		ObjSort_Quick(base, low, pivot_position - 1);//����
		ObjSort_Quick(base, pivot_position + 1, hight);//�E��
	}
}


//�w��͈̗͂������擾(min,max)
int Range_Random_Number(int min, int max)
{
	random_device rd;
	default_random_engine engine(rd());
	uniform_int_distribution<int> dis(min, max);

	return dis(engine);
}

//�w��͈̗͂������擾(min,max)(32bit��)
float Range_Random_NumberF(float min, float max)
{
	random_device rd;
	mt19937 engine(rd());
	uniform_real_distribution<float> dis(min, max);

	return dis(engine);
}

//�S�ẴL�[���A�������܂őҋ@
void WAIT_RELEASE_ALL_KEY()
{
	while (true)
	{
		if (CheckHitKeyAll() == 0) break;
	}
}

//�S�ẴL�[���A�������܂őҋ@�i�^�C�v�w��j
//DX_CHECKINPUT_KEY : DX_CHECKINPUT_PAD : DX_CHECKINPUT_MOUSE
void WAIT_RELEASE_ALL_KEY(int type)
{
	while (true)
	{
		if (CheckHitKeyAll(type) == 0) break;
	}
}

//���l�̕`��i�摜�n���h��, �ꌅ�ڂ̈ʒux, �ꌅ�ڂ̈ʒuy, �l, �����T�C�Yw, �����T�C�Yh)
void DrawNum(int img, int x, int y, int num, int w, int h)
{
	//���v�Z�i�\���ʒu�Ɏg�p�j
	int digits{ 0 };
	int tmp_num = num;

	while (true)
	{
		DrawRectGraph(
			x - w / 2 - digits * w, y,
			(int)tmp_num % 10 * w, 0,
			w, h,
			img,
			true
		);
		tmp_num = tmp_num / 10;
		digits++;
		if (tmp_num == 0) break;
	}
}

//���X�g����w��I�u�W�F�N�g�̎擾
Base* Get_obj(list<unique_ptr<Base>>& base, int ID)
{
	for (auto i = base.begin(); i != base.end(); i++)
	{
		if ((*i)->ID == ID)
		{
			return (*i).get();
		}
	}
	return nullptr;
}
//���X�g����w��I�u�W�F�N�g�̎擾
Base3D* Get_obj(list<unique_ptr<Base3D>>& base, int ID)
{
	for (auto i = base.begin(); i != base.end(); i++)
	{
		if ((*i)->ID == ID)
		{
			return (*i).get();
		}
	}
	return nullptr;
}
BaseVector* Get_obj(vector<unique_ptr<BaseVector>>& base, int ID)
{
	for (int i = 0; i < base.size(); i++) {
		if (base[i]->ID == ID) {
			return base[i].get();
		}
	}

	return base[0].get();
}

//�w�肵���I�u�W�F�N�g�̍��W�擾
Point Get_Point(list<unique_ptr<Base>>& base, int ID)
{
	Point p{ 0,0 };

	for (auto i = base.begin(); i != base.end(); i++) {
		if ((*i)->ID == ID) return (*i)->pos;
	}
	return p;
}
Point Get_Point(vector<unique_ptr<Base>>& base, int ID)
{
	Point p{ 0,0 };

	for (int i = 0; i<base.size();i++) {
		if (base[i]->ID == ID) p = base[i]->pos;
	}
	return p;
}

//�w�肵���I�u�W�F�N�g�ȊO�����X�g����폜
void Del_SpecifiedObj(list<unique_ptr<Base>>& base, int ID) {
	for (auto i = base.begin(); i != base.end(); i++) {
		if ((*i)->ID != ID) {
			(*i)->FLAG = false;
			(*i)->ID = -1;
		}
	}
}
void Del_SpecifiedObj(vector<unique_ptr<Base>>& base, int ID) {
	for (auto i = 0; i<base.size();i++){
		if (base[i]->ID != ID) {
			base[i]->FLAG = false;
			base[i]->ID = -1;
		}
	}
}

//�w��I�u�W�F�N�g�����X�g����폜(FLAG��false�ɂ���)
void Del_ListObj(list<unique_ptr<Base>>& base, int ID) {
	for (auto i = base.begin(); i != base.end(); i++) {
		if ((*i)->ID == ID) {
			(*i)->FLAG = false;
			(*i)->ID = -1;
		}
	}
}
void Del_ListObj(vector<unique_ptr<Base>>& base, int ID) {
	for (int i = 0; i < base.size(); i++) {
		if (base[i]->ID == ID) {
			base[i]->FLAG = false;
			base[i]->ID = -1;
		}
	}
}

//�w��I�u�W�F�N�g�����X�g����폜�͈�(FLAG��false�ɂ���)
void Del_ListObj(list<unique_ptr<Base>>& base, int ID, int ID2) {
	for (auto i = base.begin(); i != base.end(); i++) {
		if ((*i)->ID >= ID && (*i)->ID <= ID2) {
			(*i)->FLAG = false;
			(*i)->ID = -1;
		}
	}
}
void Del_ListObj(vector<unique_ptr<Base>>& base, int ID, int ID2) {
	for (int i = 0; i < base.size();i++){
		if (base[i]->ID >= ID && base[i]->ID <= ID2) {
			base[i]->FLAG = false;
			base[i]->ID = -1;
		}
	}
}

/*
* �����������֐�
//int Range_Random_Number(int min, int max)
//{
//	return (rand() % (max - min + 1)) + min;
//}
*/
