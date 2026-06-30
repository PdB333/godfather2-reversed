// FUNC_NAME: CInputManager::updateActiveDevices
void CInputManager::updateActiveDevices(int startIdx, void* arg)
{
    int idx = startIdx + 1;

    // +0x80 : number of device slots (short)
    if (idx < *(short*)((int)this + 0x80))
    {
        // Array of device slots starts at +0xf4, each slot is 0x14 bytes
        int* slotPtr = (int*)((int)this + 0xf4 + idx * 0x14);

        do
        {
            // Check flag byte at slotPtr[-1] (offset -1 from slot start)
            // Bit 0x20 indicates whether this slot is active
            if ((*(unsigned char*)(slotPtr - 1) & 0x20) == 0)
                return;

            // First 4 bytes of slot: pointer to device object
            if (*slotPtr != 0)
            {
                // Call virtual function at vtable offset 0x30 (index 12)
                // This is typically an update/process method that returns bool
                bool (*updateFunc)(void*) = (bool(*)(void*))(*(int*)(*(int*)*slotPtr + 0x30));
                if (updateFunc(arg))
                    return;
            }

            idx++;
            slotPtr += 5; // advance by 5 ints = 0x14 bytes per slot
        } while (idx < *(short*)((int)this + 0x80));
    }
    return;
}