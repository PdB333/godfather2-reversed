//FUNC_NAME: PlayerSM::exitState
void __thiscall PlayerSM::exitState(PlayerSM* this) {
    // +0x88: current state (int), 0x48 = inactive/dead state
    // +0x90: pointer to some object (e.g., state machine data)
    // +0x94: flags (bit 1 = active flag)
    // +0x50: sub-object (e.g., inner state machine) passed to FUN_009af080
    if (this->state != 0 && this->state != 0x48 && this->somePointer != nullptr && (this->flags & 2) != 0) {
        FUN_009af080(&this->subObject);  // stop/cleanup sub-state
        this->flags &= ~2;               // clear active flag
    }
}