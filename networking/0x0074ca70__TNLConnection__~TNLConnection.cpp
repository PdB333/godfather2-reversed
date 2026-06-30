// FUNC_NAME: TNLConnection::~TNLConnection

#pragma pack(push, 1)
struct TNLConnection {
    void* vtable; // +0x00

    // Unknown members from +0x04 to +0x33 (48 bytes)
    // (omitted for brevity)

    struct Slot {
        void* m_pObject; // +0x00
        int field_4;     // +0x04
        int field_8;     // +0x08
    };

    Slot m_slots[32]; // offset +0x34

    // Internal cleanup helper (address 0x004daf90)
    void __thiscall cleanupSlot(Slot* slot);

    // Destructor
    virtual __thiscall ~TNLConnection() {
        // Iterate slots from last to first, cleaning up non-null pointers
        for (int i = 31; i >= 0; --i) {
            Slot* slot = &m_slots[i];
            if (slot->m_pObject != 0) {
                cleanupSlot(slot);
            }
        }
        // Set vtable to purecall to prevent further virtual calls
        this->vtable = (void*)0x00e407a4;
    }
};
#pragma pack(pop)