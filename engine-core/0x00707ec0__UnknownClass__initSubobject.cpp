// FUNC_NAME: UnknownClass::initSubobject
// Function at 0x00707ec0: Delegates initialization of a subobject at this+0x198.
// Likely a member function that calls a constructor or setup routine for a subcomponent.
void UnknownClass::initSubobject() {
    // Call the subobject initializer at offset 0x198.
    FUN_00707520(reinterpret_cast<char*>(this) + 0x198);
}