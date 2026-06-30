// FUNC_NAME: Global_clearEntryByID
// Function at 0x006fbca0: Iterates through a global linked list and clears the entry that matches the given ID.
// The list node structure: offset0 = some key (maybe handle), offset4 = ID, offset8 = unknown, offsetC = next pointer.
// Clearing sets both offset0 and offset4 to 0, marking it as unused.

#include <cstdint>

// Structure for a linked list node used by this function.
struct EntryNode {
    int32_t key;       // +0x00: Some key or handle
    int32_t id;        // +0x04: The ID to match
    int32_t unknown;   // +0x08: Possibly padding or another field
    EntryNode* next;   // +0x0C: Pointer to next node
};

// Global head of the linked list (defined elsewhere).
extern EntryNode* g_entryListHead; // originally DAT_0112aaa8

void Global_clearEntryByID(int32_t idToClear)
{
    EntryNode* currentNode = g_entryListHead;
    if (currentNode != nullptr)
    {
        do
        {
            if (currentNode->id == idToClear)
            {
                // Clear the entry's key and ID to mark as invalid
                currentNode->key = 0;
                currentNode->id = 0;
            }
            currentNode = currentNode->next;
        }
        while (currentNode != nullptr);
    }
}