
// ImageProcessingView.h : CImageProcessingView Ŭ������ �������̽�
//

#pragma once


class CImageProcessingView : public CView
{
protected: // serialization������ ��������ϴ�.
	CImageProcessingView();
	DECLARE_DYNCREATE(CImageProcessingView)

// Ư���Դϴ�.
public:
	CImageProcessingDoc* GetDocument() const;

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
	virtual ~CImageProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDownsampling();
	afx_msg void OnUpSampling();
	afx_msg void Onquant();
	afx_msg void OnSumConstant();
	afx_msg void OnMulConstant();
	afx_msg void OnSubConstant();
	afx_msg void OnDivConstant();
	afx_msg void OnAndOperate();
	afx_msg void OnOrOperate();
	afx_msg void OnXorOperate();
//	afx_msg void Onbrightandcontrast();
	afx_msg void Onbrightandcontrast();
	afx_msg void OnNegaTransform();
	afx_msg void OnGammaCorrection();
	afx_msg void OnBinarization();
	afx_msg void OnStressTransform();
	afx_msg void OnHistoStretch();
	afx_msg void OnHistogram();
	afx_msg void OnHistoEqual();
	afx_msg void OnHistoSpec();
	afx_msg void OnEmbossing();
	afx_msg void OnBlurr();
	afx_msg void OnGaussianFilter();
	afx_msg void OnSharpening();
	afx_msg void OnHpfSharp();
	afx_msg void OnLpfSharp();
	afx_msg void OnHomogenOperator();
	afx_msg void OnDiffOperatorHor();
	afx_msg void OnMedi();
	afx_msg void OnNearest();
	afx_msg void OnBilinear();
	afx_msg void OnRotate30();
	afx_msg void OnCoffeeCup();
	afx_msg void OnTranslation();
	afx_msg void OnMirrorHor();
};

#ifndef _DEBUG  // ImageProcessingView.cpp�� ����� ����
inline CImageProcessingDoc* CImageProcessingView::GetDocument() const
   { return reinterpret_cast<CImageProcessingDoc*>(m_pDocument); }
#endif

