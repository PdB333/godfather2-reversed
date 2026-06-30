// FUNC_NAME: Entity::updateActionTimer
// Address: 0x006b5950
// Role: Updates an action/state timer for an entity. When timer exceeds duration, it resets and either
//       triggers a new animation (if currentAnim exists) or checks state progression and fires an event.
// Context: EA EARS engine, The Godfather 2. Entity class with animation/state machine.

// Offsets (relative to this):
//   +0x16c: bool  bDead
//   +0xfc:  bool  bPaused
//   +0x34:  uint32 flags (bit29 = bSuspended)
//   +0x74:  void* currentAnim   // pointer to current animation state
//   +0x6c:  void* previousAnim  // pointer to previous or alternative animation state
//   +0x7c:  float timer         // accumulated time
//   +0x80:  float duration      // threshold time
//   +0x68:  uint32 currentStateId
//   +0x58:  uint32 targetStateId
//   +0x60:  uint32 stateCounter
//   +0x5c:  uint32 stateMaxCounter
//   +0x40:  uint32 entityId     // identifier used for event dispatch

// DAT_012067e8: global frame delta time (gDeltaTime)
extern float gDeltaTime;   // DAT_012067e8

void __fastcall Entity::updateActionTimer(int this)
{
    float newTimer;

    // Abort if entity is dead, paused, suspended, or has no animation states
    if ( *(int*)(this + 0x16c) != 0 ) return;
    if ( *(int*)(this + 0xfc)  != 0 ) return;
    if ( (*(uint32_t*)(this + 0x34) >> 0x1d) & 1 ) return; // bit29 set = suspended
    if ( *(int*)(this + 0x74) == 0 && *(int*)(this + 0x6c) == 0 ) return;

    // Advance timer by global delta time
    newTimer = *(float*)(this + 0x7c) + gDeltaTime;
    *(float*)(this + 0x7c) = newTimer;

    // Check if timer exceeds duration (strictly greater)
    if ( *(float*)(this + 0x80) <= newTimer && newTimer != *(float*)(this + 0x80) )
    {
        // Reset timer
        *(float*)(this + 0x7c) = 0.0f;

        if ( *(int*)(this + 0x74) != 0 )
        {
            // Current animation state is active: start the next animation and clear action data
            FUN_006b3b10(1);   // likely: startAnimation(1) or beginAction(1)
            FUN_006b4da0();    // likely: clearActionState()
            return;
        }

        // No current animation – check state progression condition
        if ( *(int*)(this + 0x68) == *(int*)(this + 0x58) &&       // current state matches target
             (uint32_t)*(int*)(this + 0x60) <= (uint32_t)*(int*)(this + 0x5c) ) // counter <= threshold
        {
            // Transition to next state and fire event with entity ID
            FUN_006b3b40(1);                                         // endCurrentState(1)
            FUN_008c7890(*(uint32_t*)(this + 0x40), 1);              // triggerEvent(entityId, 1)
        }
    }
}