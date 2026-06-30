// FUNC_NAME: EARSObject::construct
// Address: 0x004f1920
// This function is a placement-new style constructor for EARSObject.
// It takes a context pointer (param_1) and a memory block (param_2),
// initializes the vtable, calls a base initializer, and stores a resource ID.

class EARSObject {
public:
    // Vtable pointer at offset 0x00 (set to &PTR_FUN_00e374d0)
    // ID field at offset 0x24 (9 * 4 bytes) - stores a unique identifier

    static EARSObject* construct(void* context, EARSObject* memory) {
        if (memory != nullptr) {
            // Read ID from context structure:
            // context points to some manager; offset +0x04 is a pointer,
            // offset +0x0c from that pointer is the ID value.
            uint32_t id = *(uint32_t*)(*(int32_t*)((uint8_t*)context + 4) + 0xC);
            
            // Call base initialization (likely a virtual function or static initializer)
            initializeBase();
            
            // Store ID at offset 0x24
            memory->field_0x24 = id;
            
            // Set vtable pointer
            memory->vtable = (void**)&PTR_FUN_00e374d0;
            
            return memory;
        }
        return nullptr;
    }

private:
    void* vtable;               // +0x00
    // ... other members ...
    uint32_t field_0x24;        // +0x24
};