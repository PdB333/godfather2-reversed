// Xbox PDB: EARS::Framework::Lua::LuaGroupLibrary::ToGroup
// FUNC_NAME: writeGroupsToStream
// Address: 0x0046a160
// This function iterates over all registered Group objects and writes their IDs into a stream buffer.
// It is likely part of the network serialization system for replicating group membership.
// The stream structure at param_1 has a write pointer at offset +0x8 (buffer pointer) and possibly base at -0x10.

int writeGroupsToStream(void* stream) {
    // Get the type info for "Group" class
    int* groupTypeInfo = (int*)getClassType(1, "Group"); // FUN_00627e50
    if (groupTypeInfo == nullptr) {
        printError("Object is not a '%s'.\n", "Group");
        // Software interrupt (likely assertion failure)
        void (*crashFunc)() = (void (*)())(swi(3)); // intentional crash
        return crashFunc();
    }

    // Access the global group list: base address at DAT_01223414 + 4, then +8 + groupTypeIndex * 0x1c
    // This structure appears to be an array of linked lists, one per group type.
    int* groupListHead = *(int**)(*(int*)(DAT_01223414 + 4) + 8 + *groupTypeInfo * 0x1c);
    int* currentNode = groupListHead;

    while (currentNode != nullptr) {
        int groupId = currentNode[0]; // The group object pointer or ID
        if (groupId != 0) {
            // Write two 32-bit values from the group into the stream buffer
            uint* writePtr = *(uint**)((int)stream + 8);
            writePtr[0] = writePtr[-2]; // Copy from earlier buffer content? Actually writePtr[-2] is before base?
            writePtr[1] = writePtr[-1];
            // Advance write pointer
            *(int*)((int)stream + 8) += 8;

            // Read group-specific data
            readGroupData(groupId); // FUN_0046b880

            // Serialize the just-written data into the stream
            // The second parameter points to the beginning of the two 32-bit values we wrote
            serializeGroupToStream(stream, (void*)(*(int*)((int)stream + 8) - 0x10), 0); // FUN_006362d0
        }
        currentNode = (int*)currentNode[1]; // Next node in linked list
    }
    return 1; // Success
}