
// ImageProcessingDoc.cpp : CImageProcessingDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"
#include <math.h>
#include <propkey.h>
#include "stdafx.h"
#include "ImageProcessing.h"
#include "ImageProcessingDoc.h"
#include "DownSampleDlg.h" // 대화상자 사용을 위한 헤더 선언
#include "UpSampleDlg.h"
#include "QuantizationDlg.h" 
#include "ConstantDlg.h" 
#include "StressTransformDlg.h" // 범위 강조 대화상자를 위한 헤더 선언
#include "Histogram.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessingDoc

IMPLEMENT_DYNCREATE(CImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessingDoc, CDocument)
	ON_COMMAND(ID_SUM_CONSTANT, &CImageProcessingDoc::OnSumConstant)
	ON_COMMAND(ID_MUL_CONSTANT, &CImageProcessingDoc::OnMulConstant)
	ON_COMMAND(ID_SUB_CONSTANT, &CImageProcessingDoc::OnSubConstant)
	ON_COMMAND(ID_DIV_CONSTANT, &CImageProcessingDoc::OnDivConstant)
	ON_COMMAND(ID_AND_OPERATE, &CImageProcessingDoc::OnAndOperate)
	ON_COMMAND(ID_OR_OPERATE, &CImageProcessingDoc::OnOrOperate)
	ON_COMMAND(ID_XOR_OPERATE, &CImageProcessingDoc::OnXorOperate)
	ON_COMMAND(ID_brightandcontrast, &CImageProcessingDoc::Onbrightandcontrast)
	ON_COMMAND(ID_NEGA_TRANSFORM, &CImageProcessingDoc::OnNegaTransform)
	ON_COMMAND(ID_GAMMA_CORRECTION, &CImageProcessingDoc::OnGammaCorrection)
	ON_COMMAND(ID_BINARIZATION, &CImageProcessingDoc::OnBinarization)
	ON_COMMAND(ID_STRESS_TRANSFORM, &CImageProcessingDoc::OnStressTransform)
	ON_COMMAND(ID_HISTO_STRETCH, &CImageProcessingDoc::OnHistoStretch)
	ON_COMMAND(ID_HISTOGRAM, &CImageProcessingDoc::OnHistogram)
	ON_COMMAND(ID_HISTO_EQUAL, &CImageProcessingDoc::OnHistoEqual)
	ON_COMMAND(ID_HISTO_SPEC, &CImageProcessingDoc::OnHistoSpec)
	ON_COMMAND(ID_EMBOSSING, &CImageProcessingDoc::OnEmbossing)
	ON_COMMAND(ID_BLURR, &CImageProcessingDoc::OnBlurr)
	ON_COMMAND(ID_GAUSSIAN_FILTER, &CImageProcessingDoc::OnGaussianFilter)
	ON_COMMAND(ID_SHARPENING, &CImageProcessingDoc::OnSharpening)
	ON_COMMAND(ID_HPF_SHARP, &CImageProcessingDoc::OnHpfSharp)
	ON_COMMAND(ID_LPF_SHARP, &CImageProcessingDoc::OnLpfSharp)
	ON_COMMAND(ID_DIFF_OPERATOR_HOR, &CImageProcessingDoc::OnDiffOperatorHor)
	ON_COMMAND(ID_HOMOGEN_OPERATOR, &CImageProcessingDoc::OnHomogenOperator)
	ON_COMMAND(ID_MEDI, &CImageProcessingDoc::OnMedi)
	ON_COMMAND(ID_NEAREST, &CImageProcessingDoc::OnNearest)
	ON_COMMAND(ID_BILINEAR, &CImageProcessingDoc::OnBilinear)
	ON_COMMAND(ID_ROTATE30, &CImageProcessingDoc::OnRotate30)
	ON_COMMAND(ID_COFFEE_CUP, &CImageProcessingDoc::OnCoffeeCup)
	ON_COMMAND(ID_TRANSLATION, &CImageProcessingDoc::OnTranslation)
	ON_COMMAND(ID_MIRROR_HOR, &CImageProcessingDoc::OnMirrorHor)
END_MESSAGE_MAP()


// CImageProcessingDoc 생성/소멸

CImageProcessingDoc::CImageProcessingDoc()
	: m_InputImage(0)
	, m_width(0)
	, m_height(0)
	, m_size(0)
	, m_OutputImage(NULL)
	, m_Re_width(0)
	, m_Re_height(0)
	, m_Re_size(0)
	, m_tempImage(NULL)
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageProcessingDoc::~CImageProcessingDoc()
{
}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProcessingDoc serialization

void CImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProcessingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProcessingDoc 진단

#ifdef _DEBUG
void CImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessingDoc 명령


BOOL CImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{

	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	
      CFile File; // 파일 객체 선언

      File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
      // 파일 열기 대화상자에서 선택한 파일을 지정하고 읽기 모드 선택

      // 이 책에서는 영상의 크기 256*256, 512*512, 640*480만을 사용한다.
      if(File.GetLength() == 256*256){ // RAW 파일의 크기 결정

      m_height = 256;
      m_width = 256;
   }
   else if(File.GetLength() == 512*512){ // RAW 파일의 크기 결정
      m_height = 512;
      m_width = 512;
   }
   else if(File.GetLength() == 640*480){ // RAW 파일의 크기 결정
      m_height = 480;
      m_width = 640;
   }
   else{
      AfxMessageBox(_T("Not Support Image Size")); // 해당 크기가 없는 경우
      return 0;
   }
      CSize sizeTotal;
   sizeTotal.cx = m_width;
   sizeTotal.cy = m_height;
   m_size = m_width * m_height; // 영상의 크기 계산

   m_InputImage = new unsigned char [m_size];
   // 입력 영상의 크기에 맞는 메모리 할당

   for(int i = 0 ; i<m_size ; i++)
      m_InputImage[i] = 255; // 초기화
   File.Read(m_InputImage, m_size); // 입력 영상 파일 읽기
   File.Close(); // 파일 닫기

	return TRUE;
}


void CImageProcessingDoc::OnDownSampling()
{
	
   int i, j;
   CDownSampleDlg dlg;
   if(dlg.DoModal() == IDOK) // 대화상자의 활성화 여부
   {
      m_Re_height = m_height / dlg.m_DownSampleRate;
      // 축소 영상의 세로 길이를 계산
      m_Re_width = m_width / dlg.m_DownSampleRate;
      // 축소 영상의 가로 길이를 계산
      m_Re_size = m_Re_height * m_Re_width;
      // 축소 영상의 크기를 계산

      m_OutputImage = new unsigned char [m_Re_size];     
      // 축소 영상을 위한 메모리 할당

      for(i=0 ; i<m_Re_height ; i++){
       for(j=0 ; j<m_Re_width ; j++){
         m_OutputImage[i*m_Re_width + j]
          = m_InputImage[(i*dlg.m_DownSampleRate*m_width)+dlg.m_DownSampleRate*j];
                // 축소 영상을 생성
         }
     }
   }
}


void CImageProcessingDoc::OnUpSampling()
{
	 int i, j;
   
   CUpSampleDlg dlg;
   if(dlg.DoModal() == IDOK){ // DoModal 대화상자의 활성화 여부
       m_Re_height = m_height * dlg.m_UpSampleRate;
       // 확대 영상의 세로 길이 계산
       m_Re_width = m_width * dlg.m_UpSampleRate;
       // 확대 영상의 가로 길이 계산
       m_Re_size = m_Re_height * m_Re_width;
       // 확대 영상의 크기 계산
       m_OutputImage = new unsigned char[m_Re_size];
       // 확대 영상을 위한 메모리 할당

       for(i=0 ; i<m_Re_size ; i++)
           m_OutputImage[i] = 0; // 초기화

       for(i=0 ; i<m_height ; i++){
           for(j=0 ; j<m_width ; j++){
			   for (int k = 0; k <dlg.m_UpSampleRate; k++)
			   {
				   for (int b = 0; b < dlg.m_UpSampleRate; b++)
				   {
					   m_OutputImage[i*dlg.m_UpSampleRate*m_Re_width + k*m_Re_width + dlg.m_UpSampleRate*j+b]= m_InputImage[i*m_width + j];
				   }
			   }
             // m_OutputImage[i*dlg.m_UpSampleRate*m_Re_width + dlg.m_UpSampleRate*j]= m_InputImage[i*m_width + j];
           } // 재배치하여 영상 확대
       }
   }
   
}


void CImageProcessingDoc::OnQuantization(void)
{
	CQuantizationDlg dlg;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	if(dlg.DoModal() == IDOK)
	{
		int i, sb;
		sb = 8 - dlg.mQuantBit;
		for(i=0 ; i<m_size ; i++){
			m_OutputImage[i] = m_InputImage[i]>>sb<<sb;
		}
	}

}


void CImageProcessingDoc::OnSumConstant()
{
	CConstantDlg dlg; // 상수 값을 입력받는 대화상자

   int i;

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;

   m_OutputImage = new unsigned char[m_Re_size];

   if(dlg.DoModal() == IDOK){
     for(i=0 ; i<m_size ; i++){
       if(m_InputImage[i] + dlg.m_Constant >= 255)
          m_OutputImage[i] = 255;
       // 출력 값이 255보다 크면 255 출력
       else
       m_OutputImage[i]=(unsigned char)(m_InputImage[i] + dlg.m_Constant);
       // 상수 값과 화소 값과의 덧셈
     }
  }

}


void CImageProcessingDoc::OnMulConstant()
{
	CConstantDlg dlg;

   int i;

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;

   m_OutputImage = new unsigned char[m_Re_size];

   if(dlg.DoModal() == IDOK){
      for(i=0 ; i<m_size ; i++){
         if(m_InputImage[i] * dlg.m_Constant > 255)
                 m_OutputImage[i] = 255;
         // 곱의 값이 255보다 크면 255를 출력
         else if(m_InputImage[i] * dlg.m_Constant < 0)
                 m_OutputImage[i] = 0;
         // 곱의 값이 0보다 작으면 0을 출력
         else
            m_OutputImage [i] 
                  = (unsigned char)(m_InputImage[i] * dlg.m_Constant);
         // 상수 값과 화소 값 곱셈
      }
   }

}


void CImageProcessingDoc::OnSubConstant()
{
   CConstantDlg dlg;

   int i;

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;

   m_OutputImage = new unsigned char[m_Re_size];

   if(dlg.DoModal() == IDOK){
      for(i=0 ; i<m_size ; i++){
         if(m_InputImage[i] - dlg.m_Constant < 0)
                   m_OutputImage[i] = 0; // 출력 값이 255보다 크면 255를 출력
         else
            m_OutputImage [i]                    = (unsigned char)(m_InputImage[i] - dlg.m_Constant);
         // 상수 값과 화소 값과의 뺄셈
      }
   }

}


void CImageProcessingDoc::OnDivConstant()
{
	   CConstantDlg dlg;

   int i;

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;

   m_OutputImage = new unsigned char[m_Re_size];

   if(dlg.DoModal() == IDOK){
      for(i=0 ; i<m_size ; i++){
         if(m_InputImage[i] / dlg.m_Constant > 255)
                   m_OutputImage[i] = 255;
         // 나눗셈의 값이 255보다 크면 255를 출력
         else if(m_InputImage[i] / dlg.m_Constant < 0)
                   m_OutputImage[i] = 0;
         // 나눗셈의 값이 0보다 작으면 0을 출력
         else
            m_OutputImage [i] 
                    = (unsigned char)(m_InputImage[i] / dlg.m_Constant);
         // 상수 값과 화소 값 나눗셈
      }
   }

}


void CImageProcessingDoc::OnAndOperate()
{
   CConstantDlg dlg;
   int i;

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;

   m_OutputImage = new unsigned char[m_Re_size];

   if(dlg.DoModal() == IDOK){
      for(i=0 ; i<m_size ; i++){
         // 비트 단위 AND 연산
         if((m_InputImage[i] & (unsigned char)dlg.m_Constant)>= 255)
                            {m_OutputImage[i] = 255;
         }
         else if((m_InputImage[i] & (unsigned char)dlg.m_Constant)< 0)
                            {m_OutputImage[i] = 0;
         }
         else{
              m_OutputImage [i] = (m_InputImage[i] 
                             & (unsigned char)dlg.m_Constant);
         }
      }
   }
}


void CImageProcessingDoc::OnOrOperate()
{
	CConstantDlg dlg;
   int i;

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;

   m_OutputImage = new unsigned char[m_Re_size];

   if(dlg.DoModal() == IDOK){
      for(i=0 ; i<m_size ; i++){
        // 비트 단위 OR 연산
        if((m_InputImage[i] | (unsigned char)dlg.m_Constant) >= 255){
                          m_OutputImage[i] = 255;
        }
        else if((m_InputImage[i] |(unsigned char)dlg.m_Constant) < 0){
                          m_OutputImage[i] = 0;
        }
       else{
            m_OutputImage [i] = (m_InputImage[i] | (unsigned char)dlg.m_Constant);
       }
     }
  }

}


void CImageProcessingDoc::OnXorOperate()
{
   CConstantDlg dlg;
   int i;

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;

   m_OutputImage = new unsigned char[m_Re_size];
   
   if(dlg.DoModal() == IDOK){
      for(i=0 ; i<m_size ; i++){
         // 비트 단위 XOR 연산
         if((m_InputImage[i] ^ (unsigned char)dlg.m_Constant) >= 255){
               m_OutputImage[i] = 255;
         }
         else if((m_InputImage[i] ^ (unsigned char)dlg.m_Constant) < 0){ 
               m_OutputImage[i] = 0;
         }
         else{
            m_OutputImage [i] = (m_InputImage[i] 
                                ^ (unsigned char)dlg.m_Constant);
         }
      }
   }
}


void CImageProcessingDoc::Onbrightandcontrast()
{
	//CQuantizationDlg dlg;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];


	int i,j,k;
	double m = 0.0;
	double s = 0.0;
	for(i=0 ; i<m_size ; i++){
		m += m_InputImage[i]/m_size;
	}
	for (int k = 0; k < m_size; k++)
	{
		s += pow(m_InputImage[k]-m, 2);
	}
	s = sqrt(s/m_size);
	double a = 0.0;
	a = 30/s;
	for (j= 0; j < m_size; j++)
	{
		m_OutputImage[j] = a*(m_InputImage[j] - m) + 128;
	}
}


void CImageProcessingDoc::OnNegaTransform()
{
	int i;

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;

   m_OutputImage = new unsigned char[m_Re_size];

   for(i=0 ; i<m_size ; i++)
      m_OutputImage[i] = 255 - m_InputImage[i]; // 영상 반전을 수행
}


void CImageProcessingDoc::OnGammaCorrection()
{
	CConstantDlg dlg;

   int i;
   double temp;

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;

   m_OutputImage = new unsigned char[m_Re_size];

   if(dlg.DoModal() == IDOK){
      for(i=0 ; i<m_size ; i++){
         temp = pow(m_InputImage[i], 1/dlg.m_Constant);
         // 감마 값 계산
      if(temp < 0)
         m_OutputImage[i] = 0;
      else if(temp > 255)
         m_OutputImage[i] = 255;
      else
         m_OutputImage[i] = (unsigned char)temp;
      }
   }
}


void CImageProcessingDoc::OnBinarization()
{
   CConstantDlg dlg;

   int i;

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;

   m_OutputImage = new unsigned char[m_Re_size];

   if(dlg.DoModal() == IDOK){
      for(i=0 ; i<m_size ; i++){
         if(m_InputImage[i] >= dlg.m_Constant)
             m_OutputImage[i] = 255; // 임계 값보다 크면 255 출력
         else
             m_OutputImage[i] = 0; // 임계 값보다 작으면 0 출력
      }
   }

}


void CImageProcessingDoc::OnStressTransform()
{
	CStressTransformDlg dlg;

   int i;

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;

   m_OutputImage = new unsigned char[m_Re_size];

   if(dlg.DoModal() == IDOK){
      for(i=0 ; i<m_size ; i++){
         // 입력 값이 강조 시작 값과 강조 종료 값 사이에 위치하면 255 출력
         if(m_InputImage[i] >= dlg.m_StartPoint &&
            m_InputImage[i] <= dlg.m_EndPoint)
            m_OutputImage[i] = 255;
         else
            m_OutputImage[i] = m_InputImage[i];
      }
   }

}


void CImageProcessingDoc::OnHistoStretch()
{
   CHistogram dlg;
   int i;
   unsigned char LOW, HIGH, MAX, MIN;

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;
   if(dlg.DoModal() == IDOK){
   LOW = dlg.m_HistoMin;
   HIGH = dlg.m_HistoMax;

   MIN = m_InputImage[0]; // 최소값을 찾기 위한 초기값
   MAX = m_InputImage[0]; // 최대값을 찾기 위한 초기값

   // 입력 영상의 최소값 찾기
   for(i=0 ; i<m_size ; i++){
      if(m_InputImage[i] < MIN)
         MIN = m_InputImage[i];
   }

   // 입력 영상의 최대값 찾기
   for(i=0 ; i<m_size ; i++){
      if(m_InputImage[i] > MAX)
         MAX = m_InputImage[i];
   }

   m_OutputImage = new unsigned char[m_Re_size];

   // 히스토그램 stretch
   for(i=0 ; i<m_size ; i++)
	   m_OutputImage[i] = (unsigned char)((m_InputImage[i] - MIN)*HIGH / (MAX-MIN) + LOW);
   }
}
double m_HIST[256];
double m_Sum_Of_HIST[256];
unsigned char m_Scale_HIST[256];


void CImageProcessingDoc::OnHistogram()
{
	 int i, j, value;
   unsigned char LOW, HIGH;
   double MAX, MIN, DIF;

   m_Re_height = 256;
   m_Re_width = 256;
   m_Re_size = m_Re_height * m_Re_width;

   LOW = 0;
   HIGH = 255;

   // 초기화
   for(i=0 ; i<256 ; i++)
      m_HIST[i] = LOW;

   // 빈도 수 조사
   for(i=0 ; i<m_size ; i++){
      value = (int)m_InputImage[i];
      m_HIST[value]++;
   }

   // 정규화
   MAX = m_HIST[0];
   MIN = m_HIST[0];

   for(i=0 ; i<256 ; i++){
      if(m_HIST[i] > MAX)
         MAX = m_HIST[i];
   }

   for(i=0 ; i<256 ; i++){
      if(m_HIST[i] < MIN)
         MIN = m_HIST[i];
   }
   DIF = MAX - MIN;

   // 정규화된 히스토그램
   for(i=0 ; i<256 ; i++)
      m_Scale_HIST[i] = (unsigned char)((m_HIST[i] - MIN) * HIGH / DIF);
   
   // 정규화된 히스토그램 출력
   m_OutputImage = new unsigned char [m_Re_size + (256*20)];

   for(i=0 ; i<m_Re_size ; i++)
      m_OutputImage[i] = 255;

   // 정규화된 히스토그램의 값은 출력 배열에 검은 점(0)으로 표현
   for(i=0 ; i<256 ; i++){
      for(j = 0 ; j<m_Scale_HIST[i] ; j++){
         m_OutputImage[m_Re_width*(m_Re_height-j-1) + i] = 0;
      }
   }

   // 히스토그램을 출력하고 그 아래 부분에 히스토그램의 색을 표시
   for(i = m_Re_height ; i<m_Re_height + 5 ; i++){
      for(j=0 ; j<256 ; j++){
         m_OutputImage[m_Re_height * i + j] = 255;
      }
   }

   for(i = m_Re_height+5 ; i<m_Re_height + 20 ; i++){
         for(j=0 ; j<256 ; j++){
         m_OutputImage[m_Re_height * i + j] = j;
      }
   }

   m_Re_height = m_Re_height + 20;
   m_Re_size = m_Re_height * m_Re_width;
}


void CImageProcessingDoc::OnHistoEqual()
{
	
   int i, value;
   unsigned char LOW, HIGH, Temp;
   double SUM = 0.0;

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;

   LOW = 0;
   HIGH = 255;

   // 초기화
   for(i=0 ; i<256 ; i++)
      m_HIST[i] = LOW;

   // 빈도 수 조사
   for(i=0 ; i<m_size ; i++){
      value = (int)m_InputImage[i];
      m_HIST[value]++;
   }

   // 누적 히스토그램 생성
   for(i=0 ; i<256 ; i++){
      SUM += m_HIST[i];
      m_Sum_Of_HIST[i] = SUM;
   }

   m_OutputImage = new unsigned char[m_Re_size];

   // 입력 영상을 평활화된 영상으로 출력
   for(i=0 ; i<m_size ; i++){
      Temp = m_InputImage[i];
      m_OutputImage[i]=(unsigned char)(m_Sum_Of_HIST[Temp]*HIGH/m_size);
   }
}


void CImageProcessingDoc::OnHistoSpec()
{
	int i, value, Dvalue, top, bottom, DADD;
   unsigned char *m_DTEMP, m_Sum_Of_ScHIST[256], m_TABLE[256];
   unsigned char LOW, HIGH, Temp, *m_Org_Temp;
   double m_DHIST[256], m_Sum_Of_DHIST[256], SUM = 0.0, DSUM = 0.0;
   double DMAX, DMIN;
   
   top = 255;
   bottom = top - 1;

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;

   m_OutputImage = new unsigned char [m_Re_size];
   m_Org_Temp = new unsigned char [m_size];

   CFile File;
   CFileDialog OpenDlg(TRUE);
// 원하는 히스토그램이 있는 영상을 입력받음
   if(OpenDlg.DoModal() == IDOK){
      File.Open(OpenDlg.GetPathName(), CFile::modeRead);
      
      if(File.GetLength() == (unsigned)m_size){
         m_DTEMP = new unsigned char[m_size];
         File.Read(m_DTEMP, m_size);
         File.Close();
      }
      else{
         AfxMessageBox (_T(" Image size not matched"));
         // 같은 크기의 영상을 대상으로 함
         return;
      }
}

   LOW = 0;
   HIGH = 255;

   // 초기화
   for(i=0 ; i<256 ; i++){
      m_HIST[i] = LOW;
      m_DHIST[i] = LOW;
      m_TABLE[i] = LOW;
   }
   // 빈도 수 조사
   for(i=0 ; i<m_size ; i++){
      value = (int)m_InputImage[i];
      m_HIST[value]++;
      Dvalue = (int)m_DTEMP[i];
      m_DHIST[Dvalue]++;
   }

   // 누적 히스토그램 조사
   for(i=0 ; i<256 ; i++){
      SUM += m_HIST[i];
      m_Sum_Of_HIST[i] = SUM;
      DSUM += m_DHIST[i];
      m_Sum_Of_DHIST[i] = DSUM;
   }
   // 원본 영상의 평활화
   for(i=0 ; i<m_size ; i++){
      Temp = m_InputImage[i];
      m_Org_Temp[i]=(unsigned char)(m_Sum_Of_HIST[Temp]*HIGH/m_size);
   }

   // 누적 히스토그램에서 최소값과 최대값 지정
   DMIN = m_Sum_Of_DHIST[0];
   DMAX = m_Sum_Of_DHIST[255];

   // 원하는 영상을 평활화
   for(i=0 ; i<256 ; i++){
      m_Sum_Of_ScHIST[i]=(unsigned char)((m_Sum_Of_DHIST[i]
      -DMIN)*HIGH/(DMAX - DMIN));
   }


   // 룩업테이블을 이용한 명세화
   for( ; ; ){
      for(i=m_Sum_Of_ScHIST[bottom] ;
      i <= m_Sum_Of_ScHIST [top] ; i++){
      m_TABLE[i] = top;
   }
   top = bottom;
   bottom = bottom - 1;

   if(bottom < -1)
   break;
   }

   for(i=0 ; i<m_size ; i++){
      DADD = (int)m_Org_Temp[i];
      m_OutputImage[i] = m_TABLE[DADD];
   }

}


void CImageProcessingDoc::OnEmbossing()
{
   int i, j;
// double EmboMask[3][3] = {{-1., 0., 0.}, {0., 0., 0.}, {0., 0., 1.}};
   // 마스크 선택
//double EmboMask[3][3] = {{0., 0., 0.}, {0., 1., 0.}, {0., 0., 0.}};
//double EmboMask[3][3] = {{1., 1., 1.}, {1., -8.,1.}, {1., 1., 1.}};
//double EmboMask[3][3] = {{1.,-2.,3.},{-4,5.,-6.},{7.,-8.,9.}};
//double EmboMask[3][3] = {{1.,1.,1.},{-2.,-2.,-2.},{1.,1.,1.}};
//double EmboMask[3][3] = {{-1.,-1.,-1.},{2.,2.,2.},{-1.,-1.,-1.}};
   double EmboMask[3][3] = {{100.,50.,0.},{-75.,-150.,-75.},{0.,50.,100.}};

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;
   m_OutputImage = new unsigned char [m_Re_size];
   m_tempImage = OnMaskProcess(m_InputImage, EmboMask);
   // OnMaskProcess 함수를 호출하여 회선 처리를 한다.

  /* for(i=0 ; i<m_Re_height ; i++){
      for(j=0 ; j<m_Re_width ; j++){
         if(m_tempImage[i][j] > 255.)
            m_tempImage[i][j] = 255.;
         if(m_tempImage[i][j] < 0.)
            m_tempImage[i][j] = 0.;
      }
   }*/ // 회선 처리 결과가 0~255 사이 값이 되도록 한다.
 m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
   // 정규화 함수를 사용할 때

   // 회선 처리 결과나 정규화 처리 결과는 2차원 배열 값이 되므로
   // 2차원 배열을 1차원 배열로 바꾸어 출력하도록 한다.
   for(i=0 ; i<m_Re_height ; i++){
      for(j=0 ; j<m_Re_width ; j++){
         m_OutputImage[i*m_Re_width + j]
            = (unsigned char)m_tempImage[i][j];
      }
   }
}   


double** CImageProcessingDoc::OnMaskProcess(unsigned char *Target, double Mask[3][3])
{ // 회선 처리가 일어나는 함수
   int i, j, n, m;
   double **tempInputImage, **tempOutputImage, S = 0.0;

   tempInputImage = Image2DMem(m_height + 2, m_width + 2);
   // 입력 값을 위한 메모리 할당
   tempOutputImage = Image2DMem(m_height, m_width);
   // 출력 값을 위한 메모리 할당

   // 1차원 입력 영상의 값을 2차원 배열에 할당한다.
   for(i=0 ; i<m_height ; i++){
      for(j=0 ; j<m_width ; j++){
         tempInputImage[i+1][j+1]
            = (double)Target[i * m_width + j];
      }
   }

   // 회선연산
   for(i=0 ; i<m_height ; i++){
      for(j=0 ; j<m_width ; j++){
         for(n=0 ; n<3 ; n++){
            for(m=0 ; m<3 ; m++){
               S += Mask[n][m] * tempInputImage[i+n][j+m];
            }
         } // 회선 마스크의 크기 만큼 이동하면서 값을 누적
         tempOutputImage[i][j] = S; // 누적된 값을 출력 메모리에 저장
         S = 0.0; // 다음 블록으로 이동하면 누적 값을 초기화
         }
      }
   return tempOutputImage; // 결과 값 반환
}   


double** CImageProcessingDoc::OnScale(double **Target, int height, int width)
{ // 정규화를 위한 함수
   int i, j;
   double min, max;

   min = max = Target[0][0];

   for(i=0 ; i<height ; i++){
      for(j=0 ; j<width ; j++){
         if(Target[i][j] <= min)
            min = Target[i][j];
      }
   }

   for(i=0 ; i<height ; i++){
      for(j=0 ; j<width ; j++){
         if(Target[i][j] >= max)
            max = Target[i][j];
      }
   }

   max = max - min;

   for(i=0 ; i<height ; i++){
      for(j=0 ; j<width ; j++){
         Target[i][j] = (Target[i][j] - min) * (255. / max);
      }
   }

   return Target;
}


double** CImageProcessingDoc::Image2DMem(int height, int width)
{ // 2차원 메모리 할당을 위한 함수
   double** temp;
   int i, j;
   temp = new double *[height];
   for(i=0 ; i<height ; i++){
      temp[i] = new double [width];
   }
   for(i=0 ; i<height ; i++){
      for(j=0 ; j<width ; j++){
         temp[i][j] = 0.0;
      }
   } // 할당된 2차원 메모리를 초기화
   return temp;
}   


void CImageProcessingDoc::OnBlurr()
{
	int i, j;
   double BlurrMask[3][3] = {{1./9., 1./9., 1./9.},
      {1./9., 1./9., 1./9.}, {1./9., 1./9., 1./9.}};

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;

   m_OutputImage = new unsigned char [m_Re_size];

   m_tempImage = OnMaskProcess(m_InputImage, BlurrMask);
   // 블러링 처리
   // m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

   // 정규화
   for(i=0 ; i<m_Re_height ; i++){
      for(j=0 ; j<m_Re_width ; j++){
         if(m_tempImage[i][j] > 255.)
            m_tempImage[i][j] = 255.;
         if(m_tempImage[i][j] < 0.)
            m_tempImage[i][j] = 0.;
      }
   }
   for(i=0 ; i<m_Re_height ; i++){
         for(j=0 ; j<m_Re_width ; j++){
            m_OutputImage[i*m_Re_width + j]
               = (unsigned char)m_tempImage[i][j];
      }
   }
}


void CImageProcessingDoc::OnGaussianFilter()
{
	int i, j;
   double GaussianMask[3][3] = {{1./16., 1./8., 1./16.},
         {1./8., 1./4., 1./8.}, {1./16., 1./8., 1./16.}};

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;

   m_OutputImage = new unsigned char [m_Re_size];

   m_tempImage = OnMaskProcess(m_InputImage, GaussianMask);
   // m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

   for(i=0 ; i<m_Re_height ; i++){
      for(j=0 ; j<m_Re_width ; j++){
         if(m_tempImage[i][j] > 255.)
            m_tempImage[i][j] = 255.;
         if(m_tempImage[i][j] < 0.)
            m_tempImage[i][j] = 0.;
      }
   }

   for(i=0 ; i<m_Re_height ; i++){
      for(j=0 ; j<m_Re_width ; j++){
         m_OutputImage[i*m_Re_width + j]
            = (unsigned char)m_tempImage[i][j];
      }
   }

}


void CImageProcessingDoc::OnSharpening()
{
	int i, j;
   //double SharpeningMask[3][3] = {{-1., -1., -1.},      {-1., 9., -1.}, {-1., -1., -1.}};
   double SharpeningMask[3][3] = {{0., -1., 0.}, {-1., 5.,
      -1.}, {0., -1., 0.}};

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;

   m_OutputImage = new unsigned char [m_Re_size];

   m_tempImage = OnMaskProcess(m_InputImage, SharpeningMask);
   // m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

   for(i=0 ; i<m_Re_height ; i++){
      for(j=0 ; j<m_Re_width ; j++){
         if(m_tempImage[i][j] > 255.)
            m_tempImage[i][j] = 255.;
         if(m_tempImage[i][j] < 0.)
            m_tempImage[i][j] = 0.;
      }
   }

   for(i=0 ; i<m_Re_height ; i++){
      for(j=0 ; j<m_Re_width ; j++){
         m_OutputImage[i*m_Re_width + j]
            = (unsigned char)m_tempImage[i][j];
      }
   }

}


void CImageProcessingDoc::OnHpfSharp()
{
	int i, j;
   double HpfSharpMask[3][3] = {{-1./9., -1./9., -1./9.},{-1./9., 8./9., -1./9.}, {-1./9., -1./9., -1./9.}};

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;

   m_OutputImage = new unsigned char [m_Re_size];

   m_tempImage = OnMaskProcess(m_InputImage, HpfSharpMask);
   //m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

   for(i=0 ; i<m_Re_height ; i++){
      for(j=0 ; j<m_Re_width ; j++){
         if(m_tempImage[i][j] > 255.)
            m_tempImage[i][j] = 255.;
         if(m_tempImage[i][j] < 0.)
            m_tempImage[i][j] = 0.;
      }
   }

   for(i=0 ; i<m_Re_height ; i++){
      for(j=0 ; j<m_Re_width ; j++){
         m_OutputImage[i*m_Re_width + j]
            = (unsigned char)m_tempImage[i][j];
      }
   }

}


void CImageProcessingDoc::OnLpfSharp()
{
	CConstantDlg dlg; // 상수를 입력받으려고 대화상자 선언

   int i, j, alpha;
   double LpfSharpMask[3][3] = {{1./9., 1./9., 1./9.},
      {1./9., 1./9., 1./9.}, {1./9., 1./9., 1./9.}};

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;

   m_OutputImage = new unsigned char [m_Re_size];

   if(dlg.DoModal() == IDOK){
      alpha = (int)dlg.m_Constant;
      // 대화상자를 이용하여 상수를 입력받는다.
   }

   m_tempImage = OnMaskProcess(m_InputImage, LpfSharpMask);

   for(i=0 ; i<m_height ; i++){
      for(j=0 ; j<m_width ; j++){
         m_tempImage[i][j] = (alpha * m_InputImage
            [i*m_width + j]) - (unsigned char) m_tempImage[i][j];
      }
   }
// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

   for(i=0 ; i<m_Re_height ; i++){
      for(j=0 ; j<m_Re_width ; j++){
         if(m_tempImage[i][j] > 255.)
            m_tempImage[i][j] = 255.;
         if(m_tempImage[i][j] < 0.)
            m_tempImage[i][j] = 0.;
      }
   }

   for(i=0 ; i<m_Re_height ; i++){
      for(j=0 ; j<m_Re_width ; j++){
         m_OutputImage[i*m_Re_width + j]
            = (unsigned char)m_tempImage[i][j];
      }
   }
}


void CImageProcessingDoc::OnDiffOperatorHor()
{
	int i, j;
   double DiffHorMask[3][3] 
        = {{0., -1., 0.}, {0., 1., 0.}, {0., 0., 0.}};
   // 수평 필터 선택

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;
   m_OutputImage = new unsigned char [m_Re_size];

   m_tempImage = OnMaskProcess(m_InputImage, DiffHorMask);
   // m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

for(i=0 ; i< m_Re_height ; i++){
      for(j=0 ; j< m_Re_width ; j++){
         if(m_tempImage[i][j] > 255.) 
            m_tempImage[i][j] = 255.;
         if(m_tempImage[i][j] < 0.)
            m_tempImage[i][j] = 0.;
      }
   }

   for(i=0 ; i< m_Re_height ; i++){
      for(j=0 ; j< m_Re_width ; j++){
         m_OutputImage[i* m_Re_width + j] = (unsigned char)m_tempImage[i][j];
      }
   }
}


void CImageProcessingDoc::OnHomogenOperator()
{
	int i, j, n, m;
   double max, **tempOutputImage;

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;
   m_OutputImage = new unsigned char [m_Re_size];

   m_tempImage = Image2DMem(m_height + 2, m_width + 2);
   tempOutputImage = Image2DMem(m_Re_height, m_Re_width);

   for(i=0 ; i<m_height ; i++){
      for(j=0 ; j<m_width ; j++){
         m_tempImage[i+1][j+1] = (double)m_InputImage[i * m_width + j];
      }
   }
for(i=0 ; i<m_height ; i++){
      for(j=0 ; j<m_width ; j++){
         max = 0.0; // 블록이 이동할 때마다 최대값 초기화
         for(n=0 ; n<3 ; n++){
            for(m=0 ; m<3 ; m++){
               if(DoubleABS(m_tempImage[i+1][j+1] -
                  m_tempImage[i+n][j+m]) >= max)
                  // 블록의 가운데 값 - 블록의 주변 픽셀 값의 절대 값
                  // 중에서 최대값을 찾는다.

                     max = DoubleABS(m_tempImage[i+1]
                           [j+1] - m_tempImage[i+n][j+m]);
            }
         }
         tempOutputImage[i][j] = max; // 찾은 최대값을 출력 값으로 지정
      }
   }
   for(i=0 ; i< m_Re_height ; i++){
      for(j=0 ; j< m_Re_width ; j++){
         if(tempOutputImage[i][j] > 255.)
            tempOutputImage[i][j] = 255.;
         if(tempOutputImage[i][j] < 0.)
            tempOutputImage[i][j] = 0.;
      }
   }

   for(i=0 ; i< m_Re_height ; i++){
      for(j=0 ; j< m_Re_width ; j++){
         m_OutputImage[i* m_Re_width + j]
            = (unsigned char)tempOutputImage[i][j];
      }
   }

}


double CImageProcessingDoc::DoubleABS(double X)
{
	// 실수의 절대 값 연산 함수
   if(X >= 0)
      return X;
   else
      return -X;

}


void CImageProcessingDoc::OnMedi()
{
	int i, j, n, m;
	double buf[9] = {0,};
	double temp = 0;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char [m_Re_size];

	// 회선연산
	for(i=0 ; i<m_height ; i++)
	{
		for(j=0 ; j<m_width ; j++)
		{
			for(n=0 ; n<3 ; n++) //9개 화소 추출
			{
				for(m=0 ; m<3 ; m++)
				{
					if (((i+n)*m_Re_width + (j+m))>=m_Re_size)
					{//화소의 범위를 넘어서게 될 경우 처리를 위한 if문 3개
						buf[n*3 + m] = m_InputImage[m_Re_size - 1];
						continue;
					}
					else if ((i+n)>=m_Re_height)
					{
						buf[n*3 + m] = m_InputImage[(m_height-1)*m_Re_width + (j+m)];
						continue;
					}
					else if ((j+m)>=m_Re_width)
					{
						buf[n*3 + m] = m_InputImage[(i+n)*m_Re_width + m_Re_height-1];
						continue;
					}
					buf[n*3 + m] = m_InputImage[(i+n)*m_Re_width + (j+m)];
				}
			}
			for (n = 0; n < 9; n++) //오름차순 정렬
			{
				for (m = 0; m < 8; m++)
				{
					if (buf[m+1] < buf[m])
					{
						temp = buf[m+1];
						buf[m+1] = buf[m];
						buf[m] = temp;
					}
				}
			}
			m_OutputImage[i*m_Re_width + j] = buf[4]; //중간값(메디안값) 대입
			
			if(m_OutputImage[i*m_Re_width + j] > 255.)
				m_OutputImage[i*m_Re_width + j] = 255.;
			if(m_OutputImage[i*m_Re_width + j] < 0)
				m_OutputImage[i*m_Re_width + j] = 0.;
			
			for (n = 0; n < 9; n++)
			{
				buf[n] = 0.0;
			} // 초기화
		}
	}
}


void CImageProcessingDoc::OnNearest()
{
   int i,j;
   int ZoomRate = 2; // 영상 확대 배율
   double **tempArray;
   
   m_Re_height = int(ZoomRate*m_height); // 확대된 영상의 높이
   m_Re_width = int(ZoomRate*m_width); // 확대된 영상의 너비
   m_Re_size = m_Re_height * m_Re_width;

   m_tempImage = Image2DMem(m_height, m_width);
   tempArray = Image2DMem(m_Re_height, m_Re_width);

   m_OutputImage = new unsigned char [m_Re_size];

   for(i=0 ; i<m_height ; i++){
      for(j=0 ; j<m_width ; j++){
         m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
      }
   }

   for(i=0 ; i< m_Re_height ; i++){
      for(j=0 ; j< m_Re_width ; j++){
         tempArray[i][j] = m_tempImage[i/ZoomRate][j/ZoomRate];
         // 이웃한 화소를 이용한 보간
      }
   }

   for(i=0 ; i< m_Re_height ; i++){
      for(j=0 ; j< m_Re_width ; j++){
         m_OutputImage[i* m_Re_width + j] = (unsigned char)tempArray[i][j];
      }
   }
}


void CImageProcessingDoc::OnBilinear()
{
   int i, j, point, i_H, i_W;
   unsigned char newValue;
   double ZoomRate = 2.0, r_H, r_W, s_H, s_W;
   double C1, C2, C3, C4;

   m_Re_height = (int)(m_height * ZoomRate); // 확대된 영상의 높이
   m_Re_width = (int)(m_width * ZoomRate); // 확대된 영상의 너비
   m_Re_size = m_Re_height * m_Re_width;

   m_tempImage = Image2DMem(m_height, m_width);
   m_OutputImage = new unsigned char [m_Re_size];

   for(i=0 ; i<m_height ; i++){
      for(j=0 ; j<m_width ; j++){
         m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
      }
   }
   for(i=0 ; i< m_Re_height ; i++){
      for(j=0 ; j< m_Re_width ; j++){
         r_H = i / ZoomRate;//사상 전의 화소위치. 출력은 정수인데 입력부분은 소수점 부분일수도 있다.
         r_W = j / ZoomRate;

         i_H = (int)floor(r_H); //실수값의 정수값
         i_W = (int)floor(r_W);

         s_H = r_H - i_H; //실수값의 소수점값
         s_W = r_W - i_W;

         if(i_H < 0 || i_H >= (m_height-1) || i_W < 0  
            || i_W >= (m_width-1))
         {
            point = i* m_Re_width + j;
            m_OutputImage[point] = 255;
         }
         
         else // 소수점 값 보간하기
         {
            C1 = (double)m_tempImage[i_H][i_W];
            C2 = (double)m_tempImage[i_H][i_W+1];
            C3 = (double)m_tempImage[i_H+1][i_W+1];
            C4 = (double)m_tempImage[i_H+1][i_W];

            newValue = (unsigned char)(C1*(1-s_H)*(1-s_W)
               +C2*s_W*(1-s_H)+C3*s_W*s_H+C4*(1-s_W)*s_H);
            point = i* m_Re_width+j;
            m_OutputImage[point] = newValue;
         }
      }
   }

}


void CImageProcessingDoc::OnRotate30()
{
   int i, j, point, i_H, i_W;
   unsigned char newValue;
   double ZoomRate = 1.0, r_H, r_W, s_H, s_W;
   double C1, C2, C3, C4;

   m_Re_height = (int)(m_height * ZoomRate); // 확대된 영상의 높이
   m_Re_width = (int)(m_width * ZoomRate); // 확대된 영상의 너비
   m_Re_size = m_Re_height * m_Re_width;

   m_tempImage = Image2DMem(m_height, m_width);
   m_OutputImage = new unsigned char [m_Re_size];

   for(i=0 ; i<m_height ; i++){
      for(j=0 ; j<m_width ; j++){
         m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
      }
   }
   for(i=0 ; i< m_Re_height ; i++){
      for(j=0 ; j< m_Re_width ; j++){

		  r_W = (cos((30.0/180)*3.14)*(j-m_Re_width/2)) + (sin((30.0/180)*3.14)*(i-m_Re_height/2)) + m_Re_width/2;
		  r_H = -(sin((30.0/180)*3.14)*(j-m_Re_width/2))+ (cos((30.0/180)*3.14)*(i-m_Re_height/2)) + m_Re_height/2;

         i_H = (int)floor(r_H);
         i_W = (int)floor(r_W);

         s_H = r_H - i_H;
         s_W = r_W - i_W;

         if(i_H < 0 || i_H >= (m_height-1) || i_W < 0  
            || i_W >= (m_width-1))
         {
            point = i* m_Re_width + j;
            m_OutputImage[point] = 255;
         }
         
         else
         {
            C1 = (double)m_tempImage[i_H][i_W];
            C2 = (double)m_tempImage[i_H][i_W+1];
            C3 = (double)m_tempImage[i_H+1][i_W+1];
            C4 = (double)m_tempImage[i_H+1][i_W];

            newValue = (unsigned char)(C1*(1-s_H)*(1-s_W)
               +C2*s_W*(1-s_H)+C3*s_W*s_H+C4*(1-s_W)*s_H);
            point = i* m_Re_width+j;
            m_OutputImage[point] = newValue;
         }
      }
   }
}


void CImageProcessingDoc::OnCoffeeCup()
{
   int i, j, point, i_H, i_W;
   unsigned char newValue;
   double ZoomRate = 1.0, r_H, r_W, s_H, s_W;
   double C1, C2, C3, C4;
   double d;


   m_Re_height = (int)(m_height * ZoomRate); // 확대된 영상의 높이
   m_Re_width = (int)(m_width * ZoomRate); // 확대된 영상의 너비
   m_Re_size = m_Re_height * m_Re_width;

   m_tempImage = Image2DMem(m_height, m_width);
   m_OutputImage = new unsigned char [m_Re_size];

   for(i=0 ; i<m_height ; i++){
      for(j=0 ; j<m_width ; j++){
         m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
      }
   }
   for(i=0 ; i< m_Re_height ; i++){
      for(j=0 ; j< m_Re_width ; j++){

		  d = sqrt(pow((m_Re_width-1.0)/2.0 - (double)j, 2.0) +pow((m_Re_height-1.0)/2.0 - (double)i, 2.0)); 
		  r_W = (cos(d*3.1415/60)*(j-m_Re_width/2)) + (sin(d*3.1415/60)*(i-m_Re_height/2)) + m_Re_width/2;
		  r_H = -(sin(d*3.1415/60)*(j-m_Re_width/2))+ (cos(d*3.1415/60)*(i-m_Re_height/2)) + m_Re_height/2;

         i_H = (int)floor(r_H);
         i_W = (int)floor(r_W);

         s_H = r_H - i_H;
         s_W = r_W - i_W;

         if(i_H < 0 || i_H >= (m_height-1) || i_W < 0  
            || i_W >= (m_width-1))
         {
            point = i* m_Re_width + j;
            m_OutputImage[point] = 255;
         }
         
         else
         {
            C1 = (double)m_tempImage[i_H][i_W];
            C2 = (double)m_tempImage[i_H][i_W+1];
            C3 = (double)m_tempImage[i_H+1][i_W+1];
            C4 = (double)m_tempImage[i_H+1][i_W];

            newValue = (unsigned char)(C1*(1-s_H)*(1-s_W)
               +C2*s_W*(1-s_H)+C3*s_W*s_H+C4*(1-s_W)*s_H);
            point = i* m_Re_width+j;
            m_OutputImage[point] = newValue;
         }
      }
   }
}


void CImageProcessingDoc::OnTranslation()
{
	   int i,j;
   int h_pos = 30, w_pos = 30;
   double **tempArray;

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;

   m_OutputImage = new unsigned char [m_Re_size];

   m_tempImage = Image2DMem(m_height, m_width);
   tempArray = Image2DMem(m_Re_height, m_Re_width);

   for(i=0 ; i<m_height ; i++)
   {
      for(j=0 ; j<m_width ; j++)
	  {
         m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
      }
   }
   for(i=0 ; i<m_height - h_pos ; i++)
   {
      for(j=0 ; j<m_width - w_pos ; j++)
	  {
         tempArray[i + h_pos][j + w_pos] = m_tempImage[i][j];
         // 입력 영상을 h_pos, w_pos만큼 이동
      }
   }

   for(i=0 ; i< m_Re_height ; i++)
   {
      for(j=0 ; j< m_Re_width ; j++)
	  {
         m_OutputImage[i* m_Re_width + j] = (unsigned char)tempArray[i][j];
      }
   }

   delete [] m_tempImage;
   delete [] tempArray;

}



void CImageProcessingDoc::OnMirrorHor()
{
   int i,j;

   m_Re_height = m_height;
   m_Re_width = m_width;
   m_Re_size = m_Re_height * m_Re_width;

   m_OutputImage = new unsigned char [m_Re_size];

   for(i=0 ; i<m_height ; i++)
   {
      for(j=0 ; j<m_width ; j++)
	  {
         m_OutputImage[i*m_width + m_width - j - 1] = m_InputImage[i*m_width + j];
         // 입력 영상의 배열 값을 출력 영상을 위한 
         // 배열의 수평축 뒷자리부터 저장
      }
   }

}
