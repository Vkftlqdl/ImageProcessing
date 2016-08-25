
// WinColorView.h : CWinColorView Ŭ������ �������̽�
//

#pragma once


class CWinColorView : public CView
{
protected: // serialization������ ��������ϴ�.
	CWinColorView();
	DECLARE_DYNCREATE(CWinColorView)

// Ư���Դϴ�.
public:
	CWinColorDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CWinColorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // WinColorView.cpp�� ����� ����
inline CWinColorDoc* CWinColorView::GetDocument() const
   { return reinterpret_cast<CWinColorDoc*>(m_pDocument); }
#endif

