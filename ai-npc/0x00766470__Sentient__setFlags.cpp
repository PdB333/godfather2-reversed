// FUNC_NAME: Sentient::setFlags
// Function at 0x00766470 sets bit flags at offset 0xC88, calls notification callback if flags changed.
void __thiscall Sentient::setFlags(uint32 flags)
{
    uint32* pFlags = reinterpret_cast<uint32*>(reinterpret_cast<uint8*>(this) + 0xC88); // +0xC88: m_flags
    uint32 current = *pFlags;
    uint32 newFlags = current | flags;
    if (newFlags != current)
    {
        // Call notification via a pointer at this+0x58, offset 0x28 (likely m_pStateMachine->onStateChange)
        void* pNotifyObj = *reinterpret_cast<void**>(reinterpret_cast<uint8*>(this) + 0x58); // +0x58: m_pStateMachine
        typedef void (__thiscall *NotifyFunc)(void*, int);
        NotifyFunc func = *reinterpret_cast<NotifyFunc*>(reinterpret_cast<uint8*>(pNotifyObj) + 0x28); // +0x28: vtable slot for notification
        func(pNotifyObj, 0x10); // 0x10 = eReasonFlagsChanged
        *pFlags = newFlags;
    }
}