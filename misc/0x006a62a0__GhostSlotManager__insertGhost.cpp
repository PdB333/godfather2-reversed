// FUNC_NAME: GhostSlotManager::insertGhost
// Function at 0x006a62a0: Insert a ghost node into a slot and manage packet window state
// This function finds an empty slot or a slot matching the given id, then inserts a linked list node
// into the slot's list and updates slot data with transform/scale information.

#include <cstdint>

// Global float constant used for scaling (e.g., inverse square of distance)
extern float g_scaleFactor; // from _DAT_00d5780c

struct GhostSlot {
    int32_t id;           // +0x00
    int32_t* listHead;    // +0x04, pointer to linked list of nodes
    float pos[3];         // +0x0C, position/transform
    float scale;          // +0x18
    uint32_t data1;       // +0x20
    uint32_t data2;       // +0x24
}; // total size 0x28

struct GhostNode {
    int32_t value;        // +0x00
    GhostNode* next;      // +0x04 (pointer stored at node+4)
};

class GhostSlotManager {
public:
    // Array of 32 slots starting at offset 0x20
    // Note: The scanning loop uses a base at this+0x48 (slot index 1)
    GhostSlot m_slots[32];      // +0x20, size 32*0x28 = 0x500, ends at 0x520

    int32_t m_activeCount;      // +0x520 (starts where m_slots ends)
    GhostNode** m_currentHead;  // +0x53c, pointer to head of a list (maybe temporary)
    int32_t m_currentSlotIndex; // +0x678, current slot index (-1 if none)
    int32_t m_currentNode;      // +0x68c, value of a node (maybe current node id)
    int32_t m_useCustom;        // +0x6a4, flag: use custom transform/scale
    float m_customPos[3];       // +0x6a8, custom position
    float m_customScale;        // +0x6b4, custom scale
    int32_t m_state;            // +0x6b8, state (0=idle,1=active,2=done)

public:
    // Main function: inserts or finds a slot for given id and attaches a node
    bool insertGhost(int32_t id, GhostNode** nodePtr, uint32_t extraData1, uint32_t extraData2);
};

bool GhostSlotManager::insertGhost(int32_t id, GhostNode** nodePtr, uint32_t extraData1, uint32_t extraData2) {
    int32_t emptySlotIndex = -1;
    bool success = false;
    int32_t i = 0;
    GhostSlot* slot = &m_slots[1]; // Start at slot index 1 because scan uses this+0x48 = &m_slots[1]

    // Scan 32 slots in groups of 4 (stride 0x28)
    while (i < 32) {
        // Check slots i, i+1, i+2, i+3 relative to current slot pointer
        // slot[-1] is m_slots[i], slot[0] is m_slots[i+1], slot[1] is m_slots[i+2], slot[2] is m_slots[i+3]
        int32_t currentSlotIndex = i; // for first slot checked
        // Slot at index i (slot[-1])
        if (emptySlotIndex < 0 && (slot[-1].id == 0)) {
            emptySlotIndex = i;
        } else if (slot[-1].id == id) {
            // Found matching slot
            i = i; // already set
            break;
        }

        // Slot at index i+1 (slot[0])
        if (emptySlotIndex < 0 && (slot[0].id == 0)) {
            emptySlotIndex = i + 1;
        } else if (slot[0].id == id) {
            i = i + 1;
            break;
        }

        // Slot at index i+2 (slot[1])
        if (emptySlotIndex < 0 && (slot[1].id == 0)) {
            emptySlotIndex = i + 2;
        } else if (slot[1].id == id) {
            i = i + 2;
            break;
        }

        // Slot at index i+3 (slot[2])
        if (emptySlotIndex < 0 && (slot[2].id == 0)) {
            emptySlotIndex = i + 3;
        } else if (slot[2].id == id) {
            i = i + 3;
            break;
        }

        i += 4;
        slot += 4; // move by 4 slots (0x28*4 = 0xA0 bytes) but pointer arithmetic in int* units
        // Actually slot is a GhostSlot pointer, so incrementing by 4 moves by 4*0x28 = 0xA0 bytes
    }

    // If we found a matching slot (i<32) OR an empty slot (emptySlotIndex>=0), then if slot not found and no empty, fail
    if (i < 32 || emptySlotIndex >= 0) {
        // If no empty slot found and no match
        return false;
    }

    // Determine the slot index to use: if matching, use i; else use emptySlotIndex
    int32_t slotIndex;
    if (i < 32) {
        slotIndex = i;
    } else {
        slotIndex = emptySlotIndex;
    }

    // Now handle the linked list insertion
    GhostNode* existingNode = *nodePtr;  // param_3 is node pointer, its content is the node to insert?
    // Actually param_3 is a pointer to a GhostNode* (double pointer) - nodePtr
    int32_t nodeValue = existingNode->value; // first int of node
    GhostNode* listHead = nullptr;
    GhostNode* newListNode = nullptr;

    if (nodeValue == 0 || nodeValue == 0x48) {
        // Node value is sentinel: use the current slot's list head
        if (m_currentSlotIndex >= 0) {
            GhostSlot* curSlot = &m_slots[m_currentSlotIndex];
            if (curSlot->listHead == &listHead) {
                goto finish;
            }
            newListNode = (GhostNode*)curSlot->listHead;
            existingNode = curSlot->listHead; // reuse
        } else {
            // No current slot, check if m_currentNode is sentinel
            if (m_currentNode != 0 && m_currentNode != 0x48) {
                // Use the node from m_currentNode?
                existingNode = (GhostNode*)m_currentNode;
            } else {
                // Fallback: call a helper to set up? The decompiled calls FUN_006a5d20 and FUN_006a5380
                // We'll assume those are internal setup functions, not fully reconstructible
                // For now, we'll just set newListNode to null and let later code handle it
                newListNode = nullptr;
            }
        }
    } else {
        // Node value is normal
        newListNode = existingNode;
    }

    // If newListNode is null, skip insertion
    if (newListNode == nullptr) {
        goto finish;
    }

    // Insert node at head of local list
    existingNode->next = (GhostNode*)&listHead; // store pointer to head
    listHead = newListNode;

    // If the list head is valid, increment count
    if (listHead != nullptr && (int32_t)listHead != 0x48) {
        m_activeCount++;

        // Set up the slot at slotIndex
        GhostSlot* targetSlot = &m_slots[slotIndex];
        targetSlot->id = id;
        // Link the slot's listHead to the head of our temporary list
        if (targetSlot->listHead != &listHead) {
            if (targetSlot->listHead != nullptr) {
                // Remove existing list (FUN_004daf90 likely a destructor)
                // We'll simulate with a call to destroyList
                destroyList(targetSlot->listHead);
            }
            targetSlot->listHead = (int32_t*)listHead; // store the head pointer
            if (listHead != nullptr) {
                // Update the next pointer of the new head to point to the slot's listHead field
                *(int32_t*)(listHead + 4) = (int32_t)&targetSlot->listHead;
            }
        }

        targetSlot->data1 = extraData1;
        targetSlot->data2 = extraData2;

        if (m_useCustom == 0) {
            targetSlot->pos[0] = 0;
            targetSlot->pos[1] = 0;
            targetSlot->pos[2] = 0;
            targetSlot->scale = g_scaleFactor;
        } else {
            targetSlot->pos[0] = m_customPos[0];
            targetSlot->pos[1] = m_customPos[1];
            targetSlot->pos[2] = m_customPos[2];
            targetSlot->scale = g_scaleFactor / (m_customScale * m_customScale);
        }

        // Notify that insertion is complete (FUN_006a57c0)
        onSlotInserted();
    }

    success = true;

finish:
    // Update state machine
    if (m_state == 0) {
        m_useCustom = 0;
    } else if (m_state == 1) {
        m_state = 2;
    }

    // If list head exists, clear it (FUN_004daf90 likely frees the list)
    if (listHead != nullptr) {
        destroyList(listHead);
    }

    return success;
}

// Stub functions for calls that are not fully reconstructed
void GhostSlotManager::destroyList(GhostNode* head) {
    // Placeholder: would normally free nodes
    // FUN_004daf90
}

void GhostSlotManager::onSlotInserted() {
    // Placeholder: FUN_006a57c0
}