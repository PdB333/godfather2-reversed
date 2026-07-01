//FUNC_NAME: AudioEmitter::calculatePan

float AudioEmitter::calculatePan(int unkParam, float inputPan, float offset)
{
    bool bVar1;
    char cVar2;
    float *pfVar3;
    float10 fVar4;
    float10 fVar5;
    undefined1 *puVar6;
    undefined1 *puVar7;
    float local_48;
    float local_44;
    float local_40;
    float local_3c;
    float local_38;
    float local_34;
    undefined1 local_30[16];
    undefined1 local_20[28];

    local_44 = inputPan;
    cVar2 = FUN_004ac260(); // likely isMuted() or isPaused()
    if ((cVar2 == '\0') && ((*(uint *)(this + 0xac) >> 1 & 1) == 0)) {
        bVar1 = false;
    } else {
        bVar1 = true;
    }
    if ((*(float *)(this + 0x30) <= _DAT_00d577a0) || (!bVar1)) {
        fVar4 = (float10)FUN_0045fa40(); // getRandomFloat() or getTime()
        local_40 = (float)fVar4;
        fVar5 = (float10)FUN_0045fa60(); // another random/time function
        fVar4 = (float10)local_40;
        local_40 = (float)(fVar4 / fVar5);
        if (fVar4 / fVar5 < (float10)DAT_00e52fa8) {
            return (float10)0;
        }
        puVar7 = local_20;
        puVar6 = local_30;
        fVar4 = (float10)FUN_0045fa40(puVar6, puVar7); // fill vectors
        FUN_0045fbc0((float)fVar4, puVar6, puVar7); // process vectors
        FUN_0056d810(local_30, &local_48, &local_3c, &local_38); // extract components
        local_48 = local_48 * DAT_00e44748;
        fVar4 = (float10)FUN_006d6350(*(float *)(this + 0x80) - offset); // fabs?
        fVar4 = (float10)FUN_006d6350((float)(fVar4 - (float10)local_48));
        local_38 = (float)(fVar4 * (float10)_DAT_00e52ff8);
        local_3c = (local_40 - DAT_00e52fa8) / (_DAT_00d5780c - DAT_00e52fa8);
        local_40 = _DAT_00d5780c;
        local_48 = 0.0;
        if (local_3c <= _DAT_00d5780c) {
            pfVar3 = &local_48;
            if (0.0 <= local_3c) {
                pfVar3 = &local_3c;
            }
        } else {
            pfVar3 = &local_40;
        }
        local_44 = *pfVar3 * local_38 + offset;
    }
    FUN_007992a0(local_44, DAT_00e52fec, unkParam, &local_34, 0); // apply pan
    return (float10)local_34;
}