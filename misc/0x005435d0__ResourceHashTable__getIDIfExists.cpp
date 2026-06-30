// FUNC_NAME: ResourceHashTable::getIDIfExists
uint __thiscall ResourceHashTable::getIDIfExists(int* thisPtr)
{
    uint hash = 0x1bc97c13;

    int outStatus; // Unused output parameter
    bool isValid = (bool)(*(code**)(*thisPtr + 0x10))(hash, &outStatus);

    // Return the hash if valid, otherwise 0
    return isValid ? hash : 0;
}