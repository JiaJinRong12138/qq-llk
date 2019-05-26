#include "stdafx.h"
#include "CChessPoint.h"


CChessPoint::CChessPoint(POINT pxy)
{
	up = pxy;
	down = pxy;
	left = pxy;
	right = pxy;
	p = pxy;
	up.y = pxy.y - 1;
	down.y = pxy.y + 1;
	left.x = pxy.x - 1;
	right.x = pxy.x + 1;
}


CChessPoint::~CChessPoint()
{
}
