#pragma once
#include "hitobj.h"

CHitobj::CHitobj()
{

}

int CHitobj::Action(vector<unique_ptr<BaseVector>>& base)
{
	for (auto i = base.begin(); i != base.end(); i++)
	{
		if ((*i)->ID == BURNABLE)
		{
			
		}
	}

	return 0;
}

void CHitobj::Draw()
{

}