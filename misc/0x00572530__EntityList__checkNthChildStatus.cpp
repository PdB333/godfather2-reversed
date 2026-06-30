// FUNC_NAME: EntityList::checkNthChildStatus
// Function at 0x00572530
// Checks if the nth child (by index) of a parent object has a specific flag set or a float value below a global threshold.
// Parent object has a linked list of children: first child pointer at this+0x124.
// Each child node: next pointer at +0x124, flags at +0x10, float value at +0x24.
// Second parameter (index) is passed in ESI (non-standard __fastcall convention).

struct ChildNode {
    // +0x00: other members (size unknown)
    int flags;              // +0x10
    float value;            // +0x24
    ChildNode* next;        // +0x124 (pointer to next sibling)
};

struct ParentObject {
    // +0x00..+0x120: other members
    ChildNode* firstChild;  // +0x124 (pointer to first child in linked list)
};

extern float gThreshold; // DAT_00e2b1a4

bool __fastcall checkNthChildStatus(ParentObject* parent, int index) {
    ChildNode* node = nullptr;

    if (parent == nullptr || index < 0) {
        node = nullptr;
    } else {
        node = parent->firstChild;
        int i = 0;
        if (index > 0) {
            do {
                if (node == nullptr) break;
                node = node->next;
                i++;
            } while (i < index);
        }
    }

    // If node is null, the following accesses would crash – caller ensures valid index.
    return ((node->flags & 0x2000003) != 0) || (node->value <= gThreshold);
}