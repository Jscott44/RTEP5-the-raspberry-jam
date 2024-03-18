#ifndef ALSALISTENER_H
#define ALSALISTENER_H

#include <memory>
#include <cstdint>

class AlsaListener
{
public:
	//AlsaListener();
	//~AlsaListener();

	virtual void hasBuffer(uint8_t* buffer) = 0;

protected:
	uint8_t* m_listenerBuffer;
};


#endif // !ALSALISTENER_H
