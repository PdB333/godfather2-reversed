// FUNC_NAME: ObjectRegistration::pushToGlobalStack
// Address: 0x005db6c0
// This function registers an object's vtable and two data fields onto a global stack,
// and updates a field at offset +0x0c with value from +0x18.

struct ObjectStackManager {
    uint8_t pad0[0x14];               // +0x00
    void** stackTop;                  // +0x14 - pointer to the current top of the stack
};

// Global instance - address DAT_01206880
extern ObjectStackManager* g_pObjectStackManager;

void __fastcall ObjectRegistration::pushToGlobalStack(void* this) {
    void* vtable = &PTR_LAB_011273b8;      // vtable pointer (PTR_LAB_011273b8)
    int32_t field_0x20 = *(int32_t*)((uint8_t*)this + 0x20); // +0x20: first data value
    int32_t field_0x14 = *(int32_t*)((uint8_t*)this + 0x14); // +0x14: second data value

    // Push three dwords onto the global stack
    void** pStackTop = &(g_pObjectStackManager->stackTop);
    *(*pStackTop)++ = vtable;
    *(*pStackTop)++ = (void*)field_0x20;
    *(*pStackTop)++ = (void*)field_0x14;

    // Update this+0x0c with the value from this+0x18
    *(int32_t*)((uint8_t*)this + 0x0c) = *(int32_t*)((uint8_t*)this + 0x18);
}