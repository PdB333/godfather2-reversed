// FUNC_NAME: EARSObject::destructorWithDeleteFlag
int* EARSObject::destructorWithDeleteFlag(byte shouldDelete)
{
    // Check if first member (likely internal data pointer) is non-null
    if (this->someMember != 0) {
        // Call internal cleanup / virtual destructor
        this->cleanup();
    }
    // If delete flag is set (bit 0), deallocate memory
    if ((shouldDelete & 1) != 0) {
        // EARS memory deallocation (operator delete)
        EARS::Memory::deallocate(this);
    }
    return this;
}