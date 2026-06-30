// FUNC_NAME: ObjectPool::constructNode
void __fastcall ObjectPool::constructNode(int this)
{
    void *poolBuffer = *(void **)(this + 8);
    undefined4 localStackBuffer[3]; // 12 bytes fallback
    undefined4 *puVar1;

    if (poolBuffer == nullptr) {
        localStackBuffer[0] = 0;
        localStackBuffer[1] = 0;
        localStackBuffer[2] = 0;
        puVar1 = (undefined4 *)localStackBuffer;
    } else {
        puVar1 = (undefined4 *)poolBuffer;
    }

    // Call allocator function via vtable at offset 4, size 0x18 (24 bytes)
    // The second argument is a hint buffer, may be used for placement or ignored.
    puVar1 = (undefined4 *)( (** (code **) (**(int **)(this + 4) ))(0x18, puVar1) );

    if (puVar1 != nullptr) {
        *puVar1 = 0;                // +0x00: int field A
    }
    if (puVar1 + 1 != nullptr) {
        puVar1[1] = 0;              // +0x04: int field B
    }
    if (puVar1 + 2 != nullptr) {
        puVar1[2] = 0;              // +0x08: int field C
    }
    *(byte *)((int)puVar1 + 0x15) = 0;  // +0x15: byte flag1
    *(byte *)(puVar1 + 5) = 1;          // +0x14: byte flag2 (puVar1+5 is at byte offset 20)
    return;
}