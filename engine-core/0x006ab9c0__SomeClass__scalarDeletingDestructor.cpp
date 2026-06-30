// FUNC_NAME: SomeClass::scalarDeletingDestructor
// Function address: 0x006ab9c0
// Role: Compiler-generated scalar deleting destructor. Calls the actual destructor (FUN_006ab8a0),
// then conditionally calls operator delete (FUN_0043b960) on the object if param_2's lowest bit is set.
// Object size: 0x9c (156 bytes)

#include <cstddef>

class SomeClass {
    // Object size: 0x9c (156 bytes) based on the delete call.
public:
    // __thiscall is used for member functions.
    // param_2: flag (bit 0 indicates whether to free memory).
    __thiscall SomeClass* scalarDeletingDestructor(byte param_2) {
        // Call the actual destructor (base class or custom cleanup).
        this->someDestructor();  // FUN_006ab8a0

        // If the low bit of param_2 is set, release the memory.
        if ((param_2 & 1) != 0) {
            // FUN_0043b960 is likely operator delete with size hint.
            operator delete(this, 0x9c);  // or custom free
        }

        // Return the this pointer (as expected by the calling convention).
        return this;
    }

private:
    // Placeholder for the actual destructor body (FUN_006ab8a0).
    void someDestructor() {
        // Actual cleanup code would go here.
    }

    // Overload operator delete to match the call pattern.
    void operator delete(void* ptr, size_t size) {
        // MSVC-style sized delete – often mapped to free().
        // In the game, this is likely FUN_0043b960.
        ::operator delete(ptr, size);
    }
};