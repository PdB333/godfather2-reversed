// FUNC_NAME: FlagManager::modifyFlags

void __thiscall FlagManager::modifyFlags(uint setMask, uint clearMask)
{
    uint oldMask = *(uint *)(this + 0x88);          // +0x88: current bitmask
    uint newMask = (~clearMask & *(uint *)(this + 0x88)) | setMask;

    if (newMask != oldMask)
    {
        *(uint *)(this + 0x88) = newMask;

        // Notify listener if present (vtable + 0x40)
        void *listener = *(void **)(this + 0x130);  // +0x130: pointer to listener object
        if (listener != nullptr)
        {
            // Compute bits that changed state
            uint xorMask = oldMask ^ newMask;
            uint newlySet = xorMask & newMask;      // bits that became set
            uint newlyCleared = xorMask & ~newMask; // bits that became cleared

            // Prepare change notification struct
            struct FlagChange
            {
                uint newlySet;
                uint newlyCleared;
            } change;
            change.newlySet = newlySet;
            change.newlyCleared = newlyCleared;

            // Call listener's handler (vtable entry at offset 0x40)
            typedef void (*HandlerFunc)(uint flagGroupId, FlagChange *change);
            HandlerFunc handler = *(HandlerFunc *)(*(uint **)listener + 0x40);
            handler(0x20e5862, &change); // 0x20e5862: flag group identifier
        }
    }
}