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

	//ごみの仮生成
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

	//焼却炉の炎を生成
	base.emplace_back((unique_ptr<BaseVector>)new CIncinerator());
	//プレス機を生成
	base.emplace_back((unique_ptr<BaseVector>)new CPressmachine());
}

//更新処理
int CGame::Update(){
	//更新処理
	for (int i = 0; i < base.size(); i++)
		switch (base[i]->Action(base))
		{
		case 1://正しい
			SCORE++;
			break;
		case 2://間違い
			SCORE--;
			break;
		}

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

	//スコアの表示
	DrawBox(900, 500, 950, 500 - SCORE * 50, GetColor(0, 255, 0), true);
}

CGame::~CGame()
{

}
