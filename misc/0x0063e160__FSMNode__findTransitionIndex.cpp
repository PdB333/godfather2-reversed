// FUNC_NAME: FSMNode::findTransitionIndex
// Purpose: Recursive search within a hierarchy of state machine nodes for a transition matching the given event ID.
//          The function traverses the node's local transition table first, then recursively searches child nodes.
//          The output buffer (param_3) contains a result code and index.
//
// Offsets for FSMNode (param_1 as int*):
//   +0x00: vtable or pointer to external descriptor (used to access transition data)
//   +0x08: pointer to child FSMNode (next in hierarchy)
//   +0x34: number of local transitions (param_1[0xd])
//   +0x2b4: array of indices into the global transition table (param_1 + 0xad) — iterated in reverse
//
// The global transition table is obtained as: *(int*)(*(int*)(this[0] + 0x18))
// Each element in that table is a struct of size 0xC (12 bytes), containing an event ID at offset 0.

class FSMNode;

// Forward declarations of external functions called by this function.
void FUN_0063e140();                // Called when a match is found locally (side effect)
int FUN_0063e000(FSMNode* node, int eventID, int* resultBuf);  // Attempt to resolve transition after child search
int FUN_00642a50();                 // Allocates/creates something when no match overall and at top level

// Result buffer layout (param_3):
//   [0]: result type (7 = no match, 5 = local match, 6 = match after child search)
//   [1]: result index (transition index or newly created handle)
//   [3]: reserved, set to -1
//   [4]: reserved, set to -1

struct TransitionResult {
    int type;
    int index;
    int unused1;  // always -1
    int unused2;  // always -1
};

void FSMNode::findTransitionIndex(FSMNode* node, int eventID, TransitionResult* result, bool isTopLevel) {
    // If node is null, return "not found" with type=7 and default index=0xFF
    if (node == nullptr) {
        result->type = 7;          // Not found
        result->index = 0xFF;      // Sentinel index
        result->unused1 = -1;
        result->unused2 = -1;
        return;
    }

    // Number of local transitions in this node
    int numTransitions = node->m_numTransitions;  // param_1[0xd]
    int currentIndex = numTransitions - 1;

    // Search the local transition table in reverse order
    if (currentIndex >= 0) {
        // piVar2 = &node->m_transitionIndices[numTransitions - 1]  (end of array)
        int* piVar2 = &node->m_transitionIndices[numTransitions - 1];

        do {
            // Access the global transition table: pointer from descriptor at node->vtable+0x18
            // Index into that table with the current index from the local array.
            int* globalTableBase = *(int**)(*(int*)node->m_vtableDescriptor + 0x18);  // *node[0] -> +0x18
            int transitionID = globalTableBase[*piVar2 * 3]; // each entry is 0xC = 3 ints

            if (eventID == transitionID) {
                if (currentIndex >= 0) {
                    // Match found locally
                    result->type = 5;               // Local match
                    result->index = currentIndex;    // Index in local table
                    result->unused1 = -1;
                    result->unused2 = -1;

                    if (!isTopLevel) {
                        // If not top-level call, execute a side-effect function
                        FUN_0063e140();
                    }
                    // If top-level, just return the result (no side effect)
                    return;
                }
                break; // Should not happen if currentIndex >=0
            }
            currentIndex--;
            piVar2--;
        } while (currentIndex >= 0);
    }

    // No local match found; recursively search the child node
    findTransitionIndex(node->m_childNode, eventID, result, false);

    // After child search, interpret the result
    if (result->type == 7) {
        // Child also returned "not found"
        if (isTopLevel) {
            // Top-level: create a new transition (allocate using FUN_00642a50)
            int newIndex = FUN_00642a50();
            result->index = newIndex;
        }
        // Otherwise, leave result as "not found" (type 7)
    } else {
        // Child found a match, but we need to adjust using the parent's context
        int adjustedIndex = FUN_0063e000(node, eventID, result);
        result->type = 6;               // Match found via child search
        result->index = adjustedIndex;
    }
}