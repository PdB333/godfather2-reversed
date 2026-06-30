// FUNC_NAME: Player::setActionValue
void __thiscall Player::setActionValue(int value)
{
    // this+0x18: m_pActionComponent (pointer to some component/state machine)
    // component+0x14: m_actionValue or m_targetValue
    *(int *)(*(int *)(this + 0x18) + 0x14) = value;
}