// FUNC_NAME: Sentient::getCurrentState
int __fastcall Sentient::getCurrentState(Sentient* this) {
    int state = this->field_0x2104; // possibly mCurrentState at +0x2104
    // If state is not 18 (e.g., STATE_IDLE?) and bit 25 of flags at +0x1F54 is not set
    if ((state != 0x12) && ((this->field_0x1F54 >> 0x19 & 1) == 0)) {
        // Call virtual function at vtable+0x1bc (e.g., isActionAllowed?)
        bool canOverride = (*(bool (__thiscall**)(Sentient*))(*(int*)this + 0x1bc))(this);
        if (canOverride != false) {
            return 3; // e.g., STATE_SPECIAL_1
        }
        // Check bitflags at +0x1F98 (byte), mask 0x70 (bits 4-6)
        if ((*(unsigned char*)((char*)this + 0x1F98) & 0x70) != 0) {
            return 4; // e.g., STATE_SPECIAL_2
        }
    }
    return state;
}