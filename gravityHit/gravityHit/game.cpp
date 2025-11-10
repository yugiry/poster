//ゲームシーン
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
#include "triangle.h"

//コンストラクタ
CGame::CGame(CManager* p) :CScene(p){
	//base.emplace_back((unique_ptr<BaseVector>)new CBox());
	base.emplace_back((unique_ptr<BaseVector>)new CBoxs());

	//base.emplace_back((unique_ptr<BaseVector>)new CCircle());
	//base.emplace_back((unique_ptr<BaseVector>)new CCircles());

	//base.emplace_back((unique_ptr<BaseVector>)new CLine());
	//base.emplace_back((unique_ptr<BaseVector>)new CLines());

	//base.emplace_back((unique_ptr<BaseVector>)new CTriangle());
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
}

CGame::~CGame()
{

}
