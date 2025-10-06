#pragma once
#include "2D_function.h"

//���W + �x�N�g��
Point Add_Point_Vector(Point p0, Vector v0) {Point r;	r.x = p0.x + v0.x;	r.y = p0.y + v0.y;	return r; }
//���W - ���W
Vector Sub_Point_Point(Point p0, Point p1) { Vector r;	r.x = p0.x - p1.x;	r.y = p0.y - p1.y;	return r; }
//���W - ���W(x,y,x,y)
Vector Sub_Point_Point(float x1, float y1, float x2, float y2) {	Vector r;	r.x = x1 - x2;	r.y = y1 - y2;	return r;}
//�x�N�g�� - �x�N�g��
Vector Sub_Vector_Vector(Vector p0, Vector p1) { Vector r;	r.x = p0.x - p1.x;	r.y = p0.y - p1.y;	return r; }
//�x�N�g�� + �x�N�g��
Vector Add_Vector_Vector(Vector v0, Vector v1) { Vector r;	r.x = v0.x + v1.x;	r.y = v0.y + v1.y;	return r; }
//�x�N�g�� �~ �X�J���[
Vector Mul_Vector_Scaler(Vector v, float s) { Vector r;	r.x = v.x * s;	r.y = v.y * s;	return r; }
//�x�N�g���̒���
float Vector_Length(Vector v) { float l = sqrtf((v.x * v.x + v.y * v.y));	return l; }
//�x�N�g���̐��K��
Vector Vector_Normalize(Vector v) { float l = Vector_Length(v);	Vector n;	n.x = v.x / l;	n.y = v.y / l;	return n; }
//�x�N�g���̒�����ݒ�
Vector Vector_SetLength(Vector v, float length) { v = Vector_Normalize(v);	v = Mul_Vector_Scaler(v, length);	return v; }
//�x�N�g���̉�]
Vector Vector_Rotation(Vector v, float angle) {	Vector r;	float l = Vector_Length(v);	v = Vector_Normalize(v);	r.x = v.x * cos(RADIAN(angle)) - v.y * sin(RADIAN(angle));	r.y = v.x * sin(RADIAN(angle)) + v.y * cos(RADIAN(angle));	return r;}

//������(�ʒuA,���aA,�ʒuB,���aB)
bool HitCheck_Sphere(Point3 A, float RA, Point3 B, float RB) {
	if (DistanceF(A, B) < RA + RB)
		return true;
	return false;
}
//��`����(x1,y1,x2,y2,w,h)
bool HitCheck_box(float x1, float y1, float x2, float y2, int w, int h) {
	if (x1 < x2 + w && x2 < x1 + w && y1 < y2 + h && y2 < y1 + h)
		return 1;
	return 0;
}
//��`����Q(x1,y1,x2,y2,w1,h1,w2,h2)
bool HitCheck_box(float x1, float y1, float x2, float y2, int w1, int h1, int w2, int h2) {
	if (x1 < x2 + w2 && x2 < x1 + w1 &&	y1 < y2 + h2 && y2 < y1 + h1)
		return 1;
	return 0;
}
//��`����3(�I�u�W�F�N�g,�I�u�W�F�N�g)
//�摜�T�C�Y(ImgWidth,ImgHeight)�Ŕ���
bool HitCheck_box(Base* a, Base* b){
	if (a->pos.x < b->pos.x + b->ImgWidth &&
		b->pos.x < a->pos.x + a->ImgWidth &&
		a->pos.y < b->pos.y + b->ImgHeight &&
		b->pos.y < a->pos.y + a->ImgHeight)
		return 1;
	return 0;
}
bool HitCheck_box(BaseVector* a, BaseVector* b) {
	if (a->pos.x < b->pos.x + b->ImgWidth &&
		b->pos.x < a->pos.x + a->ImgWidth &&
		a->pos.y < b->pos.y + b->ImgHeight &&
		b->pos.y < a->pos.y + a->ImgHeight)
		return true;
	return false;
}

//ID�w���`����
//�摜�T�C�Y(ImgWidth,ImgHeight)�Ŕ���
bool HitCheck_box(vector<unique_ptr<BaseVector>>& base, BaseVector* a, int ID) {
	for (int i = 0; i < base.size(); i++) {
		if (base[i]->ID == ID) {
			if (HitCheck_box(a, base[i].get())) {
				return true;
			}
		}
	}
	return false;
}

//���������I�u�W�F�N�g���󂯎��
BaseVector* HitCheck_box_GetObj(vector<unique_ptr<BaseVector>>& base, BaseVector* a, int ID) {
	for (int i = 0; i < base.size(); i++) {
		if (base[i]->ID == ID) {
			if (HitCheck_box(a, base[i].get())) {
				return base[i].get();
			}
		}
	}
	return a;
}


//�~�Ƌ�`����p�֐��i��`�̈�ԋ߂��ʒu���v�Z�j
float Circle_Center_With_Closest_Point(float a, float b, float c)
{
	if (a < b) {
		return b;
	}
	else if (a > c) {
		return c;
	}
	else {
		return a;
	}
}
//�~�Ƌ�`���菈��(�~�I�u�W�F�N�g,��`�I�u�W�F�N�g,�~�̔��a)
void HitCheck_Box_Circle(Base* a, Base* b, float radius) {
	Point pc{ a->pos.x + a->vec.x + a->ImgWidth / 2,a->pos.y + a->vec.y + a->ImgHeight / 2 };//���S���W�v�Z
	Point n{ -1,-1 };//��`�̈�ԋ߂����W
	n.x = Circle_Center_With_Closest_Point(pc.x, b->pos.x, b->pos.x + b->ImgWidth);
	n.y = Circle_Center_With_Closest_Point(pc.y, b->pos.y, b->pos.y + b->ImgHeight);

	float l = DistanceF(pc.x, pc.y, n.x, n.y);//��ԋ߂����W���璆�S�܂ł̋���
	if (l < radius)//���aradius�Ŕ���
	{
		Vector v{ n.x - pc.x, n.y - pc.y };//�����x�N�g��
		v = Vector_Normalize(v);//�����x�N�g�����K��
		v = Vector_SetLength(v, radius - l);
		a->vec.x -= (int)v.x;
		a->vec.y -= (int)v.y;
	}
}

//��_�ԋ���
float DistanceF(float a, float b, float c, float d)
{
	return sqrtf((a - c) * (a - c) + (b - d) * (b - d));
}
float DistanceF(Point3 A, Point3 B) {
	float r;
	r = sqrtf((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y) + (A.z - B.z) * (A.z - B.z));
	return r;
}