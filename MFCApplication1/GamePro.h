#pragma once
#ifndef __GAMEPRO_H__

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "CChessPoint.h"

HWND gameH;
DWORD processId;
CString gameName = TEXT("QQ游戏 - 连连看角色版");
RECT rt;
POINT oldP;
BYTE chessDate[11][19];
DWORD QpID = 0x00199F68;
int i, j, x, y;
bool Click2p(POINT p1, POINT p2);

void GameS() {

	gameH = ::FindWindow(NULL, gameName);
	::GetWindowRect(gameH, &rt);
	::GetCursorPos(&oldP);
	::SetCursorPos(rt.left+660, rt.top+577);
	::mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	::mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	::SetCursorPos(oldP.x, oldP.y);

}
void GameP() {
	gameH = ::FindWindow(NULL, gameName);
	::GetWindowRect(gameH, &rt);
	::GetCursorPos(&oldP);
	::SetCursorPos(rt.left + 722, rt.top + 577);
	::mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	::mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	::SetCursorPos(oldP.x, oldP.y);
}

void updatdChess()      /* 更新棋盘数据至 chessdata */
{
	/*
	 * TODO: Add your control notification handler code here
	 * 获取窗口句柄
	 */
	HWND gameh = ::FindWindow(NULL, gameName);
	/* 获取窗口进程ID */
	DWORD processid;
	::GetWindowThreadProcessId(gameh, &processid);
	/* 打开指定进程 */
	HANDLE processH = ::OpenProcess(PROCESS_ALL_ACCESS, false, processid);
	/* 读指定进程 内存数据 */
	DWORD	byread;
	LPCVOID pbase = (LPCVOID)0x00199F5C; /* 棋盘数据基址 */
	LPVOID	nbuffer = (LPVOID)&chessDate;  /* 存放棋盘数据ni */
	::ReadProcessMemory(processH, pbase, nbuffer, 11 * 19, &byread);
}


bool CheckLine(POINT p1, POINT p2)
{
	int x, y, t;                            /*同一线上的两点间 全为0 则返回真 */

	/* 如果 p1==p2 也返回真 */
	if ((p1.x == p2.x) && (p1.y == p2.y) && (chessDate[p1.y][p1.x] == 0) && (chessDate[p2.y][p2.x] == 0))
	{
		return(true);
	}
	else
		if ((p1.x < 0) || (p1.x > 18) || (p1.y < 0) || (p1.y > 10) ||
			(p2.x < 0) || (p2.x > 18) || (p2.y < 0) || (p2.y > 10))
		{
			return(false);
		}

	if (p1.x == p2.x) /* 如果X轴相等则 比较 */
	{
		if (p1.y > p2.y)
		{
			t = p1.y; p1.y = p2.y; p2.y = t;
		}
		for (y = p1.y; y <= p2.y; y++)
		{
			if (chessDate[y][p1.x] != 0)
			{
				return(false);
			}
		}
	}
	if (p1.y == p2.y)
	{          /* 如果Y轴相等 则比较 */
		if (p1.x > p2.x)
		{
			t = p1.x; p1.x = p2.x; p2.x = t;
		}
		for (x = p1.x; x <= p2.x; x++)
		{
			if (chessDate[p1.y][x] != 0)
			{
				return(false);
			}
		}
		;
	}
	;
	return(true);
};


bool Check2p(POINT a, POINT b)
{
	CChessPoint	p1(a), p2(b);
	POINT		pa, pb; /* 转角点 */
	int		x, y;

	/* 如果2点为同一点 则返回假 */
	if ((a.x == b.x) && (a.y == b.y))
	{
		return(false);
	}
	else
		if ((chessDate[a.y][a.x] == 0) || (chessDate[b.y][b.x] == 0))
		{
			return(false);
		}
		else
			if (chessDate[a.y][a.x] != chessDate[b.y][b.x])
			{
				return(false);
			}

	pa = a; pb = b;
	/* 在横向一条线上 y坐标 相同 */
	if (a.y == b.y)
	{              /* 2点在y轴相邻 */
		if ((p1.right.x == p2.p.x) || (p1.left.x == p2.p.x))
		{
			return(true);
		}
		/* 检测 这条线是否有一条路径相通 */

		if (CheckLine(p1.right, p2.left))
		{
			return(true);
		}
		/*
		 * 检测 上下
		 * y 上
		 */
		pa = a; pb = b;
		if ((p1.up.y >= 0) && (p1.up.y <= 10))
			for (y = 0; y <= p1.up.y; y++)
			{
				pa.y = y; pb.y = y;
				if (CheckLine(pa, p1.up) && CheckLine(pb, p2.up) && CheckLine(pa, pb))
				{
					return(true);
				}
			}
		/* y下 */
		pa = a; pb = b;
		if ((p1.down.y >= 0) && (p1.down.y <= 10))
			for (y = p1.down.y; y <= 10; y++)
			{
				pa.y = y; pb.y = y;
				if (CheckLine(pa, p1.down) && CheckLine(pb, p2.down) && CheckLine(pa, pb))
				{
					return(true);
				}
			}

		/* 检测 左右    因为 y轴相等，所以不存在左右路径 */
	}
	else
		/* 纵向一条线  x 坐标 相同 */
		if (a.x == b.x)
		{
			/* x下上 相邻不 */
			if ((p1.down.y == p2.p.y) || (p1.up.y == p2.p.y))
			{
				return(true);
			}
			/* 检测 这条线是否有一条路径相通 */
			if (CheckLine(p1.down, p2.up))
			{
				return(true);
			}
			/* 检测 上下   国为x 轴相等 所以不存在路径 */

			/*
			 * 检测 左右
			 * x左
			 */
			pa = a; pb = b;
			for (x = 0; x <= p1.left.x; x++)
			{
				pa.x = x;
				pb.x = x;
				if (CheckLine(pa, p1.left) && CheckLine(pb, p2.left) && CheckLine(pa, pb))
				{
					return(true);
				}
			}
			/* x右 */

			pa = a; pb = b;
			for (x = p1.right.x; x <= 18; x++)
			{
				pa.x = x;
				pb.x = x;
				if (CheckLine(pa, p1.right) && CheckLine(pb, p2.right) && CheckLine(pa, pb))
				{
					return(true);
				}
			}
		}
		else {
			/* xy 坐标 都不相同 {{{{{{ */
			pa = a; pb = b;

			if (a.x > b.x)        /* p2点 在 左 left */
			{                       /* //////////////xxxxxxxxxxxxxxxxx  找x轴路径 */
				for (x = 0; x <= p2.left.x; x++)
				{
					pa.x = x; pb.x = x;
					if (CheckLine(pa, p1.left) && CheckLine(pa, pb) && CheckLine(pb, p2.left))
					{
						return(true);
					}
				} /* end for */

				for (x = p2.right.x; x <= p1.left.x; x++)
				{
					pa.x = x; pb.x = x;
					if (CheckLine(p2.right, pb) && CheckLine(pa, pb) && CheckLine(pa, p1.left))
					{
						return(true);
					}
				}
				for (x = p2.right.x; x <= 18; x++)
				{
					pa.x = x; pb.x = x;
					if (CheckLine(p1.right, pa) && CheckLine(p2.right, pb) && CheckLine(pa, pb))
					{
						return(true);
					}
				}
				/* ///////////////yyyyyyyyyyyyyyyyyyyy 找y轴路径 由于是从上向下 搜索 所以p1.y>p2.y */
				pa.x = a.x;   pb.x = b.x;               /* 初始化坐标 y渐变 */
				for (y = 0; y <= p1.up.y; y++)        /* 1段 */
				{
					pa.y = y; pb.y = y;
					if (CheckLine(pb, pa) && CheckLine(pa, p1.up) && CheckLine(pb, p2.up))
					{
						return(true);
					}
				}
				/* ////////////////////// */
				for (y = p1.down.y; y <= p2.up.y; y++) /* 2段 */
				{
					pa.y = y; pb.y = y;
					if (CheckLine(pb, pa) && CheckLine(p1.down, pa) && CheckLine(pb, p2.up))
					{
						return(true);
					}
				}
				/* ///////////////////// */
				for (y = p2.down.y; y <= 10; y++) /* 3段 */
				{
					/* ///////////////////////////// */
					pa.y = y; pb.y = y;
					if (CheckLine(pb, pa) && CheckLine(p1.down, pa) && CheckLine(p2.down, pb))
					{
						return(true);
					}
				}
			}
			else {
				/* //////////p2点  在 右 right a.x>b.x */
				pa.y = a.y;   pb.y = b.y; /* 初始化坐标 */
				for (x = 0; x <= p1.left.x; x++)
					;
				{
					pa.x = x; pb.x = x;
					if (CheckLine(pa, pb) && CheckLine(pa, p1.left) && CheckLine(pb, p2.left))
					{
						return(true);
					}
				}
				/* /////////////////// */

				for (x = p1.right.x; x <= p2.left.x; x++)
				{
					pa.x = x; pb.x = x;
					if (CheckLine(pa, pb) && CheckLine(p1.right, pa) && CheckLine(pb, p2.left))
					{
						return(true);
					}
				}
				/* ///////////////////// */

				for (x = p2.right.x; x <= 18; x++)
				{
					pa.x = 0; pb.x = x;
					if (CheckLine(pa, pb) && CheckLine(p1.right, pa) && CheckLine(p2.right, pb))
					{
						return(true);
					}
				}
				/* /////////////////////yyyyyyyyyyyyyyyyyy   y轴渐变 */
				pa.x = a.x;   pb.x = b.x;                       /* 初始化坐标 */
				if ((p1.up.y >= 0) && (p1.up.y <= 10))
				{
					for (y = 0; y <= p1.up.y; y++)        /* 1段 */
					{
						pa.y = y; pb.y = y;
						if (CheckLine(pa, pb) && CheckLine(pa, p1.up) && CheckLine(pb, p2.up))
						{
							return(true);
						}
					}
				}
				/* //// */
				pa.x = a.x;   pb.x = b.x;                               /* 初始化坐标 */
				if ((p1.down.y <= 10) && (p2.up.y >= 0))
				{
					for (y = p1.down.y; y <= p2.up.y; y++)        /* 2段 */
					{
						pa.y = y; pb.y = y;
						if (CheckLine(pa, pb) && CheckLine(p1.down, pa) && CheckLine(pb, p2.up))
						{
							return(true);
						}
					}
				}
				/* // */
				pa.x = a.x;   pb.x = b.x;                       /* 初始化坐标 */
				if (p2.down.y <= 10)
				{
					for (y = p2.down.y; y <= 10; y++)     /* 3段 */
					{
						pa.y = y; pb.y = y;
						if (CheckLine(pa, pb) && CheckLine(p1.down, pa) && CheckLine(p2.down, pb))
						{
							return(true);
						}
					}
				}
			}
		}

	/* xy 坐标 都不相同 }}}}}}}}} */


	return(false);
}


bool Click2p(POINT p1, POINT p2)
{
	/* 点击p1 */
	HWND	hwnd = FindWindow(NULL, gameName);
	int	lparam;
	lparam = ((p1.y * 35 + 192) << 16) + (p1.x * 31 + 21);
	SendMessage(hwnd, WM_LBUTTONDOWN, 0, lparam); /*  */
	SendMessage(hwnd, WM_LBUTTONUP, 0, lparam);   /*  */
	/* 点击p2 */
	lparam = ((p2.y * 35 + 192) << 16) + (p2.x * 31 + 21);
	SendMessage(hwnd, WM_LBUTTONDOWN, 0, lparam); /*  */
	SendMessage(hwnd, WM_LBUTTONUP, 0, lparam);   /*  */
	return(true);
}
#endif // !__GAMEPRO_H__
