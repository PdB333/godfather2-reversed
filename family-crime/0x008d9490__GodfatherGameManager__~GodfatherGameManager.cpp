// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
void __fastcall GodfatherGameManager::~GodfatherGameManager(unsigned int* this)
{
    int* piVar1;
    int iVar2;
    int* piVar3;

    // Set main vtable pointer (class vtable)
    this[0] = &PTR_FUN_00d7dcb0;

    // Set vtable pointers for embedded sub-objects (offsets in dwords)
    this[0xf] = &PTR_LAB_00d7dca0;  // +0x3C
    this[0x12] = &PTR_LAB_00d7dc9c; // +0x48
    this[0x14] = &PTR_LAB_00d7dc98; // +0x50
    this[0x15] = &PTR_LAB_00d7dc38; // +0x54
    this[0x16] = &PTR_LAB_00d7dbd0; // +0x58

    // Initialize global/static containers
    FUN_004086d0(&DAT_0120e93c);   // Possibly vector<string> or manager list
    FUN_004086d0(&DAT_012069c4);
    FUN_004086d0(this + 0x74);    // +0x1D0 (some data structure)
    FUN_00408310(this + 0x74);    // resize/init
    FUN_004086d0(this + 0x76);    // +0x1D8
    FUN_00408310(this + 0x76);
    FUN_004086d0(&DAT_0112a628);
    FUN_004086d0(&DAT_0112a5c4);
    FUN_004086d0(&DAT_0112adf0);

    piVar1 = this + 0x6c; // +0x1B0

    // Destroy sub-object at offset +0x1B0 if non-null and not a special marker
    if ((this[0x6c] != 0) && (this[0x6c] != 0x48)) {
        if (*piVar1 == 0) {
            piVar3 = (int*)0x0;
        } else {
            // Recover base of embedded object (subtract 0x48 for vtable/header)
            piVar3 = (int*)(*piVar1 - 0x48);
        }
        // Call virtual destructor at vtable offset 0x18
        (**(code**)(*piVar3 + 0x18))();
        if (*piVar1 == 0) {
            iVar2 = 0;
        } else {
            iVar2 = *piVar1 - 0x48;
        }
        FUN_004088c0(iVar2 + 0x3c); // Additional cleanup at +0x3C within sub-object
    }

    // Release audio/stream resources at +0x200 and +0x204
    if (this[0x80] != 0) {
        FUN_004df600(); // e.g., releaseStream
    }
    if (this[0x81] != 0) {
        FUN_004df600();
    }

    // Call function pointers for callback cleanup
    if (this[0x93] != 0) { // +0x24C
        (*(code*)this[0x96])(this[0x93]); // call funptr at +0x258 with data at +0x24C
    }
    if (this[0x8f] != 0) { // +0x23C
        (*(code*)this[0x92])(this[0x8f]); // call funptr at +0x248 with data at +0x23C
    }
    if (this[0x8b] != 0) { // +0x22C
        FUN_004daf90(this + 0x8b); // operator delete on smart pointer at +0x22C
    }
    if (this[0x89] != 0) { // +0x224
        FUN_004daf90(this + 0x89);
    }

    // Explicitly clear and release audio streams
    iVar2 = this[0x81];
    if (iVar2 != 0) {
        *(unsigned int*)(iVar2 + 8) = 0; // mark as null/invalid
        this[0x81] = 0;
    }
    iVar2 = this[0x80];
    if (iVar2 != 0) {
        *(unsigned int*)(iVar2 + 8) = 0;
        this[0x80] = 0;
    }

    // Destroy containers at +0x1B8 and +0x1B0
    if (this[0x6e] != 0) { // +0x1B8
        FUN_004daf90(this + 0x6e);
    }
    if (*piVar1 != 0) { // +0x1B0
        FUN_004daf90(piVar1);
    }

    // Final cleanup function (maybe static destruction)
    FUN_008d8620();
    return;
}