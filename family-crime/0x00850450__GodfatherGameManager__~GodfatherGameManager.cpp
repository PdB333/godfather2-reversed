// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager

void __fastcall GodfatherGameManager::~GodfatherGameManager(int *this) // __fastcall: ecx = this
{
    char flag;
    int localString[1]; // Actually a string struct, but we'll treat as ints
    int local8;
    char local4;

    // Set vtable pointers to base class or deleted-state vtables
    *this = (int)&PTR_GodfatherGameManagerVtable; // +0x00
    this[0xf] = (int)&PTR_GodfatherGameManager_Offset0x3C_Vtable; // +0x3C
    this[0x12] = (int)&PTR_GodfatherGameManager_Offset0x48_Vtable; // +0x48

    // Check some global flag (e.g., initialization flag)
    flag = FUN_00402080(&DAT_0112ddd8);
    if (flag != '\0') {
        // If flag set, release and nullify a global string/data
        FUN_004086d0(&DAT_0112ddd8); // Release (like freeString)
        localString[0] = DAT_0112dde8;
        local8 = 0;
        local4 = 0;
        FUN_00408a00(localString, 0); // Assign null or clear
    }

    // Release various global memory/data structures
    FUN_004086d0(&DAT_0112ddf0);
    FUN_004086d0(&DAT_0112ddf8);
    FUN_004086d0(&DAT_01129aa0);
    FUN_00408310(&DAT_0112ddf0); // Possibly delete[] or freeArray
    FUN_00408310(&DAT_0112ddf8);
    FUN_004086d0(&DAT_01129a7c);
    FUN_004086d0(&DAT_01129a84);
    FUN_00408310(&DAT_0112ddd8);
    FUN_00408310(&DAT_0112dde0);
    FUN_00408310(&DAT_0112dde8);
    FUN_00408310(&DAT_0112ddc4);
    FUN_00408310(&DAT_0112ddd0);
    FUN_004086d0(&DAT_01218020);
    FUN_00408310(&DAT_01218020);
    FUN_004086d0(&DAT_01218028);
    FUN_00408310(&DAT_01218028);

    // Release member objects at offsets 0x50, 0x58
    FUN_004086d0(this + 0x14); // this+0x50
    FUN_00408310(this + 0x14); // delete array if any
    FUN_00408310(this + 0x16); // this+0x58

    // More global releases
    FUN_004086d0(&DAT_01206940);
    FUN_004086d0(&DAT_012069c4);
    FUN_004086d0(&DAT_012069b4);
    FUN_004086d0(&DAT_0120685c);

    // Delete allocated objects if non-null
    if (this[0x26] != 0) { // offset 0x98
        FUN_004b4280(this[0x26]); // deleteObject
        this[0x26] = 0;
    }
    if (this[0x20] != 0) { // offset 0x80
        FUN_004035f0(this[0x20], 0x1ff, this + 0xf); // deleteWithSize (0x1ff bytes)
        this[0x20] = 0;
    }
    if (this[0x1c] != 0) { // offset 0x70
        (*(void (**)(int))this[0x1f])(this[0x1c]); // call virtual destructor? this[0x1f] is likely vtable+offset
    }
    if (this[0x18] != 0) { // offset 0x60
        (*(void (**)(int))this[0x1b])(this[0x18]); // similar
    }

    // Final global cleanup (e.g., shutdown manager)
    FUN_0046c640();
}