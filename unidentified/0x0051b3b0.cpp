// FUN_0051b3b0: EARSObject::destroy

class EARSObject {
public:
    uint32_t m_flags;               // +0x0C: flag bits (0x200000 = destroying)
    EARSObject** m_ppParentLink;    // +0x08: pointer to parent's pointer to this child (used to clear parent's reference)
    EARSObject* m_pNext;            // +0x14: next node in global object list
    EARSObject* m_pOwner;           // +0x18: owning/parent object

    void destroy();
};

extern EARSObject* g_pObjectListHead; // 0x01205514
extern void preDestroy();            // FUN_0051d6b0

void EARSObject::destroy() {
    // Mark object as being destroyed to avoid recursive reentry
    m_flags |= 0x200000;

    // Execute pre-destruction logic (e.g., notify attached systems)
    preDestroy();

    // Clear the back-pointer in the parent if it exists
    // This removes this object from the parent's child list (or similar link)
    if (m_ppParentLink != nullptr) {
        *m_ppParentLink = nullptr;
        m_ppParentLink = nullptr;
    }

    // Recursively destroy all child objects that reference this as owner
    EARSObject* iter = g_pObjectListHead;
    while (iter != nullptr) {
        EARSObject* next = iter->m_pNext;
        if (iter->m_pOwner == this && (iter->m_flags & 0x200000) == 0) {
            iter->destroy();
        }
        iter = next;
    }
}