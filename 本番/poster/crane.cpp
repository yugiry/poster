#pragma once
#include "crane.h"
#include "function.h"
#include "hitobj.h"

constexpr bool OPEN = true;		//アームが開いている
constexpr bool CLOSE = false;	//アームが閉じている

CCrane::CCrane()
{
	//アームの初期位置
	pos.x = 0;
	pos.y = 20;

	//アームの画像サイズ
	ImgWidth = 64;
	ImgHeight = 48;

	arm_state = CLOSE;

	//ボタンが押されているか判定の初期化
	for (int i = 0; i < HBEND; i++)
	{
		Click_Check[i] = false;
	}

	Point p;
	p.x = pos.x + 8; p.y = pos.y + ImgHeight;
	Larm = new CArm(p);
	p.x = pos.x + ImgWidth - 8;
	Rarm = new CArm(p);
}

int CCrane::Action(vector<unique_ptr<BaseVector>>& base)
{
	//アームが閉まっている時
	if (arm_state == CLOSE)
	{
		Point p{ pos.x,pos.y + ImgHeight };
		//物を掴む判定を出す
		base.emplace_back((unique_ptr<BaseVector>)new CHitobj(p, vec, ImgWidth, 32, 1, ARM));
	}

	//移動ベクトルのリセット
	vec.x = vec.y = 0;

	//アームが動いている
	if (move_time == 0)
	{
		move_time--;
	}
	if (move_time > 0)
	{
		move_time--;
	}

	if (close_time == 0)
	{
		close_time--;
		Click_Check[R] = false;
	}
	if (close_time > 0)
	{
		close_time--;
		arm_state = CLOSE;
	}

	//アームが開く
	if (arm_open == 0 && Click_Check[F])
	{
		arm_open--;
		arm_down = true;
		Click_Check[F] = false;
	}
	if (arm_open == 0 && Click_Check[R])
	{
		arm_open--;
		close_time = 30;
	}
	if (arm_open > 0)
	{
		arm_open--;
		arm_state = OPEN;
	}

	//アームを下げる
	if (CheckHitKey(KEY_INPUT_J) && !arm_down && pos.y == 20)
	{
		arm_open = 30;
		Click_Check[F] = true;
	}
	//アームを開く
	if (CheckHitKey(KEY_INPUT_U) && !Click_Check[R])
	{
		arm_open = 30;
		Click_Check[R] = true;
	}

	//アームが下がっていない時
	if (!arm_down && pos.y <= 20 && move_time < 0 && arm_open < 0)
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
				arm_state = CLOSE;
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
						break;
					}
				}
				else if ((*i)->radius > 0)
				{
					if (HitCheck_Box_CircleB((*i).get(), this, (*i)->radius))
					{
						arm_down = false;
						move_time = GRAP_TIME;
						vec.y -= 4.0f;
						pos.y += vec.y;
						Larm->pos.y += vec.y;
						Rarm->pos.y += vec.y;
						arm_state = CLOSE;
						break;
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
					if (HitCheck_box(this, (*i).get()))
					{
						arm_down = false;
						move_time = GRAP_TIME;
						vec.y -= 4.0f;
						pos.y += vec.y;
						Larm->pos.y += vec.y;
						Rarm->pos.y += vec.y;
						arm_state = CLOSE;
						break;
					}
				}
				else if ((*i)->radius > 0)
				{
					if (HitCheck_Box_CircleB((*i).get(), this, (*i)->radius))
					{
						break;
					}
				}
			}
		}
		//プラスティック
		{
			if ((*i)->ID == PLASTIC)
			{
				if ((*i)->radius == -1)
				{
					if (HitCheck_box(this, (*i).get()))
					{
						break;
					}
				}
				else if ((*i)->radius > 0)
				{
					if (HitCheck_Box_CircleB((*i).get(), this, (*i)->radius))
					{
						break;
					}
				}
			}
		}
	}

	//座標更新
	pos.x += vec.x;
	pos.y += vec.y;
	Larm->pos.x += vec.x;
	Larm->pos.y += vec.y;
	Rarm->pos.x += vec.x;
	Rarm->pos.y += vec.y;

	//左右に移動できる範囲指定
	if (pos.x < 0)pos.x = 0;
	if (pos.x > GAME_WIDTH -ImgWidth)pos.x = GAME_WIDTH - ImgWidth;

	Larm->pos.x = pos.x + 8;
	Larm->pos.y = pos.y + ImgHeight;
	Rarm->pos.x = pos.x + ImgWidth - 8;
	Rarm->pos.y = pos.y + ImgHeight;

	Larm->Action(base);
	Rarm->Action(base);

	return 0;
}

void CCrane::Draw()
{
	DrawBox(pos.x, pos.y, pos.x + ImgWidth, pos.y + ImgHeight, GetColor(255, 0, 0), true);

	Larm->Draw();
	Rarm->Draw();
}