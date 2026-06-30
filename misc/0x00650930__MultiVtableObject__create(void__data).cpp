// FUNC_NAME: MultiVtableObject::create(void* data)
// Address: 0x00650930
// This function allocates a MultiVtableObject (size 0x24) and initializes its fields.
// It sets up two vtables (at offsets 0x00 and 0x18) and a function pointer (offset 0x1C).
// If allocation fails, it uses a global placeholder and calls Init with null.

void MultiVtableObject::create(void* data)
{
    // Allocation attempt (0x24 bytes = 36 bytes)
    MultiVtableObject* obj = (MultiVtableObject*)operator new(0x24);
    if (obj != nullptr) {
        // Field offsets documented with comments
        obj->vtable1 = (void*)&PTR_LAB_00e43004;     // +0x00: First vtable
        obj->field1 = 0;                             // +0x04
        obj->field2 = 0;                             // +0x08
        obj->field3 = 1;                             // +0x0C: initial count/flag
        obj->field4 = 0;                             // +0x10
        obj->selfPtr = (uint8_t*)obj + 0x18;         // +0x14: pointer to itself+0x18 (second vtable)
        obj->vtable2 = (void*)&PTR_LAB_00e42fec;     // +0x18: Second vtable (e.g., interface)
        obj->funcPtr = (void*)&LAB_00652750;         // +0x1C: Function pointer (callback)
        obj->userData = data;                        // +0x20: Stored parameter

        // Call initialization routine
        FUN_0064ef60(obj);
    } else {
        // Fallback: store data in global and call Init with null
        g_defaultInstance = data;
        FUN_0064ef60(nullptr);
    }
}