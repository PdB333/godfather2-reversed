// FUNC_NAME: EARSNode::attachChild

class EARSObject {
public:
    // vtable offsets:
    // +0x00: destructor (not used here)
    // +0x04: virtual void methodAt4(int param1, int param2) – called with (childId, 0) when childId != 0
    // +0x08: virtual void onAdd() – called to notify child of attachment (twice in some cases)
    // +0x0C: virtual void onPostAdd() – called at end of attachment process
};

class EARSNode {
public:
    // +0x00: vtable pointer
    // +0x0C: EARSObject* m_child;   // stored child pointer
    // +0x10: int m_handle;          // handle/reference ID for the child

    __thiscall void attachChild(EARSObject* child, int childId) {
        // Notify child that it is being attached (first pass)
        child->onAdd(); // vtable+8

        // Create a handle for the child if a non‑zero ID is provided
        int handle = (childId != 0) ? createHandle(childId, child) : 0;

        // Associate the handle with the child (e.g., store it inside the child)
        setChildHandle(child, handle); // calls FUN_004cae60

        // Store the child pointer in this node
        this->m_child = child; // +0x0C

        // Notify child again (second pass, possibly for final setup)
        child->onAdd(); // vtable+8

        if (childId != 0) {
            // Create handle again (now referencing the stored child)
            handle = createHandle(childId, this->m_child);

            // Store the handle in the node
            this->m_handle = handle; // +0x10

            // Call virtual method on child with (childId, 0)
            child->methodAt4(childId, 0); // vtable+4

            // Finalize attachment
            child->onPostAdd(); // vtable+0xC
        } else {
            // No ID, clear handle
            this->m_handle = 0; // +0x10

            // Finalize attachment without extra operations
            child->onPostAdd(); // vtable+0xC
        }
    }
};