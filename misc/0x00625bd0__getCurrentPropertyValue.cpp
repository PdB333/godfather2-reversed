// FUNC_NAME: getCurrentPropertyValue

// Function: 0x00625bd0
// Retrieves the value of the current element in a variant property list iterator.
// The iterator structure (this) has:
//   +0x08 : end pointer (one past last element)
//   +0x0C : current element pointer
// Each element is a 2-word struct: { int type; int value; }
// Types 2 and 7 require a conversion call to 0x00625b60.
// Types 5, 6, 8 return the raw value word directly.
// Otherwise returns 0.

struct VariantElement {
    int type;   // +0x00: discriminator
    int value;  // +0x04: payload
};

// External conversion function for certain types (e.g. float/int unpack)
int __attribute__((cdecl)) FUN_00625b60();

int __thiscall getCurrentPropertyValue(void* thisPtr) {
    VariantElement** currentPtr = reinterpret_cast<VariantElement**>(
        reinterpret_cast<char*>(thisPtr) + 0xC);
    VariantElement** endPtr = reinterpret_cast<VariantElement**>(
        reinterpret_cast<char*>(thisPtr) + 0x8);

    // Ensure current pointer is valid and within bounds
    if (*currentPtr != nullptr && *currentPtr < *endPtr) {
        VariantElement* elem = *currentPtr;
        switch (elem->type) {
            case 2:
            case 7:
                return FUN_00625b60();   // Convert and return
            case 5:
            case 6:
            case 8:
                return elem->value;      // Direct return
            default:
                break;
        }
    }
    return 0;
}