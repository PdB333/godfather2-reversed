// FUNC_NAME: Entity::update
void __fastcall Entity::update(Entity* this)
{
    bool bNeedsPostUpdate = false;

    // Counter at +0x60 guards against re-entrancy; only run first time
    if (this->m_frameCounter == 0)
    {
        // Called twice per update – likely pre/post sync or double-buffer
        this->preUpdateSync();
        this->preUpdateSync();  // second call (maybe intended for another operation?)

        // Check global condition (e.g., game scene active)
        if (*(int*)(gGlobalPtr + 0xC) != 0)
        {
            this->updateAnimationsAndPhysics();
            // Bit 4 of flags (+0x5C) : handle special state
            if (this->m_flags & (1 << 4))
            {
                this->handleSpecialFlag();
            }
        }

        this->genericUpdate();

        // Bit 0xF of flags : trigger state machine update
        if (this->m_flags & (1 << 15))
        {
            this->updateStateMachine(0);
            bNeedsPostUpdate = true;
        }
    }

    // Increment frame counter (always)
    this->m_frameCounter++;

    if (bNeedsPostUpdate)
    {
        // Post-update action using data at +0xC8 (offset 200)
        this->postUpdateAction(*(int*)((char*)this + 200), 1, 0);
    }
}