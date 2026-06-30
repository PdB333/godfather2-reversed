// FUNC_NAME: EARS::String::operator=(EARS::String&&)
void __thiscall EARS::String::moveAssign(EARS::String&& other)
{
    // Clear the internal small buffer (0x48 to 0x5f) before copying
    *(int*)(this + 0x48) = 0;
    *(int*)(this + 0x4c) = 0;
    *(int*)(this + 0x50) = 0;
    *(int*)(this + 0x54) = 0;
    *(int*)(this + 0x58) = 0;
    *(int*)(this + 0x5c) = 0;

    // Release any existing string data
    EARS::String::release(this);

    // Move the pointer and zero out source's pointer
    this->mData = other.mData;          // +0x40
    other.mData = nullptr;

    int movedPtr = this->mData;
    // Copy the length and small buffer
    this->mLength = other.mLength;      // +0x44
    *(int*)(this + 0x48) = *(int*)(other + 0x48);
    *(long long*)(this + 0x4c) = *(long long*)(other + 0x4c); // Copy 8 bytes at 0x4c
    *(long long*)(this + 0x54) = *(long long*)(other + 0x54); // Copy 8 bytes at 0x54
    *(int*)(this + 0x5c) = *(int*)(other + 0x5c);
    *(int*)(this + 0x60) = *(int*)(other + 0x60);

    // Debug or assert check using global debug system
    if (movedPtr != 0) {
        int* debugSys = *(int**)(*DAT_0113dfc8 + 0x14)(); // Get debug system instance
        int debugId = debugSys->getTypeId(movedPtr);       // +0x10 method
        char* str = (char*)FUN_00ab06f0(&stack0xfffffffb, debugId);
        if (*str == '\0') goto afterDebugCheck;
    }

    if (this->mData != 0) {
        // Set ownership/reference flag on the allocated block (offset +0x2c)
        *(uint*)(this->mData + 0x2c) = (uint)this >> 2 | 0xC0000000;
    }

afterDebugCheck:
    // Copy the final two fields (e.g., capacity or reference count)
    *(int*)(this + 0x64) = *(int*)(other + 0x64);
    *(int*)(this + 0x68) = *(int*)(other + 0x68);
}