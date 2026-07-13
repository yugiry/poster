#pragma once
#include "objBase.h"

class HitChecker
{
public:
	HitChecker();

#pragma region ä÷êî

	int CheckerUpdate(const ObjList&);
	void HitCheck_PP(BaseVector*, BaseVector*);
	void HitCheck_CC(BaseVector*, BaseVector*);
	void HitCheck_PC(BaseVector*, BaseVector*);
	bool CheckInPolygon(vector<Point>, Point);

	void Draw();
#pragma endregion

#pragma region ïœêî

	//vector<Vector> shortrang_vec;//
	bool object_hit{ false };

#pragma endregion
};