// Xbox PDB: EARS::Framework::SavePoint::Restore
// FUNC_NAME: PersistableSavePoint::restore

void __thiscall PersistableSavePoint::restore(uint32_t inBuffer, uint32_t inSize, uint32_t inFlags) {
    // Store the input parameters into the object (offsets: +0x34 = size, +0x38 = flags)
    *(uint32_t *)((int)this + 0x34) = inSize;
    *(uint32_t *)((int)this + 0x38) = inFlags;

    // Get a pointer to the persistable handle slot at offset +0x28
    int *persistableHandle = (int *)((int)this + 0x28);

    // Look up the type ID for the "iMsgSavePointPersistableRestore" interface
    uint32_t typeId = FUN_004dafd0("iMsgSavePointPersistableRestore");

    // Assign the type – likely registers or initializes the persistable handle
    FUN_00408260(persistableHandle, typeId);

    // If the persistable handle is now valid, perform additional initialization
    if (*persistableHandle != 0) {
        FUN_00407e60(this, persistableHandle);   // (restore data stream or similar)
    }

    // Check if we have a valid read/write range (offsets +0x18 and +0x1C)
    if (*(int *)((int)this + 0x1C) != 0 && *(int *)((int)this + 0x18) != 0) {
        // Adjust pointers: step back 4 bytes from start, step forward 4 bytes from end
        *(int *)((int)this + 0x20) = *(int *)((int)this + 0x18) - 4;
        *(uint32_t *)((int)this + 0x30) = inBuffer;
        *(int *)((int)this + 0x24) = *(int *)((int)this + 0x1C) + 4;
        FUN_004c0920();   // Restore with adjusted buffer bounds
    } else {
        // No valid range – just store the buffer pointer and use a simpler restore
        *(uint32_t *)((int)this + 0x30) = inBuffer;
        FUN_004c0a60();   // Restore without buffer adjustment
    }
}