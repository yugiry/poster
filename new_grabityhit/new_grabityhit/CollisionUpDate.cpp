//当たり判定関数
#include "CollisionUpdate.h"
#include "function.h"

//当たり判定関数
//この関数を使用する場合、objIDについて取り扱いに注意すること
void CollisionUpDate(ObjList& base) {
	for (int i = 0; i < base.size(); i++) {
		BaseVector* a = base[i].get();
		for(int j = i + 1; j < base.size(); j++) 
		{
			BaseVector* b = base[j].get();
			//ID順を統一
			//if(a==b)とif(b==a)は同じオブジェクトの判定になるので、ID順を統一する
			if (a->ID > b->ID) swap(a, b);
			//例）
			//IDがPLAYERとENEMYの場合
			//if (a->ID == (int)ObjID::PLAYER && b->ID == (int)ObjID::ENEMY) {
				//判定処理
			//}
		}
	}
}