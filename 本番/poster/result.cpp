#include "DxLib.h"
#include "Scene_Manager.h"
#include "title.h"
#include "result.h"
#include "function.h"

//コンストラクタ
CResult::CResult(CManager* p) :CScene(p) {

}

int CResult::Update() {
	//シーン移行
	if (CheckHitKey(KEY_INPUT_BACK)) {
		manager->Scene_Delete();
		manager->scene = new CTitle(manager);
		return 0;
	}

	return 0;
}

void CResult::Draw() {
	DrawString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "リザルト", 0xfcffff);
}

CResult::~CResult() {}