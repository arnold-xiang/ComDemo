
// ComDemoDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ComDemo.h"
#include "ComDemoDlg.h"
#include "afxdialogex.h"
#include "EnumSerial.h"


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


// CComDemoDlg 对话框



CComDemoDlg::CComDemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COMDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CComDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CComDemoDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CComDemoDlg 消息处理程序

BOOL CComDemoDlg::OnInitDialog()
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
	EnumPort();
	SendBuf1[0] = 0X71;
	SendBuf1[1] = 0Xfe;
	SendBuf1[2] = 0X10;
	SendBuf1[3] = 0Xaa;
	SendBuf1[4] = 0Xbb;
	SendBuf1[5] = 0Xcc;
	SendBuf1[6] = 0Xdd;
	SendBuf1[7] = 0X00;
	SendBuf2[0] = 0X71;
	SendBuf2[1] = 0Xfe;
	SendBuf2[2] = 0X11;
	SendBuf2[3] = 0X12;
	SendBuf2[4] = 0X34;
	SendBuf2[5] = 0X56;
	SendBuf2[6] = 0X78;
	SendBuf2[7] = 0X00;
	if (!mySerialPort.InitPort(PortNum, CBR_9600, 'N', 8, 1, EV_RXCHAR))//是否打开串口，3就是你外设连接电脑的com口，可以在设备管理器查看，然后更改这个参数
	{
		MessageBox("initPort fail !" );
	}
	if (!mySerialPort.OpenListenThread())//是否打开监听线程，开启线程用来传输返回值
	{
		MessageBox("OpenListenThread fail !" );
	}
	if (!mySerialPort.WriteData(SendBuf1,8))
	{
		MessageBox("WriteData fail !");
	}
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CComDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CComDemoDlg::OnPaint()
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
HCURSOR CComDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

    

void CComDemoDlg::OnBnClickedButton1()
{
	//m_Recived = mySerialPort.b;
	//MessageBox(m_Recived.c_str());
	m_Recived = "";
	//第二次通信
	if (!mySerialPort.WriteData(SendBuf2, 8))
	{
		MessageBox("WriteData fail !");
	}
	Sleep(30);
	m_Recived = mySerialPort.b;
	MessageBox(m_Recived.c_str());
}

//枚举串口
int CComDemoDlg::EnumPort()
{
	PortNum = 3;
	string portnum = "3";
	string strr = "Silicon";
	CArray<SSerInfo, SSerInfo&> asi;
	EnumSerialPorts(asi, FALSE/*include all*/);
	for (int ii = 0; ii < asi.GetSize(); ii++) {
		string str = asi[ii].strFriendlyName;
		string::size_type idx = str.find(strr);
		if (idx != string::npos)
		{
			int n = str.length();
			portnum = str.substr(43, 1);
			PortNum = atoi(portnum.c_str());
			/*CString s;
			s.Format("%d", n);
			MessageBox(s);*/
		}
	}
	return PortNum;
}