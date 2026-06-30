In the decompiled code, the bitwise AND with DAT_00e44680 suggests that the data might be integers representing floats, but the compare is float <= (float)(uint & uint). That's strange. Possibly the globals are actually floats, and the decompiler shows them as uint due to bitwise operations. Alternatively, they are masks for component selection. I'll just represent as float comparisons with threshold, acknowledging the uncertainty.

I'll also note that the virtual function at +0x90 might be "getDirection" and at +500 "playReactionAnimation".

Let's write the code.// FUNC_NAME: Player::processPunch
void __thiscall Player::processPunch(int *this, int *hitInfo, char isPunch)
{
    // vtable method at offset 0x90: likely getHitDirection(this+0x1BA, outBuffer, 1)
    // outBuffer is a 12-byte vector (three floats) followed by other locals
    undefined hitDirection[12];
    uint uStack_3c;  // re-interpreted as first component (X)
    float fStack_38; // Y component
    uint local_34;   // Z component? But used as uint in bitwise compare.
    uint local_44;
    uint local_24;
    uint local_14;
    
    local_44 = 0;
    local_34 = 0;
    local_24 = 0;
    local_14 = _DAT_00d5780c;    // constant (e.g., 0 or identity)
    
    (*(code **)(*this + 0x90))(hitDirection, this + 0x1BA, 1);
    
    // Compare each component (stored as int for bitwise) against threshold
    // DAT_00e44680 appears to be a mask or reinterpreted float constant
    float threshold = DAT_00d5ef84;
    float hitForce;
    if (threshold <= (float)(uStack_3c & DAT_00e44680) ||
        threshold <= (float)((uint)fStack_38 & DAT_00e44680) ||
        threshold <= (float)(local_34 & DAT_00e44680)) {
        // Read Y component, convert to double, call a helper (e.g., FPSetRoundingMode)
        double dVar4 = (double)fStack_38;
        FUN_00b9a9fa();   // likely sets floating-point control word or does nothing
        hitForce = (float)dVar4;
    } else {
        hitForce = 0.0f;
    }
    
    // Obtain defender's data from global function (e.g., getCurrentCharacter)
    int *defenderData = FUN_00471610();
    float defForce;
    if (threshold <= (float)(*(uint *)(defenderData + 0x20) & DAT_00e44680) ||
        threshold <= (float)(*(uint *)(defenderData + 0x24) & DAT_00e44680) ||
        threshold <= (float)(*(uint *)(defenderData + 0x28) & DAT_00e44680)) {
        double dVar4 = (double)*(float *)(defenderData + 0x24);
        FUN_00b9a9fa();
        defForce = (float)dVar4;
    } else {
        defForce = 0.0f;
    }
    
    // Apply the effective force difference
    FUN_007f7540(hitForce - defForce, DAT_00d62b78, DAT_00d5f520);
    
    // If this is a punch (param_3 != 0), play reaction animation based on hit type
    if (isPunch) {
        if (*(int *)(hitInfo + 0x30) == 2) {
            // Heavy punch reaction – constant string stored at DAT_00d62b70
            (*(code **)(*this + 500))(&DAT_00d62b70);
            return;
        }
        if (*(int *)(hitInfo + 0x30) == 1) {
            // Light punch reaction
            (*(code **)(*this + 500))("punched");
        }
    }
}