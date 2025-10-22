//DX Library Copyright (C) 2001-2022 Takumi Yamada.
//Dxlib_lib_6.0 2025 Kcom�e���v���[�g Shinya Wakisaka.
#pragma once
#include "main.h"
#include "Scene_Manager.h"
//#include "Title.h"
#include "game.h"

constexpr auto FPS = 60;//��{FPS

//Point3 CCameraInfo::pos;//�J������񏉊���(�O���[�o���j

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE,
	_In_ LPWSTR lpCmdline, _In_ int nShowCmd)
{
	//Dx���C�u�����̃��O�o��off
	SetOutApplicationLogValidFlag(false);

	//window���[�h�؂�ւ�
	ChangeWindowMode(true);
	//window�T�C�Y
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
	//�o�b�N�O���E���h�����̋���
	SetAlwaysRunFlag(true);
	//���d�N���̋���
	SetDoubleStartValidFlag(true);

	//Dx���C�u�����̏�����
	if (DxLib_Init() == -1) return -1;

	//window�̖��O
	SetWindowText("");

	//�`�����o�b�N�o�b�t�@�ɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	//3D�Ɋւ��鏉���ݒ�
	SetUseLighting(false);//���C�g�I�t
	SetUseZBuffer3D(true);//z�o�b�t�@�L��
	SetWriteZBuffer3D(true);//z�o�b�t�@�ւ̏������݂�L���ɂ���

	//�V�[���Ǘ��N���X
	CManager* manager = new CManager();

	//����V�[���̐���
	//manager->scene = new CTitle(manager);
	manager->scene = new CGame(manager);


	//���[�v
	while (true) {
		ClearDrawScreen();	//��ʃN���A

		double nextTime = GetNowCount();	//���ݎ��Ԃ̎擾

		//�V�[���̍X�V�ƕ`�揈��
		manager->Update();
		manager->Draw();

		//FPS����
		nextTime += 1000 / FPS;	//1�t���[���ɂ����鎞�Ԃ����Z
		if (nextTime > GetNowCount()) {
			//�������Ԃ��w��FPS�̎��Ԃ��o�߂��Ă��Ȃ��ꍇ�A�o�߂܂őҋ@
			WaitTimer((int)nextTime - GetNowCount());
		}

		ScreenFlip();	//��ʂ��X�V

		//esc�L�[�Ńv���O�����I��
		if (CheckHitKey(KEY_INPUT_ESCAPE) || (ProcessMessage() == -1)) break;
	}

	//�V�[���̍폜
	delete manager;

	//Dx���C�u�����I������
	DxLib_End();

	return 0;
}