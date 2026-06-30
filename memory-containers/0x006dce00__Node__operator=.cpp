// FUNC_NAME: Node::operator=
// Function at 0x006dce00: Assignment operator for a class with two embedded singly-linked list nodes and a data payload.
// The first 8 bytes form a node (value + next pointer) for list1, next 8 bytes for list2, then 84 ints (0x150 bytes) of data.
// When copying, the list nodes are inserted after the source's corresponding nodes (to maintain list integrity?).
// FUN_004daf90 is a release/deallocation function for the old pointer values.

class Node {
public:
    int*  m_list1Value;   // +0x00
    Node* m_list1Next;    // +0x04
    int*  m_list2Value;   // +0x08
    Node* m_list2Next;    // +0x0C
    int   m_data[84];     // +0x10 (0x150 bytes)

    Node& operator=(const Node& other) {
        if (this == &other)
            return *this;

        // Handle first intrusive list node
        if (m_list1Value != other.m_list1Value) {
            if (m_list1Value)
                release(m_list1Value);                // FUN_004daf90
            m_list1Value = other.m_list1Value;
            if (other.m_list1Value) {
                m_list1Next = other.m_list1Next;      // copy next pointer
                other.m_list1Next = this;             // insert this after other's node
            }
        }

        // Handle second intrusive list node
        if (m_list2Value != other.m_list2Value) {
            if (m_list2Value)
                release(m_list2Value);
            m_list2Value = other.m_list2Value;
            if (other.m_list2Value) {
                m_list2Next = other.m_list2Next;
                other.m_list2Next = this;
            }
        }

        // Copy data payload (offsets 0x10 through 0x15C)
        for (int i = 0; i < 84; ++i)
            m_data[i] = other.m_data[i];

        return *this;
    }

private:
    void release(int* ptr); // stub for FUN_004daf90
};