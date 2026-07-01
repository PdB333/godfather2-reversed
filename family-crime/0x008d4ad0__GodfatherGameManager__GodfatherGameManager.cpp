// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
undefined4 * __thiscall GodfatherGameManager::GodfatherGameManager(undefined4 *this, undefined4 initParam) {
    // Call base class constructor (likely SimManager or EARSObject)
    FUN_0046c590(initParam);

    // Set vtable pointer
    *this = &PTR_FUN_00d7d63c; // vtable for GodfatherGameManager

    // Sub-system vtable pointers
    this[0xf] = &PTR_LAB_00d7d62c; // +0x3C: maybe state machine vtable
    this[0x12] = &PTR_LAB_00d7d628; // +0x48: maybe behavior system vtable

    // Initialize various member fields (many are zeroed)
    this[0x14] = 0;                     // +0x50: DWORD
    *(uint16 *)((byte*)this + 0x54) = 0; // +0x54: WORD (lower half of field at +0x54)
    *(uint16 *)((byte*)this + 0x56) = 0; // +0x56: WORD (upper half of same field?)
    this[0x16] = 0;                     // +0x58: DWORD
    *(uint16 *)((byte*)this + 0x5C) = 0; // +0x5C: WORD
    *(uint16 *)((byte*)this + 0x5E) = 0; // +0x5E: WORD
    *(uint8 *)((byte*)this + 0x60) = 0;  // +0x60: BYTE
    this[0x19] = 0;                     // +0x64: DWORD
    this[0x1a] = 0;                     // +0x68: DWORD
    this[0x1b] = 0;                     // +0x6C: DWORD
    this[0x1c] = 0;                     // +0x70: DWORD
    this[0x1d] = 0;                     // +0x74: DWORD
    this[0x1e] = 0;                     // +0x78: DWORD
    this[0x1f] = 0;                     // +0x7C: DWORD
    this[0x20] = 0;                     // +0x80: DWORD
    this[0x21] = 0;                     // +0x84: DWORD
    this[0x22] = 0;                     // +0x88: DWORD
    this[0x23] = 0;                     // +0x8C: DWORD
    this[0x24] = 0;                     // +0x90: DWORD
    this[0x25] = 0;                     // +0x94: DWORD
    this[0x26] = 0;                     // +0x98: DWORD

    return this;
}