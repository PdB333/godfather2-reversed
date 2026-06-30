// FUNC_NAME: DeferredAction::processTrigger
void __fastcall DeferredAction::processTrigger(DeferredAction* this)
{
    // Check three conditions: ready flag (+0x7a), active flag (+0x78), and target pointer (+0x70)
    if (this->m_bReady != 0 && this->m_bActive != 0 && this->m_pTarget != nullptr)
    {
        // Execute the deferred action (likely sound, animation, or script trigger)
        executeDeferredAction();
        // Clear the ready flag to prevent re‑triggering
        this->m_bReady = 0;
    }
}