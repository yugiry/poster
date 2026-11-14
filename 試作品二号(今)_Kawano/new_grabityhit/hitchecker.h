#pragma once
#include "objBase.h"

class HitChecker
{
public:
	HitChecker();

#pragma region 関数

	int CheckerUpdate(const ObjList&);
	void HitCheck_PW(BaseVector*, BaseVector*);
	void HitCheck_PW_Axis(BaseVector*, BaseVector*);//テスト関数
	void HitCheck_CW(BaseVector*, BaseVector*);
	void HitCheck_PP(BaseVector*, BaseVector*);
	void HitCheck_CC(BaseVector*, BaseVector*);
	void HitCheck_PC(BaseVector*, BaseVector*);
	bool CheckInPolygon(vector<Point>, Point);

	void Draw();
#pragma endregion

#pragma region 定数
	const float ANGLE_MAX_TIMER = 30.0f;

#pragma endregion

#pragma region 変数

	//vector<Vector> shortrang_vec;//
	bool object_hit{ false };
	float angle_power{0.0f};//角速度に加算する値
	float angle_set_timer = ANGLE_MAX_TIMER;
	Point contact{0,0};//回転用の接触点
	Vector normal{ 0,0 };//カベから物体への法線ベクトル

#pragma endregion




};