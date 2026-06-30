// FUNC_NAME: BaseObject::release
void __thiscall BaseObject::release(BaseObject* this)
{
    // lock global mutex or enter critical section (likely)
    internalLockMutex();

    // call virtual destructor chain or cleanup children
    internalDestructorChain(this);

    // call global destruction callback (e.g., finalizer hook)
    (g_globalDestructionCallback)();

    // decrement a counter at offset 0x24 within the object's control block
    // the control block is pointed to by [this + 0x10]
    if (this != nullptr) {
        int* controlBlock = *(int**)(((char*)this) + 0x10); // +0x10: pointer to control block
        int* counter = controlBlock + 0x24 / 4;             // +0x24: e.g., allocation size or ref count
        *counter -= 0x58;                                   // subtract 0x58 (likely a debug tracking delta)
    }
}