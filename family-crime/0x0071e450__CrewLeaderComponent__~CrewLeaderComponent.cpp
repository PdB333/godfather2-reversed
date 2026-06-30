// FUNC_NAME: CrewLeaderComponent::~CrewLeaderComponent

class CrewLeaderComponent {
public:
    void** vtable;                    // +0x00
    // +0x14: children[0]
    // +0x20: children[1]
    // +0x2c: children[2]
    // +0x38: children[3]
    // +0x44: children[4]
    // +0x50: children[5]
    // +0x5c: children[6]
    // +0x68: children[7]
    void* children[8];                // 8 pointers at offsets 0x14, 0x20, 0x2c, 0x38, 0x44, 0x50, 0x5c, 0x68
    // +0x78: m_pSomePointer
    void* somePointer;                // +0x78 (index 0x1e)
    // +0x84: m_Flags
    uint32_t flags;                   // +0x84 (index 0x21)
    // total size >= 0x88

    // Destructor
    void __thiscall ~CrewLeaderComponent();
};

// Helper functions (deduced from calls)
extern void SetDerivedVTable(CrewLeaderComponent* obj);  // sets vtable to PTR_FUN_00d61e30
extern void ResetToBaseVTable(CrewLeaderComponent* obj); // sets vtable to PTR_LAB_00d61acc
extern void DerivedCleanup(CrewLeaderComponent* obj);    // FUN_007ee320
extern void BaseCleanup();                               // FUN_0071dc20
extern void FreePointerAndSetNull(void** pp);            // FUN_004daf90

void __thiscall CrewLeaderComponent::~CrewLeaderComponent() {
    // Set vtable to derived class's vtable during destruction
    SetDerivedVTable(this);

    // If flag bit 0 is set, perform additional cleanup
    if (this->flags & 1) {
        this->flags &= ~1;
        DerivedCleanup(this);
        BaseCleanup();
    }

    // Free the single pointer at offset +0x78
    if (this->somePointer != nullptr) {
        FreePointerAndSetNull(&this->somePointer);
    }

    // Free all 8 child pointers in reverse order (from last to first)
    // The loop iterates indices 7 down to 0 (offsets 0x68, 0x5c, ..., 0x14)
    for (int i = 7; i >= 0; --i) {
        if (this->children[i] != nullptr) {
            FreePointerAndSetNull(&this->children[i]);
        }
    }

    // Restore base vtable after cleanup (for correct destruction chain)
    ResetToBaseVTable(this);
}