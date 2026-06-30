// FUNC_NAME: Manager::createObject
void Manager::createObject(uint id, uint unusedParam, uint arg3, uint arg4, uint arg5, uint arg6, uint arg7, uint arg8, uint arg9)
{
    // Buffer for object creation metadata: [id, type, size, flags?]
    uint creationBuffer[5];
    creationBuffer[1] = 2;        // +0x04: object type/family
    creationBuffer[2] = 0x10;     // +0x08: base size / offset?
    creationBuffer[3] = 0;        // +0x0C: flags / reserved

    // Allocate 0xA0 bytes using custom allocator (placement or pool-based)
    // Second argument points to the creation metadata
    void* allocatedMemory = customAlloc(0xA0, &creationBuffer[1]);
    if (allocatedMemory == nullptr)
    {
        newObject = nullptr;
    }
    else
    {
        // Construct the object with the remaining 7 parameters
        newObject = constructObject(arg3, arg4, arg5, arg6, arg7, arg8, arg9);
    }

    creationBuffer[0] = id;       // +0x00: unique identifier

    // Compute slot in the manager’s hash table:
    // DAT_01223398 is a global pointer to the manager instance;
    // offset +0x8 points to a structure with bucket count at +0x8.
    uint bucketCount = *(uint*)(*(int*)(globalManager + 8) + 8);  // globalManager is DAT_01223398
    uint slotIndex = id % bucketCount;

    // Insert (id, creation buffer, new object pointer) into the table at slotIndex
    insertIntoTable(creationBuffer, &newObject, slotIndex);

    return;
}