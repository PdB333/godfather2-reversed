// FUNC_NAME: NodePool::insertAfter

// This function inserts a new node into an intrusive linked list after a given node.
// The pool grows automatically (doubles capacity) when full.
// Each node is 8 bytes: [prev pointer (4), next pointer (4)].
// param_2 is a pointer to a variable that holds the node after which to insert (or null if list is empty).
void __thiscall NodePool::insertAfter(int **ppAfterNode) {
    int *newNode;
    int *afterNode;

    // If pool is full, grow capacity
    if (m_size == m_capacity) {
        if (m_capacity == 0) {
            m_capacity = 1;
        } else {
            m_capacity *= 2;
        }
        // Reallocate node array (size = m_capacity * 8 bytes)
        // FUN_00727cc0 is likely a realloc function that takes the new element count
        FUN_00727cc0(m_capacity);
    }

    // Allocate new node from the end of the array
    newNode = (int *)(m_pNodes + m_size * 8);
    m_size++;

    if (newNode != nullptr) {
        afterNode = *ppAfterNode; // the node after which we insert
        newNode[0] = (int)afterNode; // store after node as "prev" pointer (or data)
        newNode[1] = 0; // next pointer initially null
        if (afterNode != nullptr) {
            // Link new node into the list: new node's next = afterNode->next
            newNode[1] = *(int *)(afterNode + 4);
            // afterNode's next now points to new node
            *(int **)(afterNode + 4) = newNode;
        }
    }
}