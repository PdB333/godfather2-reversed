// FUNC_NAME: TimerManager::~TimerManager
void __fastcall TimerManager::~TimerManager(undefined4 *this)
{
    int objWithFlag; // param_1[0xd8]
    undefined4 *timerData; // reused for each timer slot
    char globalCheck; // result from global function

    // Set up vtable pointers for base sub-objects/components
    *this = &PTR_FUN_00e39808;                    // +0x00: primary vtable
    this[0xf] = &PTR_LAB_00e39a64;                // +0x3C: vtable for subobject at offset 0x3C
    this[0x12] = &PTR_LAB_00e39a74;               // +0x48
    this[0x14] = &PTR_LAB_00e39a78;               // +0x50
    this[0x15] = &PTR_LAB_00e39a80;               // +0x54
    this[0x16] = &PTR_LAB_00e39ae0;               // +0x58
    this[0xb8] = &PTR_LAB_00e39b44;               // +0x2E0
    this[0xb9] = &PTR_LAB_00e39b58;               // +0x2E4

    // Check a global flag via function pointer
    globalCheck = ((code *)PTR_FUN_00e399a0)();
    if (globalCheck != '\0')
    {
        objWithFlag = this[0xd8];                 // +0x360: pointer to some tracked object
        if (objWithFlag != 0 && *(int *)(objWithFlag + 8) != 0)
        {
            FUN_009ec070(objWithFlag);
        }
    }

    // Process multiple timer/callback structures.
    // Each structure at an offset in this has the layout:
    //   +0: function pointer (vtable/callback)
    //   +2: short current count (how many references remain)
    //   +6: short remaining time (ticks until callback fires)
    // When the timer expires (time reaches 0), the callback is invoked with argument 1.
    // Offsets used: 0xdd, 0xe2, 0xe1, 0xda, 0xdf, 0xe0, 0xde, 0xe3
    // Corresponding byte offsets: 0x374, 0x388, 0x384, 0x368, 0x37C, 0x380, 0x378, 0x38C

    timerData = (undefined4 *)this[0xdd];          // +0x374
    if (*(short *)(timerData + 1) != 0)            // count > 0 ?
    {
        *(short *)((int)timerData + 6) = *(short *)((int)timerData + 6) - 1;
        if (*(short *)((int)timerData + 6) == 0)
        {
            (**(code **)*timerData)(1);
        }
    }

    timerData = (undefined4 *)this[0xe2];          // +0x388
    if (*(short *)(timerData + 1) != 0)
    {
        *(short *)((int)timerData + 6) = *(short *)((int)timerData + 6) - 1;
        if (*(short *)((int)timerData + 6) == 0)
        {
            (**(code **)*timerData)(1);
        }
    }

    timerData = (undefined4 *)this[0xe1];          // +0x384
    if (*(short *)(timerData + 1) != 0)
    {
        *(short *)((int)timerData + 6) = *(short *)((int)timerData + 6) - 1;
        if (*(short *)((int)timerData + 6) == 0)
        {
            (**(code **)*timerData)(1);
        }
    }

    timerData = (undefined4 *)this[0xda];          // +0x368
    if (*(short *)(timerData + 1) != 0)
    {
        *(short *)((int)timerData + 6) = *(short *)((int)timerData + 6) - 1;
        if (*(short *)((int)timerData + 6) == 0)
        {
            (**(code **)*timerData)(1);
        }
    }

    timerData = (undefined4 *)this[0xdf];          // +0x37C
    if (*(short *)(timerData + 1) != 0)
    {
        *(short *)((int)timerData + 6) = *(short *)((int)timerData + 6) - 1;
        if (*(short *)((int)timerData + 6) == 0)
        {
            (**(code **)*timerData)(1);
        }
    }

    timerData = (undefined4 *)this[0xe0];          // +0x380
    if (*(short *)(timerData + 1) != 0)
    {
        *(short *)((int)timerData + 6) = *(short *)((int)timerData + 6) - 1;
        if (*(short *)((int)timerData + 6) == 0)
        {
            (**(code **)*timerData)(1);
        }
    }

    timerData = (undefined4 *)this[0xde];          // +0x378
    if (*(short *)(timerData + 1) != 0)
    {
        *(short *)((int)timerData + 6) = *(short *)((int)timerData + 6) - 1;
        if (*(short *)((int)timerData + 6) == 0)
        {
            (**(code **)*timerData)(1);
        }
    }

    timerData = (undefined4 *)this[0xe3];          // +0x38C
    if (*(short *)(timerData + 1) != 0)
    {
        *(short *)((int)timerData + 6) = *(short *)((int)timerData + 6) - 1;
        if (*(short *)((int)timerData + 6) == 0)
        {
            (**(code **)*timerData)(1);
        }
    }

    // Special case: handle timer slot at offset 0xcc (+0x330)
    if (this[0xcc] != 0)
    {
        FUN_00557020();                            // additional cleanup for this slot
        timerData = (undefined4 *)this[0xcc];
        if (*(short *)(timerData + 1) != 0)
        {
            *(short *)((int)timerData + 6) = *(short *)((int)timerData + 6) - 1;
            if (*(short *)((int)timerData + 6) == 0)
            {
                (**(code **)*timerData)(1);
            }
        }
        this[0xcc] = 0;                            // clear the pointer
    }

    // Restore vtable pointers to purecall/default
    this[0xb9] = &PTR___purecall_00e3924c;        // +0x2E4
    this[0xb8] = &PTR_LAB_00dc3dd4;               // +0x2E0

    // Final destruction step
    FUN_00542920();
}