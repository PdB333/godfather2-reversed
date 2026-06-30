// FUNC_NAME: SomeClass::releaseResource
// Address: 0x006a8c80
// Role: Releases a resource pointed to by member at +0x40, then clears both pointer and associated count/size at +0x44.
// Called from destructor or cleanup path.

void __fastcall SomeClass::releaseResource(void)
{
    // +0x40: pointer to allocated resource (e.g., buffer, object)
    // +0x44: associated integer (e.g., size, count, or reference)
    if (*(int *)(this + 0x40) != 0) {
        // Call the actual deallocation function (likely free or release)
        FUN_005e3c00(*(int *)(this + 0x40));
        // Clear both fields to avoid dangling pointers
        *(int *)(this + 0x40) = 0;
        *(int *)(this + 0x44) = 0;
    }
}