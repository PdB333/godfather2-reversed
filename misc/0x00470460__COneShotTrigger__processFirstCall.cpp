// FUNC_NAME: COneShotTrigger::processFirstCall
// Address: 0x00470460
// Increments a call counter at +0x161 and triggers a virtual function on the first call
// if the target pointer at +0x130 is non-null. The virtual function is at vtable index 0x4c (offset 0x130).

void __thiscall COneShotTrigger::processFirstCall()
{
    char *callCount = reinterpret_cast<char *>(reinterpret_cast<uintptr_t>(this) + 0x161); // +0x161: m_nCallCount
    char prevCount = *callCount;
    *callCount = prevCount + 1;

    void *target = *reinterpret_cast<void **>(reinterpret_cast<uintptr_t>(this) + 0x130); // +0x130: m_pTarget

    if (prevCount == 0 && target != nullptr)
    {
        // Call virtual function at vtable offset 0x130 (index 0x4c)
        void **vtable = *reinterpret_cast<void ***>(this);
        void (__thiscall *triggerFunc)(void *) = reinterpret_cast<void (__thiscall *)(void *)>(vtable[0x4c]);
        triggerFunc(this);
    }
}