// FUNC_NAME: EARSObject::initializeDefault
void __thiscall EARSObject::initializeDefault(void)
{
    // Delegates to a more complete initialization function with a zero flag
    // (likely indicates no forced reset or similar)
    this->initializeInternal(0);
}