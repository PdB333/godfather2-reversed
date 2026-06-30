// FUNC_NAME: ControllerManager::setSlotActionValue
void __thiscall ControllerManager::setSlotActionValue(int value) {
    // this->m_pSlotConfig (offset 0x18) -> m_actionID (offset 0x14) = value
    *(int*)(*(int*)((char*)this + 0x18) + 0x14) = value;
}