// FUNC_NAME: Entity::updateState
void __thiscall Entity::updateState(bool isActive)
{
    // Base class update (e.g., animation, physics)
    baseUpdate();

    // +0x40: type ID (0x637b907 seems special – perhaps "vehicle" or "building")
    if (this->mType == 0x637b907)
    {
        if (!isActive)
        {
            // +0x58: some active/paused flag
            // Global at DAT_0112a590+4: maybe "enableVehicleSpawning" flag
            // +0xc4: state (1=active, 0=inactive or idle)
            if ((this->mPauseState == 0) &&
                (*(char*)(DAT_0112a590 + 4) != '\0') &&
                ((this->mInternalState == 1) || (this->mInternalState == 0)))
            {
                // +0x38: pointer to a spawn/deactivation context
                activateInternal(*(int*)(this + 0x38));
            }
        }
        else
        {
            deactivate();
        }
    }

    // Save current type and subtype for later debug logging
    int savedType = this->mType;            // +0x40
    int savedSubtype = this->mSubtype;      // +0x3c

    // Build a debug message structure and log it
    // The structure contains a vtable pointer (PTR_LAB_00d5e22c) and the object pointer
    // This appears to be a generic logging call
    DebugMessage msg;
    msg.vtable = &PTR_LAB_00d5e22c;        // function table for debug output
    msg.messageId = DAT_0112a620;          // some debug message ID
    msg.flags = 0;
    msg.object = this;
    debugLog(&msg, 0);                     // log with parameter 0

    // Second log with different message ID, no vtable
    msg.vtable = nullptr;
    msg.messageId = DAT_0112a630;
    msg.flags = 0;
    debugLog(&msg, 0);

    // Third log, only if subtype matches the special type
    if (savedSubtype == 0x637b907)
    {
        msg.vtable = nullptr;
        msg.messageId = DAT_0112a594;
        msg.flags = 0;
        debugLog(&msg, 0);
    }
}