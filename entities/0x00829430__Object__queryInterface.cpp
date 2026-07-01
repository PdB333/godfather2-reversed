// FUNC_NAME: Object::queryInterface
// Function address: 0x00829430
// This function appears to be a simplified QueryInterface implementation.
// It checks the property ID against two known constants and returns a pointer to itself if matched.
// Returns 1 (S_OK) on success, 0 on failure.
int __thiscall queryInterface(int propertyId, void** outPtr)
{
    // 0xD87443A3 = -0x278bbc5d (as signed)
    if (propertyId == 0xD87443A3) {
        if (outPtr != nullptr) {
            *outPtr = (void*)this;
            return 1;
        }
    }
    else {
        if (outPtr != nullptr) {
            *outPtr = nullptr;
        }
        // 0xFFD2E5B1 = -0x2d1a4f (as signed)
        if (propertyId != 0xFFD2E5B1) {
            return 0; // Not a known property
        }
        if (outPtr != nullptr) {
            *outPtr = (void*)this;
        }
    }
    return 1;
}