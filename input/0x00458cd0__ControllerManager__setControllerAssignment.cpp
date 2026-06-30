// FUNC_NAME: ControllerManager::setControllerAssignment
void __thiscall ControllerManager::setControllerAssignment(uint index, int value)
{
    // Check index is valid (0 or 1 for two players)
    if (index < 2) {
        // +0x08: array of 2 pointers to controller objects (index * 4 bytes each)
        ControllerObject* obj = *(ControllerObject**)((char*)this + 8 + index * 4);
        obj->m_controllerIndex = index;   // +0x20c: controller index (uint)
        obj->m_associatedValue = value;   // +0x204: associated value (undefined4)
    }
}