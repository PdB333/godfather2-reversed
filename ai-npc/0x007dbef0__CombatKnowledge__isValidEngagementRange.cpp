// FUNC_NAME: CombatKnowledge::isValidEngagementRange
int __fastcall CombatKnowledge::isValidEngagementRange(CombatKnowledge* this)
{
    float ratio;
    
    // +0x54: byte flag indicating if this target/knowledge entry is active
    if (this->field_0x54 != 0) {
        // +0x5c: current distance
        // +0x70: maximum engagement distance
        if (this->field_0x5c <= this->field_0x70) {
            // +0x58: integer mode or direction (0 = front? 1 = back?)
            if (this->field_0x58 == 0) {
                return 0; // not valid when within range but mode==0
            }
        }
        else {
            ratio = this->field_0x70 / this->field_0x5c;
            if (this->field_0x58 != 0) {
                // Global constant (likely 1.0f) used to invert the ratio
                ratio = _DAT_00d5780c - ratio;
            }
            if (ratio > 0.0f) {
                return 0; // ratio too large -> not valid
            }
        }
    }
    return 1; // all checks passed -> can engage
}