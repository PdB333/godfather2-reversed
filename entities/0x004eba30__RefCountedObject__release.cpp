// FUNC_NAME: RefCountedObject::release
void RefCountedObject::release(bool immediate)
{
    if (this != nullptr) {
        this->refCount -= 1; // +0x14
        if (immediate) {
            this->pendingReleaseCount -= 1; // +0x18
        }
        if ((this->refCount < 1) && (this->slotIndex == g_currentFreeSlotIndex)) { // +0x16
            g_currentFreeSlotIndex -= 1;
            if (g_currentFreeSlotIndex >= 0) {
                short* slotRefCount = &g_slotArray[g_currentFreeSlotIndex].refCount; // +4 within slot (0x20 size)
                do {
                    if (*slotRefCount > 0) {
                        return;
                    }
                    g_currentFreeSlotIndex -= 1;
                    slotRefCount -= 0x10; // move to previous slot's refCount (0x20/2 = 0x10 shorts)
                } while (g_currentFreeSlotIndex >= 0);
            }
        }
    }
}