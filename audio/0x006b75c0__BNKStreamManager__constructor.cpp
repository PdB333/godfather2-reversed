// FUNC_NAME: BNKStreamManager::constructor
// Address: 0x006b75c0
// Role: Constructor for BNKStreamManager. Sets up vtables (multiple inheritance), initializes a field, and allocates the global stream buffer pool.

BNKStreamManager* __thiscall BNKStreamManager::constructor(BNKStreamManager* this, int param_2)
{
    // Base class constructor (likely AudioDataManager or similar)
    constructBaseAudioManager(param_2);

    // Primary vtable
    *this = (BNKStreamManager*)&PTR_FUN_00d5e558;

    // Secondary vtables for additional interfaces
    this->field_0x3C = &PTR_LAB_00d5e548;  // +0x3C
    this->field_0x48 = &PTR_LAB_00d5e544;  // +0x48

    // Zero out field at +0xA0
    this->field_0xA0 = 0;                  // +0xA0

    // Initialize the global BNK stream buffer pool (32767 bytes max)
    initStreamBufferPool(&DAT_0120e93c, 0x7fff);

    return this;
}