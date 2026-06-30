// FUNC_NAME: SomeClass::setInitializedFlag
void __thiscall SomeClass::setInitializedFlag() {
    // +0x228: initialization flag (0 = not initialized, 1 = initialized)
    if (*(int *)((int)this + 0x228) == 0) {
        *(int *)((int)this + 0x228) = 1;
    }
}