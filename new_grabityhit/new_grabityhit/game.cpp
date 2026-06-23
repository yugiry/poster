//ゲームシーン
#include "DxLib.h"
#include "Scene_Manager.h"
#include "game.h"
#include "function.h"

#include "box.h"

//コンストラクタ
CGame::CGame(CManager* p) :CScene(p)
{
	base.push_back(make_unique<CBox>());
	Point pos = { WINDOW_WIDTH / 2,WINDOW_HEIGHT - 50 };
	base.push_back(make_unique<CBox>(pos));
}

//更新処理
int CGame::UpDate(){
	ObjList add_list;//追加処理用オブジェクトリスト

	//更新
	for (auto& obj : base)
	obj->Action(base,add_list);

	hitchecker->CheckerUpdate(base);

	//オブジェクト追加処理
	for (auto& obj : add_list)
		base.push_back(move(obj));

	//削除処理
	erase_if(base, [](const auto& obj) {return !obj->FLAG; });

	//c++17 Releaseでerase_ifでエラーが出る場合こちらを利用するかコンパイルバージョンを変更
	/*
	base.erase(remove_if(base.begin(), base.end(), [](const unique_ptr<BaseVector>& base)
		{return !base->FLAG;}),
		base.end());
	*/

	//オブジェクトのソート処理(クイックソート)指定したインデックス間
	ObjSort_Quick(base, 0, base.size() - 1);

	return 0;
}

//描画処理
void CGame::Draw()
{
	
	for (auto& obj : base) obj->Draw();

	SetFontSize(16);
	//オブジェクト個数
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Object_Count = %d", base.size());
}

CGame::~CGame()
{

}
