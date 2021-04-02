#include "Image.h"

HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO();
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBit = 
		(HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap); //memDC를 통해서 bitmap에 있는 이미지 정보에 접근할 수 있음
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_KIND::EMPTY;



	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}
	this->isTransparent = false;
	this->transColor = false;


	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, bool isTransparent , COLORREF transColor )
{
	HDC hdc = GetDC(g_hWnd);
	
	imageInfo = new IMAGE_INFO();
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit =
		(HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap); //memDC를 통해서 bitmap에 있는 이미지 정보에 접근할 수 있음
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_KIND::FILE;


	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}
	this->isTransparent = isTransparent;
	this->transColor = transColor;

	return S_OK;
}
HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO();
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit =
		(HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap); //memDC를 통해서 bitmap에 있는 이미지 정보에 접근할 수 있음
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_KIND::FILE;

	imageInfo->maxFrameX = maxFrameX;
	imageInfo->maxFrameY = maxFrameY;
	imageInfo->frameWidth = width / maxFrameX;
	imageInfo->frameHeight = height / maxFrameY;
	imageInfo->currFrameX = 0;
	imageInfo->currFrameY = 0;


	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}
	this->isTransparent = isTransparent;
	this->transColor = transColor;

	return S_OK;

}

//winhandle은 hdc가 항상 있는데 원하는곳이 많다 역할이 많다보니까 getdc를 하면 참조할 수있게해준다 그리고 releasedc를하면 참조 카운트가 내려간다
//참조할떄는 메모리가 생성되지않는다 그냥 가져다 쓰는거다 댕꿀 참조 카운트가 올라가지 메모리가 늘어나지않는다
//메인 hdc를 얻어올수있음 hdc를 얻어온다음 releasedc를 한다  
//delete와 release의 차이는? delete는 메모리전체 release는 메모리의 참조해서 사용을 한다,or 안한다는 개념 참조한다 안한다가 핵심
//다시 반환을 해줘야함 release를 안해주면 카운트가 내려가지가 않는다. 참조 카운트가 올라가있으면 다른곳에서 메모리해제가 안된다.
//hdc를 전역변수로 하지않고 필요할때만 참조를 하는게 winapi가 권장하는 방식이다

void Image::Release()
{
	if (imageInfo)
	{
		SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBitmap);
		DeleteDC(imageInfo->hMemDC);

		delete imageInfo;
		imageInfo = nullptr;
	}
}

void Image::Render(HDC hdc, int destX, int destY)
{	//bitmap에 있는 이미지 정보를 다른 비트맵에 복사
	if (isTransparent) //특정색상을 뺴고 복사하는 함수
	{
		//매개변수가 더 많다는 애기는 기능이 더 많다는 소리야~ 좋은거지?
		GdiTransparentBlt(hdc, destX, destY, imageInfo->width, imageInfo->height, imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height, transColor);//transColor는 뺴고싶은 색상
	}
	else {
		BitBlt(
			hdc,				// 복사 목적지 DC
			destX, destY,		// 복사 시작 위치
			imageInfo->width,	// 원본에서 복사될 가로크기
			imageInfo->height,	// 원본에서 복사될 세로크기
			imageInfo->hMemDC,	// 원본 DC
			0, 0,				// 원본에서 복사 시작 위치
			SRCCOPY				// 복사 옵션
		);
	}
}


void Image::Render(HDC hdc, int destX, int destY, int frameIndex)
{
	imageInfo->currFrameX = frameIndex;
	if (isTransparent) //특정색상을 뺴고 복사하는 함수
	{
		GdiTransparentBlt(hdc,								//목적지dc
			destX, destY,									//복사위치
			imageInfo->frameWidth, imageInfo->frameHeight,	//복사크기
			imageInfo->hMemDC,								//원본dc
			imageInfo->frameWidth * imageInfo->currFrameX,  //복사x크기
			imageInfo->frameHeight * imageInfo->currFrameY, //복사 y크기
			imageInfo->frameWidth, imageInfo->frameHeight,  //복사크기
			transColor);									//transColor는 뺴고싶은 색상
	}
	else
	{
		BitBlt(			//이오리 전용이지만 공통으로 만들기
			hdc,
			destX, destY,
			imageInfo->frameWidth, imageInfo->frameHeight,
			imageInfo->hMemDC,
			imageInfo->frameWidth * imageInfo->currFrameX,
			imageInfo->frameHeight * imageInfo->currFrameY,
			SRCCOPY
		);
	}
}

void Image::Render(HDC hdc, int X, int Y, int frameIndex, int width)
{
	if (isTransparent) //특정색상을 뺴고 복사하는 함수
	{
		//매개변수가 더 많다는 애기는 기능이 더 많다는 소리야~ 좋은거지?
		GdiTransparentBlt(hdc, X,Y, imageInfo->width, imageInfo->height, imageInfo->hMemDC, 0,0, imageInfo->width, imageInfo->height,transColor);//transColor는 뺴고싶은 색상
	}
	else
	{
		BitBlt(			//오공 전용
			hdc,
			X, Y,
			(imageInfo->width / 20),
			imageInfo->height - 20,
			imageInfo->hMemDC,
			(imageInfo->width / 20) * (frameIndex), 0,
			SRCCOPY
		);
	}
}
