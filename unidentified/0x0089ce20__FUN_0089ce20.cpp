// FUNC_NAME: SomeClass::destroy
// Function at 0x0089ce20: Destructor-like cleanup with optional memory deallocation.
// Checks if a sub-object at offset +0x8 exists, calls its destructor, then optionally frees this object.

class SomeClass {
public:
    // +0x8: pointer to a sub-object (e.g., a resource or component)
    SomeSubObject* m_subObject;

    // Destroys the sub-object and optionally deallocates this instance.
    // param_2: bit 0 set = also free this object's memory.
    SomeClass* destroy(byte flags) {
        if (m_subObject != nullptr) {
            // Call sub-object's destructor/release (FUN_004daf90)
            m_subObject->release();
        }
        if ((flags & 1) != 0) {
            // Free this object's memory (FUN_009c8eb0)
            operator delete(this);
        }
        return this;
    }
};