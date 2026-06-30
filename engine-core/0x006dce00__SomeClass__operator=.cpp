// FUNC_NAME: SomeClass::operator=
// Function address: 0x006dce00
// Role: Deep copy assignment operator for a class with two embedded intrusive linked list nodes.
// The class contains two node structures (each holding a pointer to an object and a previous link pointer).
// After copying the node pointers (with list re-linking), it bulk-copies the remaining 0x54 ints (0x150 bytes) of data.

// Forward declaration of the release function (likely decrements refcount or removes from list)
void releaseNode(int* nodePtr);

class SomeClass {
public:
    // Offsets:
    // +0x00: pointer to first linked list element (node value)
    // +0x04: previous link pointer for first node
    // +0x08: pointer to second linked list element
    // +0x0C: previous link pointer for second node
    // +0x10 to +0x15C: remaining data fields (bulk copied)

    SomeClass& __thiscall operator=(const SomeClass& other) {
        if (this == &other) {
            return *this;
        }

        // Copy first node pointer
        int newFirst = other.m_firstNodeValue;
        if (m_firstNodeValue != newFirst) {
            if (m_firstNodeValue != 0) {
                releaseNode(&m_firstNodeValue);
            }
            m_firstNodeValue = newFirst;
            if (newFirst != 0) {
                // Update linked list: set this node's previous to the new node's previous,
                // then make the new node's previous point back to this node.
                m_firstNodePrev = *(int*)(newFirst + 4);
                *(int**)(newFirst + 4) = &m_firstNodeValue;
            }
        }

        // Copy second node pointer (similar pattern)
        int newSecond = other.m_secondNodeValue;
        if (m_secondNodeValue != newSecond) {
            if (m_secondNodeValue != 0) {
                releaseNode(&m_secondNodeValue);
            }
            m_secondNodeValue = newSecond;
            if (newSecond != 0) {
                m_secondNodePrev = *(int*)(newSecond + 4);
                *(int**)(newSecond + 4) = &m_secondNodeValue;
            }
        }

        // Bulk copy remaining data from offset 4 (0x10 bytes) to end (0x57 ints = 0x15C bytes)
        // Using array indexing starting at index 4 (since m_firstNodePrev is at [1], m_secondNodeValue at [2], etc.)
        // In the original, it copies indices 4 through 0x57 inclusive.
        for (int i = 4; i <= 0x57; ++i) {
            ((int*)this)[i] = ((int*)&other)[i];
        }

        return *this;
    }

private:
    int m_firstNodeValue;   // +0x00: pointer to node data
    int m_firstNodePrev;    // +0x04: previous link
    int m_secondNodeValue;  // +0x08: pointer to second node data
    int m_secondNodePrev;   // +0x0C: previous link for second node
    // +0x10 to +0x15C: other member data (0x54 ints)
};