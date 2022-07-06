
// CarAccidentListDlg.h: 헤더 파일
//

#pragma once
#include "DataController.h"
#include <string>


using namespace std;

// CCarAccidentListDlg 대화 상자
class CCarAccidentListDlg : public CDialogEx
{
// 생성입니다.
public:
	CCarAccidentListDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CARACCIDENTLIST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DataController DC;
public:
	
	CListCtrl m_list;
	afx_msg void OnBnClickedButtonload();
	CString m_keyword;
	afx_msg void OnBnClickedButtonsearch();
	int selectedIDX;
	afx_msg void OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	CListCtrl m_listSubTotal;
	void SetListSubTotal(int* subTotal);
};
