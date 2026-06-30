// FUNC_NAME: Player::~Player
void __thiscall Player::~Player(Player* this) // offset param_1
{
    int iVar1;
    char local_8[8]; // unused buffer for string copy?

    // Set vtable to current class vtable (destructor may restore it for inheritance chain)
    *this = &PTR_FUN_00d61640; // +0x00: virtual table pointer
    // Set additional vtable pointers for multiple inheritance bases
    this->vtableBase1 = &PTR_LAB_00d61630; // +0x3C
    this->vtableBase2 = &PTR_LAB_00d6162c; // +0x48
    this->vtableBase3 = &PTR_LAB_00d61628; // +0x50
    this->vtableBase4 = &PTR_LAB_00d615c8; // +0x54
    this->vtableBase5 = &PTR_LAB_00d61560; // +0x58

    // Release animated character handle if valid
    if (this->animHandle != -1) { // +0x398 (0xe6*4)
        FUN_0090dff0(this->animHandle);
        this->animHandle = 0xFFFFFFFF;
    }

    // Call base class destructor (likely EARS::Framework::Object)
    FUN_008f67c0(0xd, this);

    // Release various static/dynamic objects
    FUN_004086d0(&DAT_0112ac64);
    FUN_004086d0(&DAT_0112ac5c);
    FUN_004086d0(&DAT_0112ac6c);
    FUN_004086d0(&DAT_0112b36c);
    FUN_004086d0(&this->someList); // +0x388 (0xe2*4)
    FUN_00408310(&this->someList);
    FUN_00408310(&this->someCount); // +0x390 (0xe4*4)
    FUN_004086d0(&DAT_0112ac74);

    // Bitfield check: flags at +0x39E (ushort) & 0x102 (bit 1 and bit 8)
    if ((this->flags & 0x102) != 0 && this->someRelatedPtr != 0) { // +0x6c*4 = +0x1B0
        FUN_009f0250(local_8, 0x2001);
        FUN_0070b2b0();
    }

    // Release attached script/callback object if present
    if (this->scriptObject != 0) { // +0x2D0 (0xb4*4)
        // Call virtual function at index 4 (offset +0x10) on the script object
        (*(code**)this->scriptObject)[4](1);
        this->scriptObject = 0;
    }

    // Global cleanup: remove from manager, etc.
    FUN_004df590();

    // Delete allocated buffers if present
    if (this->bufferA != 0) { // +0x3A0 (0xe8*4)
        FUN_004daf90(this->bufferA);
        this->bufferA = 0;
    }
    if (this->bufferB != 0) { // +0x374 (0xdd*4)
        FUN_004daf90(this->bufferB);
        this->bufferB = 0;
    }

    // Another global cleanup (maybe shutdown sound/UI)
    FUN_004c2390();

    // Release linked list node
    iVar1 = this->nodePointer; // +0x334 (0xcd*4)
    if (iVar1 != 0) {
        // Clear next pointer of the node to prevent linked list corruption
        *(undefined4*)(iVar1 + 8) = 0;
        this->nodePointer = 0;
    }

    // Delete another allocated object
    if (this->someOtherBuffer != 0) { // +0x2D4 (0xb5*4)
        FUN_004daf90(this->someOtherBuffer);
        this->someOtherBuffer = 0;
    }

    // Final cleanup (possibly deregistering from global managers)
    FUN_00708830();
    return;
}