#pragma once
#include "CCamera.h"
#include "3D_function.h"

CCamera::CCamera() {
	GetMousePoint(&tmp_mouseX, &tmp_mouseY);//���݂̃}�E�X�̈ʒu����ۑ�

	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;

	target.x = 0.0f;
	target.y = 0.0f;
	target.z = 0.0f;

	//�J��������
	SetCameraNearFar(0.051f, 1000.0f);
}

//���L�[�ŃJ�����ړ�(�^�[�Q�b�g�͌��_)
void CCamera::Action() {
	//���E�ړ�
	if (CheckHitKey(KEY_INPUT_LEFT)) pos.x -= 1.0f;
	if (CheckHitKey(KEY_INPUT_RIGHT)) pos.x += 1.0f;

	//���V�t�g�����Ȃ���㉺��z��
	if (CheckHitKey(KEY_INPUT_LSHIFT)) {
		if (CheckHitKey(KEY_INPUT_UP)) pos.z += 1.0f;
		if (CheckHitKey(KEY_INPUT_DOWN)) pos.z -= 1.0f;
	}
	else {
		if (CheckHitKey(KEY_INPUT_UP)) pos.y += 1.0f;
		if (CheckHitKey(KEY_INPUT_DOWN)) pos.y -= 1.0f;
	}

	//�J�����̏��X�V
	SetCameraPositionAndTarget_UpVecY(
		VGet(pos.x, pos.y, pos.z),
		VGet(target.x, target.y, target.z)
	);
}

//�w�肵���I�u�W�F�N�g��ǐ�
void CCamera::Action(Base3D* obj, list<unique_ptr<Base3D>>& base) {

	GetMousePoint(&mouseX, &mouseY);//�}�E�X�̈ʒu���擾

	//�}�E�X�̈ړ������擾
	horizontal_angle -= (mouseX - tmp_mouseX) * 0.2f;
	vertical_angle += (mouseY - tmp_mouseY) * 0.2f;

	//�c��] 90���ŉ�]���~�߂�i�J���������]����ׁj
	if (horizontal_angle >= 360)horizontal_angle = 0;
	if (horizontal_angle <= -360)horizontal_angle = 0;

	if (vertical_angle >= 90)vertical_angle = 89;
	if (vertical_angle <= -10)vertical_angle = -10;

	//�����_�̌v�Z
	Point3 target = obj->pos;
	target.y += LOOK_AT_HEIGHT;

	//�v�Z�p�ϐ�
	float sin_param, cos_param;//��]�p
	Point3 p1, p2;//�v�Z�p�ʒu

	//yz���ʂ̉�]
	sin_param = (float)sin(RADIAN(vertical_angle));
	cos_param = (float)cos(RADIAN(vertical_angle));
	p1.x = 0.0f;
	p1.y = sin_param * LOOK_AT_DISTANCE;
	p1.z = -cos_param * LOOK_AT_DISTANCE;

	//xz���ʂ̉�]
	sin_param = (float)sin(RADIAN(horizontal_angle));
	cos_param = (float)cos(RADIAN(horizontal_angle));
	p2.x = cos_param * p1.x - sin_param * p1.z;
	p2.y = p1.y;
	p2.z = sin_param * p1.x + cos_param * p1.z;

	//�J�����̈ʒu���v�Z
	pos.x = p2.x + target.x;
	pos.y = p2.y + target.y;
	pos.z = p2.z + target.z;

	//�J�����̏��X�V
	SetCameraPositionAndTarget_UpVecY(
		VGet(pos.x, pos.y, pos.z),
		VGet(target.x, target.y, target.z)
	);

	//�}�E�X�̈ʒu����ʒ����Ɉړ�
	SetMousePoint(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	//�}�E�X�̈ʒu���ۑ�
	GetMousePoint(&tmp_mouseX, &tmp_mouseY);

	//�J�������̈ʒu�X�V(�O���[�o��)
	//CCameraInfo::SetPos(pos);
}

void CCamera::Draw() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%.0lf,%.0lf,%.0lf", pos.x, pos.y, pos.z);
}

void CCamera::Action(list<unique_ptr<Base3D>>& base) {}
CCamera::~CCamera() {}