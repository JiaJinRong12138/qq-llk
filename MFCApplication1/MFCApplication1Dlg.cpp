
// MFCApplication1Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "GamePro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
	, m_autoPlay(FALSE)
	, m_INT(0)
	, m_isKillGame(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_autoPlay);
	DDX_Control(pDX, IDC_SLIDER1, m_ctl_slider);
	DDX_Text(pDX, IDC_EDIT1, m_INT);
	DDX_Check(pDX, IDC_CHECK4, m_isKillGame);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::GameStart)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::GamePractice)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::AddZnz)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::AddCl)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication1Dlg::EliminateChess)
	ON_BN_CLICKED(IDC_CHECK1, &CMFCApplication1Dlg::OnCheckPlay)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CMFCApplication1Dlg::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDC_CHECK4, &CMFCApplication1Dlg::OnBnClickedCheck4)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO: 在此添加额外的初始化代码
	this->m_ctl_slider.SetRange(1, 10);
	this->m_ctl_slider.SetTicFreq(1);
	this->m_ctl_slider.SetPos(3);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::GameStart()
{
	// TODO: 在此添加控件通知处理程序代码
	GameS();//自动开局

}


void CMFCApplication1Dlg::GamePractice()
{
	// TODO: 在此添加控件通知处理程序代码
	GameP();//自动练习
}

DWORD dwPid;//进程ID
DWORD Num = 20;
DWORD size = 0;
HANDLE hProcess;//进程句柄

void CMFCApplication1Dlg::AddZnz()
{
	// TODO: 在此添加控件通知处理程序代码
	//点击添加10次指南针
	DWORD ZnzAddr = 0x00186EDA;//练习状态下的指南针基址
	gameH = ::FindWindow(NULL, gameName);
	::GetWindowThreadProcessId(gameH, &dwPid);
	hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, false, dwPid);
	WriteProcessMemory(hProcess, (LPVOID)ZnzAddr, &Num, sizeof(DWORD), &size);

}


void CMFCApplication1Dlg::AddCl()
{
	// TODO: 在此添加控件通知处理程序代码
	//点击添加10次重列
	DWORD ClAddr = 0x00186EEA;
	gameH = ::FindWindow(NULL, gameName);
	::GetWindowThreadProcessId(gameH, &dwPid);
	hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, false, dwPid);
	WriteProcessMemory(hProcess, (LPVOID)ClAddr, &Num, sizeof(DWORD), &size);
}

bool CheckPoints() //消除一对棋子
{
	//读出棋盘数据至chessdata 11,19
	updatdChess();
	//遍历整个棋盘 找出相同类型 一对棋子
	POINT p1, p2;
	int x1, y1, x2, y2;
	for (y1 = 0; y1 < 11; y1++)
		for (x1 = 0; x1 < 19; x1++)
		{
			for (y2 = y1; y2 < 11; y2++)
				for (x2 = 0; x2 < 19; x2++)
					if ((chessDate[y1][x1] == chessDate[y2][x2]) // 棋子1与棋子2 类型是否相同
						&& (!((x1 == x2) && (y1 == y2)))  //要求点1与点2 相等则假
						)
					{
						p1.x = x1; p1.y = y1;
						p2.x = x2; p2.y = y2;
						//检测 相同的2个棋子是否可消掉
						if (Check2p(p1, p2))//如果可消除 则返回真
						{
							//click2p 鼠标模拟 点击 p1，p2
							Click2p(p1, p2);
							return true;

						}
					}
		}
	return false;
}

//快速开始游戏的方法


void CMFCApplication1Dlg::EliminateChess()
{
	// TODO: 在此添加控件通知处理程序代码
	CheckPoints();
}

VOID CALLBACK PlayProc(HWND hwnd,
	UINT uMsg,
	UINT_PTR idEvent,
	DWORD dwTime
) {
	CheckPoints();
}


//定义常量
const int PLAYID = 111;

void CMFCApplication1Dlg::OnCheckPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_autoPlay) {
		SetTimer(PLAYID, m_INT*1000, &PlayProc);
	}
	else {
		KillTimer(PLAYID);
	}
}






void CMFCApplication1Dlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	m_INT = this->m_ctl_slider.GetPos();
	UpdateData(false);
	*pResult = 0;
}






void CMFCApplication1Dlg::OnBnClickedCheck4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_isKillGame) {
		SetTimer(PLAYID, 0, &PlayProc);
	}
	else {
		KillTimer(PLAYID);
	}
}
