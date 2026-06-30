// FUNC_NAME: SomeEntity::scalarDeletingDestructor
class SomeEntity {
public:
    // Scalar deleting destructor – called by operator delete with a flag
    // byte flag: if bit 0 is set, memory will be freed after destruction
    void* scalarDeletingDestructor(byte flag) {
        // Call the actual destructor (defined at FUN_007256d0)
        this->~SomeEntity();

        // If the object was allocated with new, free the memory (size known: 0x140 = 320 bytes)
        if (flag & 1) {
            operator delete(this, 0x140);
        }

        return this; // return 'this' for potential chaining or delete operator
    }

    // Actual destructor (defined elsewhere, e.g., at 0x007256d0)
    // ~SomeEntity() will call base destructors and clean up resources.
};