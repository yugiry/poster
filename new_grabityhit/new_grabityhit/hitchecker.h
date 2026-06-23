#pragma once
#include "objBase.h"

class HitChecker
{
public:
	HitChecker();

	int CheckerUpdate(const ObjList&);

	void HitCheck_PP();
	void HitCheck_CC();
	void HitCheck_PC();
};