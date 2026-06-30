// FUNC_NAME: RefCounted::assign (variant with list insertion)
// Address: 0x006fea40
// Role: Copies data from source object (param_3) into this, updates a doubly-linked list membership,
//       and calls a registration/tracking function with the given key and extra params.

#include <cstdint>

// Forward declaration of the deallocation function
void freeListNode(void* ptr); // 0x004daf90 - likely frees a list node

// Forward declaration of the tracking/register function
uint32_t registerByKey(int key, uint32_t extraA, uint32_t extraB); // 0x006fe750

// Structure representing a node in the linked list (offset 0x48 from the containing object)
struct ListNode {
    ListNode* next;      // +0x00
    ListNode* prev;      // +0x04
};

// RefCounted base class (inferred layout)
struct RefCounted {
    void (__thiscall* vtable[?])();   // +0x00
    int field_4;                       // +0x04
    // ... gaps ...
    int* m_pListEntry;                 // +0x10 (pointer to a ListNode pointer field in parent)
    int  m_savedNext;                  // +0x14 (temporary storage for list insertion)
    void* m_pSome;                     // +0x18 (used in vtable call)
    int  m_type;                       // +0x1C (4=active, 0=unused, 3=other)
};

uint32_t __thiscall
RefCounted::assign(RefCounted* this, int key, const RefCounted* source, int listParent, uint32_t extraA, uint32_t extraB)
{
    uint32_t retVal = 0;
    // Initial value based on EAX (likely used for flag checking elsewhere, overwritten later)

    if (key != 0) {
        // If the object is valid and its type is not one of the special states (0,3,4),
        // call a cleanup function through the vtable.
        if ( (this->vtable != nullptr) &&
             (int type = this->m_type; type != 4 && type != 0 && type != 3) )
        {
            this->vtable[0](this->m_pSome, 4, this->field_4);
        }

        // Copy the vtable pointer and field_4 from source (if different object)
        if (this != source) {
            this->vtable = source->vtable;
            this->field_4 = source->field_4;
        }

        // Handle linked list insertion (listParent is a pointer to an object that contains a ListNode at offset 0x48)
        int* newListEntryPtr = (listParent != 0) ? (int*)((char*)listParent + 0x48) : (int*)0;
        if (this->m_pListEntry != newListEntryPtr) {
            // Remove old list entry if present
            if (this->m_pListEntry != 0) {
                freeListNode(this->m_pListEntry);  // deallocate old node
            }
            this->m_pListEntry = newListEntryPtr;
            if (newListEntryPtr != 0) {
                // Save the current next pointer of the list node at newListEntryPtr+4
                this->m_savedNext = *(newListEntryPtr + 4);
                // Insert this node's list pointer into the list: update the prev pointer of the node pointed by newListEntryPtr
                *(int**)((char*)newListEntryPtr + 4) = &(this->m_pListEntry);
            }
        }

        // Register or acquire a reference based on the key
        retVal = registerByKey(key, extraA, extraB);
    }

    return retVal;
}