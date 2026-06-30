// FUNC_NAME: SlotManager::acquireSlot
int __thiscall SlotManager::acquireSlot(int thisPtr, ushort slotIndex)
{
    int slotBase;
    uint status; // in_EAX
    uint retVal;

    status = globalStatus >> 8; // globalStatus is a register value, possibly from a previous call
    if (slotIndex < 0x80) {
        slotBase = (uint)slotIndex * 0xf8 + 0x5a0 + thisPtr; // slotBase points to the slot at this->slotArray[slotIndex]
        status = FUN_005e9d10(); // returns some status
        if ((status != 0) && (*(int *)(thisPtr + 0x580) != 0)) {
            FUN_00c9eac0(); // allocate/initialize audio/stream resource
            FUN_00c9cd40(1, 0); // set some parameters
            uVar3 = FUN_00c9eb20(); // get resource handle
            *(undefined4 *)(slotBase + 0xe0) = uVar3; // store handle at slot->resourceHandle
            FUN_00c9eae0(); // finalize resource allocation
            FUN_005efb60(); // notify or register callback
            *(undefined4 *)(slotBase + 0xdc) = 0; // slot->state = 0
            *(undefined4 *)(slotBase + 0xe0) = 0; // slot->resourceHandle = 0 (maybe redundant? actually set above then cleared? Could be a second field)
            *(undefined4 *)(slotBase + 0xe4) = 0; // slot->someFlag = 0
            return 1;
        }
        retVal = status >> 8;
    } else {
        retVal = status << 8;
    }
    return retVal;
}