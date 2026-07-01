// FUNC_NAME: SomeClass::getParentClass
int* __thiscall SomeClass::getParentClass(int this) {
    // Check if pointer at offset +0xFC is non-null
    if (*(int**)(this + 0xFC) != nullptr) {
        // Return pointer at offset +0xFC adjusted by -0x48 (i.e., base offset)
        return (int*)(*(int*)(this + 0xFC) - 0x48);
    }
    return nullptr;
}