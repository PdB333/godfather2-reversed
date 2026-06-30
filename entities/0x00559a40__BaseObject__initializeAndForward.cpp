// FUNC_NAME: BaseObject::initializeAndForward
void __thiscall BaseObject::initializeAndForward(void* this, uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
    // Global engine state initialization (e.g., static data or singleton update)
    initStaticData();

    // Forward the call to the actual handler with the original parameters
    forwardToTarget(this, arg1, arg2, arg3);
}