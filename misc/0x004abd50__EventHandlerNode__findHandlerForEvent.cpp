// FUNC_NAME: EventHandlerNode::findHandlerForEvent
// Function address: 0x004abd50
// Searches a tree of event handler nodes for the deepest node that handles a given event flag.
// Each node has a self-handle mask at +0x3C and a children-handle mask at +0x40.
// If the children mask contains the flag, the search recurses into the child list.
// If the self mask contains the flag, the current node is returned.
// Otherwise, returns nullptr.

class EventHandlerNode {
    // ... other members (offsets 0x00-0x1F not used in this function)
    EventHandlerNode* pFirstChild;   // +0x20: pointer to first child node
    EventHandlerNode* pNextSibling;  // +0x28: pointer to next sibling in parent's child list
    uint32_t selfFlags;              // +0x3C: bitmask of events this node handles directly
    uint32_t childrenFlags;          // +0x40: bitmask of events handled somewhere in subtree
public:
    EventHandlerNode* findHandlerForEvent(uint32_t eventFlag) {
        if (childrenFlags & eventFlag) {
            // Search through children recursively
            EventHandlerNode* child = pFirstChild;
            while (child != nullptr) {
                EventHandlerNode* result = child->findHandlerForEvent(eventFlag);
                if (result != nullptr) {
                    return result;
                }
                child = child->pNextSibling;
            }
            // No child handled the event
            return nullptr;
        }

        if (selfFlags & eventFlag) {
            // This node handles the event
            return this;
        }

        return nullptr;
    }
};