#include "lab3.h"
#include <Windows.h>
#include <stdio.h>

//
// lab3 code should be located here!
//

using namespace std;


#define THREADCOUNT 13
HANDLE hMutex;
HANDLE hThreads[THREADCOUNT];

volatile int n;

HANDLE sem_b, sem_c, sem_d, sem_f;
HANDLE sem_g, sem_e, sem_k, sem_i;
HANDLE sem_n, sem_m;

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

DWORD WINAPI thread_a(LPVOID iNum) {
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(hMutex, INFINITE);
		cout << "a" << flush;
		ReleaseMutex(hMutex);
		computation();
	}
	return 0;
}

DWORD WINAPI thread_b(LPVOID iNum) {
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(sem_b, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "b" << flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_c, 1, NULL);
	}
	return 0;
}

DWORD WINAPI thread_c(LPVOID iNum) {
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(sem_c, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "c" << flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_d, 1, NULL);
	}
	return 0;
}

DWORD WINAPI thread_d(LPVOID iNum) {
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(sem_d, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "d" << flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_f, 1, NULL);
	}

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(sem_d, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "d" << flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_g, 1, NULL);
	}

	for (int i = 0; i < 3; i++) {
		sleep_ms(1000);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "d" << flush;
		ReleaseMutex(hMutex);
		computation();
	}

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(sem_d, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "d" << flush;
		ReleaseMutex(hMutex);
		ReleaseSemaphore(sem_n, 1, NULL);
		computation();
	}

	return 0;
}


DWORD WINAPI thread_f(LPVOID iNum) {
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(sem_f, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "f"<<flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_b, 1, NULL);
	}

	WaitForSingleObject(sem_b, INFINITE);
	ReleaseSemaphore(sem_f, 1, NULL);

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(sem_f, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "f" << flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_d, 1, NULL);
	}

	return 0;
}

DWORD WINAPI thread_g(LPVOID iNum) {
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(sem_g, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "g" << flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_i, 1, NULL);
	}
	return 0;
}

DWORD WINAPI thread_e(LPVOID iNum) {
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(sem_e, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "e" << flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_f, 1, NULL);
	}
	return 0;
}

DWORD WINAPI thread_k(LPVOID iNum) {
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(sem_k, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "k" << flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_e, 1, NULL);
	}

	for (int i = 0; i < 3; i++) {
		sleep_ms(1000);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "k" << flush;
		ReleaseMutex(hMutex);
		computation();
	}

	sleep_ms(1000);
	ReleaseSemaphore(sem_k, 1, NULL);
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(sem_k, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "k" << flush;
		ReleaseMutex(hMutex);
		ReleaseSemaphore(sem_m, 1, NULL);
		computation();
	}

	return 0;
}

DWORD WINAPI thread_i(LPVOID iNum) {
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(sem_i, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "i" << flush;
		ReleaseMutex(hMutex);
		computation();
		ReleaseSemaphore(sem_k, 1, NULL);
	}


	for (int i = 0; i < 3; i++) {
		sleep_ms(1000);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "i" << flush;
		ReleaseMutex(hMutex);
		computation();
	}

	return 0;
}

DWORD WINAPI thread_h(LPVOID iNum) {
	for (int i = 0; i < 3; i++) {
		sleep_ms(1000);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "h" << flush;
		ReleaseMutex(hMutex);
		computation();
	}
	return 0;
}

DWORD WINAPI thread_m(LPVOID iNum) {

	for (int i = 0; i < 3; i++) {
		sleep_ms(1000);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "m" << flush;
		ReleaseMutex(hMutex);
		computation();
	}

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(sem_m, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "m" << flush;
		ReleaseMutex(hMutex);
		ReleaseSemaphore(sem_d, 1, NULL);
		computation();
	}
	return 0;
}

DWORD WINAPI thread_n(LPVOID iNum) {
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(sem_n, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "n" << flush;
		ReleaseMutex(hMutex);
		ReleaseSemaphore(sem_k, 1, NULL);
		computation();
	}
	return 0;
}

DWORD WINAPI thread_p(LPVOID iNum) {
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(hMutex, INFINITE);
		cout << "p" << flush;
		ReleaseMutex(hMutex);
		computation();
	}
	return 0;
}

int lab3_init()
{
	DWORD IDThread;
	// creating a mutex
	CONST HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
	// creating semaphores
	sem_b = CreateSemaphore(NULL, 1, 1, NULL);
	if (sem_b == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	sem_c = CreateSemaphore(NULL, 0, 1, NULL);
	if (sem_c == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	sem_d = CreateSemaphore(NULL, 0, 1, NULL);
	if (sem_d == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	sem_f = CreateSemaphore(NULL, 0, 1, NULL);
	if (sem_f == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	// creating semaphores
	sem_g = CreateSemaphore(NULL, 0, 1, NULL);
	if (sem_g == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	sem_e = CreateSemaphore(NULL, 0, 1, NULL);
	if (sem_e == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	sem_k = CreateSemaphore(NULL, 0, 1, NULL);
	if (sem_k == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	sem_i = CreateSemaphore(NULL, 0, 1, NULL);
	if (sem_i == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	sem_n = CreateSemaphore(NULL, 0, 1, NULL);
	if (sem_n == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	sem_m = CreateSemaphore(NULL, 0, 1, NULL);
	if (sem_m == NULL) {
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}
	// start the threads - interval 1
	hThreads[0] = CreateThread(NULL, 0, thread_a, NULL, 0, &IDThread);
	if (hThreads[0] == NULL)
		return GetLastError();

	WaitForSingleObject(hThreads[0], INFINITE);

	// interval 2
	hThreads[1] = CreateThread(NULL, 0, thread_b, NULL, 0, &IDThread);
	if (hThreads[1] == NULL)
		return GetLastError();

	hThreads[2] = CreateThread(NULL, 0, thread_c, NULL, 0, &IDThread);
	if (hThreads[2] == NULL)
		return GetLastError();

	hThreads[3] = CreateThread(NULL, 0, thread_d, NULL, 0, &IDThread);
	if (hThreads[3] == NULL)
		return GetLastError();

	hThreads[4] = CreateThread(NULL, 0, thread_f, NULL, 0, &IDThread);
	if (hThreads[4] == NULL)
		return GetLastError();

	WaitForSingleObject(hThreads[1], INFINITE);
	WaitForSingleObject(hThreads[2], INFINITE);

	// interval 3

	hThreads[5] = CreateThread(NULL, 0, thread_g, NULL, 0, &IDThread);
	if (hThreads[5] == NULL)
		return GetLastError();

	hThreads[6] = CreateThread(NULL, 0, thread_e, NULL, 0, &IDThread);
	if (hThreads[6] == NULL)
		return GetLastError();

	hThreads[7] = CreateThread(NULL, 0, thread_k, NULL, 0, &IDThread);
	if (hThreads[7] == NULL)
		return GetLastError();

	hThreads[8] = CreateThread(NULL, 0, thread_i, NULL, 0, &IDThread);
	if (hThreads[8] == NULL)
		return GetLastError();

	WaitForSingleObject(hThreads[5], INFINITE);
	WaitForSingleObject(hThreads[6], INFINITE);
	WaitForSingleObject(hThreads[4], INFINITE);

	// interval 4 (d[3], k[7], i[8], h[9], m[10])

	hThreads[9] = CreateThread(NULL, 0, thread_h, NULL, 0, &IDThread);
	if (hThreads[9] == NULL)
		return GetLastError();

	hThreads[10] = CreateThread(NULL, 0, thread_m, NULL, 0, &IDThread);
	if (hThreads[10] == NULL)
		return GetLastError();

	WaitForSingleObject(hThreads[8], INFINITE);
	WaitForSingleObject(hThreads[9], INFINITE);

	// interval 5
	hThreads[11] = CreateThread(NULL, 0, thread_n, NULL, 0, &IDThread);
	if (hThreads[11] == NULL)
		return GetLastError();

	WaitForSingleObject(hThreads[7], INFINITE);
	WaitForSingleObject(hThreads[10], INFINITE);
	WaitForSingleObject(hThreads[11], INFINITE);
	WaitForSingleObject(hThreads[3], INFINITE);

	// final interval
	hThreads[12] = CreateThread(NULL, 0, thread_p, NULL, 0, &IDThread);
	if (hThreads[12] == NULL)
		return GetLastError();

	WaitForSingleObject(hThreads[12], INFINITE);

	for (int i = 0; i < THREADCOUNT; i++) 
		CloseHandle(hThreads[i]);

	CloseHandle(hMutex);
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
    return 0;
}
