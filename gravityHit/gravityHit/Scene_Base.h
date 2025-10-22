#pragma once
#include "Scene_Manager.h"

class CManager;//�V�[���Ǘ��N���X

//�V�[���x�[�X�N���X
class CScene {
protected:
	CManager* manager{ nullptr };
public:
	CScene(CManager* pManager) { manager = pManager; };

	//�X�V����
	virtual int Update() { return 0; };
	//�`�揈��
	virtual void Draw() {};
	//�f�X�g���N�^
	virtual ~CScene() {};
};