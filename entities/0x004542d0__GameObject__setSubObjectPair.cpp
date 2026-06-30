// FUNC_NAME: GameObject::setSubObjectPair
void __thiscall GameObject::setSubObjectPair(uint32_t param1, uint32_t param2) {
    // Get sub-object pointer at this+0x14 (m_pSubObject)
    uint8_t* subObj = *(uint8_t**)(this + 0x14);
    // Write param1 to subObj+0x84, param2 to subObj+0x88
    *(uint32_t*)(subObj + 0x84) = param1;
    *(uint32_t*)(subObj + 0x88) = param2;
}