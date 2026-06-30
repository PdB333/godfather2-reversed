// FUNC_NAME: EAString::EAString(const char* sourceString)
// Address: 0x004d3b00
// Role: Constructor for EA EARS string object from a C-style string.
// Structure layout:
//   +0x00 char* mData         - pointer to allocated buffer
//   +0x04 int   mLength       - length of the string (excluding null terminator)
//   +0x08 int   mCapacity     - allocated buffer size (including null terminator)
//   +0x0C void* mDeallocator  - function pointer for custom deallocation

EAString* __fastcall EAString::EAString(EAString* this, const char* sourceString)
{
    int length;
    char* buffer;

    // Get the length of the source string (FUN_004d47e0 is likely stringLength)
    length = stringLength(sourceString);

    // Set both length and capacity to the same value (no extra allocation)
    this->mLength = length;
    this->mCapacity = length;

    // Allocate memory for the string + null terminator (FUN_009c8e50 is likely earAllocate)
    buffer = (char*)earAllocate(length + 1);

    // Store the buffer pointer
    this->mData = buffer;

    // Copy the source string into the allocated buffer
    memcpy(buffer, sourceString, length);

    // Null-terminate the string
    buffer[length] = '\0';

    // Set the custom deallocation function (thunk to FUN_009c8eb0, likely earFree)
    this->mDeallocator = (void*)earFree;

    return this;
}