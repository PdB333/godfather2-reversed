// FUNC_NAME: ContainerIterator::getCurrentData

// Address: 0x00694860
// Role: Retrieves a pointer to the user data stored in the current element of a custom container iterator.
// The container seems to be a linked list or similar structure where each node has a header (at least a pointer to the end sentinel)
// and the actual data starts at offset 0xC from the node pointer.

struct ContainerHeader
{
    int *m_start; // +0x00: pointer to first node (or some other field)
    int *m_end;   // +0x04: pointer to the end sentinel node
};

struct Iterator
{
    ContainerHeader *m_container; // +0x00: pointer to the container
    int *m_currentNode;          // +0x04: pointer to the current node in the iteration
};

// External assert function (likely EA_ASSERT or DebugBreak)
extern void __cdecl DebugAssert(void);

// __fastcall: ECX points to the Iterator object (this)
int *__fastcall Iterator::getCurrentData()
{
    if (this->m_container == nullptr)
    {
        DebugAssert();
    }
    if (this->m_currentNode == this->m_container->m_end)
    {
        DebugAssert();
    }
    // Return pointer to user data embedded in the node (at offset +0xC from the node pointer)
    return reinterpret_cast<int *>(reinterpret_cast<char *>(this->m_currentNode) + 0xC);
}