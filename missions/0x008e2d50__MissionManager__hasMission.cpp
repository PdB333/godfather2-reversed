// FUNC_NAME: MissionManager::hasMission
undefined4 __thiscall MissionManager::hasMission(int *this, int missionId)
{
    char boolResult;
    int *objectPtr;
    int missionSlotIndex;
    int *slotHandlePtr;
    int *outData;
    int slotIndex;

    slotIndex = 0;
    slotHandlePtr = this + 0x22; // offset to array of 3 slot handles (each 0x5C bytes)
    outData = this;
    do {
        // resolve handle to an object (likely mission slot object)
        objectPtr = (int *)resolveHandle(slotHandlePtr, 0);
        if (objectPtr != (int *)0x0) {
            outData = (int *)0x0;
            // call vtable+0x10: attempt to get mission data from hash 0x254cce9
            boolResult = (**(code **)(*objectPtr + 0x10))(0x254cce9, &outData);
            objectPtr = outData;
            if ((boolResult != '\0') && (outData != (int *)0x0)) {
                // check if active (vtable+0x154)
                boolResult = (**(code **)(*outData + 0x154))();
                if (boolResult != '\0') {
                    // get mission ID (vtable+0x160) and compare
                    missionSlotIndex = (**(code **)(*objectPtr + 0x160))();
                    if (missionSlotIndex == missionId) {
                        return 1;
                    }
                }
            }
        }
        slotIndex = slotIndex + 1;
        slotHandlePtr = slotHandlePtr + 0x17; // next slot handle (0x17 words = 0x5C bytes)
    } while (slotIndex < 3);
    return 0;
}