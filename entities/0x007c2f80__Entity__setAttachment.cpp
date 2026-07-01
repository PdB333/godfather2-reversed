// FUNC_NAME: Entity::setAttachment
void __thiscall Entity::setAttachment(int thisPtr, int attachment) {
    // +0x78: m_attachment (pointer or handle to attached object)
    *(int *)(thisPtr + 0x78) = attachment;
}