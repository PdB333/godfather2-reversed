// FUNC_NAME: GameManager::initInternalComponents
void __fastcall GameManager::initInternalComponents(void* thisPtr)
{
    // Set vtable pointers at known offsets
    *((int**)thisPtr) = (int*)0x00d7ff08; // vtable 0
    *((int**)thisPtr + 0xf) = (int*)0x00d7fef8; // offset 0x3C (15*4)
    *((int**)thisPtr + 0x12) = (int*)0x00d7fef4; // offset 0x48 (18*4)

    // Initialize sub-object at offset 0x50 (20*4) and offset 0x60 (24*4)
    FUN_004086d0(thisPtr + 0x50);
    FUN_00408310(thisPtr + 0x50);
    FUN_004086d0(thisPtr + 0x60);
    FUN_00408310(thisPtr + 0x60);

    // Initialize sub-object at offset 0x58 (22*4)
    FUN_00408310(thisPtr + 0x58);

    // Initialize an array of 8 items starting at offset 0x184 (0x61*4)
    int* arrayBase = (int*)thisPtr + 0x61;
    int count = 8;
    do {
        FUN_00408310(arrayBase - 2);  // Initialize previous slot
        FUN_004086d0(arrayBase);      // Construct current slot
        FUN_00408310(arrayBase);      // Initialize current slot
        arrayBase += 1;               // Move to next 4-byte slot
        count--;
    } while (count != 0);

    // Final initialization call
    FUN_0046c640();
}