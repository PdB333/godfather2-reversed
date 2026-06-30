// FUNC_NAME: SomeClass::SomeClass
undefined4 __thiscall SomeClass::SomeClass(byte constructionFlags) {
    // Base class constructor call (likely Entity or similar)
    BaseClass::BaseClass();

    // If the low bit of constructionFlags is set, perform additional initialization with value 100
    if ((constructionFlags & 1) != 0) {
        // This likely allocates or sets up internal data (e.g., memory pool or resource size)
        this->additionalInit(100);
    }

    return this;
}