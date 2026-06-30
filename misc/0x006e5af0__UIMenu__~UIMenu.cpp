// FUNC_NAME: UIMenu::~UIMenu
// Reconstructed based on Ghidra decompilation at 0x006e5af0
// Class manages a linked list of items (m_pItemList at +0x04) and a single child object (m_pChild at +0x18).
// Destructor clears list nodes (without freeing them) and destroys the child object.

class UIMenu {
public:
    void** vtable;                  // +0x00 vtable pointer
    class ItemNode* m_pItemList;    // +0x04 head of singly linked list
    // +0x08 .. +0x14 unknown
    class ChildObject* m_pChild;    // +0x18 single child object

    // Forward declarations
    void __fastcall destroyChild(ChildObject* obj); // calls FUN_004daf90
};

struct ItemNode {
    void* pData;                    // +0x00 arbitrary data (cleared to 0)
    ItemNode* pNext;                // +0x04 next node (cleared to 0)
};

void __fastcall UIMenu::~UIMenu(void* thisPtr)
{
    UIMenu* self = (UIMenu*)thisPtr;

    // Set vtable to first target (likely most-derived or a specific cleanup vtable)
    self->vtable = (void**)&PTR_FUN_00d5faf8;

    // Destroy child object if present
    if (self->m_pChild != 0) {
        self->destroyChild(self->m_pChild); // calls FUN_004daf90 on the pointer
    }

    // Reset vtable to base class (or final vtable) after derived cleanup
    self->vtable = (void**)&PTR_FUN_00e32808;

    // Clear linked list: iterate and zero out each node (no deallocation)
    ItemNode* node = self->m_pItemList;
    while (node != 0) {
        ItemNode* next = node->pNext;
        node->pNext = 0;
        node->pData = 0;
        node = next;
    }
}