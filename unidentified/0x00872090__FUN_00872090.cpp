// FUNC_NAME: UnknownClass::~UnknownClass
// Address: 0x00872090
// Role: Destructor for a class with a sub-object pointer at offset 0x8.
// The vtable pointer is set to PTR_FUN_00d76138.
// If the sub-object (at +0x8) exists, it is released via releaseSubObject() and a global cleanup is called.
// If deallocFlag (bit 0 of param_2) is set, operatorDelete is called to free memory.

class UnknownClass {
public:
    // Vtable pointer (set to PTR_FUN_00d76138)
    void* vtable; // +0x0

    // Sub-object pointer (e.g., a resource or child object)
    void* subObject; // +0x8

    // Destructor
    // param_2: bit 0 indicates whether to deallocate memory (operator delete)
    void __thiscall ~UnknownClass(byte deallocFlag) {
        // Set vtable to the correct one for this class
        this->vtable = &PTR_FUN_00d76138;

        // Release sub-object if it exists
        if (this->subObject != 0) {
            releaseSubObject(this->subObject); // FUN_00851230
            cleanupGlobal();                   // FUN_009f01a0
            this->subObject = 0;
        }

        // If deallocation flag is set, free the memory
        if ((deallocFlag & 1) != 0) {
            operatorDelete(this); // FUN_009c8eb0
        }
    }
};

// Helper functions (stubs for callees)
void releaseSubObject(void* obj); // FUN_00851230
void cleanupGlobal();             // FUN_009f01a0
void operatorDelete(void* ptr);   // FUN_009c8eb0