// FUNC_NAME: registerReplicatedFieldOffsets
void __thiscall ObjectReplicator::registerReplicatedFieldOffsets(void* thisPointer, int fieldGroupId)
{
    // Array of field offsets (relative to object base) to be replicated.
    // Offsets: 0x50, 0x60, 0x70, 0x80, 0x90
    int offsetArray[5] = {
        0x50,   // +0x50: likely some state or position field
        0x60,   // +0x60: another replicated field
        0x70,   // +0x70: ...
        0x80,   // +0x80: ...
        0x90    // +0x90: ...
    };
    // Register these offsets with the replication system.
    // The callee (FUN_004eba90) expects: object pointer, field group ID, array pointer, element count
    FUN_004eba90(thisPointer, fieldGroupId, offsetArray, 5);
}