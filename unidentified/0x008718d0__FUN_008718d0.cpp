// FUNC_NAME: SomeComponent::~SomeComponent

// Reconstructed destructor for an unknown component class.
// Typically sets vtable to a special destructor vtable, then releases a resource pointer at offset +0x8.

// Address: 0x008718d0
// Calling convention: __thiscall (implied by __fastcall with one parameter)

// Forward declaration of the class (partial)
class SomeComponent {
public:
    // Vtable pointer at +0x0
    void* vtable;
    // Resource pointer at +0x8
    void* m_pResource;

    ~SomeComponent();
    // static vtable for destructor (from Ghidra)
    static const void* kDestructorVtable;
};

// External helper functions called by destructor
namespace {
    void releaseResource(void* ptr);    // FUN_00851230
    void finalizeCleanup();             // FUN_009f01a0
}

SomeComponent::~SomeComponent() {
    // Set vtable to the destructor-specific vtable (ensures correct dispatch during destruction)
    this->vtable = &SomeComponent::kDestructorVtable;

    // If the resource pointer is non-null, release it and perform final cleanup
    if (this->m_pResource != 0) {
        releaseResource(this->m_pResource);
        finalizeCleanup();
        this->m_pResource = 0;
    }
}