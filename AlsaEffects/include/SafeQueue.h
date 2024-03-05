#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

class SafeQueue
{
public:
	SafeQueue();
	~SafeQueue();

	void setBuffer(std::shared_ptr<uint8_t> buffer);
	std::shared_ptr<uint8_t> getBuffer();

	void unblock();
private:
	std::queue<std::shared_ptr<uint8_t>> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_cv;
	bool m_forceUnblock;
};

#endif