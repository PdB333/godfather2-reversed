// FUNC_NAME: PacketWindow::PacketWindow

class PacketEntry {
public:
    void* m_data;      // +0x00
    int m_field4;      // +0x04
    int m_field8;      // +0x08
};

class PacketWindow {
public:
    PacketWindow(int windowSize, int maxSlots);
    // ... other methods
private:
    void freeEntry(PacketEntry* entry); // wrapper for FUN_004daf90

    // +0x00 vtable pointer (set to PTR_FUN_00d5d8c8)
    int m_windowSize;    // +0x04
    int m_maxSlots;      // +0x08
    PacketEntry m_entries[32]; // +0x0C (each 12 bytes, total 384)
    int m_extra;         // +0x18C (offset 396)
};

PacketWindow::PacketWindow(int windowSize, int maxSlots) {
    // Set vtable
    *(void**)this = (void*)0x00d5d8c8;

    // Initialize all entries to zero
    PacketEntry* entry = &m_entries[0];
    for (int i = 0; i < 32; i++) {
        entry->m_data  = nullptr;
        entry->m_field4 = 0;
        entry->m_field8 = 0;
        entry++;
    }

    m_windowSize = windowSize;
    m_maxSlots = maxSlots;

    // Clean any leftover entries (should be null after above, but safe)
    entry = &m_entries[0];
    for (int i = 0; i < 32; i++) {
        if (entry->m_data != nullptr) {
            freeEntry(entry);
            entry->m_data = nullptr;
        }
        entry->m_field8 = 0;
        entry++;
    }

    m_extra = 0;
}