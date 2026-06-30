// FUNC_NAME: EarsBase::internalUpdate

void __thiscall EarsBase::internalUpdate(void *this, int additionalArg) {
    // Calls FUN_004a0cd0 with two pointers from this object (offsets +0xf0 and +0x100)
    // and a global constant (likely a callback or event type)
    FUN_004a0cd0((int)this + 0x100, (int)this + 0xf0, additionalArg, &DAT_00e2e358);
}