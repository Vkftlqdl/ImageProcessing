
// WinColorView.cpp : CWinColorView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "WinColor.h"
#endif

#include "WinColorDoc.h"
#include "WinColorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinColorView

IMPLEMENT_DYNCREATE(CWinColorView, CView)

BEGIN_MESSAGE_MAP(CWinColorView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_RGB_CHANNEL_SPLATTING, &CWinColorView::OnRgbChannelSplatting)
	ON_COMMAND(ID_EDIT_COPY, &CWinColorView::OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, &CWinColorView::OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &CWinColorView::OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_RGB_CHANNEL_SPLATTING, &CWinColorView::OnUpdateRgbChannelSplatting)
	ON_COMMAND(ID_HSIChannel_Splatting, &CWinColorView::OnHsichannelSplatting)
	ON_UPDATE_COMMAND_UI(ID_HSIChannel_Splatting, &CWinColorView::OnUpdateHsichannelSplatting)
	ON_COMMAND(ID_COLOR2GREY, &CWinColorView::OnColor2grey)
	ON_UPDATE_COMMAND_UI(ID_COLOR2GREY, &CWinColorView::OnUpdateColor2grey)
	ON_COMMAND(ID_EMBOSSING, &CWinColorView::OnEmbossing)
	ON_UPDATE_COMMAND_UI(ID_EMBOSSING, &CWinColorView::OnUpdateEmbossing)
	ON_COMMAND(ID_RGB_SHARPENING, &CWinColorView::OnRgbSharpening)
	ON_UPDATE_COMMAND_UI(ID_RGB_SHARPENING, &CWinColorView::OnUpdateRgbSharpening)
END_MESSAGE_MAP()

// CWinColorView 생성/소멸

CWinColorView::CWinColorView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	BmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO)+256*sizeof(RGBQUAD));
	for(int i=0; i<256; i++) 
	{
		BmInfo->bmiColors[i].rgbRed= BmInfo->bmiColors[i].rgbGreen = BmInfo->bmiColors[i].rgbBlue = i; 
		BmInfo->bmiColors[i].rgbReserved = 0;
	}
}

CWinColorView::~CWinColorView()
{
	if(BmInfo) 
		delete BmInfo;
}

BOOL CWinColorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CWinColorView 그리기

void CWinColorView::OnDraw(CDC* pDC)
{
	CWinColorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->m_InImg==NULL) 
		return;

	height = pDoc->dibHi.biHeight;
	width = pDoc->dibHi.biWidth;
	rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount*pDoc->dibHi.biWidth);
	BmInfo->bmiHeader = pDoc->dibHi;

	SetDIBitsToDevice(pDC->GetSafeHdc(),0,0,width,height,
						0,0,0,height,pDoc->m_InImg,BmInfo, DIB_RGB_COLORS);

}


// CWinColorView 인쇄

BOOL CWinColorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CWinColorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CWinColorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CWinColorView 진단

#ifdef _DEBUG
void CWinColorView::AssertValid() const
{
	CView::AssertValid();
}

void CWinColorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinColorDoc* CWinColorView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinColorDoc)));
	return (CWinColorDoc*)m_pDocument;
}
#endif //_DEBUG


// CWinColorView 메시지 처리기

void CWinColorView::OnEditCopy()
{
	CWinColorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->CopyClipboard(pDoc->m_InImg,height, width,pDoc->dibHi.biBitCount);
}


void CWinColorView::OnEditPaste()
{
	if(!IsClipboardFormatAvailable(CF_DIB)) 
		return;

	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


void CWinColorView::OnUpdateEditPaste(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsClipboardFormatAvailable(CF_DIB));	
}

void CWinColorView::OnRgbChannelSplatting()
{
	CWinColorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int index, i, j;
	for(int k=2; k>=0; k--)
	{
		for(i=0; i<height*rwsize; i++) pDoc->m_OutImg[i]=0;
		for(i=0; i<height; i++)
		{
			index = (height-i-1)*rwsize;
			for(j=0; j<width; j++) pDoc->m_OutImg[index+3*j+k]= pDoc->m_InImg[index+3*j+k];
		}
		pDoc->CopyClipboard(pDoc->m_OutImg,height,width,24);
		AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
	}
}

void CWinColorView::OnUpdateRgbChannelSplatting(CCmdUI *pCmdUI)
{
	CWinColorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pCmdUI->Enable(pDoc->dibHi.biBitCount==24);
}


void CWinColorView::OnHsichannelSplatting()
{
	CWinColorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_RGB2Gray(pDoc->m_InImg,pDoc->m_OutImg,height,width);

	int index, i, j;
	int grRWSIZE = WIDTHBYTES(8*width);
	unsigned char *GrayImg = new unsigned char [height*grRWSIZE];
	for(i=0; i<height; i++)
	{
		index = (height-i-1)*rwsize;
		for(j=0; j<width; j++) GrayImg[(height-i-1)*grRWSIZE+j]= pDoc->m_OutImg[index+3*j];
	}

	pDoc->CopyClipboard(GrayImg,height,width,8);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
	delete []GrayImg;	
}


void CWinColorView::OnUpdateHsichannelSplatting(CCmdUI *pCmdUI)
{
	CWinColorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pCmdUI->Enable(pDoc->dibHi.biBitCount==24);
}


void CWinColorView::OnColor2grey()
{
	CWinColorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_RGB2Gray(pDoc->m_InImg,pDoc->m_OutImg,height,width);

	int index, i, j;
	int grRWSIZE = WIDTHBYTES(8*width);
	unsigned char *GrayImg = new unsigned char [height*grRWSIZE];
	for(i=0; i<height; i++)
	{
		index = (height-i-1)*rwsize;
		for(j=0; j<width; j++) GrayImg[(height-i-1)*grRWSIZE+j]= pDoc->m_OutImg[index+3*j];
	}

	pDoc->CopyClipboard(GrayImg,height,width,8);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
	delete []GrayImg;	

}


void CWinColorView::OnUpdateColor2grey(CCmdUI *pCmdUI)
{
	CWinColorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pCmdUI->Enable(pDoc->dibHi.biBitCount==24);
}


void CWinColorView::OnEmbossing()
{
	CWinColorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_ColorEmbossing(pDoc->m_InImg,pDoc->m_OutImg,height,width);

	pDoc->CopyClipboard(pDoc->m_OutImg,height,width,24);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


void CWinColorView::OnUpdateEmbossing(CCmdUI *pCmdUI)
{
	CWinColorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pCmdUI->Enable(pDoc->dibHi.biBitCount==24);	
}


void CWinColorView::OnRgbSharpening()
{
	CWinColorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_RGBSharpening(pDoc->m_InImg,pDoc->m_OutImg,height,width);

	pDoc->CopyClipboard(pDoc->m_OutImg,height,width,24);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);

}


void CWinColorView::OnUpdateRgbSharpening(CCmdUI *pCmdUI)
{
	CWinColorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pCmdUI->Enable(pDoc->dibHi.biBitCount==24);
}
