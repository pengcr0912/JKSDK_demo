
// JASDK_demo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CJASDK_demoApp:
// �йش����ʵ�֣������ JASDK_demo.cpp
//

class CJASDK_demoApp : public CWinApp
{
public:
	CJASDK_demoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CJASDK_demoApp theApp;