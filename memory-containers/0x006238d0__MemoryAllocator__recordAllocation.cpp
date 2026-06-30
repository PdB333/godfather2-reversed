// FUNC_NAME: MemoryAllocator::recordAllocation
void __thiscall MemoryAllocator::recordAllocation(void *this, int typeId)
{
    // +0x4: pointer to vtable for the allocator's allocation function
    // +0x8: fallback buffer (if non-null, use it; else use stack)
    AllocationRecord *record;
    undefined4 stackBuf[3]; // local fallback buffer (stack)

    void *fallbackBuf = *(void **)((int)this + 8);
    if (fallbackBuf == (void *)0x0) {
        // No fallback provided, use stack buffer
        stackBuf[0] = 0;
        stackBuf[1] = 0;
        stackBuf[2] = 0;
        fallbackBuf = &stackBuf;
    }

    // Call vtable function at (this+4)->0 to allocate 0x28 bytes
    // This allocator returns a pointer to an AllocationRecord struct
    record = ((AllocationRecord* (__thiscall *)(void *, int, void *))(
        *(int **)((int)this + 4))[0])(0x28, fallbackBuf);
    // The third parameter (fallbackBuf) is passed in ECX? Actually the call pattern:
    // (**(code **)**(undefined4 **)(param_1 + 4))(0x28, puVar1)
    // implies first param is size, second is the buffer/hint

    if (record != (AllocationRecord *)0x0) {
        // Initialize the record fields
        record->field_0 = stackBuf[0]; // Usually 0 when using null fallback
        record->callerRetAddr = (void *)__builtin_return_address(0); // captured by unaff_retaddr
        record->typeId = typeId;
        // Copy 24 bytes from ESI (source data) into record's data array
        record->data[0] = *(undefined8 *)((int)ESI + 0); // ESI is a register set by caller
        record->data[1] = *(undefined8 *)((int)ESI + 8);
        record->data[2] = *(undefined8 *)((int)ESI + 16);
        // Zero out two flag bytes at the end of the record
        *(char *)((int)record + 0x24) = 0;
        *(char *)((int)record + 0x25) = 0;
    }
    return;
}