#ifndef EFFECTLISTENER_H
#define EFFECTLISTENER_H

#include <cstdint>

class EffectListener
{
public:
	//EffectListener();
	//~EffectListener();

	virtual void hasAlteredBuffer(uint8_t* buffer) = 0;

private:

};

#endif // !EFFECTLISTENER_H
