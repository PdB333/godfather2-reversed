// FUNC_NAME: Entity::activate
// Function address: 0x005db700
// Increments activation counter, clears state pointer, calls onActivate.

void __thiscall Entity::activate()
{
    this->m_activationCount++;      // +0x24: activation counter
    this->m_currentState = 0;       // +0xc: current state pointer/index
    this->onActivate();             // FUN_005db0a0
}