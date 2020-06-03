#include "lab3.h"
#include <windows.h>
#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h> // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

//
// lab3 code should be located here!
//
// using namespace std;
#define THREADCOUNT 10

HANDLE hMutex;
HANDLE hThreads[THREADCOUNT];

volatile int n;

HANDLE sem_b, sem_c, sem_e, sem_f;
HANDLE sem_bs, sem_es, sem_ds, sem_gs, sem_fs;
HANDLE sem_hs, sem_is, sem_ks;

int num = 3;

unsigned int lab3_thread_graph_id() 
{
    return 16;
}

const char* lab3_unsynchronized_threads()
{
    return "bcef";
}

const char* lab3_sequential_threads()
{
	return "ehi";
}

DWORD WINAPI thread_a(LPVOID iNum) 
{
	UNREFERENCED_PARAMETER(iNum);
	// interval 1
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'a' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}
	return 0;
}

DWORD WINAPI thread_b(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	// interval 2
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'b' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}
	ReleaseSemaphore(sem_b, 4, NULL);
	WaitForSingleObject(sem_c, INFINITE);
	WaitForSingleObject(sem_e, INFINITE);
	WaitForSingleObject(sem_f, INFINITE);

	// interval 3
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_bs, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'b' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_es, 1, NULL);
	}
	return 0;
}

DWORD WINAPI thread_c(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	// interval 2
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'c' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}
	ReleaseSemaphore(sem_c, 5, NULL);
	return 0;
}

DWORD WINAPI thread_e(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	// interval 2
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'e' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}
	ReleaseSemaphore(sem_e, 4, NULL);
	WaitForSingleObject(sem_b, INFINITE);
	WaitForSingleObject(sem_c, INFINITE);
	WaitForSingleObject(sem_f, INFINITE);

	// interval 3
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_es, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'e' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_ds, 1, NULL);
	}

	// 4
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_es, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'e' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_fs, 1, NULL);
	}
	//5
	ReleaseSemaphore(sem_es, 1, NULL);

	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_es, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'e' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_hs, 1, NULL);
	}
	return 0;
}

DWORD WINAPI thread_f(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	// interval 2
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'f' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}
	ReleaseSemaphore(sem_f, 4, NULL);
	// interval 3
	WaitForSingleObject(sem_b, INFINITE);
	WaitForSingleObject(sem_c, INFINITE);
	WaitForSingleObject(sem_e, INFINITE);

	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_fs, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'f' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	    ReleaseSemaphore(sem_bs, 1, NULL);
	}
	// 4
	ReleaseSemaphore(sem_fs, 1, NULL);

	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_fs, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'f' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_gs, 1, NULL);
	}

	return 0;
}

//--------------------------------//
DWORD WINAPI thread_d(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	// interval 3
	WaitForSingleObject(sem_b, INFINITE);
	WaitForSingleObject(sem_c, INFINITE);
	WaitForSingleObject(sem_e, INFINITE);
	WaitForSingleObject(sem_f, INFINITE);

	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_ds, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'd' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_gs, 1, NULL);
	}
	return 0;
}

DWORD WINAPI thread_g(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	WaitForSingleObject(sem_b, INFINITE);
	WaitForSingleObject(sem_c, INFINITE);
	WaitForSingleObject(sem_e, INFINITE);
	WaitForSingleObject(sem_f, INFINITE);
	// interval 3
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_gs, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'g' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_fs, 1, NULL);
	}
	// 4
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_gs, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'g' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_hs, 1, NULL);
	}
	return 0;
}
//--------------------------------//

DWORD WINAPI thread_h(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	// interval 4
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_hs, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'h' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_es, 1, NULL);
	}

	//5
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_hs, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'h' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_is, 1, NULL);
	}


	return 0;
}

DWORD WINAPI thread_i(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	// interval 5
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_is, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'i' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_es, 1, NULL);
	}
	ReleaseSemaphore(sem_is, 1, NULL);
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_is, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'i' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_ks, 1, NULL);
	}
	return 0;
}

DWORD WINAPI thread_k(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	// interval 6
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_ks, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'k' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_is, 1, NULL);
	}
	return 0;
}

int lab3_init()
{
	DWORD IDThread;
	// creating a mutex
	CONST HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
	// creating semaphores
	sem_b = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_b == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	sem_c = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_c == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	sem_e = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_e == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	sem_f = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_f == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	// creating semaphores
	sem_gs = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_gs == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	sem_bs = CreateSemaphore(NULL, 1, 10, NULL);
	if (sem_bs == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	sem_ds = CreateSemaphore(NULL, 0, 10, NULL);

	if (sem_ds == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	sem_fs = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_fs == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	sem_es = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_es == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	sem_hs = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_hs == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	sem_is = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_hs == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	sem_ks = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_hs == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}

	// the first interval
	hThreads[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_a, NULL, 0, &IDThread);
	if (hThreads[0] == NULL) return GetLastError();
	WaitForSingleObject(hThreads[0], INFINITE);

	hThreads[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_b, NULL, 0, &IDThread);
	if (hThreads[1] == NULL) return GetLastError();
	hThreads[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_c, NULL, 0, &IDThread);
	if (hThreads[2] == NULL) return GetLastError();
	hThreads[3] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_e, NULL, 0, &IDThread);
	if (hThreads[3] == NULL) return GetLastError();
	hThreads[4] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_f, NULL, 0, &IDThread);
	if (hThreads[4] == NULL) return GetLastError();

	hThreads[5] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_d, NULL, 0, &IDThread);
	if (hThreads[5] == NULL) return GetLastError();
	hThreads[6] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_g, NULL, 0, &IDThread);
	if (hThreads[6] == NULL) return GetLastError();

	WaitForSingleObject(hThreads[1], INFINITE);
	WaitForSingleObject(hThreads[5], INFINITE);

	hThreads[7] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_h, NULL, 0, &IDThread);
	if (hThreads[7] == NULL) return GetLastError();

	WaitForSingleObject(hThreads[4], INFINITE);
	WaitForSingleObject(hThreads[6], INFINITE);
	WaitForSingleObject(hThreads[2], INFINITE);

	hThreads[8] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_i, NULL, 0, &IDThread);
	if (hThreads[8] == NULL) return GetLastError();

	WaitForSingleObject(hThreads[3], INFINITE);
	WaitForSingleObject(hThreads[7], INFINITE);


	hThreads[9] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_k, NULL, 0, &IDThread);
	if (hThreads[9] == NULL) return GetLastError();

	WaitForSingleObject(hThreads[8], INFINITE);
	WaitForSingleObject(hThreads[9], INFINITE);

	// closing threads
	for (int i = 0; i < THREADCOUNT; i++) 
		if (hThreads[i] != NULL) { CloseHandle(hThreads[i]); }

	// closing the mutex and semaphores
	CloseHandle(hMutex);

	CloseHandle(sem_b);
	CloseHandle(sem_c);
	CloseHandle(sem_e);
	CloseHandle(sem_f);

	CloseHandle(sem_bs);
	CloseHandle(sem_es);
	CloseHandle(sem_ds);
	CloseHandle(sem_gs);
	CloseHandle(sem_fs);

	CloseHandle(sem_is);
	CloseHandle(sem_hs);
	CloseHandle(sem_ks);
    return 0;
}
