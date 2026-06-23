#include "hitchecker.h"

//コンストラクタ
HitChecker::HitChecker()
{

}

//当たり判定の更新処理
int HitChecker::CheckerUpdate(const ObjList& base)
{
	for (int i = 0; i < base.size(); i++)
	{
		for (int j = i + 1; j < base.size(); j++)
		{
			if (base[i]->ID == (int)ObjID::POLYGON || base[j]->ID == (int)ObjID::POLYGON)
			{

			}
			if (base[i]->ID == (int)ObjID::CIRCLE || base[j]->ID == (int)ObjID::CIRCLE)
			{

			}
		}
	}

	return 0;
}

//多角形と多角形の当たり判定処理
void HitChecker::HitCheck_PP()
{

}

//円と円の当たり判定処理
void HitChecker::HitCheck_CC()
{

}

//多角形と円の当たり判定処理
void HitChecker::HitCheck_PC()
{

}
