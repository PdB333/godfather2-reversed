//FUNC_NAME: StateMachine::processFirstFrame

void __fastcall StateMachine::processFirstFrame(StateMachine* this)
{
    // Offsets: +0x4C = m_bFirstFrameProcessed (byte), +0x48 = m_bShouldExecute (byte)
    if (!this->m_bFirstFrameProcessed)
    {
        this->m_bFirstFrameProcessed = true;
        if (this->m_bShouldExecute)
        {
            // Virtual function at vtable offset 0xA0 (index 0x28)
            (this->vtable[0x28])();
        }
    }
}