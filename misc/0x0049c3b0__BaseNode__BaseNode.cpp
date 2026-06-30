// FUNC_NAME: BaseNode::BaseNode
// Function address: 0x49c3b0
// Constructor for a game object node. Sets vtable and initializes child relationship.

// Forward declaration for inner object type
struct InnerObject;

// Vtable offsets for InnerObject (assuming vtable layout)
// +0x00: unknown
// +0x04: method(void* data, int param) - called conditionally
// +0x0C: method() - always called if child exists

struct BaseNode
{
    void** vtable;                   // +0x00
    InnerObject* m_pChild;           // +0x04
    int m_nParam;                    // +0x08
    void* m_pData;                   // +0x10
};

void __thiscall BaseNode::BaseNode(void)
{
    // Set the virtual function table for this class
    this->vtable = reinterpret_cast<void**>(&PTR_FUN_00e35228);

    if (this->m_pData != nullptr && this->m_pChild != nullptr)
    {
        // Call method at vtable+4 on child: passes data pointer and param
        auto func = reinterpret_cast<void (__thiscall*)(void*, void*, int)>(
            this->m_pChild->vtable[1]
        );
        func(this->m_pChild, this->m_pData, this->m_nParam);
    }

    if (this->m_pChild != nullptr)
    {
        // Call method at vtable+0xC on child (no additional args)
        auto func = reinterpret_cast<void (__thiscall*)(void*)>(
            this->m_pChild->vtable[3]
        );
        func(this->m_pChild);
    }
}