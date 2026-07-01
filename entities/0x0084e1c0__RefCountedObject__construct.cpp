// FUNC_NAME: RefCountedObject::construct
// Function address: 0x0084e1c0
// Role: Constructor for a reference-counted object with vtable, embedded list node, and two stored parameters.
void RefCountedObject::construct(int param1, int param2)
{
    // Allocate 108 bytes (0x6c) for the object
    int* obj = (int*)allocMemory(0x6c);
    if (obj == nullptr) {
        return;
    }
    // Initialize reference counting system (flags, increment)
    initRefCount(1, 1);
    // Set vtable pointer (class-specific vtable at global LAB_00d74e70)
    obj[0] = (int)&PTR_LAB_00d74e70;  // +0x00: vtable pointer
    // Register a cleanup/event callback (function pointer FUN_0084de50)
    registerCallback(FUN_0084de50);
    // Set embedded list pointer: offset +0x14 points to itself + 0x18
    // (likely a linked list node)
    obj[5] = (int)(obj + 6);          // +0x14: pointer to node data at +0x18
    // Increment reference count at offset +0x08
    obj[2] = obj[2] + 1;              // +0x08: reference count
    // Store parameters at offsets +0x20 and +0x24
    obj[8] = param1;                  // +0x20: first stored parameter
    obj[9] = param2;                  // +0x24: second stored parameter
    // Stack frame initialization (debug/assert)
    stackFrameInit(&stack0x0000000c);
    // Release a lock/mutex
    releaseLock();
    // Decrement reference count; if zero, call destructor via vtable+8
    if (obj != nullptr) {
        int* refCount = obj + 2;
        *refCount = *refCount - 1;
        if (*refCount == 0) {
            // Call destructor function at vtable offset 8
            (**(code**)(obj[0] + 8))();
        }
    }
}