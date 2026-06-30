// FUNC_NAME: GodfatherGameManager::shutdown
// Address: 0x00735560
// Role: Cleanup/destruction of GodfatherGameManager components. Called from destructor (0x00738430) and another context (0x0072b0b0).
// Sets vtable pointers for sub-objects (offsets 0x3C, 0x48, 0x50, 0x54, 0x58, 0x390, 0x394, 0x3A0, 0x1F30, etc.), 
// then deallocates resources, stops subsystems, and resets the vtable at offset 0x7CC to a sentinel.

void __fastcall GodfatherGameManager::shutdown(GodfatherGameManager* this) {
    int* piVar3;

    // Initialize vtable pointers for the main object and internal components
    // These are likely set to the final overrider vtables (during actual construction they'd be set earlier)
    this->vtable = (int*)&PTR_FUN_00d62d08;                          // +0x00 main vtable
    this->field_0x0f = (int*)&PTR_LAB_00d62cf8;                    // +0x3C
    this->field_0x12 = (int*)&PTR_LAB_00d62cf4;                    // +0x48
    this->field_0x14 = (int*)&PTR_LAB_00d62cf0;                    // +0x50
    this->field_0x15 = (int*)&PTR_LAB_00d62c90;                    // +0x54
    this->field_0x16 = (int*)&PTR_LAB_00d62c28;                    // +0x58
    this->field_0xe4 = (int*)&PTR_LAB_00d62c08;                    // +0x390
    this->field_0xe5 = (int*)&PTR_FUN_00d62bf4;                    // +0x394
    this->field_0xe8 = (int*)&PTR_LAB_00d62bec;                    // +0x3A0
    this->field_0x7cc = (int*)&PTR_LAB_00d62be4;                   // +0x1F30

    // Reference count increments on various global singleton objects
    // (FUN_004086d0 likely increments a reference counter or registers a user)
    FUN_004086d0(&DAT_0112a5e0);
    FUN_004086d0(&DAT_0112a620);

    // Initialize streaming resources? (FUN_008f67c0 with IDs: 0x17,1,5,4,3,2)
    FUN_008f67c0(0x17, this);   // resource group 23
    FUN_008f67c0(1, this);      // resource group 1
    FUN_008f67c0(5, this);      // resource group 5
    FUN_008f67c0(4, this);      // resource group 4
    FUN_008f67c0(3, this);      // resource group 3
    FUN_008f67c0(2, this);      // resource group 2

    // More reference increments on audio / UI globals?
    FUN_004086d0(&DAT_012069f4);
    FUN_004086d0(&this->field_0x7f0.member);    // offset 0x7F0 * 4
    FUN_004086d0(&this->field_0x7f8.member);    // offset 0x7F8
    FUN_004086d0(&this->field_0x7f6.member);    // offset 0x7F6

    // Initialize/clear bit flags? (FUN_00408310 may reset a flag array)
    FUN_00408310(&this->field_0x7f0.member);    // +0x1FC0
    FUN_00408310(&this->field_0x7f8.member);    // +0x1FE0
    FUN_00408310(&this->field_0x7f6.member);    // +0x1FD8
    FUN_00408310(&this->field_0x7f2.member);    // +0x1FC8
    FUN_00408310(&this->field_0x7f4.member);    // +0x1FD0
    FUN_00408310(&this->field_0x834.member);    // +0x20D0
    FUN_00408310(&this->field_0x836.member);    // +0x20D8
    FUN_00408310(&this->field_0x838.member);    // +0x20E0
    FUN_00408310(&this->field_0x83a.member);    // +0x20E8
    FUN_00408310(&this->field_0x83c.member);    // +0x20F0
    FUN_00408310(&this->field_0x83e.member);    // +0x20F8
    FUN_00408310(&this->field_0x7fa.member);    // +0x1FE8
    FUN_00408310(&this->field_0x7fc.member);    // +0x1FF0
    FUN_00408310(&this->field_0x7fe.member);    // +0x1FF8

    // More global ref counting
    FUN_004086d0(&DAT_0112adb8);
    FUN_004086d0(&DAT_0112dd08);
    FUN_004086d0(&DAT_0112ade8);
    FUN_004086d0(&DAT_0112ada8);
    FUN_004086d0(&DAT_0112adc0);
    FUN_004086d0(&DAT_0112ade0);
    FUN_004086d0(&DAT_0112adc8);
    FUN_004086d0(&DAT_0112b36c);
    FUN_004086d0(&DAT_0112e0fc);
    FUN_00408310(&DAT_0112add0);

    // Check flags before shutting down audio? (bit 25 high means audio needs cleanup)
    if (((uint)this->field_0x7d6 >> 0x19 & 1) == 0) {
        char cVar2 = FUN_007f4800();  // possibly check if audio system is active
        if (cVar2 != '\0') {
            FUN_0081cf20(this);       // shutdown audio system
        }
    }

    piVar3 = &this->field_0x1d3;  // +0x74C
    // Cleanup: if pointer is non-null and not a sentinel (0x48?), call its destructor
    if ((this->field_0x1d3 != 0) && (this->field_0x1d3 != 0x48)) {
        (**(code**)(*this + 0x260))();   // virtual call via vtable+0x260
        if (*piVar3 != 0) {
            FUN_004daf90(piVar3);        // deallocate memory
            *piVar3 = 0;
        }
    }

    // Another sub-object cleanup
    if ((*piVar3 != 0) && (*piVar3 != 0x48)) {
        (**(code**)(*this + 0x25c))();   // virtual call via vtable+0x25C
    }

    // Cleanup a flag-based subsystem
    if ((char)this->field_0x847 != '\0') {  // +0x211C
        FUN_004df600();  // shutdown something (maybe debug overlay?)
        *(char*)&this->field_0x847 = 0;
    }

    // Destroy a stored object pointer
    int iVar1 = this->field_0x848;  // +0x2120
    if (iVar1 != 0) {
        FUN_0090c670();    // pre-cleanup
        FUN_009c8eb0(iVar1); // release object
        this->field_0x848 = 0;
    }

    // Deregister this object from a global hash? (hash 0x369ac561)
    FUN_008e9cb0(0x369ac561, this);
    FUN_008ec4d0(this);    // finalize/decrement reference

    // Reset some flags
    if ((((uint)this->field_0x7d6 >> 1 & 1) != 0) && ((*(byte*)((int)this + 0x1f5e) & 1) != 0)) {
        this->field_0x7d7 = this->field_0x7d7 & 0xfffeffff;  // +0x1F5C
    }

    // Check if online/networking is active, if so shutdown
    if (((uint)this->field_0x7d6 >> 0x12 & 1) != 0) {
        FUN_007f47a0();  // shutdown online session?
    }

    // Network packet cleanup: send a reliable packet?
    if (this->field_0x7b9 != 0) {  // +0x1EE4
        FUN_004035f0(this->field_0x7b9, 0x10, &this->field_0x0f); // send with data
        this->field_0x7b9 = 0;
        FUN_007f9340(0, 0); // clear some flag
    }

    // Call a thunk (likely another destructor/cleanup)
    thunk_FUN_006fa060(this);

    // Free two dynamic arrays
    if (this->field_0x9a2 != 0) {  // +0x2688
        FUN_004daf90(&this->field_0x9a2);
    }
    if (this->field_0x9a0 != 0) {  // +0x2680
        FUN_004daf90(&this->field_0x9a0);
    }

    // Global subsystem cleans up
    FUN_00732650();  // shutdown some manager
    FUN_00718940();  // maybe audio/music

    // Free another array
    if (this->field_0x85e != 0) {  // +0x2178
        FUN_004daf90(&this->field_0x85e);
    }

    // Reset callback pointer
    if (this->field_0x846 != 0) {  // +0x2118
        *(int*)(this->field_0x846 + 8) = 0;
        this->field_0x846 = 0;
    }

    // Cleanup two function pointers (callbacks)
    if (this->field_0x842 != 0) {  // +0x2108
        (*(void(*)(int))(this->field_0x845))(this->field_0x842); // note: field_0x845 is likely function ptr
    }
    if (this->field_0x80f != 0) {  // +0x203C
        (*(void(*)(int))(this->field_0x812))(this->field_0x80f);
    }

    // Free more memory
    if (this->field_0x805 != 0) {  // +0x2014
        FUN_004daf90(&this->field_0x805);
    }
    if (this->field_0x803 != 0) {  // +0x200C
        FUN_004daf90(&this->field_0x803);
    }
    if (this->field_0x801 != 0) {  // +0x2004
        FUN_004daf90(&this->field_0x801);
    }

    // Reset the vtable for a sub-object (offset 0x7CC) to a safe sentinel
    this->field_0x7cc = (int*)&PTR_LAB_00d61acc;  // +0x1F30

    // Global final cleanup (e.g., release handles)
    FUN_008079c0();
    return;
}