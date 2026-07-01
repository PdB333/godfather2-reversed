// FUNC_NAME: GamePlayLogging::processEvent
void __thiscall GamePlayLogging::processEvent(int thisPtr, int* eventDescriptor, uint eventData, uint eventTime)
{
    bool isEventEnabled;
    undefined8 retAddr;
    int moduleBase;
    int stackBuf[0xD]; // sized 0x34 bytes (13 ints)
    int* pvVar1;
    float fVar1;
    int tempData1;
    int tempData2;
    int tempData3;
    uint cycleIndex;
    int allocPtr1;
    int allocPtr2;
    int allocPtr3;

    // Check if event is enabled for logging via descriptor's static method (hash 0x10e5319e)
    isEventEnabled = (**(code**)(*eventDescriptor + 0x10))(0x10e5319e) != 0;
    if (isEventEnabled && &stackBuf[0] != (int*)0x34) {
        retAddr = *(undefined8*)&stackBuf[13]; // unaff_retaddr, read from stack beyond buffer
        FUN_00878800(stackBuf);
        moduleBase = (int)((ulonglong)retAddr >> 0x20);
        if (eventDescriptor == nullptr) {
            (**(code**)(moduleBase + 0x1c))(stackBuf);
        } else {
            // offset 0x2bc = 700 decimal
            (**(code**)(moduleBase + 700))(stackBuf, eventDescriptor, 1);
        }
        FUN_0083cac0(thisPtr, &retAddr, eventTime);
        FUN_00408bb0(&DAT_0112dc58, tempData1 + 0x3c, stackBuf, 0);

        // Random probability check (offset 0x148 = event threshold)
        int randVal = _rand();
        if ((float)randVal * DAT_00e44590 < *(float*)(thisPtr + 0x148)) {
            // Allocate three 8-byte blocks (likely for string logs)
            allocPtr1 = FUN_006eb670(8);
            allocPtr2 = FUN_006eb670(8);
            allocPtr3 = FUN_006eb670(8);

            FUN_0043b870(DAT_0112ded0);
            // Write to debug stream 0xf (likely debug output)
            FUN_00858cf0(0xf, allocPtr1);
            FUN_00858cf0(0xf, allocPtr2);
            FUN_00858cf0(0xf, allocPtr3);
        }

        // Interpolation cycle (offset 0x150 = start, 0x154 = end)
        cycleIndex = DAT_010c2678 & DAT_012054b4; // mask
        DAT_012054b4 = DAT_012054b4 + 1; // global cycle counter
        fVar1 = *(float*)(thisPtr + 0x150);
        float interpResult = (*(float*)(thisPtr + 0x154) - fVar1) * *(float*)(&DAT_010c2680 + cycleIndex * 4) + fVar1;
        FUN_00875dc0(interpResult);

        // Cleanup allocated stack objects (probably simple destructors)
        if (aiStack_20[0] != 0) {
            FUN_004daf90(aiStack_20);
        }
        if (aiStack_28[0] != 0) {
            FUN_004daf90(aiStack_28);
        }
    }
}