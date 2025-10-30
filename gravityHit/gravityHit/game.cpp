//�Q�[���V�[��
#include "DxLib.h"
#include "Scene_Manager.h"
#include "game.h"
#include "function.h"

#include "box.h"
#include "boxs.h"
#include "circle.h"
#include "circles.h"
#include "line.h"
#include "lines.h"

//�R���X�g���N�^
CGame::CGame(CManager* p) :CScene(p){
	//base.emplace_back((unique_ptr<BaseVector>)new CBox());
	//base.emplace_back((unique_ptr<BaseVector>)new CBoxs());

	//base.emplace_back((unique_ptr<BaseVector>)new CCircle());
	//base.emplace_back((unique_ptr<BaseVector>)new CCircles());

	base.emplace_back((unique_ptr<BaseVector>)new CLine());
	base.emplace_back((unique_ptr<BaseVector>)new CLines());
}

//�X�V����
int CGame::Update(){
	//�X�V����
	for (int i = 0; i < base.size(); i++)
		base[i]->Action(base);

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
}

CGame::~CGame()
{

}
