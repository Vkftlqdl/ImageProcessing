
// WinColorDoc.cpp : CWinColorDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "WinColor.h"
#endif

#include "WinColorDoc.h"
#include "ColorConv.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWinColorDoc

IMPLEMENT_DYNCREATE(CWinColorDoc, CDocument)

BEGIN_MESSAGE_MAP(CWinColorDoc, CDocument)
END_MESSAGE_MAP()


// CWinColorDoc 생성/소멸

CWinColorDoc::CWinColorDoc()
	: height(0)
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	m_InImg = NULL;
	m_OutImg = NULL;
	for(int i=0; i<256; i++) 
	{
		palRGB[i].rgbBlue= palRGB[i].rgbGreen= palRGB[i].rgbRed= i;
		palRGB[i].rgbReserved = 0;
	}
}

CWinColorDoc::~CWinColorDoc()
{
	if(m_InImg) delete []m_InImg;
	if(m_OutImg) delete []m_OutImg;
}

BOOL CWinColorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;


	::OpenClipboard(NULL);
	if(!IsClipboardFormatAvailable(CF_DIB)) return FALSE;
	HGLOBAL m_hImage = ::GetClipboardData(CF_DIB);
	::CloseClipboard();

	LPSTR pDIB = (LPSTR) ::GlobalLock((HGLOBAL)m_hImage);

	memcpy(&dibHi,pDIB,sizeof(BITMAPINFOHEADER));
	height = dibHi.biHeight; width = dibHi.biWidth;
	int rwsize = WIDTHBYTES(dibHi.biBitCount*width);
	DWORD dwBitsSize = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256+rwsize*height*sizeof(char); //
	m_InImg = new unsigned char [dibHi.biSizeImage];
	m_OutImg = new unsigned char [dibHi.biSizeImage];

	if(dibHi.biBitCount==8) 
	{
		memcpy(palRGB,pDIB+sizeof(BITMAPINFOHEADER),sizeof(RGBQUAD)*256);
		memcpy(m_InImg,pDIB+dwBitsSize-dibHi.biSizeImage,dibHi.biSizeImage);
	}
	else memcpy(m_InImg,pDIB+sizeof(BITMAPINFOHEADER),dibHi.biSizeImage); 

	// BITMAP Filer Header파라메타의 설정 
	dibHf.bfType = 0x4d42;  // 'BM'
	dibHf.bfSize = dwBitsSize+sizeof(BITMAPFILEHEADER); // 전체파일 크기 
	if(dibHi.biBitCount==24) dibHf.bfSize -= sizeof(RGBQUAD)*256; // no pallette 
	dibHf.bfOffBits = dibHf.bfSize - rwsize*height*sizeof(char); 
	dibHf.bfReserved1 = dibHf.bfReserved2 = 0;

	return TRUE;
}




// CWinColorDoc serialization

void CWinColorDoc::Serialize(CArchive& ar)
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
void CWinColorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CWinColorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CWinColorDoc::SetSearchContent(const CString& value)
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

// CWinColorDoc 진단

#ifdef _DEBUG
void CWinColorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWinColorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CWinColorDoc 명령


BOOL CWinColorDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	CFile hFile;

	hFile.Open(lpszPathName,CFile::modeRead | CFile::typeBinary);
	hFile.Read(&dibHf,sizeof(BITMAPFILEHEADER)); // 파일 헤드를 읽음

	//이 파일이 BMP파일인지 검사. 0x4d42==“BM”

	if(dibHf.bfType!=0x4D42) 
	{ 
		return FALSE; 
	}

	hFile.Read(&dibHi,sizeof(BITMAPINFOHEADER)); //”영상정보의Header”를읽는다.

	if(dibHi.biBitCount!=8 && dibHi.biBitCount!=24)
	{ 
		return FALSE;
	}

	if(dibHi.biBitCount==8) 
		hFile.Read(palRGB,sizeof(RGBQUAD)*256);

	// 메모리 할당
	int ImgSize;

	if(dibHi.biBitCount==8) // 흑백영상
		ImgSize = hFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER) - 256*sizeof(RGBQUAD);
	else if(dibHi.biBitCount==24) //컬러영상
		ImgSize = hFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER);

	m_InImg = new unsigned char [ImgSize]; // 원본영상 저장 버퍼
	m_OutImg = new unsigned char [ImgSize]; // 처리결과영상 저장 버퍼

	hFile.Read(m_InImg, ImgSize); // 영상데이터 입력
	hFile.Close();
	height = dibHi.biHeight; width = dibHi.biWidth;

	if(dibHi.biBitCount==24) 
		return TRUE;

	// 영상데이터 대입(흑백영상의 경우)
	int i, j, index;
	int rwsize = WIDTHBYTES(dibHi.biBitCount*width);

	for(i=0; i<height; i++)
	{
		index = i*rwsize;

		for(j=0; j<width; j++) // r, g, b값이모두같고b값을대입해줬음
			m_InImg[index+j] = (unsigned char)palRGB[(int)m_InImg[index+j]].rgbBlue;
	}

	return TRUE;
}


BOOL CWinColorDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	CFile hFile;
	
	if(!hFile.Open(lpszPathName,CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
		return FALSE;
	
	hFile.Write(&dibHf,sizeof(BITMAPFILEHEADER));
	hFile.Write(&dibHi,sizeof(BITMAPINFOHEADER));

	if(dibHi.biBitCount==8) 
		hFile.Write(palRGB, sizeof(RGBQUAD)*256);
	
	hFile.Write(m_InImg,dibHi.biSizeImage);
	hFile.Close();
	
	return CDocument::OnSaveDocument(lpszPathName);
}


void CWinColorDoc::CopyClipboard(unsigned char* m_CpyImg, int height, int width, int biBitCount)
{
	// 클립보드에 복사하기 위한 파일의 길이를 구함
	int rwsize = WIDTHBYTES(biBitCount*width);
	DWORD dwBitsSize = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256+rwsize*height*sizeof(char);
		
	// 메모리 할당(파일헤드만 제외시킨 길이)
	HGLOBAL m_hImage = (HGLOBAL)::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, dwBitsSize);
	LPSTR pDIB = (LPSTR) ::GlobalLock((HGLOBAL)m_hImage);

	// 데이타복사 
	BITMAPINFOHEADER dibCpyHi;
	memcpy(&dibCpyHi,&dibHi,sizeof(BITMAPINFOHEADER));
	dibCpyHi.biBitCount = biBitCount;
	dibCpyHi.biHeight = height;
	dibCpyHi.biWidth = width;
	dibCpyHi.biSizeImage = height*rwsize;
	if(biBitCount==8) dibCpyHi.biClrUsed = dibCpyHi.biClrImportant = 256;

	memcpy(pDIB,&dibCpyHi,sizeof(BITMAPINFOHEADER));
	if(biBitCount==8) 
	{
		memcpy(pDIB+sizeof(BITMAPINFOHEADER),palRGB,sizeof(RGBQUAD)*256);
		memcpy(pDIB+dwBitsSize-dibCpyHi.biSizeImage,m_CpyImg,dibCpyHi.biSizeImage);
	}
	else memcpy(pDIB+sizeof(BITMAPINFOHEADER),m_CpyImg,dibCpyHi.biSizeImage);

	// 클립보드 복사 
	::OpenClipboard(NULL);
	::SetClipboardData(CF_DIB, m_hImage);
	::CloseClipboard();

	::GlobalUnlock((HGLOBAL)m_hImage);
	GlobalFree(m_hImage);

}


void CWinColorDoc::m_RGB2HSI(unsigned char* InImg, unsigned char* OutImg, int height, int width)
{
	int rwsize = WIDTHBYTES(24*width);

	int i,j,index, ih;
	float r, g, b, h, s, iv;
	CColorConv pColorConv;
	for(i=0; i<height; i++)
	{
		index = (height-i-1)*rwsize;
		for(j=0; j<width; j++)
		{
			r = (float)InImg[index+3*j+2]/255.0f;
			g = (float)InImg[index+3*j+1]/255.0f;
			b = (float)InImg[index+3*j  ]/255.0f;

			pColorConv.RGB_To_HSI(r,g,b,&h,&s,&iv);
			ih = (int)(h*255.0/360.0);
			OutImg[index+3*j  ] = (unsigned char)ih;
			OutImg[index+3*j+1] = (unsigned char)(s*255.0);
			OutImg[index+3*j+2] = (unsigned char)(iv*255.0);
		}
	}

}


void CWinColorDoc::m_RGB2Gray(unsigned char* OutImg, unsigned char* InImg, int height, int width)
{
	int rwsize = WIDTHBYTES(24*width);

	int i,j,index;
	float r, g, b, gray;
	CColorConv pColorConv;
	for(i=0; i<height; i++)
	{
		index = (height-i-1)*rwsize;
		for(j=0; j<width; j++)
		{
			r = (float)InImg[index+3*j+2]/255.0f;
			g = (float)InImg[index+3*j+1]/255.0f;
			b = (float)InImg[index+3*j  ]/255.0f;

			pColorConv.RGB_To_Gray(r,g,b,&gray);
			OutImg[index+3*j  ] = (unsigned char)(gray*255.0);
			OutImg[index+3*j+1] = (unsigned char)(gray*255.0);
			OutImg[index+3*j+2] = (unsigned char)(gray*255.0);
		}
	}

}

#define CLIP(val, low, high) {if(val<low) val=low; if(val>high)val=high;}
void CWinColorDoc::m_ColorEmbossing(unsigned char* InImg, unsigned char* OutImg, int height, int width)
{
	int rwsize = WIDTHBYTES(24*width);

	// convolution MASK의 정의 
	int i, j, k, l, index1, index2, index3, winsize=3;
	float *Mask =new float [winsize*winsize];
	for(i=0; i<winsize*winsize; i++) Mask[i]=0.0f;
	Mask[0]=-1.0f; Mask[8]=1.0f;

	//
	int n=(winsize-1)>>1;	// winsize 절반의 offset크기를 계산 

	for(i=n; i<height-n; i++)
	{
		index1 =i*rwsize;
		for(j=n; j<width-n; j++)
		{
			float sum1=0.0f;
			float sum2=0.0f;
			float sum3=0.0f;

			for(k=-n; k<=n; k++)
			{
				index2 = (i+k)*rwsize;
				index3 = (k+n)*winsize;
				for(l=-n; l<=n; l++)
				{
					sum1 +=InImg[index2+3*(j+l)  ]*Mask[index3+l+n];
					sum2 +=InImg[index2+3*(j+l)+1]*Mask[index3+l+n];
					sum3 +=InImg[index2+3*(j+l)+2]*Mask[index3+l+n];
				}
			}
			sum1 += 128; sum2 += 128; sum3 += 128;
			CLIP(sum1,0,255); CLIP(sum2,0,255); CLIP(sum3,0,255);

			OutImg[index1+3*j  ] = (unsigned char)sum1;
			OutImg[index1+3*j+1] = (unsigned char)sum2;
			OutImg[index1+3*j+2] = (unsigned char)sum3;
		}
	}
	delete []Mask;
}


void CWinColorDoc::m_ImgConvolution(unsigned char* InImg, unsigned char* OutImg, int height, int width, float* Mask, int winsize)
{
	// 출력 메모리 초기화 
	memset(OutImg,0,height*width*sizeof(char));

	// winsize 절반의 offset크기를 계산 
	int n=(winsize-1)>>1;	

	int i, j, k, l, index1, index2, index3;
	float sum;
	for(i=n; i<height-n; i++)
	{
		index1 = i*width;
		for(j=n; j<width-n; j++)
		{
			sum=0.0f;

			for(k=-n; k<=n; k++)
			{
				index2 = (i+k)*width;
				index3 = (k+n)*winsize;
				for(l=-n; l<=n; l++) sum +=InImg[index2+(j+l)]*Mask[index3+l+n];
			}
			CLIP(sum,0,255);
			OutImg[index1+j] =(unsigned char)sum;
		}
	}
}


void CWinColorDoc::m_RGBSharpening(unsigned char* InImg, unsigned char* OutImg, int height, int width)
{
	int rwsize = WIDTHBYTES(24*width);

	// convolution MASK의 정의 
	int i, j, index1, index2, winsize=3;
	float *Mask =new float [winsize*winsize];
	for(i=0; i<winsize*winsize; i++) Mask[i]=0.0f;
	Mask[1]=Mask[3]=Mask[5]=Mask[7]=-1.0f; Mask[4]=5.0f;

	// HSI영상을 위한 메모리 정의
	short *H =new short [height*width];
	unsigned char *S =new unsigned char [height*width];
	unsigned char *IV =new unsigned char [height*width];

	float hue, satu, intens, r, g, b, rr,gg,bb;
	CColorConv pColorConv;

	// RGB --> HSI로의 변환 
	for(i=0; i<height; i++)
	{
		index1 = (height-i-1)*rwsize;
		index2 = (height-i-1)*width;
		for(j=0; j<width; j++)
		{
			r = (float)InImg[index1+3*j+2]/255.0f;
			g = (float)InImg[index1+3*j+1]/255.0f;
			b = (float)InImg[index1+3*j  ]/255.0f;

			pColorConv.RGB_To_HSI(r,g,b,&hue,&satu,&intens);

			H [index2+j] =(short)(hue);
			S [index2+j] =(unsigned char)(satu*255.0);
			IV[index2+j] =(unsigned char)(intens*255.0);
		}
	}

	// 밝기 영상에 대해 sharpening을 수행함 
	unsigned char *IVO=new unsigned char [height*width];
	m_ImgConvolution(IV, IVO, height, width, Mask, 3);

	// HSI --> RGB로의 변환 	
	for(i=0; i<height; i++)
	{
		index1 = (height-i-1)*rwsize;
		index2 = (height-i-1)*width;
		for(j=0; j<width; j++)
		{
			hue=(float)H[index2+j];
			satu=(float)S[index2+j]/255.0f;
			intens=(float)IVO[index2+j]/255.0f;

			pColorConv.HSI_To_RGB(hue,satu,intens,&r,&g,&b);
			rr = r*255.0f; gg = g*255.0f; bb = b*255.0f;
			CLIP(rr,0,255); CLIP(gg,0,255); CLIP(bb,0,255); 

			OutImg[index1+3*j  ] = (unsigned char)bb;
			OutImg[index1+3*j+1] = (unsigned char)gg;
			OutImg[index1+3*j+2] = (unsigned char)rr;
		}
	}
	delete []IVO; 
	delete []H; delete []S; delete []IV; delete []Mask;

}
