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
#define THREADCOUNT 13

HANDLE hMutex;
HANDLE hThreads[THREADCOUNT];

volatile int n;

HANDLE sem_b, sem_c, sem_d, sem_f;
HANDLE sem_g, sem_e, sem_k, sem_i;
HANDLE sem_n, sem_m, sem_h, sem_a;
HANDLE sem_bs, sem_cs, sem_ds, sem_fs;

int num = 3;

unsigned int lab3_thread_graph_id() 
{
    return 19;
}

const char* lab3_unsynchronized_threads()
{
    return "dhikm";
}

const char* lab3_sequential_threads()
{
	return "bcdf";
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

	ReleaseSemaphore(sem_a, 4, NULL);
	return TRUE;
}

DWORD WINAPI thread_b(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	WaitForSingleObject(sem_a, INFINITE);
	// interval 2
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_bs, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'b' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_cs, 1, NULL);
	}
	ReleaseSemaphore(sem_b, 6, NULL);
	return 0;
}

DWORD WINAPI thread_c(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	WaitForSingleObject(sem_a, INFINITE);
	// interval 2
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_cs, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'c' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_ds, 1, NULL);
	}
	ReleaseSemaphore(sem_c, 6, NULL);
	return TRUE;
}

DWORD WINAPI thread_d(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	WaitForSingleObject(sem_a, INFINITE);
	// interval 2
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_ds, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'd' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_fs, 1, NULL);
	}

	ReleaseSemaphore(sem_d, 5, NULL);

	WaitForSingleObject(sem_b, INFINITE);
	WaitForSingleObject(sem_c, INFINITE);
	WaitForSingleObject(sem_f, INFINITE);

	// interval 3
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'd' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}

	ReleaseSemaphore(sem_d, 4, NULL);
	// interval 4 
	WaitForSingleObject(sem_g, INFINITE);
	WaitForSingleObject(sem_i, INFINITE);
	WaitForSingleObject(sem_k, INFINITE);
	WaitForSingleObject(sem_e, INFINITE);
	WaitForSingleObject(sem_f, INFINITE);

	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'd' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}

	ReleaseSemaphore(sem_d, 3, NULL);
	// interval 5
	WaitForSingleObject(sem_h, INFINITE);
	WaitForSingleObject(sem_m, INFINITE);
	WaitForSingleObject(sem_i, INFINITE);
	WaitForSingleObject(sem_k, INFINITE);
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'd' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}
	return TRUE;
}

DWORD WINAPI thread_f(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	WaitForSingleObject(sem_a, INFINITE);
	// interval 2
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_fs, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'f' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_bs, 1, NULL);
	}

	ReleaseSemaphore(sem_f, 5, NULL);
	WaitForSingleObject(sem_b, INFINITE);
	WaitForSingleObject(sem_c, INFINITE);
	WaitForSingleObject(sem_d, INFINITE);
	// interval 3
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'f' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}
	ReleaseSemaphore(sem_f, 5, NULL);
	return TRUE;
}

DWORD WINAPI thread_e(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	WaitForSingleObject(sem_b, INFINITE);
	WaitForSingleObject(sem_c, INFINITE);
	WaitForSingleObject(sem_d, INFINITE);
	WaitForSingleObject(sem_f, INFINITE);
	// interval 3
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'e' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}
	ReleaseSemaphore(sem_e, 5, NULL);
	return TRUE;
}

DWORD WINAPI thread_g(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	WaitForSingleObject(sem_b, INFINITE);
	WaitForSingleObject(sem_c, INFINITE);
	WaitForSingleObject(sem_d, INFINITE);
	WaitForSingleObject(sem_f, INFINITE);
	// interval 3
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'g' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}
	ReleaseSemaphore(sem_g, 5, NULL);
	return TRUE;
}

DWORD WINAPI thread_k(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	WaitForSingleObject(sem_b, INFINITE);
	WaitForSingleObject(sem_c, INFINITE);
	WaitForSingleObject(sem_d, INFINITE);
	WaitForSingleObject(sem_f, INFINITE);
	// interval 3
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'k' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}
	ReleaseSemaphore(sem_k, 4, NULL);
	// interval 4

	WaitForSingleObject(sem_g, INFINITE);
	WaitForSingleObject(sem_i, INFINITE);
	WaitForSingleObject(sem_e, INFINITE);
	WaitForSingleObject(sem_f, INFINITE);
	WaitForSingleObject(sem_d, INFINITE);

	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'k' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}

	// interval 5
	ReleaseSemaphore(sem_k, 3, NULL);
	WaitForSingleObject(sem_h, INFINITE);
	WaitForSingleObject(sem_m, INFINITE);
	WaitForSingleObject(sem_i, INFINITE);
	WaitForSingleObject(sem_d, INFINITE);
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'k' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}

	return TRUE;
}

DWORD WINAPI thread_i(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	WaitForSingleObject(sem_b, INFINITE);
	WaitForSingleObject(sem_c, INFINITE);
	WaitForSingleObject(sem_d, INFINITE);
	WaitForSingleObject(sem_f, INFINITE);
	// interval 3
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'i' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}
	ReleaseSemaphore(sem_i, 4, NULL);

	WaitForSingleObject(sem_g, INFINITE);
	WaitForSingleObject(sem_k, INFINITE);
	WaitForSingleObject(sem_e, INFINITE);
	WaitForSingleObject(sem_f, INFINITE);
	WaitForSingleObject(sem_d, INFINITE);

	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'i' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}
	ReleaseSemaphore(sem_i, 4, NULL);
	return TRUE;
}

DWORD WINAPI thread_h(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);

	WaitForSingleObject(sem_g, INFINITE);
	WaitForSingleObject(sem_i, INFINITE);
	WaitForSingleObject(sem_k, INFINITE);
	WaitForSingleObject(sem_e, INFINITE);
	WaitForSingleObject(sem_f, INFINITE);
	WaitForSingleObject(sem_d, INFINITE);

	// interval 4
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'h' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}

	ReleaseSemaphore(sem_h, 4, NULL);
	return TRUE;
}

DWORD WINAPI thread_m(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	// interval 4
	WaitForSingleObject(sem_g, INFINITE);
	WaitForSingleObject(sem_i, INFINITE);
	WaitForSingleObject(sem_k, INFINITE);
	WaitForSingleObject(sem_e, INFINITE);
	WaitForSingleObject(sem_f, INFINITE);
	WaitForSingleObject(sem_d, INFINITE);
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'm' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}
	// interval 5
	ReleaseSemaphore(sem_m, 4, NULL);

	WaitForSingleObject(sem_h, INFINITE);
	WaitForSingleObject(sem_i, INFINITE);
	WaitForSingleObject(sem_k, INFINITE);
	WaitForSingleObject(sem_d, INFINITE);

	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'm' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}

	return TRUE;
}

DWORD WINAPI thread_n(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	WaitForSingleObject(sem_h, INFINITE);
	WaitForSingleObject(sem_m, INFINITE);
	WaitForSingleObject(sem_i, INFINITE);
	WaitForSingleObject(sem_k, INFINITE);
	WaitForSingleObject(sem_d, INFINITE);
	// interval 5
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'n' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}
	return TRUE;
}

DWORD WINAPI thread_p(LPVOID iNum) 
{
	UNREFERENCED_PARAMETER(iNum);
	// interval 6
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'p' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}
	return TRUE;
}

int lab3_init()
{
	DWORD IDThread;
	// creating a mutex
	CONST HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
	// creating semaphores
	sem_a = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_a == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;}
	sem_b = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_b == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;}
	sem_c = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_c == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;}
	sem_d = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_d == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;}
	sem_f = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_f == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;}
	// creating semaphores
	sem_g = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_g == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;}
	sem_e = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_e == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;}
	sem_k = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_k == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;}
	sem_i = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_i == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;}
	sem_n = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_n == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;}
	sem_m = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_m == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;}
	sem_h = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_h == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;}
	sem_bs = CreateSemaphore(NULL, 1, 10, NULL);
	if (sem_bs == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;}
	sem_cs = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_cs == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;}
	sem_ds = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_ds == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;}
	sem_fs = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_fs == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;}

	// the first interval
	hThreads[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_a, NULL, 0, &IDThread);
	if (hThreads[0] == NULL) return GetLastError();

	hThreads[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_b, NULL, 0, &IDThread);
	if (hThreads[1] == NULL) return GetLastError();

	hThreads[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_c, NULL, 0, &IDThread);
	if (hThreads[2] == NULL) return GetLastError();

	hThreads[3] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_d, NULL, 0, &IDThread);
	if (hThreads[3] == NULL) return GetLastError();

	hThreads[4] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_f, NULL, 0, &IDThread);
	if (hThreads[4] == NULL) return GetLastError();

	hThreads[5] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_e, NULL, 0, &IDThread);
	if (hThreads[5] == NULL) return GetLastError();

	hThreads[6] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_g, NULL, 0, &IDThread);
	if (hThreads[6] == NULL) return GetLastError();

	hThreads[7] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_k, NULL, 0, &IDThread);
	if (hThreads[7] == NULL) return GetLastError();

	hThreads[8] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_i, NULL, 0, &IDThread);
	if (hThreads[8] == NULL) return GetLastError();

	hThreads[9] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_h, NULL, 0, &IDThread);
	if (hThreads[9] == NULL) return GetLastError();

    hThreads[10] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_m, NULL, 0, &IDThread);
	if (hThreads[10] == NULL) return GetLastError();
	hThreads[11] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_n, NULL, 0, &IDThread);
	if (hThreads[11] == NULL) return GetLastError();

	WaitForMultipleObjects(12, hThreads, TRUE, INFINITE);

	hThreads[12] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_p, NULL, 0, &IDThread);
	if (hThreads[12] == NULL) return GetLastError();

	WaitForSingleObject(hThreads[12], INFINITE);
	// closing threads
	for (int i = 0; i < THREADCOUNT; i++) 
		if (hThreads[i] != NULL) { CloseHandle(hThreads[i]); }

	// closing the mutex and semaphores
	CloseHandle(hMutex);
	CloseHandle(sem_a);
	CloseHandle(sem_b);
	CloseHandle(sem_c);
	CloseHandle(sem_d);
	CloseHandle(sem_f);
	CloseHandle(sem_g);
	CloseHandle(sem_e);
	CloseHandle(sem_k);
	CloseHandle(sem_i);
	CloseHandle(sem_m);
	CloseHandle(sem_n);
	CloseHandle(sem_h);
	CloseHandle(sem_bs);
	CloseHandle(sem_cs);
	CloseHandle(sem_ds);
	CloseHandle(sem_fs);
    return 0;
}