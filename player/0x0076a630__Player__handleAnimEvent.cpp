// FUNC_NAME: Player::handleAnimEvent
undefined4 __thiscall Player::handleAnimEvent(int this, undefined4 param_2, undefined4 param_3, int eventType, undefined4 param_5)
{
    undefined4 uVar1;
    int iVar2;
    int *piVar3;
    float10 extraout_ST0;
    float local_c;
    float local_8;
    float local_4;
    
    if (eventType == 0x12) { // kAnimEventFootstep?
        if ((*(int *)(this + 0x70) != 0) && (*(int *)(this + 0x70) != 0x48)) {
            getPosition(this, &local_c); // gets current position of this object?
            iVar2 = getPlayerPosition(); // returns pointer to player transform
            local_c = *(float *)(iVar2 + 0x30) - local_c; // deltaX
            local_8 = *(float *)(iVar2 + 0x34) - local_8; // deltaY
            local_4 = *(float *)(iVar2 + 0x38) - local_4; // deltaZ
            if (local_4 * local_4 + local_8 * local_8 + local_c * local_c < g_footstepThreshold * g_footstepThreshold) {
                return 1; // handled
            }
        }
    }
    else {
        if (eventType == 0x13) { // kAnimEventImpact?
            if (((*(int *)(this + 0x70) != 0) && (*(int *)(this + 0x70) != 0x48)) &&
               (*(char *)(this + 0x84) != '\0')) { // m_bCanImpact?
                if (*(int *)(this + 0x70) == 0) {
                    iVar2 = 0;
                }
                else {
                    iVar2 = *(int *)(this + 0x70) + -0x48; // pointer to base object (e.g. Character)
                }
                if ((*(uint *)(iVar2 + 0xa18) >> 0x19 & 1) == 0) { // check some flag (bit 25)
                    if (*(int *)(this + 0x70) == 0) {
                        piVar3 = (int *)0x0;
                    }
                    else {
                        piVar3 = (int *)(*(int *)(this + 0x70) + -0x48);
                    }
                    (**(code **)(*piVar3 + 0x4c))(&local_c); // vtable call -> GetPosition
                    FUN_0046cb10(&local_c); // compute something (distance?)
                    if (extraout_ST0 <= (float10)g_impactDistanceThreshold) {
                        return 0; // not handled
                    }
                }
            }
            return 1;
        }
        if (eventType != 0x14) { // kAnimEventOther?
            uVar1 = defaultHandler(param_2, param_3, eventType, param_5);
            return uVar1;
        }
        if (g_globalTime < *(float *)(this + 0x88)) { // m_fNextEventTime?
            return 1;
        }
    }
    return 0;
}