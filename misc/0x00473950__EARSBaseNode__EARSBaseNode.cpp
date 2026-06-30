// FUNC_NAME: EARSBaseNode::EARSBaseNode
void __thiscall EARSBaseNode::EARSBaseNode(EARSBaseNode* this, EARSBaseNode* parentNode)
{
    this->m_unknown1 = 0;
    this->m_vtable2 = &PTR___purecall_00e32ad0; // +0x08: secondary vtable (base)
    this->m_vtable1 = &PTR_FUN_00e32ad8;       // +0x00: primary vtable
    this->m_vtable2 = &PTR_LAB_00e32aec;       // +0x08: override vtable (derived)

    // If parentNode is valid, insert this node after parentNode in a doubly-linked list
    // parentNode->m_next (at +0x04) is the next pointer
    if (parentNode == nullptr)
    {
        parentNode = nullptr;  // no-op, keep null
    }
    else
    {
        parentNode = (EARSBaseNode*)((int)parentNode + 0x48);  // why offset +0x48? maybe parentNode is actually a sub-struct? unclear.
    }
    this->m_prev = parentNode;   // +0x0c
    this->m_next = nullptr;      // +0x10, will be set below if parentNode != null

    if (parentNode != nullptr)
    {
        this->m_next = parentNode->m_next;     // +0x10 = parentNode->m_next (offset 0x04? Actually parentNode+0x04 is m_next? Inconsistent: parentNode was offset by +0x48, so parentNode+0x04 corresponds to original+0x4C)
        parentNode->m_next = (EARSBaseNode**)&this->m_prev;  // parentNode->m_next = this->m_prev (which stores parentNode itself)
    }

    // Zero out a block of 12 DWORDs (offsets 0x20 through 0x4C)
    this->m_field8 = 0;   // +0x20
    this->m_field9 = 0;   // +0x24
    this->m_fieldA = 0;   // +0x28
    this->m_fieldB = 0;   // +0x2C
    this->m_fieldC = 0;   // +0x30
    this->m_fieldD = 0;   // +0x34
    this->m_fieldE = 0;   // +0x38
    this->m_fieldF = 0;   // +0x3C
    this->m_field10 = 0;  // +0x40
    this->m_field11 = 0;  // +0x44
    this->m_field12 = 0;  // +0x48
    this->m_field13 = 0;  // +0x4C

    this->m_type1 = 0;    // +0x50
    this->m_type2 = 1;    // +0x54
    this->m_type3 = 2;    // +0x58
}