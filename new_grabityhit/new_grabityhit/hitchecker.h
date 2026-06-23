#pragma once
#include "objBase.h"

class HitChecker : public BaseVector
{
public:
	HitChecker();

	int CheckerUpdate(const ObjList&);

	void HitCheck_PP(BaseVector*, BaseVector*);
	void HitCheck_CC(BaseVector*, BaseVector*);
	void HitCheck_PC(BaseVector*, BaseVector*);
};