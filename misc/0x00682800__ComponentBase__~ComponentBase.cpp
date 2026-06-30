// FUNC_NAME: ComponentBase::~ComponentBase
// Address: 0x00682800
// Role: Destructor that releases a child pointer at offset +0x1c

void __thiscall ComponentBase::~ComponentBase(ComponentBase* this)
{
    // Call global cleanup / base class destructor
    baseCleanup();          // FUN_0043e900

    // If the child pointer at +0x1c is not null, release it
    if (this->m_childPtr != nullptr) {
        releaseChild();          // FUN_00680f50
        deleteChild(this->m_childPtr); // FUN_009c8eb0
    }

    // Null the pointer to avoid double deletion
    this->m_childPtr = nullptr; // +0x1c
}