// FUNC_NAME: PooledObject::deinit
void __fastcall PooledObject::deinit(int this)
{
    byte savedByte = *(byte *)(this + 0x10); // +0x10: byte flag, saved before pool operation

    // If global pool allocator exists, release this object back to the pool
    if (gPoolAllocator != 0) {
        releaseToPool(this, &gPoolAllocator, 0x8000); // FUN_00408900 – pool release with size 0x8000
    }

    // Delete sub-object if present
    if (*(int *)(this + 0x14) != 0) {
        deleteSubObject((int *)(this + 0x14)); // FUN_004daf90 – frees sub-object at +0x14
        *(int *)(this + 0x14) = 0;
    }

    *(int *)(this + 0x1c) = 0;  // +0x1c: clear integer field
    *(byte *)(this + 0x10) = savedByte; // Restore saved byte flag
    *(byte *)(this + 0x20) = 0;  // +0x20: clear byte field
}