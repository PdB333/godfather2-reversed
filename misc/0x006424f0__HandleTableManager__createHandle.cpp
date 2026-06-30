// FUNC_NAME: HandleTableManager::createHandle
uint __thiscall HandleTableManager::createHandle(uint componentLow, uint componentMid, uint componentHigh)
{
    // EAX register holds a pre-initialized seed value, likely a member variable.
    // Combine the seed with the three components into a single 32-bit key:
    //   bits 0-5: componentLow
    //   bits 6-14: componentHigh
    //   bits 15-23: componentMid
    //   bits 24-31: seed (in_EAX)
    uint compositeKey = ((m_handleSeed << 9 | componentMid) << 9 | componentHigh) << 6 | componentLow;

    // Retrieve a pointer to internal data from this+0x0C, then access its field at offset +8.
    // This is likely a pointer to an allocation table or hash bucket.
    void* dataBase = *(void**)(this + 0x0C);
    int tableData = *(int*)((char*)dataBase + 8);  // offset 8 in the data structure

    // Insert the composite key into the table (first call, return discarded)
    FUN_006438e0(compositeKey, tableData);

    // Invalidate the current slot index (0xFFFFFFFF = -1)
    *(uint*)(this + 0x20) = 0xFFFFFFFF;

    // Attempt to allocate a new slot using a sentinel key (0x7FFF94).
    // This likely finds a free entry or returns a handle.
    uint result = FUN_006438e0(0x7FFF94, tableData);

    // Finalize the handle creation (e.g., clear temporary state)
    FUN_00642880(this);

    return result;
}