#pragma once
#include "objBase.h"

//�_�̍��W�A���̎n�_�A���̏I�_
Point Near_Point_Line(Point, Point, Point);

//�l�p�`�̓����蔻��(���W�A�����x�N�g���A�c���x�N�g��)
void HitLeft(BaseVector*);
void HitRight(BaseVector*);
void HitUp(BaseVector*);
void HitDown(BaseVector*);