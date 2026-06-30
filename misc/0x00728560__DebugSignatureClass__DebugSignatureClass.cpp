// FUNC_NAME: DebugSignatureClass::DebugSignatureClass

// Constructor at 0x00728560 - likely a debug/development class with multiple vtable pointers and sentinel values.
// Calls a base constructor (FUN_0046c590) and initializes several zero-filled fields along with a signature block.

class DebugSignatureClass {
public:
    DebugSignatureClass(int param2) {
        // Call base class constructor (unknown, but takes param2)
        baseConstructor(param2);

        // Set up multiple virtual table pointers (multiple inheritance / interfaces)
        *(void**)this = (void*)0x00d62498;                 // +0x00: main vtable
        *(void**)((char*)this + 0x3C) = (void*)0x00d62488; // +0x3C: secondary vtable
        *(void**)((char*)this + 0x48) = (void*)0x00d62484; // +0x48: tertiary vtable

        // Zero-initialize various fields (likely vectors, quaternions, etc.)
        *(int*)((char*)this + 0x50) = 0;  // +0x50: int (maybe x of position)
        *(int*)((char*)this + 0x54) = 0;  // +0x54: int (y)
        *(int*)((char*)this + 0x58) = 0;  // +0x58: int (z)
        *(short*)((char*)this + 0x5C) = 0; // +0x5C: short
        *(short*)((char*)this + 0x5E) = 0; // +0x5E: short
        *(int*)((char*)this + 0x60) = 0;  // +0x60
        *(int*)((char*)this + 0x64) = 0;  // +0x64
        *(int*)((char*)this + 0x68) = 0;  // +0x68

        // Block 1 (4 ints)
        *(int*)((char*)this + 0x6C) = 0;  // +0x6C
        *(int*)((char*)this + 0x70) = 0;  // +0x70
        *(int*)((char*)this + 0x74) = 0;  // +0x74
        *(int*)((char*)this + 0x78) = 0;  // +0x78

        // Block 2 (4 ints)
        *(int*)((char*)this + 0x7C) = 0;  // +0x7C
        *(int*)((char*)this + 0x80) = 0;  // +0x80
        *(int*)((char*)this + 0x84) = 0;  // +0x84
        *(int*)((char*)this + 0x88) = 0;  // +0x88

        // Debug sentinel / magic signature block (4 ints)
        *(int*)((char*)this + 0x8C) = 0xbadbadba;  // +0x8C: bad memory marker
        *(int*)((char*)this + 0x90) = 0xbeefbeef;  // +0x90: beef marker
        *(int*)((char*)this + 0x94) = 0xeac15a55;  // +0x94: unknown sentinel
        *(int*)((char*)this + 0x98) = 0x91100911;  // +0x98: version/date marker

        // Tail zeros
        *(int*)((char*)this + 0x9C) = 0;  // +0x9C
        *(int*)((char*)this + 0xA0) = 0;  // +0xA0
    }

private:
    // The actual base constructor is not inlined; defined elsewhere.
    void baseConstructor(int);
};