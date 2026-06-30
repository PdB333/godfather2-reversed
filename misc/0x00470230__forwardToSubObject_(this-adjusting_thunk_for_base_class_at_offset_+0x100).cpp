// FUNC_NAME: forwardToSubObject (this-adjusting thunk for base class at offset +0x100)
void __thiscall forwardToSubObject(void* this, int param2, int param3) {
    // Adjust 'this' by +0x100 to point to the base class sub-object, then call the real implementation.
    // The real implementation is at FUN_00470130 (base class method).
    FUN_00470130(static_cast<uint8_t*>(this) + 0x100, param2, param3);
}