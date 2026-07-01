// FUNC_NAME: Entity::setDataFlagByte
void __thiscall Entity::setDataFlagByte(byte value) {
    // this+0x58: pointer to EntityData (e.g., m_pData)
    // EntityData+0x24f0: byte flag (e.g., m_bSomeFlag)
    *(byte *)(*(int *)((int)this + 0x58) + 0x24f0) = value;
}