// FUNC_NAME: Node::destroy
// Address: 0x006f09f0
// Role: Destructor for a node-like object that validates parent/child linkage and releases a handle.

// Forward declarations for external functions
extern void someGlobalCleanup();
extern void releaseHandle(char* handleBuffer); // FUN_006fdaf0

class Node {
public:
    // Offsets inferred from decompilation:
    // +0x08: pointer to something (maybe next node or linked list pointer)
    // +0x0c: unknown (cleared)
    // +0x10: pointer to parent or container
    // +0x14, +0x18, +0x1c: other fields cleared
    int* m_pLink;       // +0x08
    int m_unknown0C;    // +0x0c
    int* m_pParent;     // +0x10
    int m_field14;      // +0x14
    int m_field18;      // +0x18
    int m_field1C;      // +0x1c

    // Destructor-like method, takes an unused parameter (likely for compatibility)
    void __thiscall destroy(int unusedParam) {
        // Validation: ensure m_pParent and m_pLink are non-null,
        // and the first int pointed to by m_pLink equals the value at m_pParent->m_field18.
        if ((m_pParent != nullptr) && (m_pLink != nullptr) &&
            (*m_pLink == *(int*)((char*)m_pParent + 0x18))) {
            someGlobalCleanup(); // FUN_005e3260, possibly global state decrement

            char handleBuffer[4]; // local_10
            releaseHandle(handleBuffer); // Probably releases a handle associated with this node

            // Clear all fields
            m_pParent = nullptr;
            m_unknown0C = 0;
            m_pLink = nullptr;
            m_field14 = 0;
            m_field18 = 0;
            m_field1C = 0;
        }
    }
};