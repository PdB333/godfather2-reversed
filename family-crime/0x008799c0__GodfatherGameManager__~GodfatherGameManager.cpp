// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
void __fastcall GodfatherGameManager::destructor(GodfatherGameManager* this)
{
    int* piVar1;
    int iVar2;
    undefined4* puVar3;

    // Reset vtable pointer to base class vtable
    // +0x00: vtable pointer (PTR_FUN_00d767a0)
    *(int**)this = &PTR_FUN_00d767a0;
    // +0x3C (0x0F*4): vtable pointer for some base
    *(void**)((int)this + 0x3C) = &PTR_LAB_00d76790;
    // +0x48 (0x12*4): another vtable
    *(void**)((int)this + 0x48) = &PTR_LAB_00d7678c;
    // +0x50 (0x14*4): ...
    *(void**)((int)this + 0x50) = &PTR_LAB_00d76788;
    // +0x54 (0x15*4)
    *(void**)((int)this + 0x54) = &PTR_LAB_00d76728;
    // +0x58 (0x16*4)
    *(void**)((int)this + 0x58) = &PTR_LAB_00d766c0;
    // +0x2E0 (0xB8*4): another vtable
    *(void**)((int)this + 0x2E0) = &PTR_FUN_00d766ac;
    // +0x2E4 (0xB9*4)
    *(void**)((int)this + 0x2E4) = &PTR_LAB_00d76698;
    // +0x7B0 (0x1EC*4)
    *(void**)((int)this + 0x7B0) = &PTR_FUN_00d76684;

    // Decrement global instance count
    // DAT_0112e010 is a reference counter
    DAT_0112e010 = DAT_0112e010 - 1;

    // Call some cleanup routine
    FUN_008764f0();

    // Call a virtual function via a sub-object at +0xE88 (0x3A2*4)
    // The sub-object's vtable+0x18 entry (function index 6) with argument 0
    (*(void (__thiscall**)(void*, int))(*(int*)(*((int*)this + 0x3A2)) + 0x18))((void*)*((int*)this + 0x3A2), 0);

    // Release or destroy sub-objects at +0x32F, +0x32E, +0x32D (offsets 0xCBC, 0xCB8, 0xCB4)
    if (*(int*)((int)this + 0xCC4) != 0) {
        FUN_005f72f0(*(int*)((int)this + 0xCC4));
    }
    if (*(int*)((int)this + 0xCC0) != 0) {
        FUN_005f72f0(*(int*)((int)this + 0xCC0));
    }
    if (*(int*)((int)this + 0xCBC) != 0) {
        FUN_005f72f0(*(int*)((int)this + 0xCBC));
    }

    FUN_008783d0();

    // Release resources at +0x281-0x283
    if (*(int*)((int)this + 0xA04) != 0) {
        FUN_004df600();
    }
    if (*(int*)((int)this + 0xA08) != 0) {
        FUN_004df600();
    }
    if (*(int*)((int)this + 0xA0C) != 0) {
        FUN_004df600();
    }

    FUN_00876b50();

    // Call virtual destructors on two sub-objects at +0x2A7 and +0x2A8
    if (*(void**)((int)this + 0xA9C) != (void*)0x0) {
        (*(void (__thiscall**)(void*, int))(**(int**)((int)this + 0xA9C)))(*(void**)((int)this + 0xA9C), 1);
    }
    if (*(void**)((int)this + 0xAA0) != (void*)0x0) {
        (*(void (__thiscall**)(void*, int))(**(int**)((int)this + 0xAA0)))(*(void**)((int)this + 0xAA0), 1);
    }

    // Call base class destructor
    FUN_0081cf20(this);

    // Remove this object from two lists/tables (indices 0xF and 0x12)
    FUN_008f67c0(0xF, this);
    FUN_008f67c0(0x12, this);

    // Construct (or destruct?) three objects at +0x2E5, +0x2E7, +0x2E9
    // These are likely POD types with constructors/destructors
    FUN_004086d0((int)this + 0xB94);  // offset 0x2E5*4=0xB94
    FUN_004086d0((int)this + 0xB9C);  // offset 0x2E7*4=0xB9C
    FUN_004086d0((int)this + 0xBA4);  // offset 0x2E9*4=0xBA4
    FUN_00408310((int)this + 0xB94);
    FUN_00408310((int)this + 0xB9C);
    FUN_00408310((int)this + 0xBA4);

    // Initialize global data structures
    FUN_004086d0(&DAT_0112e104);
    FUN_004086d0(&DAT_0112adf8);
    FUN_004086d0(&DAT_0112e0f4);
    FUN_004086d0(&DAT_0112e054);
    FUN_004086d0(&DAT_0112e04c);
    FUN_004086d0(&DAT_0112e124);
    FUN_004086d0(&DAT_0112e064);
    FUN_00408310((int)this + 0xBAC);  // +0x2EB*4=0xBAC
    FUN_004086d0(&DAT_0112dfcc);
    FUN_004086d0(&DAT_0112dfc4);
    FUN_004086d0(&DAT_0112e038);
    FUN_004086d0(&DAT_0112b36c);
    FUN_004086d0(&DAT_0112e020);
    FUN_00408310(&DAT_0112e020);
    FUN_004086d0((int)this + 0xBB4);  // +0x2ED*4=0xBB4
    FUN_00408310((int)this + 0xBB4);

    // Call virtual destructor on sub-object at +0x39F (offset 0xE7C)
    if (*(void**)((int)this + 0xE7C) != (void*)0x0) {
        (*(void (__thiscall**)(void*, int))(**(int**)((int)this + 0xE7C)))(*(void**)((int)this + 0xE7C), 1);
    }

    // Destroy an array of 4 items at +0x2F0 (offset 0xBC0)
    puVar3 = (undefined4*)((int)this + 0xBC0);
    iVar2 = 4;
    do {
        FUN_0045edc0(puVar3);
        puVar3 = puVar3 + 0xC;  // each item is 12 bytes (0xC)
        iVar2 = iVar2 + -1;
    } while (iVar2 != 0);

    // Unregister this object from global manager with magic number 0xa5975eb2
    FUN_008e9cb0(0xa5975eb2, this);
    // Call another destructor
    FUN_008ec4d0(this);

    // Destroy an array of 3 items at +0x3C1 (offset 0xF04) backwards
    puVar3 = (undefined4*)((int)this + 0xF04);  // +0x3C1*4 = 0xF04
    iVar2 = 3;
    do {
        piVar1 = (int*)(puVar3 - 3);  // offset -0xC = 12 bytes back
        puVar3 = puVar3 - 3;
        if (*piVar1 != 0) {
            FUN_004daf90(puVar3);  // destructor call on the pointer
        }
        iVar2 = iVar2 + -1;
    } while (-1 < iVar2);

    FUN_00857b00();

    // Call function pointers at +0x39B, +0x397 (via +0x39E, +0x39A)
    if (*(int*)((int)this + 0xE6C) != 0) {
        (*(void (__thiscall**)(void*, int))*(int*)((int)this + 0xE78))(*(void*)((int)this + 0xE6C));
    }
    if (*(int*)((int)this + 0xE5C) != 0) {
        (*(void (__thiscall**)(void*, int))*(int*)((int)this + 0xE68))(*(void*)((int)this + 0xE5C));
    }

    // Destroy object at +0x395
    if (*(int*)((int)this + 0xE54) != 0) {
        FUN_004daf90((int)this + 0xE54);
    }

    // Destroy array of 7 items at +0x381 (offset 0xE04) backwards
    puVar3 = (undefined4*)((int)this + 0xE04);  // +0x381*4 = 0xE04
    iVar2 = 7;
    do {
        piVar1 = (int*)(puVar3 - 2);  // offset -8 bytes
        puVar3 = puVar3 - 2;
        if (*piVar1 != 0) {
            FUN_004daf90(puVar3);
        }
        iVar2 = iVar2 + -1;
    } while (-1 < iVar2);

    // Clear references to four objects at +0x2DE, +0x2DD, +0x2DC, +0x2DB
    if (*(int*)((int)this + 0xB78) != 0) {
        *(int*)(*(int*)((int)this + 0xB78) + 8) = 0;
        *(int*)((int)this + 0xB78) = 0;
    }
    if (*(int*)((int)this + 0xB74) != 0) {
        *(int*)(*(int*)((int)this + 0xB74) + 8) = 0;
        *(int*)((int)this + 0xB74) = 0;
    }
    if (*(int*)((int)this + 0xB70) != 0) {
        *(int*)(*(int*)((int)this + 0xB70) + 8) = 0;
        *(int*)((int)this + 0xB70) = 0;
    }
    if (*(int*)((int)this + 0xB6C) != 0) {
        *(int*)(*(int*)((int)this + 0xB6C) + 8) = 0;
        *(int*)((int)this + 0xB6C) = 0;
    }

    // Call destructor on object at +0x28F via function pointer at +0x292
    if (*(int*)((int)this + 0xA3C) != 0) {
        (*(void (__thiscall**)(void*, int))*(int*)((int)this + 0xA48))(*(void*)((int)this + 0xA3C));
    }

    // Clear three more references at +0x283, +0x282, +0x281
    if (*(int*)((int)this + 0xA0C) != 0) {
        *(int*)(*(int*)((int)this + 0xA0C) + 8) = 0;
        *(int*)((int)this + 0xA0C) = 0;
    }
    if (*(int*)((int)this + 0xA08) != 0) {
        *(int*)(*(int*)((int)this + 0xA08) + 8) = 0;
        *(int*)((int)this + 0xA08) = 0;
    }
    if (*(int*)((int)this + 0xA04) != 0) {
        *(int*)(*(int*)((int)this + 0xA04) + 8) = 0;
        *(int*)((int)this + 0xA04) = 0;
    }

    // Final cleanup routines
    FUN_008805e0();
    FUN_0055b1d0();
    return;
}