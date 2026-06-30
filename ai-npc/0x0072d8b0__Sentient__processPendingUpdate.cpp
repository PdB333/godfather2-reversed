// FUNC_NAME: Sentient::processPendingUpdate
void __fastcall Sentient::processPendingUpdate()
{
    char bUpdateAllowed = isUpdateAllowed(); // FUN_007f7c60: global check if updates are permitted

    if (bUpdateAllowed)
    {
        // Unknown output structure passed to startObjectUpdate (likely timestamps or flags)
        int outParam1 = 0;
        int outParam2 = 0;

        // Retrieve the simulation manager singleton (FUN_007ff880)
        SimManager* pSimMgr = SimManager::getInstance();

        // Notify manager that this object is about to update (vtable +0x204)
        pSimMgr->startObjectUpdate(this, &outParam1);

        // Execute the object’s specific update logic (vtable +0x1b4, e.g., animation/state)
        this->performUpdate();

        // Notify manager that update is complete (vtable +0x268)
        pSimMgr->endObjectUpdate(this);

        // Clear the “pending update” flag at offset +0x1F58 (bit 13)
        this->m_flags &= ~0x2000; // param_1[0x7d6]
    }
}