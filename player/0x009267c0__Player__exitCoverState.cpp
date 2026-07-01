// FUNC_NAME: Player::exitCoverState
// Address: 0x009267c0
// Called when the player exits a cover state. Checks a flag at +0x3a1, and if set,
// disables cover-related behavior, clears three cover state bytes, updates the cover manager,
// and triggers a state machine transition.
void __fastcall Player::exitCoverState(Player* this) {
    if (this->coverFlags.inCover) { // +0x3a1: bool indicating active cover
        setCoverEnabled(false);              // FUN_0069e660(0)
        this->coverFlags.inCover = false;    // +0x3a1
        this->coverFlags.leanRight = false;  // +0x3a2 (example: cover lean direction)
        this->coverFlags.coverTransition = false; // +0x3a3 (example: transitioning state)
        updateCoverSystem(&coverManagerGlobal); // FUN_004086d0(&DAT_01206978)
        applyCoverExit();                         // FUN_005c1990()
    }
}