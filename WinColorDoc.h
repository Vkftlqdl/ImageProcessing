
// WinColorDoc.h : CWinColorDoc Ŭ������ �������̽�
//


#pragma once

#define WIDTHBYTES(bits) (((bits)+31)/32*4) //4����Ʈ ����� ��ȯ



class CWinColorDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CWinColorDoc();
	DECLARE_DYNCREATE(CWinColorDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CWinColorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	int height;
	int width;
	unsigned char *m_OutImg;
	unsigned char *m_InImg;
	RGBQUAD palRGB[256];
	BITMAPINFOHEADER dibHi;
	BITMAPFILEHEADER dibHf;
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	void CopyClipboard(unsigned char* m_CpyImg, int height, int width, int biBitCount);
	void m_RGB2HSI(unsigned char* InImg, unsigned char* OutImg, int height, int width);
	void m_RGB2Gray(unsigned char* OutImg, unsigned char* InImg, int height, int width);
	void m_ColorEmbossing(unsigned char* InImg, unsigned char* OutImg, int height, int width);
	void m_ImgConvolution(unsigned char* InImg, unsigned char* OutImg, int height, int width, float* Mask, int winsize);
	void m_RGBSharpening(unsigned char* InImg, unsigned char* OutImg, int height, int width);
};