// FUNC_NAME: Item::processPickup
// Address: 0x008397a0
// Handles pickup animation, audio, and state transitions for an item.

void __fastcall Item::processPickup(Item* this)
{
    // Callback structures for async events
    int callbackHandle = 0;          // local_10
    int unused1 = 0;                 // local_c
    int unused2 = 0;                 // local_8
    CodeFunc* cleanupCallback = nullptr; // local_4

    int eventCallbackArray[3] = {0, 0, 0}; // local_20
    CodeFunc* animCallback = nullptr;       // local_14

    // Initialize async callback system
    initCallbackStructure(&callbackHandle);

    // Register an event (e.g., sound or animation) by hash
    registerEvent(0x62859231, eventCallbackArray);

    // Set up audio source and play sound
    setupAudioSource(&DAT_00e327b8);    // Audio global
    playSound(callbackHandle, 0, 0);    // channel 0, no params

    // State machine based on flags at +0xe8
    if ((this->m_flags & 0x10) == 0)    // Not yet in pickup state (bit 4)
    {
        // Start pickup animation
        this->m_flags |= 0x20;          // Set bit 5 (animating flag)
        goto setPickupTarget;
    }
    else // Already in pickup state
    {
        // Determine which value to compare based on pickup type
        if (this->m_pickupType == 0)
        {
            // Ground pickup: compare m_groundPickupAmount with current
            if (this->m_groundPickupAmount < this->m_currentPickupAmount)
            {
                goto continuePickup;
            }
        }
        else // Pickup from container (m_pickupType != 0)
        {
            // Container pickup: compare current with m_containerPickupAmount
            if (this->m_currentPickupAmount < this->m_containerPickupAmount)
            {
                goto continuePickup;
            }
        }

        // No further progress needed; stop animation and clean up
        this->m_flags &= ~0x20;         // Clear bit 5 (animating flag)
        stopSound(10);                  // Stop sound channel 10
        runAnimationCallback(eventCallbackArray); // Execute callback
        // Falls through to finalCleanup
    }

finalCleanup:
    // Global cleanup of pickup system
    resetPickupSystem();

    // Execute animation from string stored in global
    const char* animName = DAT_0112dbf4;
    playAnimation(&animName, 0);        // 0 = no additional params

    // Set pickup state to 3 (presumably "complete")
    this->m_pickupState = 3;            // +0xe4

    // Invoke any pending callbacks
    if (eventCallbackArray[0] != 0)
    {
        animCallback(eventCallbackArray[0]);
    }
    if (callbackHandle != 0)
    {
        cleanupCallback(callbackHandle);
    }
    return;

continuePickup:
    // Continue the pickup animation
    this->m_flags |= 0x20;              // Keep animating
    stopSound(10);                      // Stop sound channel 10
    runPickupAnimation(eventCallbackArray);    // Advance animation
    runAnimationCallback(eventCallbackArray);  // Execute callback
    // Fall through to set target values

setPickupTarget:
    // Set the target amount based on pickup type
    if (this->m_pickupType == 0)
    {
        this->m_currentPickupAmount = this->m_groundPickupAmount;
    }
    else
    {
        this->m_currentPickupAmount = this->m_containerPickupAmount;
    }
    this->m_flags |= 0x10;              // Mark as in pickup state
    goto finalCleanup;
}