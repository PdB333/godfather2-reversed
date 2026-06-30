// FUNC_NAME: ArrayManager::executeOnObject
// Reconstructed C++ for function at 0x00424dc0
// Purpose: Dispatches a call to a specific indexed object in an array.
// Assumes this->objectArray (offset +0x10) points to an array of 0x1d0-byte objects.

void __thiscall ArrayManager::executeOnObject(int index, uint32_t param2, uint32_t param3, uint32_t param4, uint32_t param5)
{
    // +0x10: pointer to the base of an array of objects (each 0x1d0 bytes)
    int* objectBasePtr = *(int**)(this + 0x10);
    int objectAddr = objectBasePtr + index * 0x1d0;

    // Call internal routine (likely a generic operation on the object)
    // FUN_004a1a10 takes: object address, index, and four extra parameters
    ObjectOperationFunc(objectAddr, index, param2, param3, param4, param5);
}