
// WinColorView.h : CWinColorView 클래스의 인터페이스
//

#pragma once


class CWinColorView : public CView
{
protected: // serialization에서만 만들어집니다.
	CWinColorView();
	DECLARE_DYNCREATE(CWinColorView)

// 특성입니다.
public:
	CWinColorDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CWinColorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	int height;
	int width;
	int rwsize;
	BITMAPINFO *BmInfo;
	afx_msg void OnRgbChannelSplatting();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRgbChannelSplatting(CCmdUI *pCmdUI);
	afx_msg void OnHsichannelSplatting();
	afx_msg void OnUpdateHsichannelSplatting(CCmdUI *pCmdUI);
	afx_msg void OnColor2grey();
	afx_msg void OnUpdateColor2grey(CCmdUI *pCmdUI);
	afx_msg void OnEmbossing();
	afx_msg void OnUpdateEmbossing(CCmdUI *pCmdUI);
	afx_msg void OnRgbSharpening();
	afx_msg void OnUpdateRgbSharpening(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // WinColorView.cpp의 디버그 버전
inline CWinColorDoc* CWinColorView::GetDocument() const
   { return reinterpret_cast<CWinColorDoc*>(m_pDocument); }
#endif

