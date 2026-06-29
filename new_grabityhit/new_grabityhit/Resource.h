//リソースクラス
#pragma once
#include "main.h"

class Resource {
public:
	//static int img;

	//リソースの読み込み
	static void Load();
	//各リソースの削除処理
	static void Release();
};