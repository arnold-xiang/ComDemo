
// ComDemoDlg.h: 头文件
//
#include "SerialPort.h"  
#pragma once


// CComDemoDlg 对话框
class CComDemoDlg : public CDialogEx
{
// 构造
public:
	CComDemoDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int PortNum;
	afx_msg int EnumPort();
	CSerialPort mySerialPort;
	string m_Recived;
	unsigned char SendBuf1[8] ;
	unsigned char SendBuf2[8];
	const string RecevedBuf1 = "71 FE 80 01 00 00 00 CB ";
	afx_msg void OnBnClickedButton1();
};
