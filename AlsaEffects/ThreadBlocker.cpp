#include "include/ThreadBlocker.h"

ThreadBlocker::ThreadBlocker()
	: m_mux(),
	m_cv(),
	m_dataReady(false)
{

}

ThreadBlocker::~ThreadBlocker()
{
	unblockSignal();
}

void ThreadBlocker::unblockSignal()
{
	// Lock mutex
	std::unique_lock<std::mutex> threadLock(m_mux);

	// Indicate that data is ready (protects against spurious wakeups)
	m_dataReady = true;

	// Notify other thread
	m_cv.notify_one();
}

void ThreadBlocker::waitForSignal()
{
	// Lock mutex
	std::unique_lock<std::mutex> threadLock(m_mux);

	// If data is not ready, wait for cv
	while (!m_dataReady)
	{
		m_cv.wait(threadLock);
	}

	// Once unblocked, reset data ready indicator
	m_dataReady = false;
}