// FUNC_NAME: Player::~Player

// Reconstructed destructor for the Player class (offset 0x006ade20)
// Cleans up all sub-objects, vtable pointers, and performs final shutdown.

void __fastcall Player::~Player(Player* this) // __fastcall, ECX = this
{
    int* piVar1;
    int iVar2;
    int** ppiVar3;
    undefined** local_14;
    int local_10;
    undefined4 local_c;
    undefined*** local_8;
    undefined1 local_4;

    // Set vtable pointers for multiple base classes (Multiple inheritance)
    this->vtable = &PTR_FUN_00d5dca0;                // +0x00: primary vtable
    this->base2Vtable[0] = &PTR_LAB_00d5dc90;       // +0x3C (offset 0xF)
    this->base2Vtable[1] = &PTR_LAB_00d5dc8c;       // +0x48 (0x12)
    this->base2Vtable[2] = &PTR_LAB_00d5dc88;       // +0x50 (0x14)
    this->base2Vtable[3] = &PTR_LAB_00d5dc28;       // +0x54 (0x15)
    this->base2Vtable[4] = &PTR_LAB_00d5dbc0;       // +0x58 (0x16)

    baseDestructor();                                // FUN_006b6eb0: base class shutdown

    // Cleanup sub-object if present (offset 0x60, index 0x60 -> +0x180)
    if (this->subObjectP != 0) {
        local_8 = &local_14;
        local_14 = &PTR_LAB_00d5dbb0;               // some vtable or sentinel
        local_c = DAT_0112a5b4;
        local_4 = 0;
        local_10 = this->subObjectP;                // +0x60
        someReset(&local_c, 0);                      // FUN_00408a00
        someRelease(0);                              // FUN_006b5b80
    }

    destroyBase(this);                               // FUN_006b0890: another base cleanup
    finalizeCleanup(0x14, this);                     // FUN_008f67c0: cleanup with size 20 (0x14)

    // Destroy sub-objects at various offsets (using two different destructors)
    destroyObject(&this->stateMachine1);             // +0x91 (0x244)
    destroyObject(&this->stateMachine2);             // +0x93 (0x24C)
    destroyObject(&this->stateMachine3);             // +0xAB (0x2AC)
    destroyObject(&this->someComponentA);            // +0x8F (0x23C)
    destroyObject(&this->someComponentB);            // +0x97 (0x25C)
    destroyObject(&this->someComponentC);            // +0xA3 (0x28C)
    destroyObject(&this->someComponentD);            // +0xA5 (0x294)

    destroyStateMachine(&this->playerSM0);           // +0x77 (0x1DC) - likely PlayerSM or similar
    destroyStateMachine(&this->stateMachine1);       // +0x91
    destroyStateMachine(&this->stateMachine2);       // +0x93
    destroyStateMachine(&this->someComponentB);      // +0x97
    destroyStateMachine(&this->someComponentE);      // +0x95 (0x254)
    destroyStateMachine(&this->someComponentF);      // +0x9F (0x27C)
    destroyStateMachine(&this->someComponentG);      // +0xA1 (0x284)
    destroyStateMachine(&this->someComponentH);      // +0x9D (0x274)
    destroyStateMachine(&this->someComponentI);      // +0x9B (0x26C)
    destroyStateMachine(&this->stateMachine3);       // +0xAB
    destroyStateMachine(&this->someComponentA);      // +0x8F
    destroyStateMachine(&this->someComponentC);      // +0xA3
    destroyStateMachine(&this->someComponentD);      // +0xA5
    destroyStateMachine(&this->someComponentJ);      // +0xA7 (0x29C)
    destroyStateMachine(&this->someComponentK);      // +0xA9 (0x2A4)

    // Global static destructors
    destroyStateMachine(&DAT_0112a588);
    destroyObject(&DAT_0120e93c);

    baseCleanup();                                   // FUN_006b6d90: another base cleanup

    // Cleanup array of 5 sub-object pairs at offsets 0x6B-0x75
    // Each pair: flag at lower offset, pointer at higher offset
    ppiVar3 = &this->subArray[0].pointer;            // +0x75 (start of array)
    iVar2 = 4;
    do {
        piVar1 = ppiVar3 - 2;                        // flag pointer
        ppiVar3 = ppiVar3 - 2;                      // move to next pair base
        if (*piVar1 != 0) {
            releaseSubObject(ppiVar3 + 2);           // FUN_004daf90 on the pointer part
        }
        iVar2 = iVar2 + -1;
    } while (-1 < iVar2);

    // Delete external object if present (offset 0x66 -> +0x198)
    if (this->externalObject != 0) {
        deleteObject(this->externalObject);          // FUN_009c8f10
    }

    globalPostDestroy();                             // FUN_0046ea20
    return;
}