// FUNC_NAME: PlayerSM::constructor
undefined4 * __thiscall PlayerSM::constructor(PlayerSM *this, undefined4 param)
{
    // Call base constructor (PlayerStateMachine) at 0x0046c590
    PlayerStateMachine::constructor(param);

    // Set vtable and secondary interface tables
    this->vtable = (void *)&PTR_FUN_00d77ca0;                    // +0x00 main vtable
    this->m_secondaryVtable1 = (void *)&PTR_LAB_00d77c90;        // +0x3C (offset 0x0F)
    this->m_secondaryVtable2 = (void *)&PTR_LAB_00d77c8c;        // +0x48 (offset 0x12)

    // Zero-initialize state fields
    this->m_stateTimer = 0;                                       // +0x50 (offset 0x14)
    this->m_flagsLow = 0;                                         // +0x54 (short at offset 0x15)
    this->m_flagsHigh = 0;                                        // +0x56 (short at offset 0x56)
    this->m_subStatePointer = 0;                                  // +0x58 (offset 0x16)
    this->m_subFlags1 = 0;                                        // +0x5C (short at offset 0x17)
    this->m_subFlags2 = 0;                                        // +0x5E (short at offset 0x5E)

    return this;
}