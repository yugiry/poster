#pragma once
#include "main.h"
#include "objChar.h"

using namespace std;

//�I�u�W�F�N�g�x�[�X�N���X(list)
class Base : public Character {
public:
	int pri{ 0 };//�`��̏���
	int ID{ -1 };//�I�u�W�F�N�gID
	bool FLAG{ true };//�I�u�W�F�N�g���݃t���O
	bool draw_flag{ true };//�I�u�W�F�N�g�̕`��t���O

	virtual int Action(list<unique_ptr<Base>>&) = 0;
	virtual void Draw() = 0;
	virtual ~Base() {};
};

//�I�u�W�F�N�g�x�[�X�N���X(vector)
class BaseVector : public Character {
public:
	int pri{ 0 };//�`��̏���
	int ID{ -1 };//�I�u�W�F�N�gID
	bool FLAG{ true };//�I�u�W�F�N�g���݃t���O
	bool draw_flag{ true };//�I�u�W�F�N�g�̕`��t���O

	virtual int Action(vector<unique_ptr<BaseVector>>&) = 0;
	virtual void Draw() = 0;
	virtual ~BaseVector() {};
};

//�I�u�W�F�N�g�̃\�[�g�N���X
class sort
{
public:
	bool operator()(const unique_ptr<Base>& x, const unique_ptr<Base>& y) const
	{
		return x.get()->pri < y.get()->pri;
	}
};

//�I�u�W�F�N�g�̃\�[�g�N���X�iy���W�Ń\�[�g)
class sort_position_Y
{
public:
	bool operator()(const unique_ptr<Base>& a, const unique_ptr<Base>& b) const
	{
		return a.get()->pos.y < b.get()->pos.y;
	}
};


//3D�p
class Base3D : public Character3D {
public:
	int ID{ -1 };//�I�u�W�F�N�gID
	bool FLAG{ true };//�I�u�W�F�N�g���݃t���O
	bool draw_flag{ true };//�I�u�W�F�N�g�̕`��t���O

	virtual int Action(list<unique_ptr<Base3D>>&) = 0;
	virtual void Draw() = 0;
};
