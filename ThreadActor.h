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

	// �X���b�h�J�n
	BOOL Start();
	// �X���b�h�I��
	void Stop();

	// �O���`�o�h
	void Print(const std::wstring&);

private:
	BOOL bInit;
	// �X���b�h�h�c
	DWORD dwThreadId;
	// �X���b�h�n���h��
	HANDLE hThread;
	// �X���b�h�n�o�d�m�C�x���g�����p�n���h��
	HANDLE hOpen;
	// �X���b�h�b�k�n�r�d�C�x���g�����p�n���h��
	HANDLE hClose;
	// �X���b�h�֓n���p�����[�^
	THREAD_LOCAL_PARAM param;
};
