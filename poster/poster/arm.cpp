#pragma once
#include "arm.h"
#include "function.h"
#include "hitobj.h"

constexpr bool OPEN = true;		//アームが開いている
constexpr bool CLOSE = false;	//アームが閉じている

CArm::CArm()
{
	//アームの初期位置
	pos.x = 0;
	pos.y = 20;

	//アームの画像サイズ
	ImgWidth = 64;
	ImgHeight = 64;

	arm_state = CLOSE;

	//ボタンが押されているか判定の初期化
	for (int i = 0; i < HBEND; i++)
	{
		Click_Check[i] = false;
	}
}

int CArm::Action(vector<unique_ptr<BaseVector>>& base)
{
	//アームが閉まっている時
	if (arm_state == CLOSE)
	{
		//物を掴む判定を出す
		base.emplace_back((unique_ptr<BaseVector>)new CHitobj(pos));
	}

	//移動ベクトルのリセット
	vec.x = vec.y = 0;

	//アームが動いている
	if (move_time == 0)
	{
		move_time--;
		arm_state = CLOSE;
	}
	if (move_time > 0)
	{
		move_time--;
	}

	//アームが開く
	if (arm_open == 0)
	{
		arm_open--;
		arm_state = OPEN;
		arm_down = true;
	}
	if (arm_open > 0)
	{
		arm_open--;
	}

	//アームを下げる
	if (CheckHitKey(KEY_INPUT_F) && !Click_Check[F] && !arm_down && pos.y == 20)
	{
		arm_open = 30;
	}

	//アームが下がっていない時
	if (!arm_down && pos.y <= 20 && move_time < 0)
	{
		//左右移動
		if (CheckHitKey(KEY_INPUT_A) && !Click_Check[A])
		{
			vec.x = -3.0f;
		}
		if (CheckHitKey(KEY_INPUT_D) && !Click_Check[D])
		{
			vec.x = 3.0f;
		}
	}

	//アームを下げる
	if (arm_down)
	{
		vec.y = 4.0f;
	}
	//アームをあげる
	if (!arm_down && pos.y > 20 && move_time < 0)
	{
		vec.y = -4.0f;
	}

	//当たり判定
	for (auto i = base.begin(); i != base.end(); i++)
	{
		//壁
		if ((*i)->ID == WALL)
		{
			Point late{ pos.x,pos.y + vec.y };
			if (HitCheck_box(late.x, late.y, (*i)->pos.x, (*i)->pos.y, ImgWidth, ImgHeight, (*i)->ImgWidth, (*i)->ImgHeight))
			{
				arm_down = false;
				move_time = GRAP_TIME;
				vec.y -= 4.0f;
			}
		}

		//燃えるゴミ
		{
			if ((*i)->ID == BURNABLE)
			{
				if ((*i)->radius == -1)
				{
					if (HitCheck_box(this, (*i).get()))
					{

					}
				}
				else if ((*i)->radius > 0)
				{
					if (HitCheck_Box_CircleB((*i).get(), this, (*i)->radius))
					{
						arm_down = false;
						move_time = GRAP_TIME;
						vec.y -= 4.0f;
					}
				}
			}
		}
		//鉄ごみ
		{
			if ((*i)->ID == CRUMB)
			{
				if ((*i)->radius == -1)
				{

				}
				else if ((*i)->radius > 0)
				{

				}
			}
		}
		//プラスティック
		{
			if ((*i)->ID == PLASTIC)
			{
				if ((*i)->radius == -1)
				{

				}
				else if ((*i)->radius > 0)
				{

				}
			}
		}
	}

	//座標更新
	pos.x += vec.x;
	pos.y += vec.y;

	//左右に移動できる範囲指定
	if (pos.x < 0)pos.x = 0;
	if (pos.x > GAME_WIDTH -ImgWidth)pos.x = GAME_WIDTH - ImgWidth;

	return 0;
}

void CArm::Draw()
{
	DrawBox(pos.x, pos.y, pos.x + ImgWidth, pos.y + ImgHeight, GetColor(255, 0, 0), true);
}