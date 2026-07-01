//FUNC_NAME: SubComponent::release

class Component; // forward declaration

class SubComponent {
public:
    // Fields relative to SubComponent start (this pointer)
    // +0x00: unknown (size 0xc)
    // +0x0c: flags (uint32)
    // +0x10: unknown (size 4)
    // +0x14: pointer to some object (int*)
    uint32_t flags; // at offset 0xc
    int* ptr;       // at offset 0x14

    void release(); // __fastcall, this in ecx
};

// External functions (from the game binary)
void removeFromParent(Component* parent); // FUN_0081cf20
int releaseReference(int* obj);           // FUN_006b07e0, returns non-zero if last reference
void finalizeCleanup(Component* parent);  // FUN_006aebe0

void __fastcall SubComponent::release() {
    // Check if bit 3 of flags is set (indicates some resource is active)
    if ((this->flags >> 3) & 1) {
        // Get parent Component (this is at offset 0x180 inside parent)
        Component* parent = reinterpret_cast<Component*>(reinterpret_cast<char*>(this) - 0x180);
        removeFromParent(parent);
        // Clear bit 3
        this->flags &= ~0x8;
    }

    // If the pointer at +0x14 is non-null, release it
    if (this->ptr != nullptr) {
        int refCount = releaseReference(this->ptr);
        if (refCount != 0) {
            // Last reference released, do additional cleanup on parent
            Component* parent = reinterpret_cast<Component*>(reinterpret_cast<char*>(this) - 0x180);
            finalizeCleanup(parent);
        }
    }

    // Call virtual function at vtable+0x28 on parent (likely destructor or final cleanup)
    Component* parent = reinterpret_cast<Component*>(reinterpret_cast<char*>(this) - 0x180);
    // Parent's vtable pointer is at offset 0x58 from parent base
    void** vtable = *reinterpret_cast<void***>(reinterpret_cast<char*>(parent) + 0x58);
    typedef void (*VirtualFunc)();
    VirtualFunc func = reinterpret_cast<VirtualFunc>(vtable[0x28 / 4]);
    func();
}