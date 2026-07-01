// FUNC_NAME: UnknownClass::releaseChild
// Function address: 0x00871840
// Role: Releases a child object pointer and performs global cleanup.

class UnknownClass {
public:
    void* childPtr; // +0x08
    void releaseChild();
};

// External functions
void FUN_00851230(void* ptr);
void FUN_009f01a0();

void UnknownClass::releaseChild() {
    if (this->childPtr != nullptr) {
        // Release the child object (likely a destructor or release function)
        FUN_00851230(this->childPtr);
        // Global cleanup/notification
        FUN_009f01a0();
        // Nullify pointer to prevent double-free
        this->childPtr = nullptr;
    }
}