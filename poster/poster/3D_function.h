#pragma once
#include "objBase.h"
#include "2D_function.h"

//�ő�ŏ�
//(Point3 A, Point3 B) A �� B �Ԃ̍ő�ŏ�
//�ő�l�ŏ��l
struct MINMAX{
	Vector3 min{ 0,0,0 };	Vector3 max{ 0,0,0 };
	//Point3 to Point3
	MINMAX(Point3 a, Point3 b) {min.x = a.x;min.y = a.y;min.z = a.z;max.x = a.x + b.x;max.y = a.y + b.y;max.z = a.z + b.z;}
	//Vector3 to Vector3
	MINMAX(Vector3 a, Vector3 b) {min.x = a.x;min.y = a.y;min.z = a.z;max.x = a.x + b.x;max.y = a.y + b.y;max.z = a.z + b.z;}
	//Point3 to Vector3
	MINMAX(Point3 a, Vector3 b) {min.x = a.x;min.y = a.y;min.z = a.z;max.x = a.x + b.x;max.y = a.y + b.y;max.z = a.z + b.z;}
};

//���W + �x�N�g��
Point3 Add_Point_Vector(Point3, Vector3);
//���W - ���W
Vector3 Sub_Point_Point(Point3, Point3);
//�x�N�g�� - �x�N�g��
Vector3 Sub_Vector_Vector(Vector3, Vector3);
//�x�N�g�� + �x�N�g��
Vector3 Add_Vector_Vector(Vector3, Vector3);
//�x�N�g�� �~ �X�J���[
Vector3 Mul_Vector_Scaler(Vector3, float);
//�x�N�g���̒���
float Vector_Length(Vector3);
//�x�N�g���̐��K��
Vector3 Vector_Normalize(Vector3);
//�x�N�g���̒�����ݒ�
Vector3 Vector_SetLength(Vector3, float);
//����(3D)
float Vector3_Dot(Vector3, Vector3);
//�O��(3D)
Vector3 Vector3_Cross(Vector3, Vector3);
//�x�N�g���ɑ΂��Ďw�肵���p�x�ɉ�](x����])
Vector3 Vector_Rotation_X(Vector3, float);
//�w�肵���p�x�ɉ�](x����])
Vector3 Vector_Rotation_X(float);
//�x�N�g���ɑ΂��Ďw�肵���p�x�ɉ�](y����])
Vector3 Vector_Rotation_Y(Vector3, float);
//�w�肵���p�x�ɉ�](y����])
Vector3 Vector_Rotation_Y(float);
//�x�N�g���ɑ΂��Ďw�肵���p�x�ɉ�](z����])
Vector3 Vector_Rotation_Z(Vector3, float);
//�w�肵���p�x�ɉ�](z����])
Vector3 Vector_Rotation_Z(float);

//AABB����(�I�u�W�F�N�g,�I�u�W�F�N�g)
bool HitCheck_AABB(Base3D*, Base3D*);
//AABB����
bool HitCheck_AABB(MINMAX, MINMAX);
