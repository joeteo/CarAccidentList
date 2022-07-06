// CNewDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CarAccidentList.h"
#include "CNewDlg.h"
#include "afxdialogex.h"


// CNewDlg 대화 상자

IMPLEMENT_DYNAMIC(CNewDlg, CDialogEx)

CNewDlg::CNewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEWDLG, pParent)
{

}

CNewDlg::~CNewDlg()
{
}

void CNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listChild);
}


BEGIN_MESSAGE_MAP(CNewDlg, CDialogEx)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CNewDlg 메시지 처리기


BOOL CNewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_listChild.SetExtendedStyle(
		LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_listChild.InsertColumn(0, _T("순서"), LVCFMT_CENTER, 40);
	m_listChild.InsertColumn(1, _T("시도"), LVCFMT_CENTER, 80);
	m_listChild.InsertColumn(2, _T("시군구"), LVCFMT_CENTER, 80);
	m_listChild.InsertColumn(3, _T("터널안"), LVCFMT_CENTER, 70);
	m_listChild.InsertColumn(4, _T("교량위"), LVCFMT_CENTER, 70);
	m_listChild.InsertColumn(5, _T("고가도로위"), LVCFMT_CENTER, 70);
	m_listChild.InsertColumn(6, _T("지하차도(도로)내"), LVCFMT_CENTER, 70);
	m_listChild.InsertColumn(7, _T("기타단일로"), LVCFMT_CENTER, 70);
	m_listChild.InsertColumn(8, _T("교차로내"), LVCFMT_CENTER, 70);
	m_listChild.InsertColumn(9, _T("교차로횡단보도내"), LVCFMT_CENTER, 70);
	m_listChild.InsertColumn(10, _T("교차로부근"), LVCFMT_CENTER, 70);
	m_listChild.InsertColumn(11, _T("철길건널목"), LVCFMT_CENTER, 70);
	m_listChild.InsertColumn(12, _T("기타"), LVCFMT_CENTER, 70);
	m_listChild
		.InsertColumn(13, _T("불명"), LVCFMT_CENTER, 70);

	CString str;


	for (int i = 0; i < (int)searchedRows->size(); i++)
	{
		str.Format(_T("%d"), i + 1);
		m_listChild.InsertItem(i, str);
		m_listChild.SetItem(i, 1, LVIF_TEXT, searchedRows->at(i).GetSiDo(), NULL, NULL, NULL, NULL);
		m_listChild.SetItem(i, 2, LVIF_TEXT, searchedRows->at(i).GetSiGunGoo(), NULL, NULL, NULL, NULL);


		for (int j = 0; j < LOCATION_NUMBER; j++)
		{
			str.Format(_T("%d"), searchedRows->at(i).GetAccidentCount(j));
			m_listChild.SetItem(i, j + 3, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CNewDlg::SetListControl(vector<Data>* searchedRows)
{
	this->searchedRows = searchedRows;
}

void CNewDlg::SetParentPtr(CCarAccidentListDlg* dlg)
{
	// TODO: 여기에 구현 코드 추가.
	this->dlgPtr = dlg;
}


void CNewDlg::OnDestroy()
{
	int subTotal[LOCATION_NUMBER] = {0,};

	for(int i=0 ; i< searchedRows->size() ; i++)
	{
		for(int j=0; j< LOCATION_NUMBER; j++)
		{
			subTotal[j] += searchedRows->at(i).GetAccidentCount(j);
		}
	}

	dlgPtr->SetListSubTotal(subTotal);
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
