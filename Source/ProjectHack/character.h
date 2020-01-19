#pragma once
#include "objbase.h"

class CCharacter :public CObjBase {
public:
	void PushCalc();
	void PushRefl();
	point3 m_pushed = point3(0.0f, 0.0f,0.0f);
};
