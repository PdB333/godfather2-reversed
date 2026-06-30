// FUNC_NAME: SomeClass::blockingPollUntilSuccess
// Address: 0x004d4a90
// This function repeatedly calls pollStatus until it returns a non-negative value.
// It is a blocking wait for a resource or condition to become available.
// param_1 appears to be the 'this' pointer (ECX in __thiscall), param_2 is likely a resource identifier or handle.

void SomeClass::blockingPollUntilSuccess(int resourceId) // param_2 -> resourceId
{
    int status = pollStatus(this, resourceId); // FUN_004d4a10
    while (status < 0) {
        // Keep polling while the resource is busy (negative return)
        status = pollStatus(this, resourceId);
    }
    // Non-negative status indicates success or ready
}