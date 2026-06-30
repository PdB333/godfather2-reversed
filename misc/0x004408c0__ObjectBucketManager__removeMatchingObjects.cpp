// FUNC_NAME: ObjectBucketManager::removeMatchingObjects
class ObjectBucketManager {
public:
    struct Node {
        Node* next;         // +0x00
        // +0x04: unknown (unused)
        int id;             // +0x08
        int secondaryId;    // +0x0C
        // +0x10: unknown
        // +0x14: unknown
        void* attachedObj;  // +0x18 (puVar7[6])
        uint8_t flags;      // +0x1C (bit 0 tested)
    };

    struct NodeComparator {
        // vtable at +0x00, with method at +0x04
        virtual bool matches(int id, int* secondaryId, void* obj, int unknown) = 0;
    };

    short bucketCount;      // +0x16 (number of containers minus 1? Actually max index)
    int* containerArray;    // +0x18 (pointer to array of pointers to Container objects)

    // Container objects have a Node* head at +0x18 (dummy node for circular list)
    struct Container {
        // ... other fields ...
        Node* dummyHead;    // +0x18 (points to dummy node, not the real first node)
    };

    // Removes all nodes in all containers that match the given ID and optional criteria.
    // Returns the number of nodes removed.
    int __thiscall removeMatchingObjects(int id, int* optionalId, NodeComparator* comparator) {
        int removedCount = 0;
        if (bucketCount < 0) return 0;

        for (short idx = bucketCount; idx >= 0; idx--) {
            Container* container = reinterpret_cast<Container*>(containerArray[idx]);
            if (!container) continue;

            // Assume container has a dummy head node at +0x18; list is circular.
            Node* dummy = container->dummyHead;
            Node* current = dummy->next; // first real node
            Node* prev = container;      // Actually previous node pointer is stored as container? 
            // In the original code prev (iVar8) is initially the container pointer.
            // We'll adapt: we keep a pointer to the container (or dummy) as "prev" for list manipulation.

            // We'll iterate through the circular list until we return to the dummy.
            // The original code uses a while(1) with break when current == dummy.
            // We'll emulate that.

            while (true) {
                // Safety check: ensure prev and current are valid.
                if (!prev || prev != container) {
                    // assert(FUN_00b97aea);
                    // In practice should not happen.
                }
                if (current == dummy) break; // Traversed all real nodes.

                bool matchCondition = (current->id == id) &&
                    (optionalId == nullptr || *optionalId == current->secondaryId) &&
                    (comparator == nullptr || comparator->matches(current->id, &current->secondaryId, current->attachedObj, *(int*)(&current[5])));

                if (matchCondition) {
                    // Optional cleanup: if attachedObj exists and flag bit 0 not set, call its first virtual func.
                    if (current->attachedObj != nullptr && (current->flags & 0x01) == 0) {
                        void* vtable = *reinterpret_cast<void**>(current->attachedObj);
                        void (*func)(void*) = reinterpret_cast<void(*)(void*)>(*reinterpret_cast<void**>(vtable));
                        func(current->attachedObj);
                    }

                    // Call removal function: returns the new current node and next node.
                    // FUN_00440e30(container, stack_space, prev, node_to_remove);
                    // We'll assume it unlinks the node and returns a struct with two Node pointers:
                    // first is the new "prev" (maybe dummy), second is the next node to process.
                    // For simplicity, we'll use a standard unlink operation.
                    // In the actual code, the removal function updates the list and returns the next node.
                    // We'll mimic by calling a helper.

                    auto result = unlinkNode(prev, current);
                    // After removal, the next node to process is result.nextNode.
                    // The new "prev" is result.newPrev (usually remains same or points to prev of removed node).
                    // The original code updates iVar8 and puVar7 accordingly.

                    // Simplified: we'll just continue from the node after the removed one.
                    // The next iteration should start with current = result.nextNode, prev = prev (unchanged).
                    current = result.nextNode;
                    removedCount++;
                } else {
                    // No match: advance.
                    prev = current;
                    current = current->next;
                }
            }
        }
        return removedCount;
    }
};