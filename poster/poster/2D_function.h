#pragma once
#include "objBase.h"

//���W + �x�N�g��
Point Add_Point_Vector(Point, Vector);
//���W - ���W
Vector Sub_Point_Point(Point, Point);
//���W - ���W(x,y,x,y)
Vector Sub_Point_Point(float, float, float, float);
//�x�N�g�� - �x�N�g��
Vector Sub_Vector_Vector(Vector, Vector);
//�x�N�g�� + �x�N�g��
Vector Add_Vector_Vector(Vector, Vector);
//�x�N�g�� �~ �X�J���[
Vector Mul_Vector_Scaler(Vector, float);
//�x�N�g���̒���
float Vector_Length(Vector);
//�x�N�g���̐��K��
Vector Vector_Normalize(Vector);
//�x�N�g���̒�����ݒ�
Vector Vector_SetLength(Vector, float);
//�x�N�g���̉�]
Vector Vector_Rotation(Vector, float);


//������(�ʒuA,���aA,�ʒuB,���aB)
bool HitCheck_Sphere(Point3, float, Point3, float);
//��`����(x1,y1,x2,y2,w,h)
bool HitCheck_box(float, float, float, float, int, int);
//��`����Q(x1,y1,x2,y2,w1,h1,w2,h2)
bool HitCheck_box(float, float, float, float, int, int, int, int);
//��`����3(�I�u�W�F�N�g,�I�u�W�F�N�g)
//�摜�T�C�Y(ImgWidth,ImgHeight)�Ŕ���
bool HitCheck_box(Base*, Base*);
bool HitCheck_box(BaseVector*, BaseVector*);

//ID�w���`����
//�摜�T�C�Y(ImgWidth,ImgHeight)�Ŕ���
bool HitCheck_box(vector<unique_ptr<BaseVector>>&, BaseVector*, int);
//���������I�u�W�F�N�g���󂯎��
BaseVector* HitCheck_box_GetObj(vector<unique_ptr<BaseVector>>&, BaseVector*, int);


//�~�Ƌ�`���菈��(�~�I�u�W�F�N�g,��`�I�u�W�F�N�g,�~�̔��a)
void HitCheck_Box_Circle(Base*, Base*, float);

//��_�ԋ���
float DistanceF(float, float, float, float);
float DistanceF(Point3, Point3);