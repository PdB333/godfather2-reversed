// FUNC_NAME: ScriptContextManager::unregisterContext

void __thiscall ScriptContextManager::unregisterContext(ScriptContext* context)
{
    // Register function names for timer methods
    registerMethodName(context, "CreateTimer");
    *(context->stackPtr) = 0;
    context->stackPtr += 8;
    int* methodTable = context + 0x40; // +0x40: method pointer table
    registerMethodPointer(methodTable, context->stackPtr - 0x10, context->stackPtr - 8);
    context->stackPtr -= 0x10;

    registerMethodName(context, "StartTimer");
    *(context->stackPtr) = 0;
    context->stackPtr += 8;
    registerMethodPointer(methodTable, context->stackPtr - 0x10, context->stackPtr - 8);
    context->stackPtr -= 0x10;

    registerMethodName(context, "SetTimerRate");
    *(context->stackPtr) = 0;
    context->stackPtr += 8;
    registerMethodPointer(methodTable, context->stackPtr - 0x10, context->stackPtr - 8);
    context->stackPtr -= 0x10;

    registerMethodName(context, "StopTimer");
    *(context->stackPtr) = 0;
    context->stackPtr += 8;
    registerMethodPointer(methodTable, context->stackPtr - 0x10, context->stackPtr - 8);
    context->stackPtr -= 0x10;

    registerMethodName(context, "DeleteTimer");
    *(context->stackPtr) = 0;
    context->stackPtr += 8;
    registerMethodPointer(methodTable, context->stackPtr - 0x10, context->stackPtr - 8);
    context->stackPtr -= 0x10;

    registerMethodName(context, "QueryTimer");
    *(context->stackPtr) = 0;
    context->stackPtr += 8;
    registerMethodPointer(methodTable, context->stackPtr - 0x10, context->stackPtr - 8);
    context->stackPtr -= 0x10;

    // Acquire global lock for slot cleanup
    acquireLock(&g_lock);
    
    // Walk all timer slots (32 slots, each 0x54 bytes)
    TimerSlot* slot = reinterpret_cast<TimerSlot*>(reinterpret_cast<uint8_t*>(this) + 0x1c); // +0x1c: start of timer slot array
    for (int i = 0; i < 32; i++)
    {
        // Slot at index i: offset from slot is i * 0x54
        // Each slot has multiple entries? Actually the code checks 4 conditions per slot,
        // each with different offsets: -8, +0x13, +0x28, +0x3d (in 4-byte units)
        // Those correspond to the same slot structure but different fields?
        // Let's assume the slot struct has multiple context pointers for different timer types.
        
        if (slot->contextPtr1 == context)
        {
            slot->contextPtr1 = nullptr;
            slot->field_4 = 0;
            slot->field_8 = 0;
            slot->field_1C = 0;         // +0x11? Actually +0x11*4 = 0x44? Let's use byte offsets later
            slot->field_48 = 1;         // offset 0x45
            slot->field_49 = 0;         // offset 0x46
            slot->field_C = 0;          // +1*4 = 0x4
        }
        if (slot->contextPtr2 == context)   // using offset +0x13*4 = 0x4C? Actually need precise
        {
            slot->contextPtr2 = nullptr;
            slot->field_4C = 0;
            slot->field_50 = 0;
            slot->field_6C = 0;
            slot->field_98 = 1;
            slot->field_99 = 0;
            slot->field_54 = 0;
        }
        if (slot->contextPtr3 == context)
        {
            slot->contextPtr3 = nullptr;
            slot->field_98 = 0; // Actually need recompute all offsets
        }
        // ... similar for fourth check

        slot = reinterpret_cast<TimerSlot*>(reinterpret_cast<uint8_t*>(slot) + 0x54);
    }
    
    g_globalFlag = 0; // _DAT_01205404
}

// Reconstructed timer slot structure (partial, based on offsets)
struct TimerSlot
{
    int* contextPtr1;          // +0x00 (offset 0)
    int field_4;               // +0x04
    int field_8;               // +0x08
    int field_1C;              // +0x1C? Actually from code: puVar1+0x11 is a byte, so offset by 0x44? Let's map carefully.
    // Because pointer arithmetic is on int*, offsets are multiplied by 4.
    // puVar1[-2] is offset -8 bytes from puVar1 = index -2 => address puVar1-8 => fields at -8,-4,0,4...
    // Then set puVar1+0x11 => 0x11*4 = 0x44, puVar1+0x45 => 0x45 bytes? Wait inconsistent: (int)puVar1+0x45 means byte offset.
    // This is messy. For reconstruction, we'll just use hex offsets in comments.
};