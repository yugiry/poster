//ゲームシーン
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

//コンストラクタ
CGame::CGame(CManager* p) :CScene(p) {
	//アーム生成
	base.emplace_back((unique_ptr<BaseVector>)new CCrane());
	
	Point pos; int w, h;
	//壁生成
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

	pos.x = WINDOW_WIDTH / 2; pos.y = WINDOW_HEIGHT / 2;
	base.emplace_back((unique_ptr<BaseVector>)new CPaper(pos));
	pos.x = WINDOW_WIDTH / 2 - 200;
	base.emplace_back((unique_ptr<BaseVector>)new CCan(pos));

	//焼却炉の炎を生成
	base.emplace_back((unique_ptr<BaseVector>)new CIncinerator());
	//プレス機を生成
	base.emplace_back((unique_ptr<BaseVector>)new CPressmachine());
}

//更新処理
int CGame::Update(){
	//更新処理
	for (int i = 0; i < base.size(); i++)
		base[i]->Action(base);

	//削除処理
	for (auto i = base.begin(); i != base.end();)
		(*i)->FLAG ? i++ : i = base.erase(i);

	//オブジェクトのソート処理(クイックソート)
	ObjSort_Quick(base, 0, base.size() - 1);

	//listオブジェクトの更新処理	
	//for (auto i = base.begin(); i != base.end(); i++)
	//	(*i)->Action(base);

	return 0;
}

//描画処理
void CGame::Draw()
{
	//オブジェクト個数
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Object_Count = %d", base.size());
	
	for (int i = 0; i < base.size(); i++)
		if(base[i]->FLAG) base[i]->Draw();

	//DrawBox(0, 0, 250, WINDOW_HEIGHT, GetColor(0, 255, 0), true);

	//DrawBox(250, 0, 260, WINDOW_HEIGHT, GetColor(100, 100, 100), true);

	//DrawBox(260, 0, 580, WINDOW_HEIGHT, GetColor(0, 0, 255), true);

	//DrawBox(580, 0, 590, WINDOW_HEIGHT, GetColor(100, 100, 100), true);

	//DrawBox(590, 0, 850, WINDOW_HEIGHT, GetColor(255, 0, 0), true);

	//DrawBox(850, 0, 860, WINDOW_HEIGHT, GetColor(100, 100, 100), true);
}

CGame::~CGame()
{

}
