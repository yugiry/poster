#pragma once
#include "objBase.h"
#include "CCamera.h"

class CResult :public CScene
{
private:
public:
	//オブジェクト
	//リスト
	//list<unique_ptr<Base3D>> base3D;//3Dオブジェクト
	//list<unique_ptr<Base>> base;//2Dオブジェクト
	//ベクター
	vector<unique_ptr<BaseVector>> base;

	//コンストラクタ
	CResult(CManager*);

	//デストラクタ
	~CResult();

	int Update();//更新処理
	void Draw();//描画処理

	int SCORE;
private:
	int n_game_clear_image{-1};
	int n_game_over_image{-1};

	bool n_is_clear{false};//ゲームクリアかゲームオーバーか

	//CCamera* camera;//カメラオブジェクト
};