// FUNC_NAME: StateMachine::setCurrentState
void __thiscall StateMachine::setCurrentState(StateMachine* this) {
    // +0x08: some identifier (maybe owner or state argument)
    // +0x0C: pointer to a subobject (likely a helper or manager)
    // vtable offset 0x34: virtual method on subobject (likely activate/setup)
    this->m_subObject->vfunc_0x34(this->m_ownerId, 1); // (**(code**)((**(int**)(this+0x0C))+0x34))( *(this+0x08), 1)
    // +0x10: state variable, set to 6 (some specific state)
    this->m_state = 6;
}