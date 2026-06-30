// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
void __fastcall GodfatherGameManager::destructor(GodfatherGameManager* this)
{
    int* piVar1;
    int iVar2;
    int* piVar3;

    // Set vtable to destructing state
    this->vtable = &VTABLE_Destructing; // +0x00

    // Deallocate large member at offset 0x241e (9246)
    if (this->field_0x241e != 0) {
        deallocateMemory(this->field_0x241e);
    }

    // Run engine cleanup steps 10 times (likely per-frame cleanup)
    iVar2 = 9;
    do {
        engineCleanupStep1();
        engineCleanupStep2();
        iVar2 = iVar2 - 1;
    } while (iVar2 >= 0);

    // Deallocate members at offsets 0x206b, 0x2068
    if (this->field_0x206b != 0) {
        deallocateMemory(this->field_0x206b);
    }
    if (this->field_0x2068 != 0) {
        deallocateMemory(this->field_0x2068);
    }

    // Iterate over 128 pairs of pointers starting at offset 0x2099
    // Each pair is spaced by 0x3e (62) bytes, with first pointer at -0x3b (59) from base
    iVar2 = 0x7f;
    piVar3 = &this->field_0x2099;
    do {
        piVar1 = piVar3 - 0x3b; // First pointer in pair
        piVar3 = piVar3 - 0x3e; // Move to next pair base
        if (*piVar1 != 0) {
            deallocateMemory(*piVar1);
        }
        if (*piVar3 != 0) {
            deallocateMemory(*piVar3);
        }
        iVar2 = iVar2 - 1;
    } while (iVar2 >= 0);

    // Deallocate member at offset 0x15d
    if (this->field_0x15d != 0) {
        deallocateMemory(this->field_0x15d);
    }

    // Destroy sub-object at offset 0x116
    destructSubObject(&this->field_0x116);

    // Deallocate members at offsets 0x10f, 0x10c, 0x103, 0x100, 0xf7, 0xf4, 0xeb, 0xe8
    if (this->field_0x10f != 0) {
        deallocateMemory(this->field_0x10f);
    }
    if (this->field_0x10c != 0) {
        deallocateMemory(this->field_0x10c);
    }
    if (this->field_0x103 != 0) {
        deallocateMemory(this->field_0x103);
    }
    if (this->field_0x100 != 0) {
        deallocateMemory(this->field_0x100);
    }
    if (this->field_0xf7 != 0) {
        deallocateMemory(this->field_0xf7);
    }
    if (this->field_0xf4 != 0) {
        deallocateMemory(this->field_0xf4);
    }
    if (this->field_0xeb != 0) {
        deallocateMemory(this->field_0xeb);
    }
    if (this->field_0xe8 != 0) {
        deallocateMemory(this->field_0xe8);
    }

    // Destroy sub-objects at offsets 0xa5, 100, 0x23
    destructSubObject(&this->field_0xa5);
    destructSubObject(&this->field_100);
    destructSubObject(&this->field_0x23);

    // Call a function pointer stored at offset 0x7 on member at offset 0x4
    if (this->field_0x4 != 0) {
        ((void (*)(void*))this->field_0x7)(this->field_0x4);
    }

    // Set vtable to deleted state
    this->vtable = &VTABLE_Deleted; // +0x00

    // Clear global alive flag
    g_objectAliveFlag = 0;
}