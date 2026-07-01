// FUNC_NAME: SomeClass::QueryInterface (or IUnknown::QueryInterface)
// Function address: 0x00823b80
// Role: Provides interface querying capability. Returns a pointer to the current object if the requested
//       interface ID matches one of the two supported IDs (0x35a3a7ab or 0xFFD2E5B1).
//       This is a common pattern for COM-style interface resolution or component-based object systems.

bool __thiscall SomeClass::QueryInterface(int interfaceId, void** outPtr)
{
    // Check for first supported interface ID
    if (interfaceId == 0x35a3a7ab) {
        if (outPtr != nullptr) {
            *outPtr = this;   // Return pointer to current object as the interface
            return true;
        }
    }
    else {
        // Clear output pointer if provided (even if we later fail)
        if (outPtr != nullptr) {
            *outPtr = nullptr;
        }
        // Check for second supported interface ID (0xFFD2E5B1 as unsigned, -0x2d1a4f as signed)
        if (interfaceId != -0x2d1a4f) {
            return false;       // Unsupported interface ID
        }
        if (outPtr != nullptr) {
            *outPtr = this;     // Return pointer to current object for the second interface
        }
    }
    return true;
}