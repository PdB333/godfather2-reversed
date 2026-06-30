// FUNC_NAME: EARSObject::activateAndUpdateChildren
// Address: 0x004a4e50
// Description: Activates this object (sets active flag, adds to global active list) then calls a virtual update on children that have both active and update-requested flags.

#include <cstdint>

// Forward declarations and global variable declarations
void removeFromGlobalList(int param); // Called before insertion, argument is 0
extern EARSObject* g_activeListHead; // Formerly DAT_01205488
extern EARSObject* g_activeListTail; // Formerly DAT_0120548c

// Represents a child entry in the array (each entry is 0x10 bytes)
struct ChildEntry {
    EARSComponent* component;  // +0x00: pointer to a component object (with vtable)
    uint16_t flags;            // +0x04: bitfield (bit0=1? bit1=2:active, bit9=0x200:updateRequested)
    uint8_t  padding[10];      // +0x06 to +0x0F (remainder)
};

// The class itself (partial definition)
class EARSObject {
public:
    // Fields (offsets relative to this)
    // +0x00: vtable pointer (implied)
    // +0x68: pointer to array of ChildEntry (each 16 bytes)
    ChildEntry* m_childArray;
    // +0x6c: number of children
    uint32_t m_childCount;
    // +0x80: flags (ushort)
    uint16_t m_flags;
    // +0x8c: previous pointer in global active list
    EARSObject* m_prevActive;
    // +0x90: next pointer in global active list
    EARSObject* m_nextActive;

    // The method as decompiled
    void activateAndUpdateChildren();
};

// Virtual method at vtable+0x3c in EARSComponent (likely a pure virtual update)
typedef void (__thiscall *ComponentUpdateFunc)(EARSComponent*);

void __thiscall EARSObject::activateAndUpdateChildren() {
    // Part 1: Activation – if the object has the "pending activation" flag (bit2),
    // transition to "active" (set bit1), remove from any previous state, and add to global active list.
    if ((m_flags & 0x4) != 0) {
        m_flags = (m_flags & 0xFFFB) | 0x2;  // clear bit2, set bit1
        removeFromGlobalList(0);              // ensure it's not in any list

        EARSObject* oldHead = g_activeListHead;
        if (g_activeListTail != nullptr) {
            g_activeListTail->m_nextActive = this;   // append to tail
            oldHead = g_activeListHead;
        }
        g_activeListHead = this;                     // new head (actually always head? tail update missing? Check original: iVar3 = param_1; if (DAT_0120548c !=0) {*(int *)(DAT_0120548c+0x90) = param_1; iVar3 = DAT_01205488;} DAT_01205488 = iVar3; so tail->next = this, head stays old head? Then set head = this? Wait logic: if tail exists, set tail->next = this, then head = oldHead (which stays same). So this becomes new tail? Actually then set DAT_01205488 = oldHead? That would be wrong. Let's re-analyze.

        // Original: iVar3 = param_1; if (DAT_0120548c !=0) { *(int *)(DAT_0120548c+0x90) = param_1; iVar3 = DAT_01205488; } DAT_01205488 = iVar3; So iVar3 starts as this. If tail exists, it sets tail->next = this, then iVar3 = head. Then head = iVar3 (which is head, unchanged). So this becomes new tail? But then it sets this->prev = tail, this->next = 0. So it's adding to end? Actually head is DAT_01205488, tail is DAT_0120548c. The code: if (tail) { tail->next = this; iVar3 = head; } head = iVar3; So head remains same. Then set this->prev = tail, this->next = 0; tail = this. So yes, it appends to the end of the doubly linked list.
        // So reconstruction: if tail exists, set tail->next = this; else tail is null, so head = this (since iVar3 was this, then head = this). Then set this->prev = tail; this->next = 0; tail = this.
        // Let's correct the reconstruction.

        // Correct reconstruction based on original:
        EARSObject* oldTail = g_activeListTail;
        if (oldTail != nullptr) {
            oldTail->m_nextActive = this;
        } else {
            // list was empty, so head will become this
            g_activeListHead = this;
        }
        this->m_prevActive = oldTail;
        this->m_nextActive = nullptr;
        g_activeListTail = this;
    }

    // Part 2: Process children – for each child that has both active (bit1) and update-requested (bit9) flags,
    // call the virtual method at vtable offset 0x3c (assuming it's an update function).
    if (m_childCount != 0) {
        for (uint32_t i = 0; i < m_childCount; i++) {
            ChildEntry* entry = &m_childArray[i];
            uint16_t childFlags = entry->flags;
            if ((childFlags & 0x2) != 0 && (childFlags & 0x200) != 0) {
                // The component pointer is stored at the beginning of each child entry
                EARSComponent* component = entry->component;
                // Call the virtual function at vtable+0x3c
                ComponentUpdateFunc updateFunc = *(ComponentUpdateFunc*)(*(uint32_t*)component + 0x3C);
                updateFunc(component);
            }
        }
    }
}