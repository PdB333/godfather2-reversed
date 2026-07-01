// FUNC_NAME: UnknownClass::initialize
// Address: 0x00902c40
// Role: Reinitialization/reset function that cleans up old pointers then initializes internal structures

extern void* PTR_FUN_00d81f20;   // vtable for main class
extern void* PTR_LAB_00d81f10;  // vtable for first base at offset 0x3C
extern void* PTR_LAB_00d81f0c;  // vtable for second base at offset 0x48
// Forward declarations for internal functions
void __fastcall FUN_004086d0(void* ptr);   // likely constructor for a member
void __fastcall FUN_00408310(void* ptr);   // likely constructor for another member
void __fastcall FUN_004daf90(void* ptr);   // likely destructor/free for a pointer member
void __cdecl FUN_0046c640();               // global cleanup or processing function

class UnknownClass {
    // offsets from this
    /* +0x00 */ void* vtable;            // PTR_FUN_00d81f20
    // ... other members at offsets: +0x3C, +0x48 (vtable pointers for bases)
    // +0x70: pointer member (offset 0x1c in this array notation)
    // +0x78: pointer member (offset 0x1e)
    // +0x80: first member initialized via FUN_004086d0 and FUN_00408310 (offset 0x20)
    // +0x88: second member (offset 0x22)
    // +0x90: third member (offset 0x24, only FUN_00408310)
    
public:
    void __fastcall initialize(void) {
        // Set virtual function tables for this and base classes
        this->vtable = &PTR_FUN_00d81f20;
        *(void**)((uint8_t*)this + 0x3C) = &PTR_LAB_00d81f10;   // param_1[0xf]
        *(void**)((uint8_t*)this + 0x48) = &PTR_LAB_00d81f0c;   // param_1[0x12]

        // Construct global object at DAT_012069c4
        FUN_004086d0(&DAT_012069c4);

        // Construct internal members
        // Member at offset 0x80 (array index 0x20)
        FUN_004086d0((uint8_t*)this + 0x80);
        FUN_00408310((uint8_t*)this + 0x80);

        // Member at offset 0x88 (array index 0x22)
        FUN_004086d0((uint8_t*)this + 0x88);
        FUN_00408310((uint8_t*)this + 0x88);

        // Member at offset 0x90 (array index 0x24)
        FUN_00408310((uint8_t*)this + 0x90);

        // Clean up old dynamically allocated pointers if they exist
        // Pointer at offset 0x78 (0x1e)
        void* ptr1 = *(void**)((uint8_t*)this + 0x78);
        if (ptr1 != 0) {
            FUN_004daf90(ptr1);
            // Note: pointer is not set to null after deletion (possible bug or intentional)
        }

        // Pointer at offset 0x70 (0x1c)
        void* ptr2 = *(void**)((uint8_t*)this + 0x70);
        if (ptr2 != 0) {
            FUN_004daf90(ptr2);
        }

        // Perform global processing (e.g., dispatch events)
        FUN_0046c640();
    }
};