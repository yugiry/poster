#pragma once
#include "objBase.h"
#include "2D_function.h"
#include "3D_function.h"

//�I�u�W�F�N�g�\�[�g�֐�(vector)
void ObjSort_Quick(vector<unique_ptr<BaseVector>>&, int, int);

//�w��͈̗͂������擾(min,max)
int Range_Random_Number(int, int);
float Range_Random_NumberF(float, float);

//�S�ẴL�[���A�������܂őҋ@
void WAIT_RELEASE_ALL_KEY();

//�S�ẴL�[���A�������܂őҋ@�i�^�C�v�w�� DX_CHECKINPUT_KEY : DX_CHECKINPUT_PAD : DX_CHECKINPUT_MOUS)
void WAIT_RELEASE_ALL_KEY(int);

//���l�̕`��i�摜�n���h��, �ꌅ�ڂ̈ʒux, �ꌅ�ڂ̈ʒuy, �l, �����T�C�Yw, �����T�C�Yh)
void DrawNum(int, int, int, int, int, int);

//���X�g����w��I�u�W�F�N�g�̎擾
Base* Get_obj(list<unique_ptr<Base>>&, int);
Base3D* Get_obj(list<unique_ptr<Base3D>>&, int);
BaseVector* Get_obj(vector<unique_ptr<BaseVector>>&, int);

//�w�肵���I�u�W�F�N�g�̍��W�擾
Point Get_Point(list<unique_ptr<Base>>&, int);
Point Get_Point(vector<unique_ptr<BaseVector>>&, int);

//�w�肵���I�u�W�F�N�g�ȊO�����X�g����폜
void Del_SpecifiedObj(list<unique_ptr<Base>>&, int);
void Del_SpecifiedObj(vector<unique_ptr<Base>>&, int);

//�w��I�u�W�F�N�g�����X�g����폜(FLAG��false�ɂ���)
void Del_ListObj(list<unique_ptr<Base>>&, int);
void Del_ListObj(vector<unique_ptr<Base>>&, int);

//�w��I�u�W�F�N�g�����X�g����폜�͈�(FLAG��false�ɂ���)
void Del_ListObj(list<unique_ptr<Base>>&, int, int);
void Del_ListObj(vector<unique_ptr<Base>>&, int, int);