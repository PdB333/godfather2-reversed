// FUNC_NAME: StreamManager::~StreamManager

class StreamManager {
public:
    // Virtual table pointer at +0x00
    // +0x3C: function pointer (PTR_LAB_00d5d800)
    // +0x48: function pointer (PTR_LAB_00d5d7fc)
    // +0x50: pointer to an internal object (e.g., StreamBuffer)
    // +0x58: pointer to a second internal object
    // +0x70: integer (may be a handle, pointer stored as int, or type ID; 0x48 = uninitialized sentinel)

    // Destructor
    void __thiscall destroy() {
        // Set own vtable pointer (likely to base class vtable during destruction)
        this->vtable = (void**)&PTR_FUN_00d5d810;
        this->field_0x3c = &PTR_LAB_00d5d800;
        this->field_0x48 = &PTR_LAB_00d5d7fc;

        int* typeOrPtr = &this->field_0x70; // pointer to member at +0x70
        // If the value at +0x70 is not null and not the sentinel, destroy what it references
        if ((*typeOrPtr != 0) && (*typeOrPtr != 0x48)) {
            FUN_006a55f0(typeOrPtr); // likely destroy pointed object
        }

        // Destroy and deallocate the two internal objects at +0x50 and +0x58
        FUN_004086d0(&this->field_0x50); // destroy object pointer
        FUN_00408310(&this->field_0x50); // deallocate pointer memory

        FUN_004086d0(&this->field_0x58);
        FUN_00408310(&this->field_0x58);

        // Final cleanup for the member at +0x70 if it's still valid
        if (*typeOrPtr != 0) {
            FUN_004daf90(typeOrPtr);
        }

        // Global cleanup (likely memory manager or stream system teardown)
        FUN_0046c640();
    }

private:
    void* vtable; // +0x00
    // ... other fields up to +0x3C
    void* field_0x3c; // +0x3C
    void* field_0x48; // +0x48
    // +0x50 and +0x58: likely two pointers or embedded objects (size 4 bytes each)
    void* field_0x50; // +0x50
    void* field_0x58; // +0x58
    int field_0x70;   // +0x70 (handle or pointer)
};

// External declarations for functions used
void __fastcall FUN_006a55f0(int* ptr);   // destructor for object referenced by ptr
void __fastcall FUN_004086d0(void* ptr);  // destroy object at indirect pointer
void __fastcall FUN_00408310(void* ptr);  // deallocate pointer
void __fastcall FUN_004daf90(int* ptr);   // secondary cleanup for object
void __fastcall FUN_0046c640();           // global cleanup function