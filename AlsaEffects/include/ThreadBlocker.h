#ifndef THREADBLOCKER_H
#define THREADBLOCKER_H

#include <mutex>
#include <condition_variable>
#include <memory>

class ThreadBlocker
{
public:
	ThreadBlocker();
	~ThreadBlocker();

	void unblockSignal();
	void waitForSignal();
private:
	std::mutex m_mux;
	std::condition_variable m_cv;
	bool m_dataReady; //Protects against spurious wakeups - Can also be used for force the thread to unblock when terminating
};


#endif // !THREADBLOCKER_H
