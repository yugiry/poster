#pragma once
#include "objBase.h"

class CCamera {
public:
	CCamera();

	void Action();
	void Action(Base3D*, list<unique_ptr<Base3D>>&);//�w�肵���I�u�W�F�N�g��ǐ�
	void Action(list<unique_ptr<Base3D>>&);

	//�ǐՂ���w��I�u�W�F�N�g�ɑ΂��Ă̊�ƂȂ�J�����̍���
	float LOOK_AT_HEIGHT{ 2.5 };
	//�ǐՂ���w��I�u�W�F�N�g�ɑ΂��ẴJ��������
	float LOOK_AT_DISTANCE{ 10 };

	Point3 pos{ 0,0,0 };//�J�����̈ʒu
	Point3 target{ 0,0,0 };//�J�����̒����_

	int mouseX{ 0 }, mouseY{ 0 };//�}�E�X�̈ʒu
	int tmp_mouseX{ 0 }, tmp_mouseY{ 0 };//�}�E�X�̈ʒu�ۑ��p

	float horizontal_angle{ 0 };//xy���ʊp(UpVecY)
	float vertical_angle{ 0 };//yz���ʊp(UpVecY)

	void Draw();//�J�������`��

	~CCamera();
};