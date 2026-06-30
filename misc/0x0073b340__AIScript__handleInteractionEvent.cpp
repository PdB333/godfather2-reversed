// FUNC_NAME: AIScript::handleInteractionEvent
void __thiscall AIScript::handleInteractionEvent(void *this, void *pTarget) {
    char result;
    int iVar2;
    // Global variables from decompiler: likely something like g_interactionEnabled, g_distanceX, g_distanceZ
    extern int _unaff_EBX; // Global boolean controlling interaction logic
    extern float _unaff_ESI; // Global X distance component
    extern float _unaff_EDI; // Global Z distance component (or pointer, but used as float in sqrt)
    extern float _DAT_00d5780c; // Distance threshold

    if (pTarget != nullptr) {
        // Check if target matches first event ID
        int eventId1 = 0x383225a1;
        int localArray[7] = {0};
        result = (*(code **)(*(int *)pTarget + 0x10))(eventId1, localArray);
        if (result != '\0' && _unaff_EBX != 0) {
            // Set flag on this object: bit 0x20000 at offset 0x74
            *(uint *)((int)this + 0x74) |= 0x20000;
            return;
        }

        // Check if target matches second event ID
        int eventId2 = 0x55859efa;
        int localVar; // stack0xffffffd8
        result = (*(code **)(*(int *)pTarget + 0x10))(eventId2, &localVar);
        if (result != '\0' &&
            (_unaff_EDI != 0.0 && ((*(uint *)((int)&_unaff_EDI + 0x8e8) >> 9 & 1) != 0))) {
            // Trigger response on target
            (*(code **)(*(int *)pTarget + 0x4c))(&localVar);
            // Compute squared 2D distance (ignoring Y)
            float fDistSq = _unaff_ESI * _unaff_ESI + 0.0f + _unaff_EDI * _unaff_EDI;
            if (sqrtf(fDistSq) < _DAT_00d5780c) {
                iVar2 = /* FUN_0073b060 */ someValidationCheck(pTarget);
                if (iVar2 != 0) {
                    // Set blend weight: param at this+0x5c, weight 1.0f, blend type 0
                    FUN_009b0820(*(undefined4 *)((int)this + 0x5c), 0x3f800000, 0);
                    result = /* FUN_009b0f60 */ someAnimationCheck();
                    if (result != '\0') {
                        /* FUN_0044b210 */ executeInteractionAction(pTarget);
                    }
                }
            }
        }
    }
    return;
}