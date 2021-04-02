#pragma once
#include "config.h"


class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,			// ������Ʈ ��ü�� ���� ��ų �̹���
		FILE,				// �ܺο��� �ε��� �̹���
		EMPTY,				// ��ü ���� �̹���
		END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;			// ���ҽ��� ������ ID
		HDC hMemDC;				// �׸��⸦ �ְ��ϴ� �ڵ�
		HBITMAP hBitmap;		// �̹��� ����
		HBITMAP hOldBit;		// ���� �̹��� ����
		int width;				// �̹��� ���� ũ��
		int height;				// �̹��� ���� ũ��
		BYTE loadType;			// �ε� Ÿ��

		//�ִϸ��̼� ����(�����ӵ�����)
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		int currFrameX;
		int currFrameY;

		tagImageInfo()		//������
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
	IMAGE_INFO* imageInfo;			//�̹��� ���� ����ü ������
	//LPIMAGE_INFO* tagImageInfo;

	bool isTransparent;				//Ʈ���� ��Ʈ�� �����̶� ������? ����ó���� �Ұ��� ���Ұ����ϴ� �����̰� �׸���
	COLORREF transColor;			//�̷����� 2���� �߰������� �׸��� �� ���� ������ �ҋ� �ܺο��� �޾ƿ���

public:
	// �� ��Ʈ�� �̹����� ����� �Լ�
	HRESULT Init(int width, int height);

	// ���Ϸκ��� �̹����� �ε��ϴ� �Լ�
	HRESULT Init(const char* fileName, int width, int height, bool isTransparent = false, COLORREF transColor= false);	//�Ű����� �ʱ�ȭ�����ֱ�

	HRESULT Init(const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY,								//�߰����� ������ �־�����
		bool isTransparent = false, COLORREF transColor = false);	

	// ȭ�鿡 ���
	void Render(HDC hdc, int destX= 0, int destY = 0);		//���� �־��༭ �ʱⰪ ������ ��
	void Render(HDC hdc, int destX, int destY, int frameIndex);
	void Render(HDC hdc, int destX, int destY, int frameIndex,int width);

	//void Render(HDC hdc, int x, int y, int width);		//���� �־��༭ �ʱⰪ ������ ��

	void Release();

	//get, set
	HDC GetMemDC() 
	{ if (this->imageInfo) 
		return this->imageInfo->hMemDC; 
	return NULL; }

};

