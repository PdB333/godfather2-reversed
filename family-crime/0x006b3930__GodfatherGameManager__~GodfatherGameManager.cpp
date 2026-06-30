// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
void __fastcall GodfatherGameManager::~GodfatherGameManager(undefined4 *this)
{
    int iVar1;
    undefined4 local_c;
    undefined4 *local_8;
    char local_4;

    // Set vtable pointers (base and derived)
    *this = &PTR_LAB_00d5e2a4;  // +0x00 vtable ptr
    this[1] = &PTR_LAB_00d5e294; // +0x04 vtable ptr

    // Clean up a linked list of nodes (e.g., pending actions or entities)
    iVar1 = this[0x3d]; // +0xF4: count or head pointer
    while (iVar1 != 0) {
        if (*(int *)this[0x3c] == 0) { // +0xF0: list head
            iVar1 = 0;
        } else {
            iVar1 = *(int *)this[0x3c] + -0x48; // subtract node size (0x48)
        }
        FUN_008e6320(iVar1, 0xffffffff); // release node (e.g., free)
        iVar1 = this[0x3d]; // re-read count
    }

    // Release global singletons
    FUN_004086d0(&DAT_012069c4); // decrement refcount for global1
    FUN_004086d0(&DAT_0112a640); // decrement refcount for global2

    // Cleanup self-reference (likely a global singleton back-pointer)
    local_c = DAT_0112a638; // e.g., global singleton reference
    local_4 = 0;
    local_8 = this;
    FUN_00408a00(&local_c, 0); // release self-reference

    FUN_004086d0(&DAT_0112fe38); // decrement refcount for global3

    // Destroy sub-objects via explicit destructor calls
    if (this[0x65] != 0) { // +0x194
        FUN_004daf90(this + 0x65); // destroy subobject A
    }
    if (this[0x60] != 0) { // +0x180
        *(undefined4 *)(this[0x60] + 8) = 0; // clear weak pointer
        this[0x60] = 0;
    }
    if (this[0x5f] != 0) { // +0x17C
        *(undefined4 *)(this[0x5f] + 8) = 0;
        this[0x5f] = 0;
    }

    // Destroy subobjects that have function pointers (virtual destructors)
    if (this[0x57] != 0) { // +0x15C
        (*(code *)this[0x5a])(this[0x57]); // +0x168 function ptr
    }
    if (this[0x53] != 0) { // +0x14C
        (*(code *)this[0x56])(this[0x53]); // +0x158
    }
    if (this[0x4f] != 0) { // +0x13C
        (*(code *)this[0x52])(this[0x4f]); // +0x148
    }
    if (this[0x4b] != 0) { // +0x12C
        (*(code *)this[0x4e])(this[0x4b]); // +0x138
    }
    if (this[0x47] != 0) { // +0x11C
        (*(code *)this[0x4a])(this[0x47]); // +0x128
    }
    if (this[0x43] != 0) { // +0x10C
        (*(code *)this[0x46])(this[0x43]); // +0x118
    }

    // Shutdown internal subsystems
    FUN_006b3540(); // e.g., TerminateSystem

    // Release remaining subobjects (with function ptrs)
    if (this[0x38] != 0) { // +0xE0
        (*(code *)this[0x3b])(this[0x38]); // +0xEC
    }

    // Release safe-pointer references
    if (this[0x2d] != 0) { // +0xB4
        FUN_009c8f10(this[0x2d]); // Release
    }
    if (this[0x2a] != 0) { // +0xA8
        FUN_009c8f10(this[0x2a]);
    }
    if (this[0x27] != 0) { // +0x9C
        FUN_009c8f10(this[0x27]);
    }
    if (this[0x24] != 0) { // +0x90
        FUN_009c8f10(this[0x24]);
    }
    if (this[0x21] != 0) { // +0x84
        FUN_009c8f10(this[0x21]);
    }

    // Final global cleanup
    FUN_004083d0(); // e.g., GlobalDecrementRef
    return;
}