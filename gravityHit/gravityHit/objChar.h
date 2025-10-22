#pragma once
#include "DxLib.h"
#include "main.h"
#include <list>
#include <memory>

using namespace std;

//�L�����N�^�[�x�[�X�N���X
class Character {
public:
	int img{ -1 };//�摜

	Point pos{ 0,0 };//�ʒu
	Vector vec{ 0,0 };//�ړ��x�N�g��

	int CutX{ 0 };//�摜�؂���ʒux
	int CutY{ 0 };//�摜�؂���ʒuy

	int ImgWidth{ 0 };//�摜�̉��T�C�Y
	int ImgHeight{ 0 };//�摜�̏c�T�C�Y

	int Dir{ 0 };//�I�u�W�F�N�g�̌���

	int sound[8]{ -1,-1,-1,-1,-1,-1,-1,-1 };

	~Character() { 
		DeleteGraph(img);
		for (int i = 0; i < 8; i++) DeleteSoundMem(sound[i]);
	}
};

//�L�����N�^�[�x�[�X3D
class Character3D :public Character{
public:
	int model{ -1 };//���f��

	Point3 pos{ 0,0,0 };//�ʒu
	Vector3 vec{ 0,0,0 };//�ړ��x�N�g��

	ObjSize size{ 0,0,0 };//�I�u�W�F�N�g�T�C�Y

	Vector3 b_box{ 0,0,0 };//�o�E���f�B���O�{�b�N�X�T�C�Y(�c,��,����)

	//�A�j���[�V���������p
	int AttachIndex{ -1 };//�A�j���[�V�����A�^�b�`No
	float animTime{ 0 };
	//�A�^�b�`�ԍ��擾
	int Attach_num_Get(int num) { return MV1AttachAnim(model, num, -1, false); }

	//�o�E���f�B���O�{�b�N�X�T�C�Y�Z�b�g
	void Set_Bounding_Box_Size(float x, float y, float z) {
		b_box.x = x;
		b_box.y = y;
		b_box.z = z;
	}

	~Character3D() { MV1DeleteModel(model); };
};
