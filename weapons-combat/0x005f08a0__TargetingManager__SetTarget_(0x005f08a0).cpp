// FUNC_NAME: TargetingManager::SetTarget (0x005f08a0)
// This function selects a target by ID. It iterates a linked list of selectable items,
// checking if the target is available (non-zero byte at node+0x08). If unavailable, it clears
// current selection and returns 0 (failure). Otherwise, it clears current, calls a reset helper,
// and optionally sets the new selection if forceClearOnly is false. Returns 1 on success.
// Register usage: ESI = this, EDI = targetId, stack param = forceClearOnly.

class TargetingManager {
public:
    int   currentSelection;    // +0x04: currently selected target ID (0 if none)
    void* selectableListHead;  // +0x08: linked list of SelectableNode entries
    short someFlag;            // +0x12: non-zero when there are selectable items

    struct SelectableNode {
        void*       unknown;    // +0x00
        SelectableNode* next;   // +0x04
        char        available;  // +0x08: 0 = cannot be selected, non-zero = selectable
        void*       entity;     // +0x0C: pointer to entity with ID at +0x44
    };
};

int __thiscall TargetingManager::SetTarget(int targetId, bool forceClearOnly) {
    // Check if there are selectable items and a valid target ID
    if (targetId != 0 && this->someFlag != 0) {
        // Traverse the linked list
        for (SelectableNode* node = this->selectableListHead; node != nullptr; node = node->next) {
            if (node->entity != nullptr && *(int*)((char*)node->entity + 0x44) == targetId) {
                // Found a node for this target
                if (node != nullptr && !node->available) {
                    // Target is currently not selectable → clear selection and fail
                    this->currentSelection = 0;
                    return 0;
                }
                break;  // Target is available, proceed to selection
            }
        }
    }

    // Clear any existing selection
    if (this->currentSelection != 0) {
        this->currentSelection = 0;
    }

    // Call an internal reset (e.g., clears targeting state)
    FUN_005dbc10();

    // Set the new selection unless forceClearOnly is true
    if (!forceClearOnly) {
        this->currentSelection = targetId;
    }

    return 1;  // Success
}