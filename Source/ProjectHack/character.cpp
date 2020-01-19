#include "character.h"

bool cbCharacterPushCalc(CObjBase *pTgt, void *pPara)
{//‰e‹¿‚ðŒvŽZ
	CCharacter *pJibun = (CCharacter *)pPara;
	if (pTgt != pJibun)
	{
		vector3 _Ofs = pTgt->m_pos - pJibun->m_pos;
		float radius =  pJibun->m_radius+pTgt->m_radius ;
		if (abs(_Ofs.x) < radius&&abs(_Ofs.z) < radius)
		{
			pJibun->m_pushed.x += ((_Ofs.x > 0) ? (radius - _Ofs.x) : (-radius - _Ofs.x)) / 2.0f;
			pJibun->m_pushed.z += ((_Ofs.z > 0) ? (radius - _Ofs.z) : (-radius - _Ofs.z)) / 2.0f;
		}
		pJibun->m_pushed.y = 0.0f;
	}
	return false;
}

void CCharacter::PushCalc()
{
	ObjSys.LoopStage(OBJLIST_PLAYER+OBJLIST_ENEMY, cbCharacterPushCalc, this);
}
void CCharacter::PushRefl()
{
	m_pos -= m_pushed;
	m_pushed=point3(0.0f, 0.0f, 0.0f);
}
