// FUNC_NAME: SomeClass::getPointerAt1BC
// Function at 0x00716430: Accessor that returns a pointer to a sub-object at offset 0x1BC (444 bytes) from `this`.
// Likely returns a pointer to a component or data block stored within the object.
void * __fastcall SomeClass::getPointerAt1BC() const
{
    return reinterpret_cast<void *>(reinterpret_cast<uintptr_t>(this) + 0x1BC);
}