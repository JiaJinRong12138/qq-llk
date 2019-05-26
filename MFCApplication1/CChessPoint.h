#pragma once
class CChessPoint
{
public:
	POINT p;
	POINT up;
	POINT down;
	POINT left;
	POINT right;
	CChessPoint(POINT pxy);
	~CChessPoint();
};

