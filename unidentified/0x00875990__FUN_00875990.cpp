// FUNC_NAME: SomeClass::getIndexedValue
int __thiscall SomeClass::getIndexedValue(int param2) {
    // Virtual function call at vtable offset 0x214 (likely checks validity or modifies param2)
    // The function takes param2 and a pointer to param2 as arguments; returns bool (char)
    char isValid = (this->vtable[0x214 / 4])(param2, &param2);
    
    if (isValid != '\0') {
        // unaff_ESI is likely an uninitialized register; possibly param2 or a hidden parameter.
        // Here we assume it should be param2 (the index). The array is at offset 0x293 * 4 from this.
        return this->someArray[param2 + 0x293]; // offset 0xA4C bytes
    }
    return 0;
}