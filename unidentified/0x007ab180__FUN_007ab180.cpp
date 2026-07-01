// FUNC_NAME: UnknownClass::getField6c
// Function address: 0x007ab180
// Role: Simple getter for a 4-byte value at offset 0x6c from this object.
// This is likely a member field accessor in an EARS engine class.
// TODO: Determine actual class name and field purpose.

// __thiscall convention
class UnknownClass {
public:
    // Returns the value at +0x6c (4 bytes)
    // Typically a pointer, handle, or 32-bit integer.
    int getField6c() {
        return *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 0x6C);
    }
};