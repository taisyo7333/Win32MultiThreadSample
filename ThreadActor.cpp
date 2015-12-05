#include"ThreadActor.h"
#include<Windows.h>
#include<iostream>
#include<string>
#include<memory>

#define WM_APP_PRINT   ( WM_APP + 0x01 )

static void ThreadMsgProc(MSG& msg);
DWORD WINAPI ThreadProc(LPVOID lpParameter);


// ThreadMain
// https://msdn.microsoft.com/ja-jp/library/cc429382.aspx
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	THREAD_LOCAL_PARAM* pParam = (THREAD_LOCAL_PARAM*)lpParameter;


	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));

	// Windows message Queue を生成
	::PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE);

	// Notify スレッド開始
	::SetEvent(pParam->hOpen);

	// WM_QUITが来るまで
	LONG result = 0;
	while (result = ::GetMessage(&msg, nullptr, 0, 0) != 0)
	{
		// Error occurs
		if (result == -1)
			break;
		// Message procedure
		ThreadMsgProc(msg);

	}

	// Notify スレッド終了
	::SetEvent(pParam->hClose);
	return 0;
}
static void ThreadMsgProc(MSG& msg)
{
	switch (msg.message)
	{
	case WM_APP_PRINT:
	{
		std::unique_ptr<std::wstring> text((std::wstring*)msg.wParam);

		std::wcout << *text << std::endl;
	}
	break;
	}
}


ThreadActor::ThreadActor()
	: bInit(FALSE)
	, dwThreadId(0)
	, hThread(nullptr)
	, hOpen(nullptr)
	, hClose(nullptr)
{
	::ZeroMemory(&param, sizeof(THREAD_LOCAL_PARAM));
}
ThreadActor::~ThreadActor()
{
	Stop();
}

BOOL ThreadActor::Start()
{
	// Balking
	if (bInit)
		return TRUE;
	std::wstring nameOpen(L"ENVENT_THREAD_OPEN");
	std::wstring nameClose(L"ENVENT_THREAD_CLOSE");
	hOpen = ::CreateEvent(nullptr, TRUE, FALSE, nameOpen.c_str());
	hClose = ::CreateEvent(nullptr, TRUE, FALSE, nameClose.c_str());

	// スレッドへ渡すパラメータ設定
	param.pActor = this;
	param.hOpen = hOpen;
	param.hClose = hClose;

	hThread = ::CreateThread(nullptr, 0, ThreadProc, &param, 0, &dwThreadId);
	if (hThread == NULL)
		return FALSE;

	// スレッド開始待ち
	::WaitForSingleObject(hOpen, INFINITE);

	bInit = TRUE;

	return TRUE;

}
void ThreadActor::Stop()
{
	// Balking
	if (!bInit)
		return;

	::PostThreadMessage(dwThreadId, WM_QUIT, (WPARAM)0, (LPARAM)0);

	// スレッド終了待ち
	::WaitForSingleObject(hClose, INFINITE);

	::CloseHandle(hOpen);
	::CloseHandle(hClose);

	bInit = FALSE;

}
void ThreadActor::Print(const std::wstring& text)
{
	::PostThreadMessage(dwThreadId, WM_APP_PRINT, (WPARAM)(new std::wstring(text)), (LPARAM)0);
}
