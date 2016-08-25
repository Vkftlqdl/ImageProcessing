
// WinColorDoc.h : CWinColorDoc 클래스의 인터페이스
//


#pragma once

#define WIDTHBYTES(bits) (((bits)+31)/32*4) //4바이트 배수로 변환



class CWinColorDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CWinColorDoc();
	DECLARE_DYNCREATE(CWinColorDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CWinColorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
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