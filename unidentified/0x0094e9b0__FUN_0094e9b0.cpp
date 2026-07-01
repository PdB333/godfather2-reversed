// FUNC_NAME: SomeClass::scalar_deleting_destructor
// Address: 0x0094e9b0
// Role: Scalar deleting destructor for a class of size 0x68 (104 bytes).
// Calls the actual destructor (0x0094e850) and conditionally deletes memory.

// Forward declarations (actual implementations at given addresses)
void __thiscall SomeClass::destructor(void* this); // 0x0094e850
void __cdecl operatorDelete(void* ptr, unsigned int size); // 0x0043b960

void* __thiscall SomeClass::scalar_deleting_destructor(void* this, byte flags) {
    SomeClass::destructor(this);
    
    if ((flags & 1) != 0) {
        // Delete this object with size 0x68
        operatorDelete(this, 0x68);
    }
    
    return this;
}