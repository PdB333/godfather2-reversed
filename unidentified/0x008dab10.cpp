// FUN_008dab10: Player::isActionAllowed
bool __fastcall Player::isActionAllowed(Player* this) {
    // +0x190 (400 decimal): pointer to some component or state (likely a controller or action blocker)
    // +0x180 (384 decimal): flag byte, non-zero indicates a blocking condition
    bool blocked = (*(int*)((byte*)this + 0x190) != 0) && (*(byte*)((byte*)this + 0x180) != 0);
    return !blocked; // returns 1 (true) when action is allowed, 0 (false) when blocked
}