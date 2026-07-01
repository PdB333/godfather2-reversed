// FUNC_NAME: SomeClass::copyValueToOther
void __thiscall copyValueToOther(void* thisPtr, void* otherPtr) {
    // Retrieve a 4-byte value from the current object (likely an int or pointer)
    int value = this->getSomeValue(); // FUN_00445f00 - extracts field from this
    // Set that value on the target object
    setSomeValue(otherPtr, value); // FUN_00446600 - assigns field on other
}