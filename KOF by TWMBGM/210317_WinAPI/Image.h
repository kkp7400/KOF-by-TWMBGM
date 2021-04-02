#pragma once
#include "config.h"


class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,			// 프로젝트 자체에 포함 시킬 이미지
		FILE,				// 외부에서 로드할 이미지
		EMPTY,				// 자체 생산 이미지
		END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;			// 리소스의 고유한 ID
		HDC hMemDC;				// 그리기를 주관하는 핸들
		HBITMAP hBitmap;		// 이미지 정보
		HBITMAP hOldBit;		// 기존 이미지 정보
		int width;				// 이미지 가로 크기
		int height;				// 이미지 세로 크기
		BYTE loadType;			// 로드 타입

		//애니메이션 관련(프레임데이터)
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		int currFrameX;
		int currFrameY;

		tagImageInfo()		//생성자
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_KIND::EMPTY;

			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			currFrameX = 0;
			currFrameY = 0;
		}

	}	IMAGE_INFO, * LPIMAGE_INFO;

private:
	IMAGE_INFO* imageInfo;			//이미지 정보 구조체 포인터
	//LPIMAGE_INFO* tagImageInfo;

	bool isTransparent;				//트랜스 페어런트는 투명이란 뜻이지? 투명처리를 할건지 안할건지하는 내용이고 그리고
	COLORREF transColor;			//이런변수 2개를 추가해주자 그리고 저 값을 인잇을 할떄 외부에서 받아오자

public:
	// 빈 비트맵 이미지를 만드는 함수
	HRESULT Init(int width, int height);

	// 파일로부터 이미지를 로드하는 함수
	HRESULT Init(const char* fileName, int width, int height, bool isTransparent = false, COLORREF transColor= false);	//매개변수 초기화시켜주기

	HRESULT Init(const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY,								//추가적인 데이터 넣어주자
		bool isTransparent = false, COLORREF transColor = false);	

	// 화면에 출력
	void Render(HDC hdc, int destX= 0, int destY = 0);		//수를 넣어줘서 초기값 세팅이 됨
	void Render(HDC hdc, int destX, int destY, int frameIndex);
	void Render(HDC hdc, int destX, int destY, int frameIndex,int width);

	//void Render(HDC hdc, int x, int y, int width);		//수를 넣어줘서 초기값 세팅이 됨

	void Release();

	//get, set
	HDC GetMemDC() 
	{ if (this->imageInfo) 
		return this->imageInfo->hMemDC; 
	return NULL; }

};

