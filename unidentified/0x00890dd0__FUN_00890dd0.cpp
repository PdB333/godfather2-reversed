// FUNC_NAME: SomeClass::initializeWithFlag
// Function address: 0x00890dd0
// Role: Initialization method with conditional memory deallocation based on a flag.
// Calls base init (FUN_00890b70) and optionally operator delete (FUN_0043b960) of size 0x1d0.

// Based on context: The function is a __thiscall member, returns 'this'.
// param_2 is a byte flag where bit 0 controls deletion of the object's memory.
// This pattern suggests a constructor that can optionally free memory (e.g., on failure or relocation).

class SomeClass {
public:
    // Initialize object, optionally delete if flag has bit 0 set
    SomeClass* initializeWithFlag(byte flag) {
        // Call base init (FUN_00890b70) - likely a base class constructor or zero-initialization
        baseInit();  // FUN_00890b70

        // If flag's bit 0 is set, deallocate this object's memory (size 0x1d0 = 464 bytes)
        if (flag & 1) {
            operatorDelete(this, 0x1d0);  // FUN_0043b960 - custom deallocation?
        }

        return this;
    }

private:
    void baseInit(); // inlined or defined elsewhere (FUN_00890b70)
    void operatorDelete(void* ptr, size_t size); // inlined or defined elsewhere (FUN_0043b960)
};