// FUNC_NAME: InputDeviceManager::update
void __thiscall InputDeviceManager::update(void *thisParam, int param_1)
{
    uint flags;
    char cVar2;
    int iVar3;
    uint uVar4;
    uint uVar5;
    uint *pSlotFlags;
    undefined *pPendingEntry;
    int iLoop;
    uint *pSlotFlags2;
    uint *pSlotFlagsArray;

    // Initialize 16 controller slots (each 0x74 bytes)
    pSlotFlags = (uint *)&g_controllerSlots; // 0x0119a9d0
    iLoop = 0x10;
    do {
        ControllerSlot::constructor(pSlotFlags); // FUN_0059b560
        pSlotFlags = pSlotFlags + 0x1D; // 0x74 / 4 = 0x1D
        iLoop = iLoop + -1;
    } while (iLoop != 0);

    g_isProcessing = 1; // DAT_0120551f

    // Process pending controller entries (if any)
    if ((((g_pendingEntryCount != 0) && ((**(code **)(*g_pendingManager + 4))(), 0 < g_pendingEntryCount)) &&
        (g_pendingEntryType == '\0')) && (iLoop = 0, 0 < g_pendingEntryCount)) {
        pPendingEntry = &g_pendingEntries; // 0x01221480
        do {
            iVar3 = PendingEntry::isReady(); // FUN_00597000
            if (iVar3 != 0) {
                iVar3 = *g_pendingManager; // DAT_012055a4 (vtable pointer)
                uVar4 = PendingEntry::createController(pPendingEntry); // FUN_00597370
                (**(code **)(iVar3 + 0x24))(uVar4); // virtual call at offset 0x24
                g_pendingEntryCount = g_pendingEntryCount + -1;
                (**(code **)(*g_pendingManager + 0x10))(pPendingEntry, &g_pendingEntries + g_pendingEntryCount * 0x50, 0x50);
                iLoop = iLoop + -1;
                pPendingEntry = pPendingEntry + -0x50;
            }
            iLoop = iLoop + 1;
            pPendingEntry = pPendingEntry + 0x50;
        } while (iLoop < g_pendingEntryCount);
    }

    // Update active controller slots
    pSlotFlags2 = (uint *)&g_controllerSlots;
    iLoop = 0x10;
    do {
        iVar3 = iLoop;
        flags = *pSlotFlags2;
        if ((flags & 1) != 0) {
            if ((flags & 0x20) == 0) {
                ControllerSlot::update(param_1, pSlotFlags2); // FUN_00599720
            }
            if (((flags & 8) != 0) &&
                (cVar2 = (**(code **)(*g_pendingManager + 0x18))(*(undefined4 *)(pSlotFlags2[1] + 8), 0),
                cVar2 != '\0')) {
                ControllerSlot::requestDisconnect(1, 0); // FUN_005994c0
            }
        }
        pSlotFlags2 = pSlotFlags2 + 0x1D;
        iLoop = iVar3 + -1;
    } while (iLoop != 0);

    // Clear pending disconnect flags for all controller arrays
    uVar4 = iVar3 - 0x22; // 0xFFFFFFDF (~0x20)
    uVar5 = 0;
    do {
        if (((*(uint *)((int)&g_controllerSlots + uVar5) & 1) != 0) &&
            ((*(uint *)((int)&g_controllerSlots + uVar5) & 0x20) != 0)) {
            *(uint *)((int)&g_controllerSlots + uVar5) = *(uint *)((int)&g_controllerSlots + uVar5) & uVar4;
        }
        // Similar for other arrays (g_controllerSlots2, g_controllerSlots3, g_controllerSlots4)
        if (((*(uint *)((int)&g_controllerSlots2 + uVar5) & 1) != 0) &&
            ((*(uint *)((int)&g_controllerSlots2 + uVar5) & 0x20) != 0)) {
            *(uint *)((int)&g_controllerSlots2 + uVar5) = *(uint *)((int)&g_controllerSlots2 + uVar5) & uVar4;
        }
        if (((*(uint *)((int)&g_controllerSlots3 + uVar5) & 1) != 0) &&
            ((*(uint *)((int)&g_controllerSlots3 + uVar5) & 0x20) != 0)) {
            *(uint *)((int)&g_controllerSlots3 + uVar5) = *(uint *)((int)&g_controllerSlots3 + uVar5) & uVar4;
        }
        if (((*(uint *)((int)&g_controllerSlots4 + uVar5) & 1) != 0) &&
            ((*(uint *)((int)&g_controllerSlots4 + uVar5) & 0x20) != 0)) {
            *(uint *)((int)&g_controllerSlots4 + uVar5) = *(uint *)((int)&g_controllerSlots4 + uVar5) & uVar4;
        }
        uVar5 = uVar5 + 0x740; // stride of 0x740 bytes (16 slots * 0x74)
    } while (uVar5 < 0x1d00); // 0x1d00 = 4 arrays * 0x740

    g_isProcessing = 0; // DAT_0120551f
    return;
}