// FUNC_NAME: Entity::updateState
void __fastcall Entity::updateState(int thisPtr)
{
    // Get pointer to some manager or data source at offset +0x34
    int* managerPtr = *(int**)(thisPtr + 0x34);
    
    // Call virtual function at vtable offset 0x24 (likely getCurrentTimestamp or similar)
    int timestamp = (*(int (__thiscall**)(int*))(managerPtr[0] + 0x24))(managerPtr);
    
    // Store timestamp at offset +0x0C (e.g., lastUpdateTime)
    *(int*)(thisPtr + 0x0C) = timestamp;
    
    // Call virtual function at vtable offset 0x3C (likely hasPendingUpdate or needsUpdate)
    int needsUpdate = (*(int (__thiscall**)(int*))(managerPtr[0] + 0x3C))(managerPtr);
    
    if (needsUpdate != 0) {
        // Process the pending update
        FUN_005683c0();
    }
}