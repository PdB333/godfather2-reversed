// FUNC_NAME: GameplayDebugger::DebugNode::constructor
// Function at 0x00766540: Constructor for a debug node that inserts itself into a global linked list managed by GameplayDebugger.
// Associated globals: g_gameplayDebugger (DAT_012233a0) holds singleton pointer; offset +4 points to list head node.
// Offsets for this object:
// +0x00: vtable (PTR_LAB_00d65850)
// +0x48: pointer to parent/related node (field_0x48)
// +0x50: derived offset (parent base address, parent-0x48)
// +0x54: pointer to the list head (pHeadLink)
// +0x58: next node in list (pListNext)
// +0x5C: unknown (field_0x5C)
// +0x60: flags byte (flags)
// The list uses a sentinel head; pHeadLink points to head, pListNext is the actual successor.
// Insertion is done at the front of the list.

class DebugNode : public SomeBase {
public:
    void* field_0x48;      // +0x48
    void* field_0x50;      // +0x50
    DebugNode* pHeadLink;  // +0x54  (points to list head node)
    DebugNode* pListNext;  // +0x58
    int field_0x5C;        // +0x5C
    byte flags;            // +0x60

    DebugNode(void* arg2, void* arg3) {
        SomeBase::constructor(arg2, arg3); // FUN_004ac120
        this->vtable = &PTR_LAB_00d65850;
        this->pHeadLink = nullptr;
        this->pListNext = nullptr;
        this->flags = 0;

        // Compute parent base address from field_0x48
        if (this->field_0x48 == nullptr) {
            this->field_0x50 = nullptr;
        } else {
            this->field_0x50 = (byte*)this->field_0x48 - 0x48;
        }

        // Retrieve the global list head (sentinel) from g_gameplayDebugger singleton
        DebugNode* headNode = nullptr;
        if (*(int**)((int)g_gameplayDebugger + 4) != nullptr) {
            headNode = (DebugNode*)(*(int**)((int)g_gameplayDebugger + 4) - 0x1f30);
        }

        // Insert this node into the list if not already present
        if (this->pHeadLink != headNode) {
            if (this->pHeadLink != nullptr) {
                // Remove from old list
                FUN_004daf90(&this->pHeadLink); // removeNode
            }
            this->pHeadLink = headNode;
            if (headNode != nullptr) {
                // Link in at the front
                this->pListNext = (DebugNode*)*(int*)((int)headNode + 4);
                *(int**)((int)headNode + 4) = &this->pHeadLink;
            }
        }
        this->field_0x5C = 0;

        // Conditional flag set based on global debug state
        if ((this->pHeadLink != nullptr) && (this->pHeadLink != (DebugNode*)0x48)) {
            int condition = FUN_007ff880(); // e.g., isDebugModeEnabled
            if (condition != 0) {
                int base = (this->pHeadLink == nullptr) ? 0 : (int)this->pHeadLink - 0x48;
                if ((*(uint*)(base + 0x8e0) >> 4 & 1) != 0) {
                    this->flags |= 4;
                    return;
                }
            }
        }
    }
};