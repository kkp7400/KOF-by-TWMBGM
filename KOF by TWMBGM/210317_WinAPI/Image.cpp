#include "Image.h"

HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO();
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBit = 
		(HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap); //memDC�� ���ؼ� bitmap�� �ִ� �̹��� ������ ������ �� ����
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
		(HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap); //memDC�� ���ؼ� bitmap�� �ִ� �̹��� ������ ������ �� ����
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
		(HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap); //memDC�� ���ؼ� bitmap�� �ִ� �̹��� ������ ������ �� ����
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

//winhandle�� hdc�� �׻� �ִµ� ���ϴ°��� ���� ������ ���ٺ��ϱ� getdc�� �ϸ� ������ ���ְ����ش� �׸��� releasedc���ϸ� ���� ī��Ʈ�� ��������
//�����ҋ��� �޸𸮰� ���������ʴ´� �׳� ������ ���°Ŵ� ��� ���� ī��Ʈ�� �ö��� �޸𸮰� �þ���ʴ´�
//���� hdc�� ���ü����� hdc�� ���´��� releasedc�� �Ѵ�  
//delete�� release�� ���̴�? delete�� �޸���ü release�� �޸��� �����ؼ� ����� �Ѵ�,or ���Ѵٴ� ���� �����Ѵ� ���Ѵٰ� �ٽ�
//�ٽ� ��ȯ�� ������� release�� �����ָ� ī��Ʈ�� ���������� �ʴ´�. ���� ī��Ʈ�� �ö������� �ٸ������� �޸������� �ȵȴ�.
//hdc�� ���������� �����ʰ� �ʿ��Ҷ��� ������ �ϴ°� winapi�� �����ϴ� ����̴�

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
{	//bitmap�� �ִ� �̹��� ������ �ٸ� ��Ʈ�ʿ� ����
	if (isTransparent) //Ư�������� ���� �����ϴ� �Լ�
	{
		//�Ű������� �� ���ٴ� �ֱ�� ����� �� ���ٴ� �Ҹ���~ ��������?
		GdiTransparentBlt(hdc, destX, destY, imageInfo->width, imageInfo->height, imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height, transColor);//transColor�� ������� ����
	}
	else {
		BitBlt(
			hdc,				// ���� ������ DC
			destX, destY,		// ���� ���� ��ġ
			imageInfo->width,	// �������� ����� ����ũ��
			imageInfo->height,	// �������� ����� ����ũ��
			imageInfo->hMemDC,	// ���� DC
			0, 0,				// �������� ���� ���� ��ġ
			SRCCOPY				// ���� �ɼ�
		);
	}
}


void Image::Render(HDC hdc, int destX, int destY, int frameIndex)
{
	imageInfo->currFrameX = frameIndex;
	if (isTransparent) //Ư�������� ���� �����ϴ� �Լ�
	{
		GdiTransparentBlt(hdc,								//������dc
			destX, destY,									//������ġ
			imageInfo->frameWidth, imageInfo->frameHeight,	//����ũ��
			imageInfo->hMemDC,								//����dc
			imageInfo->frameWidth * imageInfo->currFrameX,  //����xũ��
			imageInfo->frameHeight * imageInfo->currFrameY, //���� yũ��
			imageInfo->frameWidth, imageInfo->frameHeight,  //����ũ��
			transColor);									//transColor�� ������� ����
	}
	else
	{
		BitBlt(			//�̿��� ���������� �������� �����
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
	if (isTransparent) //Ư�������� ���� �����ϴ� �Լ�
	{
		//�Ű������� �� ���ٴ� �ֱ�� ����� �� ���ٴ� �Ҹ���~ ��������?
		GdiTransparentBlt(hdc, X,Y, imageInfo->width, imageInfo->height, imageInfo->hMemDC, 0,0, imageInfo->width, imageInfo->height,transColor);//transColor�� ������� ����
	}
	else
	{
		BitBlt(			//���� ����
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
