
// WinColorDoc.cpp : CWinColorDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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


// CWinColorDoc ����/�Ҹ�

CWinColorDoc::CWinColorDoc()
	: height(0)
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
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

	// BITMAP Filer Header�Ķ��Ÿ�� ���� 
	dibHf.bfType = 0x4d42;  // 'BM'
	dibHf.bfSize = dwBitsSize+sizeof(BITMAPFILEHEADER); // ��ü���� ũ�� 
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
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CWinColorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void CWinColorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CWinColorDoc ����

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


// CWinColorDoc ����


BOOL CWinColorDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	CFile hFile;

	hFile.Open(lpszPathName,CFile::modeRead | CFile::typeBinary);
	hFile.Read(&dibHf,sizeof(BITMAPFILEHEADER)); // ���� ��带 ����

	//�� ������ BMP�������� �˻�. 0x4d42==��BM��

	if(dibHf.bfType!=0x4D42) 
	{ 
		return FALSE; 
	}

	hFile.Read(&dibHi,sizeof(BITMAPINFOHEADER)); //������������Header�����д´�.

	if(dibHi.biBitCount!=8 && dibHi.biBitCount!=24)
	{ 
		return FALSE;
	}

	if(dibHi.biBitCount==8) 
		hFile.Read(palRGB,sizeof(RGBQUAD)*256);

	// �޸� �Ҵ�
	int ImgSize;

	if(dibHi.biBitCount==8) // ��鿵��
		ImgSize = hFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER) - 256*sizeof(RGBQUAD);
	else if(dibHi.biBitCount==24) //�÷�����
		ImgSize = hFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER);

	m_InImg = new unsigned char [ImgSize]; // �������� ���� ����
	m_OutImg = new unsigned char [ImgSize]; // ó��������� ���� ����

	hFile.Read(m_InImg, ImgSize); // �������� �Է�
	hFile.Close();
	height = dibHi.biHeight; width = dibHi.biWidth;

	if(dibHi.biBitCount==24) 
		return TRUE;

	// �������� ����(��鿵���� ���)
	int i, j, index;
	int rwsize = WIDTHBYTES(dibHi.biBitCount*width);

	for(i=0; i<height; i++)
	{
		index = i*rwsize;

		for(j=0; j<width; j++) // r, g, b���̸�ΰ���b��������������
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
	// Ŭ�����忡 �����ϱ� ���� ������ ���̸� ����
	int rwsize = WIDTHBYTES(biBitCount*width);
	DWORD dwBitsSize = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256+rwsize*height*sizeof(char);
		
	// �޸� �Ҵ�(������常 ���ܽ�Ų ����)
	HGLOBAL m_hImage = (HGLOBAL)::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, dwBitsSize);
	LPSTR pDIB = (LPSTR) ::GlobalLock((HGLOBAL)m_hImage);

	// ����Ÿ���� 
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

	// Ŭ������ ���� 
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

	// convolution MASK�� ���� 
	int i, j, k, l, index1, index2, index3, winsize=3;
	float *Mask =new float [winsize*winsize];
	for(i=0; i<winsize*winsize; i++) Mask[i]=0.0f;
	Mask[0]=-1.0f; Mask[8]=1.0f;

	//
	int n=(winsize-1)>>1;	// winsize ������ offsetũ�⸦ ��� 

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
	// ��� �޸� �ʱ�ȭ 
	memset(OutImg,0,height*width*sizeof(char));

	// winsize ������ offsetũ�⸦ ��� 
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

	// convolution MASK�� ���� 
	int i, j, index1, index2, winsize=3;
	float *Mask =new float [winsize*winsize];
	for(i=0; i<winsize*winsize; i++) Mask[i]=0.0f;
	Mask[1]=Mask[3]=Mask[5]=Mask[7]=-1.0f; Mask[4]=5.0f;

	// HSI������ ���� �޸� ����
	short *H =new short [height*width];
	unsigned char *S =new unsigned char [height*width];
	unsigned char *IV =new unsigned char [height*width];

	float hue, satu, intens, r, g, b, rr,gg,bb;
	CColorConv pColorConv;

	// RGB --> HSI���� ��ȯ 
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

	// ��� ���� ���� sharpening�� ������ 
	unsigned char *IVO=new unsigned char [height*width];
	m_ImgConvolution(IV, IVO, height, width, Mask, 3);

	// HSI --> RGB���� ��ȯ 	
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