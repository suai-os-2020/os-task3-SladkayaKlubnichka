#include "lab3.h"
#include <windows.h>
#include <stdio.h>

// #include "pch.h"

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

HANDLE hMutex;

HANDLE sem_bs, sem_cs, sem_ds, sem_fs; // bcdf

HANDLE sem_gs, sem_es, sem_is, sem_ks; // -> fdgike

HANDLE sem_d, sem_e, sem_i, sem_k, sem_f, sem_g; 

HANDLE sem_h, sem_m, sem_n; 

HANDLE sem_ms, sem_ns;

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
	return 0;
}

DWORD WINAPI thread_b(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
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
	return 0;
}

DWORD WINAPI thread_c(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
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
	return 0;
}

DWORD WINAPI thread_d(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
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
	// interval 3
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_ds, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'd' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_gs, 1, NULL);
	}

	ReleaseSemaphore(sem_d, 2, NULL);
	WaitForSingleObject(sem_f, INFINITE);
	WaitForSingleObject(sem_g, INFINITE);
	WaitForSingleObject(sem_i, INFINITE);
	WaitForSingleObject(sem_k, INFINITE);
	WaitForSingleObject(sem_e, INFINITE);

	// interval 4
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'd' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}

	ReleaseSemaphore(sem_d, 3, NULL);
	WaitForSingleObject(sem_h, INFINITE);
	WaitForSingleObject(sem_i, INFINITE);
	WaitForSingleObject(sem_k, INFINITE);
	WaitForSingleObject(sem_m, INFINITE);

	// interval 5
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_ds, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'd' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_ns, 1, NULL);
	}
	return 0;
}

DWORD WINAPI thread_f(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
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

	ReleaseSemaphore(sem_fs, 1, NULL);
	// interval 3
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_fs, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'f' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_ds, 1, NULL);
	}

	ReleaseSemaphore(sem_f, 3, NULL);

	return 0;
}

DWORD WINAPI thread_e(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	// interval 3
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_es, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'e' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_fs, 1, NULL);
	}

	ReleaseSemaphore(sem_e, 3, NULL);
	return 0;
}

DWORD WINAPI thread_g(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	// interval 3
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_gs, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'g' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_is, 1, NULL);
	}

	ReleaseSemaphore(sem_g, 3, NULL);
	return 0;
}

DWORD WINAPI thread_i(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	// interval 3
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_is, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'i' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_ks, 1, NULL);
	}

	ReleaseSemaphore(sem_i, 2, NULL);
	WaitForSingleObject(sem_f, INFINITE);
	WaitForSingleObject(sem_d, INFINITE);
	WaitForSingleObject(sem_g, INFINITE);
	WaitForSingleObject(sem_k, INFINITE);
	WaitForSingleObject(sem_e, INFINITE);

	// interval 4
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'i' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}

	ReleaseSemaphore(sem_i, 4, NULL);
	return 0;
}

DWORD WINAPI thread_k(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);
	// interval 3
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_ks, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'k' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_es, 1, NULL);
	}

	ReleaseSemaphore(sem_k, 2, NULL);

	WaitForSingleObject(sem_f, INFINITE);
	WaitForSingleObject(sem_d, INFINITE);
	WaitForSingleObject(sem_g, INFINITE);
	WaitForSingleObject(sem_i, INFINITE);
	WaitForSingleObject(sem_e, INFINITE);

	// interval 4

	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'k' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}

	// interval 5
	ReleaseSemaphore(sem_k, 3, NULL);
	WaitForSingleObject(sem_d, INFINITE);
	WaitForSingleObject(sem_h, INFINITE);
	WaitForSingleObject(sem_i, INFINITE);
	WaitForSingleObject(sem_m, INFINITE);

	ReleaseSemaphore(sem_ks, 1, NULL);
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_ks, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'k' << std::flush;
		ReleaseMutex(hMutex);
		ReleaseSemaphore(sem_ms, 1, NULL);
		computation();
	}
	return 0;
}

DWORD WINAPI thread_h(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);

	// interval 4
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'h' << std::flush;
		ReleaseMutex(hMutex);
		computation();
	}

	ReleaseSemaphore(sem_h, 4, NULL);

	return 0;
}

DWORD WINAPI thread_m(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);

	// interval 4
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'm' << std::flush;
		ReleaseMutex(hMutex);
		computation();

	}

	ReleaseSemaphore(sem_m, 3, NULL);
	WaitForSingleObject(sem_d, INFINITE);
	WaitForSingleObject(sem_h, INFINITE);
	WaitForSingleObject(sem_i, INFINITE);
	WaitForSingleObject(sem_k, INFINITE);

	//interval 5
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_ms, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'm' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_ds, 1, NULL);
	}
	return 0;
}

DWORD WINAPI thread_n(LPVOID iNum)
{
	UNREFERENCED_PARAMETER(iNum);

	WaitForSingleObject(sem_d, INFINITE);
	WaitForSingleObject(sem_h, INFINITE);
	WaitForSingleObject(sem_i, INFINITE);
	WaitForSingleObject(sem_k, INFINITE);
	WaitForSingleObject(sem_m, INFINITE);

	// interval 5
	for (int i = 0; i < num; i++)
	{
		WaitForSingleObject(sem_ns, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << 'n' << std::flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_ks, 1, NULL);
	}
	return 0;
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
	return 0;
}

int lab3_init()
{
	DWORD IDThread;
	HANDLE hThreads[13];
	// creating a mutex
	hMutex = CreateMutex(NULL, FALSE, NULL);
	if (hMutex == NULL) {
		std::cout << "CreateMutex error: " << GetLastError();
		return 1;
	}

	// creating semaphores
	sem_bs = CreateSemaphore(NULL, 1, 10, NULL);
	if (sem_bs == NULL){
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}

	sem_cs = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_cs == NULL) {
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

	sem_gs = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_gs == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}

	sem_is = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_is == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}

	sem_ks = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_ks == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}

	sem_f = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_f == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}

	sem_d = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_d == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}

	sem_g = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_g == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}

	sem_i = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_i == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}

	sem_k = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_k == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}

	sem_e = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_e == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}

	sem_h = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_h == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}

	sem_m = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_m == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}

	sem_n = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_n == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}

	sem_ms = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_ms == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}

	sem_ns = CreateSemaphore(NULL, 0, 10, NULL);
	if (sem_ns == NULL) {
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
	hThreads[3] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_d, NULL, 0, &IDThread);
	if (hThreads[3] == NULL) return GetLastError();
	hThreads[4] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_f, NULL, 0, &IDThread);
	if (hThreads[4] == NULL) return GetLastError();

	WaitForSingleObject(hThreads[1], INFINITE);
	WaitForSingleObject(hThreads[2], INFINITE);

	hThreads[5] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_e, NULL, 0, &IDThread);
	if (hThreads[5] == NULL) return GetLastError();
	hThreads[6] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_g, NULL, 0, &IDThread);
	if (hThreads[6] == NULL) return GetLastError();
	hThreads[7] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_i, NULL, 0, &IDThread);
	if (hThreads[7] == NULL) return GetLastError();
	hThreads[8] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_k, NULL, 0, &IDThread);
	if (hThreads[8] == NULL) return GetLastError();

	WaitForSingleObject(hThreads[4], INFINITE);
	WaitForSingleObject(hThreads[6], INFINITE);
	WaitForSingleObject(hThreads[5], INFINITE);

	hThreads[9] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_h, NULL, 0, &IDThread);
	if (hThreads[9] == NULL) return GetLastError();
	hThreads[10] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_m, NULL, 0, &IDThread);
	if (hThreads[10] == NULL) return GetLastError();

	WaitForSingleObject(hThreads[7], INFINITE);
	WaitForSingleObject(hThreads[9], INFINITE);

	hThreads[11] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_n, NULL, 0, &IDThread);
	if (hThreads[11] == NULL) return GetLastError();

	WaitForSingleObject(hThreads[3], INFINITE);
	WaitForSingleObject(hThreads[8], INFINITE);
	WaitForSingleObject(hThreads[10], INFINITE);
	WaitForSingleObject(hThreads[11], INFINITE);

	hThreads[12] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_p, NULL, 0, &IDThread);
	if (hThreads[12] == NULL) return GetLastError();

	WaitForSingleObject(hThreads[12], INFINITE);

	// closing threads
	for (int i = 0; i < 13; i++) {
		CloseHandle(hThreads[i]);
	}

	// closing the mutex and semaphores

	CloseHandle(hMutex);
	CloseHandle(sem_bs);
	CloseHandle(sem_cs);
	CloseHandle(sem_ds);
	CloseHandle(sem_fs);

	CloseHandle(sem_es);
	CloseHandle(sem_gs);
	CloseHandle(sem_is);
	CloseHandle(sem_ks);

	CloseHandle(sem_f);
	CloseHandle(sem_d);
	CloseHandle(sem_e);
	CloseHandle(sem_g);
	CloseHandle(sem_i);
	CloseHandle(sem_k);

	CloseHandle(sem_h);
	CloseHandle(sem_m);
	CloseHandle(sem_n);

	CloseHandle(sem_ms);
	CloseHandle(sem_ns);
    return 0;
}
