//�Q�[���V�[��
#include "DxLib.h"
#include "Scene_Manager.h"
#include "game.h"
#include "function.h"

#include "crane.h"
#include "wall.h"

#include "paper.h"
#include "can.h"

#include "incinerator.h"
#include "pressmachine.h"

//�R���X�g���N�^
CGame::CGame(CManager* p) :CScene(p) {
	//�A�[������
	base.emplace_back((unique_ptr<BaseVector>)new CCrane());
	
	Point pos; int w, h;
	//�ǐ���
	{
		pos.x = 250; pos.y = 200; w = 10; h = WINDOW_HEIGHT - pos.y;
		base.emplace_back((unique_ptr<BaseVector>)new CWall(pos, w, h));
		pos.x = 580; pos.y = 200; w = 10; h = WINDOW_HEIGHT - pos.y;
		base.emplace_back((unique_ptr<BaseVector>)new CWall(pos, w, h));
		pos.x = 850; pos.y = 0; w = 10; h = WINDOW_HEIGHT - pos.y;
		base.emplace_back((unique_ptr<BaseVector>)new CWall(pos, w, h));
		pos.x = 0; pos.y = WINDOW_HEIGHT - 10; w = 250; h = 10;
		base.emplace_back((unique_ptr<BaseVector>)new CWall(pos, w, h));
		pos.x = 260; pos.y = WINDOW_HEIGHT - 10; w = 580 - pos.x; h = 10;
		base.emplace_back((unique_ptr<BaseVector>)new CWall(pos, w, h));
		pos.x = 590; pos.y = WINDOW_HEIGHT - 10; w = 850 - pos.x; h = 10;
		base.emplace_back((unique_ptr<BaseVector>)new CWall(pos, w, h));
	}

	//���݂̉�����
	pos.x = WINDOW_WIDTH / 2; pos.y = WINDOW_HEIGHT / 2;
	base.emplace_back((unique_ptr<BaseVector>)new CPaper(pos));
	pos.x = WINDOW_WIDTH / 2 - 200;
	base.emplace_back((unique_ptr<BaseVector>)new CCan(pos));
	pos.x += 30;
	base.emplace_back((unique_ptr<BaseVector>)new CCan(pos));
	pos.x += 30;
	base.emplace_back((unique_ptr<BaseVector>)new CCan(pos));
	pos.x += 30;
	base.emplace_back((unique_ptr<BaseVector>)new CCan(pos));

	//�ċp�F�̉��𐶐�
	base.emplace_back((unique_ptr<BaseVector>)new CIncinerator());
	//�v���X�@�𐶐�
	base.emplace_back((unique_ptr<BaseVector>)new CPressmachine());
}

//�X�V����
int CGame::Update(){
	//�X�V����
	for (int i = 0; i < base.size(); i++)
		switch (base[i]->Action(base))
		{
		case 1://������
			SCORE++;
			break;
		case 2://�ԈႢ
			SCORE--;
			break;
		}

	//�폜����
	for (auto i = base.begin(); i != base.end();)
		(*i)->FLAG ? i++ : i = base.erase(i);

	//�I�u�W�F�N�g�̃\�[�g����(�N�C�b�N�\�[�g)
	ObjSort_Quick(base, 0, base.size() - 1);

	//list�I�u�W�F�N�g�̍X�V����	
	//for (auto i = base.begin(); i != base.end(); i++)
	//	(*i)->Action(base);

	return 0;
}

//�`�揈��
void CGame::Draw()
{
	//�I�u�W�F�N�g��
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Object_Count = %d", base.size());
	
	for (int i = 0; i < base.size(); i++)
		if(base[i]->FLAG) base[i]->Draw();

	//�X�R�A�̕\��
	DrawBox(900, 500, 950, 500 - SCORE * 50, GetColor(0, 255, 0), true);
}

CGame::~CGame()
{

}
