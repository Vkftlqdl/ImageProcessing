
// ImageProcessingView.cpp : CImageProcessingView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"
#include "ImageProcessingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessingView

IMPLEMENT_DYNCREATE(CImageProcessingView, CView)

BEGIN_MESSAGE_MAP(CImageProcessingView, CView)
	// ǥ�� �μ� �����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DownSampling, &CImageProcessingView::OnDownsampling)
	ON_COMMAND(ID_UP_SAMPLING, &CImageProcessingView::OnUpSampling)
	ON_COMMAND(ID_quant, &CImageProcessingView::Onquant)
	ON_COMMAND(ID_SUM_CONSTANT, &CImageProcessingView::OnSumConstant)
	ON_COMMAND(ID_MUL_CONSTANT, &CImageProcessingView::OnMulConstant)
	ON_COMMAND(ID_SUB_CONSTANT, &CImageProcessingView::OnSubConstant)
	ON_COMMAND(ID_DIV_CONSTANT, &CImageProcessingView::OnDivConstant)
	ON_COMMAND(ID_AND_OPERATE, &CImageProcessingView::OnAndOperate)
	ON_COMMAND(ID_OR_OPERATE, &CImageProcessingView::OnOrOperate)
	ON_COMMAND(ID_XOR_OPERATE, &CImageProcessingView::OnXorOperate)
	ON_COMMAND(ID_brightandcontrast, &CImageProcessingView::Onbrightandcontrast)
	ON_COMMAND(ID_NEGA_TRANSFORM, &CImageProcessingView::OnNegaTransform)
	ON_COMMAND(ID_GAMMA_CORRECTION, &CImageProcessingView::OnGammaCorrection)
	ON_COMMAND(ID_BINARIZATION, &CImageProcessingView::OnBinarization)
	ON_COMMAND(ID_STRESS_TRANSFORM, &CImageProcessingView::OnStressTransform)
	ON_COMMAND(ID_HISTO_STRETCH, &CImageProcessingView::OnHistoStretch)
	ON_COMMAND(ID_HISTOGRAM, &CImageProcessingView::OnHistogram)
	ON_COMMAND(ID_HISTO_EQUAL, &CImageProcessingView::OnHistoEqual)
	ON_COMMAND(ID_HISTO_SPEC, &CImageProcessingView::OnHistoSpec)
	ON_COMMAND(ID_EMBOSSING, &CImageProcessingView::OnEmbossing)
	ON_COMMAND(ID_BLURR, &CImageProcessingView::OnBlurr)
	ON_COMMAND(ID_GAUSSIAN_FILTER, &CImageProcessingView::OnGaussianFilter)
	ON_COMMAND(ID_SHARPENING, &CImageProcessingView::OnSharpening)
	ON_COMMAND(ID_HPF_SHARP, &CImageProcessingView::OnHpfSharp)
	ON_COMMAND(ID_LPF_SHARP, &CImageProcessingView::OnLpfSharp)
	ON_COMMAND(ID_HOMOGEN_OPERATOR, &CImageProcessingView::OnHomogenOperator)
	ON_COMMAND(ID_DIFF_OPERATOR_HOR, &CImageProcessingView::OnDiffOperatorHor)
	ON_COMMAND(ID_MEDI, &CImageProcessingView::OnMedi)
	ON_COMMAND(ID_NEAREST, &CImageProcessingView::OnNearest)
	ON_COMMAND(ID_BILINEAR, &CImageProcessingView::OnBilinear)
	ON_COMMAND(ID_ROTATE30, &CImageProcessingView::OnRotate30)
	ON_COMMAND(ID_COFFEE_CUP, &CImageProcessingView::OnCoffeeCup)
	ON_COMMAND(ID_TRANSLATION, &CImageProcessingView::OnTranslation)
	ON_COMMAND(ID_MIRROR_HOR, &CImageProcessingView::OnMirrorHor)
END_MESSAGE_MAP()

// CImageProcessingView ����/�Ҹ�

CImageProcessingView::CImageProcessingView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CImageProcessingView::~CImageProcessingView()
{
}

BOOL CImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CImageProcessingView �׸���

void CImageProcessingView::OnDraw(CDC* pDC)
{
	 CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
   ASSERT_VALID(pDoc);
   // TODO: add draw code for native data here

   int i, j;
   unsigned char R, G, B;
   // �Է� ���� ���
   for(i = 0 ; i<pDoc->m_height ; i++){
      for(j = 0 ; j<pDoc->m_width ; j++){
          R = pDoc->m_InputImage[i*pDoc->m_width+j];
          G = B = R;
          pDC->SetPixel(j+5, i+5, RGB(R, G, B));
      }
   }

   // ��ҵ� ���� ���
   for(i = 0 ; i<pDoc->m_Re_height ; i++){
       for(j = 0 ; j<pDoc->m_Re_width ; j++){
           R = pDoc->m_OutputImage[i*pDoc->m_Re_width+j];
           G = B = R;
           pDC->SetPixel(j+pDoc->m_width+10, i+5, RGB(R, G, B));
       }
   }

}


// CImageProcessingView �μ�

BOOL CImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}
void CImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CImageProcessingView ����

#ifdef _DEBUG
void CImageProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessingDoc* CImageProcessingView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
	return (CImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessingView �޽��� ó����


void CImageProcessingView::OnDownsampling()
{
 CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
   ASSERT_VALID(pDoc);

   pDoc->OnDownSampling(); // Doc Ŭ������ OnDownSampling �Լ� ȣ��

   Invalidate(TRUE); // ȭ�� ����
}


void CImageProcessingView::OnUpSampling()
{
   // TODO: Add your command handler code here
   CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
   ASSERT_VALID(pDoc);

   pDoc->OnUpSampling(); // Doc Ŭ������ OnUpSampling �Լ� ȣ��
 
   Invalidate(TRUE); // ȭ�� ����
}

void CImageProcessingView::Onquant()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
   ASSERT_VALID(pDoc);

   pDoc->OnQuantization(); // Doc Ŭ������ OnQuantization �Լ� ȣ��

   Invalidate(TRUE); // ȭ�� ����

}


void CImageProcessingView::OnSumConstant()
{
	// TODO: Add your command handler code here
   CImageProcessingDoc* pDoc = GetDocument();
   // ��ť��Ʈ Ŭ���� ����
   ASSERT_VALID(pDoc); // �ν��Ͻ� �ּҸ� ������

   pDoc->OnSumConstant();

   Invalidate(TRUE);

}

void CImageProcessingView::OnMulConstant()
{
   // TODO: Add your command handler code here
   CImageProcessingDoc* pDoc = GetDocument(); // ��ť��Ʈ Ŭ���� ����
   ASSERT_VALID(pDoc); // �ν��Ͻ� �ּҸ� ������

   pDoc->OnMulConstant();

   Invalidate(TRUE);
}



void CImageProcessingView::OnSubConstant()
{
   CImageProcessingDoc* pDoc = GetDocument();// ��ť��Ʈ Ŭ���� ����
   ASSERT_VALID(pDoc); // �ν��Ͻ� �ּҸ� ������

   pDoc->OnSubConstant();

   Invalidate(TRUE);

}


void CImageProcessingView::OnDivConstant()
{
   CImageProcessingDoc* pDoc = GetDocument(); // ��ť��Ʈ Ŭ���� ����
   ASSERT_VALID(pDoc); // �ν��Ͻ� �ּҸ� ������

   pDoc->OnDivConstant();

   Invalidate(TRUE);
}


void CImageProcessingView::OnAndOperate()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

   pDoc->OnAndOperate();

   Invalidate(TRUE);

}


void CImageProcessingView::OnOrOperate()
{
   CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnOrOperate();

   Invalidate(TRUE);


}


void CImageProcessingView::OnXorOperate()
{
   CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);
   pDoc->OnXorOperate();
   Invalidate(TRUE);

}



void CImageProcessingView::Onbrightandcontrast()
{
	CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);
   pDoc->Onbrightandcontrast();
   Invalidate(TRUE);
}


void CImageProcessingView::OnNegaTransform()
{
   CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnNegaTransform();

   Invalidate(TRUE);

}


void CImageProcessingView::OnGammaCorrection()
{
	   CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnGammaCorrection();

   Invalidate(TRUE);

}


void CImageProcessingView::OnBinarization()
{
   CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnBinarization();

   Invalidate(TRUE);
}


void CImageProcessingView::OnStressTransform()
{
   CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc-> OnStressTransform ();

   Invalidate(TRUE);

}


void CImageProcessingView::OnHistoStretch()
{
   CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnHistoStretch();

   Invalidate(TRUE);

}

void CImageProcessingView::OnHistogram()
{
	CImageProcessingDoc*pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnHistogram();
   Invalidate(TRUE);

}


void CImageProcessingView::OnHistoEqual()
{
	CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnHistoEqual();
   
   Invalidate(TRUE);
}


void CImageProcessingView::OnHistoSpec()
{
	   CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnHistoSpec();

   Invalidate(TRUE);
}


void CImageProcessingView::OnEmbossing()
{
	CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnEmbossing();

   Invalidate(TRUE);

}


void CImageProcessingView::OnBlurr()
{
   CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnBlurr();

   Invalidate(TRUE);
}


void CImageProcessingView::OnGaussianFilter()
{
   CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnGaussianFilter();

   Invalidate(TRUE);
}


void CImageProcessingView::OnSharpening()
{
	CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnSharpening();

   Invalidate(TRUE);
}


void CImageProcessingView::OnHpfSharp()
{
	CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnHpfSharp();

   Invalidate(TRUE);

}


void CImageProcessingView::OnLpfSharp()
{
	   CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnLpfSharp();
   
   Invalidate(TRUE);

}

void CImageProcessingView::OnDiffOperatorHor()
{
	CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnDiffOperatorHor();

   Invalidate(TRUE);

}

void CImageProcessingView::OnHomogenOperator()
{
	   CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnHomogenOperator();

   Invalidate(TRUE);

}


void CImageProcessingView::OnMedi()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMedi();
	Invalidate(TRUE);
}


void CImageProcessingView::OnNearest()
{
   CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnNearest();

   Invalidate(TRUE);

}


void CImageProcessingView::OnBilinear()
{
   CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnBilinear();

   Invalidate(TRUE);

}


void CImageProcessingView::OnRotate30()
{
   CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnRotate30();

   Invalidate(TRUE);

}


void CImageProcessingView::OnCoffeeCup()
{
	CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnCoffeeCup();
   Invalidate(TRUE);
}


void CImageProcessingView::OnTranslation()
{
   CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnTranslation();

   Invalidate(TRUE);

}


void CImageProcessingView::OnMirrorHor()
{
   CImageProcessingDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   pDoc->OnMirrorHor();

   Invalidate(TRUE);

}