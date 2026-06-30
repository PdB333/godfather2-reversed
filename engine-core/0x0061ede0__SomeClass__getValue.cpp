// FUNC_NAME: SomeClass::getValue
int __thiscall SomeClass::getValue(void) {
    // Check if the initialization flag at offset +0x23 is zero.
    // If not initialized, call the initialization routine.
    if (*(char*)((int)this + 0x23) == '\0') {
        FUN_0061e810(this);
    }
    // Return the value at offset 0 (first member of the object).
    return *(int*)this;
}