#pragma once
#include <vector>

#include "CarAccidentListDlg.h"
#include "Data.h"


// CNewDlg 대화 상자

class CNewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewDlg)

public:
	CNewDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CNewDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listChild;
	virtual BOOL OnInitDialog();
	void SetListControl(vector<Data>* searchedRows);
	vector<Data>* searchedRows;
	void SetParentPtr(CCarAccidentListDlg* dlg);
	CCarAccidentListDlg* dlgPtr;

	afx_msg void OnDestroy();
};
