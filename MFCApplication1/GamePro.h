#pragma once
#ifndef __GAMEPRO_H__

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "CChessPoint.h"

HWND gameH;
DWORD processId;
CString gameName = TEXT("QQ��Ϸ - ��������ɫ��");
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

void updatdChess()      /* �������������� chessdata */
{
	/*
	 * TODO: Add your control notification handler code here
	 * ��ȡ���ھ��
	 */
	HWND gameh = ::FindWindow(NULL, gameName);
	/* ��ȡ���ڽ���ID */
	DWORD processid;
	::GetWindowThreadProcessId(gameh, &processid);
	/* ��ָ������ */
	HANDLE processH = ::OpenProcess(PROCESS_ALL_ACCESS, false, processid);
	/* ��ָ������ �ڴ����� */
	DWORD	byread;
	LPCVOID pbase = (LPCVOID)0x00199F5C; /* �������ݻ�ַ */
	LPVOID	nbuffer = (LPVOID)&chessDate;  /* �����������ni */
	::ReadProcessMemory(processH, pbase, nbuffer, 11 * 19, &byread);
}


bool CheckLine(POINT p1, POINT p2)
{
	int x, y, t;                            /*ͬһ���ϵ������ ȫΪ0 �򷵻��� */

	/* ��� p1==p2 Ҳ������ */
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

	if (p1.x == p2.x) /* ���X������� �Ƚ� */
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
	{          /* ���Y����� ��Ƚ� */
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
	POINT		pa, pb; /* ת�ǵ� */
	int		x, y;

	/* ���2��Ϊͬһ�� �򷵻ؼ� */
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
	/* �ں���һ������ y���� ��ͬ */
	if (a.y == b.y)
	{              /* 2����y������ */
		if ((p1.right.x == p2.p.x) || (p1.left.x == p2.p.x))
		{
			return(true);
		}
		/* ��� �������Ƿ���һ��·����ͨ */

		if (CheckLine(p1.right, p2.left))
		{
			return(true);
		}
		/*
		 * ��� ����
		 * y ��
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
		/* y�� */
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

		/* ��� ����    ��Ϊ y����ȣ����Բ���������·�� */
	}
	else
		/* ����һ����  x ���� ��ͬ */
		if (a.x == b.x)
		{
			/* x���� ���ڲ� */
			if ((p1.down.y == p2.p.y) || (p1.up.y == p2.p.y))
			{
				return(true);
			}
			/* ��� �������Ƿ���һ��·����ͨ */
			if (CheckLine(p1.down, p2.up))
			{
				return(true);
			}
			/* ��� ����   ��Ϊx ����� ���Բ�����·�� */

			/*
			 * ��� ����
			 * x��
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
			/* x�� */

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
			/* xy ���� ������ͬ {{{{{{ */
			pa = a; pb = b;

			if (a.x > b.x)        /* p2�� �� �� left */
			{                       /* //////////////xxxxxxxxxxxxxxxxx  ��x��·�� */
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
				/* ///////////////yyyyyyyyyyyyyyyyyyyy ��y��·�� �����Ǵ������� ���� ����p1.y>p2.y */
				pa.x = a.x;   pb.x = b.x;               /* ��ʼ������ y���� */
				for (y = 0; y <= p1.up.y; y++)        /* 1�� */
				{
					pa.y = y; pb.y = y;
					if (CheckLine(pb, pa) && CheckLine(pa, p1.up) && CheckLine(pb, p2.up))
					{
						return(true);
					}
				}
				/* ////////////////////// */
				for (y = p1.down.y; y <= p2.up.y; y++) /* 2�� */
				{
					pa.y = y; pb.y = y;
					if (CheckLine(pb, pa) && CheckLine(p1.down, pa) && CheckLine(pb, p2.up))
					{
						return(true);
					}
				}
				/* ///////////////////// */
				for (y = p2.down.y; y <= 10; y++) /* 3�� */
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
				/* //////////p2��  �� �� right a.x>b.x */
				pa.y = a.y;   pb.y = b.y; /* ��ʼ������ */
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
				/* /////////////////////yyyyyyyyyyyyyyyyyy   y�ὥ�� */
				pa.x = a.x;   pb.x = b.x;                       /* ��ʼ������ */
				if ((p1.up.y >= 0) && (p1.up.y <= 10))
				{
					for (y = 0; y <= p1.up.y; y++)        /* 1�� */
					{
						pa.y = y; pb.y = y;
						if (CheckLine(pa, pb) && CheckLine(pa, p1.up) && CheckLine(pb, p2.up))
						{
							return(true);
						}
					}
				}
				/* //// */
				pa.x = a.x;   pb.x = b.x;                               /* ��ʼ������ */
				if ((p1.down.y <= 10) && (p2.up.y >= 0))
				{
					for (y = p1.down.y; y <= p2.up.y; y++)        /* 2�� */
					{
						pa.y = y; pb.y = y;
						if (CheckLine(pa, pb) && CheckLine(p1.down, pa) && CheckLine(pb, p2.up))
						{
							return(true);
						}
					}
				}
				/* // */
				pa.x = a.x;   pb.x = b.x;                       /* ��ʼ������ */
				if (p2.down.y <= 10)
				{
					for (y = p2.down.y; y <= 10; y++)     /* 3�� */
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

	/* xy ���� ������ͬ }}}}}}}}} */


	return(false);
}


bool Click2p(POINT p1, POINT p2)
{
	/* ���p1 */
	HWND	hwnd = FindWindow(NULL, gameName);
	int	lparam;
	lparam = ((p1.y * 35 + 192) << 16) + (p1.x * 31 + 21);
	SendMessage(hwnd, WM_LBUTTONDOWN, 0, lparam); /*  */
	SendMessage(hwnd, WM_LBUTTONUP, 0, lparam);   /*  */
	/* ���p2 */
	lparam = ((p2.y * 35 + 192) << 16) + (p2.x * 31 + 21);
	SendMessage(hwnd, WM_LBUTTONDOWN, 0, lparam); /*  */
	SendMessage(hwnd, WM_LBUTTONUP, 0, lparam);   /*  */
	return(true);
}
#endif // !__GAMEPRO_H__
