// FUNC_NAME: GameObject::isMatchingObject

bool __thiscall GameObject::isMatchingObject(int thisPtr, int otherPtr)
{
    // Skip if same object
    if (otherPtr == thisPtr) {
        return false;
    }

    // +0x1ED8: pointer to an internal data block (e.g., hash table or manager)
    int dataBlock = *(int *)(thisPtr + 0x1ED8);
    int basePtr;
    if (dataBlock == 0) {
        basePtr = 0;
    } else {
        // Navigate into the data block (subtract 0x48 to get the base of some structure)
        basePtr = dataBlock - 0x48;
    }

    // +0x88 from the base: likely a unique identifier, type ID, or hash value
    int identifier = *(int *)(basePtr + 0x88);

    // Compare the other object against this identifier
    char result = FUN_0043c6c0(otherPtr, identifier);

    return (result != 0);
}