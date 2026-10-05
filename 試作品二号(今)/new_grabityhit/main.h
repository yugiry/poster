//DX Library Copyright (C) 2001-2025 Takumi Yamada.
//Dxlib_lib_7.2 2026 Kcomテンプレート Shinya Wakisaka.
//C++20以降対応
#pragma once
#define _USE_MATH_DEFINES
#include "DxLib.h"
#include <list>
#include <vector>
#include <memory>
#include <time.h>

#include "objID.h"
#include "Resource.h"

using namespace std;

//ラジアン変換マクロ
#define RADIAN(_deg) ((float)M_PI*(_deg)/180.0f)
#define DEGREE(_rad) ((float)(_rad)*180.0f/M_PI)

//基本ウィンドウサイズ
constexpr auto WINDOW_WIDTH = 800;	//ウィンドウ横幅
constexpr auto WINDOW_HEIGHT = 600;	//ウィンドウ縦幅

constexpr auto HALF = 2;
constexpr auto THREE = 3;

//2D用
 struct Point {
	float x, y;
};
 struct Vector {
	float x, y;
};

 struct Poly {
	 vector<Point> vertex;
	 vector<float> angle;
 };

 constexpr Vector base_angle{ 1.0f,0.0f };

//3D用
struct Point3 {
	float x, y, z;
};
struct Vector3 {
	float x, y, z;
};
 struct ObjSize {
	float h, w, d;
};

//カメラ情報クラス(main.h)
//class CCameraInfo {
//private:
//	static Point3 pos;//カメラの位置
//public:
//	static Point3 GetPos() { return pos; }//カメラの位置情報取得
//	static void SetPos(Point3 p) { pos = p; }//カメラの位置情報保存
//};