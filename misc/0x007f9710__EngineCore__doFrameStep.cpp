// FUNC_NAME: EngineCore::doFrameStep
// Address: 0x007f9710
// This function is a simple forwarder that calls EngineCore::internalTick (0x006f3be0).
// Likely serves as a thunk for encapsulation or modularity.

void EngineCore::doFrameStep(void)
{
    EngineCore::internalTick();
    return;
}