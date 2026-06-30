// FUNC_NAME: GameUpdate::updateAllSystems
void __cdecl updateAllSystems(void)
{
    int *piVar1;
    undefined4 *puVar2;
    uint uVar3;
    undefined4 *puVar4;
    undefined4 unaff_ESI;
    int iVar5;
    undefined4 *puVar6;
    
    // Iterate over all registered systems and call their update function (vtable offset 0x1c)
    iVar5 = 0;
    if (0 < gSystemCount) {
        do {
            (**(code **)(*(int *)(gpSystemList[iVar5]) + 0x1c))();  // system->update()
            iVar5 = iVar5 + 1;
        } while (iVar5 < gSystemCount);
    }
    
    // Process script callbacks / event queue (two label pointers and unaff_ESI)
    processPendingEvents(&_label_004e3ba0, &_label_004e3bc0, unaff_ESI);
    
    // Process input for all devices (copy device state to active input buffer)
    uVar3 = 0;
    if (gInputDeviceCount != 0) {
        puVar2 = &gInputDeviceStateArray;  // array of device states, each 0xAC bytes
        do {
            // Copy device header info (8 bytes?) into global input state buffer
            gActiveInputState.deviceType = *(undefined2 *)((int)puVar2 + -2);
            gActiveInputState.deviceFlags = *puVar2;
            gActiveInputState.unknown1 = *(undefined2 *)(puVar2 + -1);
            gActiveInputState.unknown2 = puVar2[1];
            puVar4 = puVar2 + 2;
            puVar6 = &gActiveInputState.data[0];  // start of raw data
            for (iVar5 = 0x28; iVar5 != 0; iVar5 = iVar5 + -1) {
                *puVar6 = *puVar4;
                puVar4 = puVar4 + 1;
                puVar6 = puVar6 + 1;
            }
            processInput();  // handle input for this device
            uVar3 = uVar3 + 1;
            puVar2 = puVar2 + 0x2b;  // point to next device state (0x2b * 4 = 0xAC bytes)
        } while (uVar3 < gInputDeviceCount);
    }
    
    // Check for a specific global event/flag (matching some memory pattern)
    uVar3 = 0;
    if (gSpecialEventCount != 0) {
        puVar2 = &gSpecialEventArray;  // array of 12-byte entries
        do {
            if (((undefined1 *)puVar2[-1] == &_label_00505b10) && ((undefined *)*puVar2 == &_data_00505b20)) {
                handleSpecialEvent();  // trigger special action
                break;
            }
            uVar3 = uVar3 + 1;
            puVar2 = puVar2 + 3;  // each entry 12 bytes (3 * 4)
        } while (uVar3 < gSpecialEventCount);
    }
    
    // Update global render state? (modifying vtable pointer)
    piVar1 = (int *)(gSomeObject + 0x14);
    **(undefined4 **)(gSomeObject + 0x14) = &_vtable_01125084;
    *piVar1 = *piVar1 + 4;  // advance vtable pointer?
    
    // Reset frame counters
    resetFrameStats();  // FUN_0052e510
    
    // Clear screen shake / camera offset values
    gScreenShakeX = 0;
    gScreenShakeY = 0;
    gScreenShakeZ = 0;
    gScreenShakeW = 0;
    // Set colors/constants for rendering
    gSomeColorR = _colorData_00e2b118;
    gSomeColorG = _colorData_00e2b1a4;
    gSomeColorB = _colorData_00e446c4;
    gSomeColorA = _colorData_00e2b1a4;
    gSomeOtherValue = 0;
    return;
}