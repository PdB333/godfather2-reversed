// FUNC_NAME: Entity::getDataIfValid
// Address: 0x004e6890
// Role: Returns a pointer to internal data if a validity flag is set.
// The object has a pointer to an internal data block at offset +4,
// and the actual data pointer is at offset +0xc within that block.

// Forward declaration of the callee
undefined4 __thiscall getDataFromInternal(int this, int dataBlock);

undefined4 __thiscall Entity::getDataIfValid(int this, int isValid)
{
    if (isValid != 0) {
        // Dereference the internal data block pointer at +4, then read the data pointer at +0xc
        int dataBlock = *(int *)(this + 4); // +0x4: pointer to internal data block
        int dataPtr = *(int *)(dataBlock + 0xc); // +0xc: actual data pointer within the block
        return getDataFromInternal(this, dataPtr);
    }
    return 0;
}