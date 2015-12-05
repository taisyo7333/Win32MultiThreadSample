#include<Windows.h>
#include<string>

class ThreadActor;

struct THREAD_LOCAL_PARAM
{
	//
	ThreadActor* pActor;
	//
	HANDLE hOpen;
	//
	HANDLE hClose;
};


class ThreadActor
{
public:
	ThreadActor();
	virtual ~ThreadActor();

	// スレッド開始
	BOOL Start();
	// スレッド終了
	void Stop();

	// 外部ＡＰＩ
	void Print(const std::wstring&);

private:
	BOOL bInit;
	// スレッドＩＤ
	DWORD dwThreadId;
	// スレッドハンドル
	HANDLE hThread;
	// スレッドＯＰＥＮイベント同期用ハンドル
	HANDLE hOpen;
	// スレッドＣＬＯＳＥイベント同期用ハンドル
	HANDLE hClose;
	// スレッドへ渡すパラメータ
	THREAD_LOCAL_PARAM param;
};
