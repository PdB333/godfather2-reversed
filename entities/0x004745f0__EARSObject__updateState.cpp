// FUNC_NAME: EARSObject::updateState
bool __fastcall EARSObject::updateState(int *this)
{
    bool result = false;

    // Check if pointer at offset +0x3a (0xE8) is null
    if (this[0x3a] == 0) {
        // Call vtable function at offset 0x24 (virtual method index 9)
        (*(void (__thiscall **)(int *))(*this + 0x24))(this);
    }

    // If pointer is non-null, external condition holds, and a flag at +0xa5 is set
    if ((this[0x3a] != 0) &&
        (isStateActive() != 0) &&
        (*(char *)((int)this + 0xa5) != 0)) {

        char condA = checkSubConditionA(this[0x3a], this + 0x48);
        char condB = checkSubConditionB(this[0x3a], this[0x4c]);
        result = (condB != 0 && condA != 0);

        notifyGlobalStateChange(&gStateManager);
    }

    return result;
}