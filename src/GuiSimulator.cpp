#include "include/GuiSimulator.h"

void GuiSimulator::registerCallback(GuiListener* ptr)
{
    m_callbackPtr = ptr;
}

EffectBase* GuiSimulator::addEffect(EffectIndx desired_effect)
{
    return m_callbackPtr->addEffect(desired_effect);
}

void GuiSimulator::removeEffect(EffectBase* effect)
{
    m_callbackPtr->removeEffect(effect);
}

void GuiSimulator::alterEffect(EffectBase* effect, ParamIndx parameter, int32_t new_val)
{
    m_callbackPtr->alterEffect(effect, parameter, new_val);
}