// FUNC_NAME: RefCountedObject::addRef

// Reconstructed C++ for function at 0x0093dac0
// __thiscall: this pointer in ecx

class RefCountedObject {
public:
    // Unknown fields...
    // +0x54 : refCount (int)
    // +0x58 : vtablePtr or some pointer (int) - set only when refCount transitions from 0 to 1
    int refCount;        // offset 0x54
    int initialPtr;      // offset 0x58, set to global DAT_01205224 on first addRef

    void addRef() {
        if (refCount == 0) {
            initialPtr = DAT_01205224;   // global marker/vtable pointer
        }
        refCount++;
    }
};