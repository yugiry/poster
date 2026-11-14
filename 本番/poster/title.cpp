#include "DxLib.h"
#include "Scene_Manager.h"
#include "title.h"
#include "game.h"
#include "function.h"

//コンストラクタ
CTitle::CTitle(CManager* p) :CScene(p) {

}

int CTitle::Update() {
	//シーン移行
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		manager->Scene_Delete();
		manager->scene = new CGame(manager);
		return 0;
	}

	return 0;
}

void CTitle::Draw() {
	DrawString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "タイトル", 0xfcffff);
}

CTitle::~CTitle(){}