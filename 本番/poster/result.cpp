#include "DxLib.h"
#include "Scene_Manager.h"
#include "title.h"
#include "result.h"
#include "function.h"

//コンストラクタ
CResult::CResult(CManager* p) :CScene(p) {

	n_game_clear_image = LoadGraph("image\\GameClear.png");
	n_game_over_image = LoadGraph("image\\GameOver.png");
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
	DrawString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "Push To BACK", 0xfcffff);

	//ゲームクリアかゲームオーバー画面表示
	if (n_is_clear)
		DrawGraph(0, 0, n_game_clear_image, false);
	else
		DrawGraph(0, 0, n_game_over_image, false);
}

CResult::~CResult() {}