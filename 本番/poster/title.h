#pragma once
#include "objBase.h"
#include "CCamera.h"

class CTitle :public CScene
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
	CTitle(CManager*);

	//デストラクタ
	~CTitle();

	int Update();//更新処理
	void Draw();//描画処理
	
	int SCORE;

	//CCamera* camera;//カメラオブジェクト
private:
	int image{-1};
};