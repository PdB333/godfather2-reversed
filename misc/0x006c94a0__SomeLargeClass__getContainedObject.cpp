// FUNC_NAME: SomeLargeClass::getContainedObject

int __thiscall getContainedObject(int thisPtr)
{
    // Offset +0x24FC stores a pointer to some sub-object (e.g., a component or member structure).
    // If non-null, subtract 0x48 to get the base of the containing object (since the stored pointer
    // points into the container at offset 0x48).
    int storedPtr = *(int *)(thisPtr + 0x24FC);
    if (storedPtr != 0) {
        return storedPtr - 0x48;  // Return base address of the parent object
    }
    return 0;
}