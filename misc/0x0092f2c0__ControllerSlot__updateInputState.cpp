// FUNC_NAME: ControllerSlot::updateInputState
void __thiscall ControllerSlot::updateInputState(int this) // this is likely a this pointer
{
    int *pDeviceMgr;
    int devIndex;
    char bitFlag;
    short axisX, axisY;
    int devListCount;
    uint devListSize;
    int *pStatEntry;
    int tmpBuffer;

    // Global pointer: likely g_systemManager
    int *pSysMgr = (int *)DAT_01223484;
    if (pSysMgr != 0) {
        // Extract a bit from global state at offset 0x37c (bit 4 of the byte)
        *(byte *)(this + 0x124) = (byte)((*(uint *)(pSysMgr + 0x37c) >> 4) & 1);

        pDeviceMgr = *(int **)(DAT_0112b9b4 + 0x40); // g_inputDeviceManager->devices?
        if (pDeviceMgr != 0) {
            // Allocate a controller state object (0x28 bytes)
            int *pCtrlState = (int *)FUN_009c8e50(0x28);
            if (pCtrlState == 0) {
                *(int *)(this + 0x16c) = 0;
            }
            else {
                *(int *)(this + 0x16c) = FUN_004bace0(); // initialize controller state
            }

            // Call a virtual method on the device manager (hash-based lookup)
            FUN_004badd0(pDeviceMgr[0x18]); // some preparation?
            tmpBuffer = 0;
            // Virtual call: (*(pDeviceMgr->vtable + 0x10))(0x5ade71cd, &tmpBuffer)
            bool bSuccess = (**(bool (__stdcall **)(uint, int *))(*pDeviceMgr + 0x10))(0x5ade71cd, &tmpBuffer);
            // Note: unaff_ESI is a register that might be a second parameter or global; assume true for now.
            if (bSuccess && unaff_ESI != 0) {
                // Get device handle and store it twice
                int devHandle = FUN_008b5310();
                *(int *)(this + 0x118) = devHandle;
                *(int *)(this + 0x164) = devHandle;

                // Process device lists (likely list of active devices)
                int listA = FUN_008ae760(&tmpBuffer, 0);
                FUN_0092d970(listA);
                if (tmpBuffer != 0) {
                    FUN_009c8f10(tmpBuffer);
                }
                int listB = FUN_008b4370(&tmpBuffer);
                FUN_0092d970(listB);
                if (tmpBuffer != 0) {
                    FUN_009c8f10(tmpBuffer);
                }

                // Get device index
                devIndex = FUN_008b4dc0(*(int *)(this + 0x118));
                *(int *)(this + 0x11c) = devIndex;

                // If the bit flag is set (alternative control scheme), decrement index and do special handling
                if (*(char *)(this + 0x124) != 0) {
                    *(int *)(this + 0x11c) = devIndex - 1;
                    // Stack manipulation for context? (local_20 = &stack)
                    int *pStack = &stack0xffffffdc; // address of a local variable
                    FUN_0092dc80(pStack);
                    if (FUN_0092e150() != 0) {
                        FUN_008a3d30(1); // enable something
                    }
                    // Set bit 0x2000 in global system manager
                    *(uint *)(pSysMgr + 0x37c) |= 0x2000;
                }

                // Get list of device entries (index 1)
                int *pDevList;
                uint devCount;
                devListSize = (uint)FUN_008ae760(&pDevList, 1);
                if (devListSize != 0 && *(int *)(this + 0x16c) != 0) {
                    for (uint i = 0; i < devListSize; i++) {
                        int entry = ((int *)pDevList)[i];
                        if (*(int *)(this + 0x16c) != 0) {
                            tmpBuffer = entry;
                            axisX = FUN_008a6350(entry);
                            axisY = FUN_008a6370(entry);
                            // Pack into a struct and process raw input
                            FUN_0092f190(&tmpBuffer);
                        }
                    }
                }
                if (pDevList != 0) {
                    FUN_009c8f10(pDevList);
                }
            }
        }
    }
}