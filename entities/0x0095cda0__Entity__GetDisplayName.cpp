// FUNC_NAME: Entity::GetDisplayName
// Address: 0x0095cda0
// Role: Retrieves a localized display name string from resource ID stored at +0x38, copies to output buffer (max 128 chars).
// Dependencies: LoadStringFromResource (0x00604000), StringCopyN (0x005c4660), internal deallocation.

void __thiscall Entity::GetDisplayName(int this, char *outBuffer)
{
    char *strPtr = nullptr;        // local_10 - pointer to loaded string
    int unusedOffset = 0;          // local_c - passed as 4th arg to StringCopyN (unused)
    int unused2 = 0;               // local_8 - unused
    // local_4 was a function pointer initialized to 0 in decompiled output;
    // actual code likely uses a hardcoded deallocation function (e.g., operator delete).

    // Load string from resource manager using key at +0x38
    LoadStringFromResource(*(int *)(this + 0x38), &strPtr, 1); // 1 = allocate flag

    // Use loaded string or fallback to default constant
    char *src = strPtr;
    if (strPtr == nullptr)
    {
        src = &DAT_0120546e; // Default string (e.g., "Unnamed")
    }

    // Copy string to output buffer, max 128 characters
    StringCopyN(outBuffer, src, 0x80, unusedOffset);

    // Free the dynamically allocated string
    if (strPtr != nullptr)
    {
        // In real code: operator delete[](strPtr) or free(strPtr)
        DeallocateString(strPtr);
    }
}