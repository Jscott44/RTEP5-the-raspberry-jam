#include "include/SafeQueue.h"

SafeQueue::SafeQueue()
	: m_queue(),
	m_mutex(),
	m_cv(),
	m_forceUnblock(false)
{

}

SafeQueue::~SafeQueue()
{
	unblock();
}

void SafeQueue::setBuffer(std::shared_ptr<uint8_t> buffer)
{
	std::unique_lock<std::mutex> queueLock(m_mutex);
	m_queue.push(buffer);
	m_cv.notify_one();
}

std::shared_ptr<uint8_t> SafeQueue::getBuffer()
{
	std::unique_lock<std::mutex> queueLock(m_mutex);
	std::shared_ptr<uint8_t> retPtr;
	while (m_queue.empty() && !m_forceUnblock)
	{
		m_cv.wait(queueLock);
	}
	if (!m_forceUnblock)
	{
		retPtr = m_queue.front();
		m_queue.pop();
	}
	return retPtr;
}

void SafeQueue::unblock()
{
	m_forceUnblock = true;
	m_cv.notify_all();
}