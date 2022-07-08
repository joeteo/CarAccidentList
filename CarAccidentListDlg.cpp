
// CarAccidentListDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "CarAccidentList.h"
#include "CarAccidentListDlg.h"
#include "afxdialogex.h"
#include "CNewDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CCarAccidentListDlg 대화 상자



CCarAccidentListDlg::CCarAccidentListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CARACCIDENTLIST_DIALOG, pParent)
	, m_keyword(_T(""))
	, selectedIDX(-1)	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CCarAccidentListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Text(pDX, IDC_EDITKEYWORD, m_keyword);
	DDX_Control(pDX, IDC_LISTSUBTOTAL, m_listSubTotal);
}

BEGIN_MESSAGE_MAP(CCarAccidentListDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONLOAD, &CCarAccidentListDlg::OnBnClickedButtonload)
	ON_BN_CLICKED(IDC_BUTTONSEARCH, &CCarAccidentListDlg::OnBnClickedButtonsearch)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CCarAccidentListDlg::OnLvnItemchangedList2)
	ON_WM_DESTROY()
	ON_MESSAGE(MYMSG, &CCarAccidentListDlg::OnMymsg)
END_MESSAGE_MAP()


// CCarAccidentListDlg 메시지 처리기

BOOL CCarAccidentListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();	

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_list.SetExtendedStyle(
		LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_list.InsertColumn(0, _T("순서"), LVCFMT_CENTER, 40);
	m_list.InsertColumn(1, _T("시도"), LVCFMT_CENTER, 80);
	m_list.InsertColumn(2, _T("시군구"), LVCFMT_CENTER, 80);
	m_list.InsertColumn(3, _T("터널안"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(4, _T("교량위"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(5, _T("고가도로위"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(6, _T("지하차도(도로)내"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(7, _T("기타단일로"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(8, _T("교차로내"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(9, _T("교차로횡단보도내"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(10, _T("교차로부근"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(11, _T("철길건널목"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(12, _T("기타"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(13, _T("불명"), LVCFMT_CENTER, 70);


	m_listSubTotal.SetExtendedStyle(
		LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_listSubTotal.InsertColumn(0, _T("시도 또는 시군구"), LVCFMT_CENTER, 100);
	m_listSubTotal.InsertColumn(1, _T("터널안"), LVCFMT_CENTER, 70);
	m_listSubTotal.InsertColumn(2, _T("교량위"), LVCFMT_CENTER, 70);
	m_listSubTotal.InsertColumn(3, _T("고가도로위"), LVCFMT_CENTER, 70);
	m_listSubTotal.InsertColumn(4, _T("지하차도(도로)내"), LVCFMT_CENTER, 70);
	m_listSubTotal.InsertColumn(5, _T("기타단일로"), LVCFMT_CENTER, 70);
	m_listSubTotal.InsertColumn(6, _T("교차로내"), LVCFMT_CENTER, 70);
	m_listSubTotal.InsertColumn(7, _T("교차로횡단보도내"), LVCFMT_CENTER, 70);
	m_listSubTotal.InsertColumn(8, _T("교차로부근"), LVCFMT_CENTER, 70);
	m_listSubTotal.InsertColumn(9, _T("철길건널목"), LVCFMT_CENTER, 70);
	m_listSubTotal.InsertColumn(10, _T("기타"), LVCFMT_CENTER, 70);
	m_listSubTotal.InsertColumn(11, _T("불명"), LVCFMT_CENTER, 70);



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCarAccidentListDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCarAccidentListDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCarAccidentListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


UINT Load(LPVOID LpData)
{

	CCarAccidentListDlg* target = (CCarAccidentListDlg*)(LpData);
	target->DC.loadListFromFile();
	//LPARAM temp = (LPARAM)(target);
	SendMessage(target->m_hWnd, MYMSG, NULL, NULL);
	return 0;
}

void CCarAccidentListDlg::OnBnClickedButtonload()
{
	AfxBeginThread(Load, (LPVOID)this);		
	UpdateData(false);	
}


void CCarAccidentListDlg::OnBnClickedButtonsearch()
{
		
	UpdateData(true);
	
	vector<Data> searchedRows = DC.searchList(m_keyword);
	
	if(searchedRows.size()==0)
	{
		AfxMessageBox(_T("일치하는 결과가 없습니다"));
		return;
	}

	m_listSubTotal.DeleteAllItems();
	
	CNewDlg child;

	child.SetParentPtr(this);
	child.SetListControl(&searchedRows);

	child.DoModal();	

	m_keyword = "";

	UpdateData(false);

}


void CCarAccidentListDlg::OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	selectedIDX = pNMLV->iItem;
}


void CCarAccidentListDlg::OnDestroy()
{
	if (DC.getList().size() != 0)
	{
		for (int i = 0; i < DC.getList().size(); i++)
		{
			delete DC.getList().at(i);
		}
		DC.getList().clear();
	}
	CDialogEx::OnDestroy();

}


void CCarAccidentListDlg::SetListSubTotal(int* subTotal)
{
	m_listSubTotal.InsertItem(0, m_keyword);
	for (int i = 0; i < LOCATION_NUMBER; i++)
	{
		CString str;
		str.Format(_T("%d"), subTotal[i]);
		m_listSubTotal.SetItem(0, i+1, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
	}
}




afx_msg LRESULT CCarAccidentListDlg::OnMymsg(WPARAM wParam, LPARAM lParam)
{

	CString str;
	m_list.DeleteAllItems();

	for (int i = 0; i < (int)DC.getList().size(); i++)
	{
		str.Format(_T("%d"), i + 1);
		m_list.InsertItem(i, str);
		m_list.SetItem(i, 1, LVIF_TEXT, DC.getList().at(i)->GetSiDo(), NULL, NULL, NULL, NULL);
		m_list.SetItem(i, 2, LVIF_TEXT, DC.getList().at(i)->GetSiGunGoo(), NULL, NULL, NULL, NULL);


		for (int j = 0; j < LOCATION_NUMBER; j++)
		{
			str.Format(_T("%d"), DC.getList().at(i)->GetAccidentCount(j));
			m_list.SetItem(i, j + 3, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
		}
	}
	
	return 0;
}
