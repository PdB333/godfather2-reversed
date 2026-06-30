// FUNC_NAME: isNotContainer
// Function at 0x007450a0: Validates that a pointer (containerPtr) is not the container of a member pointer stored at memberPtrHolder.
// The member is located at offset +0x48 from the container base.
// Returns true if the container does not match the expected value, indicating an invalid link.
bool __cdecl isNotContainer(int containerPtr, int* memberPtrHolder) {
    int memberPtr = *memberPtrHolder;
    if (memberPtr != 0) {
        // Expected container = memberPtr - 0x48 (since member is at +0x48 from container)
        return containerPtr != (memberPtr - 0x48);
    }
    // If member is null, container must also be null to be valid
    return containerPtr != 0;
}