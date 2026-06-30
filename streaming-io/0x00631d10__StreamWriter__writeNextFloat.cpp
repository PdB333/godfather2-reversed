// FUNC_NAME: StreamWriter::writeNextFloat
undefined4 StreamWriter::writeNextFloat(int param_1) {
    int *piVar3;
    int iVar2;
    double dVar4;
    float local_14;
    int local_10;
    float local_c;

    piVar3 = *(int **)(param_1 + 0xc);       // +0xc: end pointer (read limit)
    if (*(int **)(param_1 + 8) <= piVar3) goto LAB_00631dcb; // current >= end? skip
    if (piVar3 == (int *)0x0) goto LAB_00631dcb;
    if (*piVar3 != 3) {
        if (*piVar3 != 4) goto LAB_00631dcb; // type must be 3 or 4
        iVar2 = FUN_00636850(&local_14);      // likely readRandom or check condition
        if (iVar2 == 0) goto LAB_00631dcb;
        local_10 = 3;
        local_c = local_14;
        piVar3 = &local_10;
    }
    local_14 = (float)piVar3[1];               // value at piVar3+1
    if (local_14 == DAT_00e2b05c) {            // sentinel value (NaN or default)
        while (true) {
            piVar3 = *(int **)(param_1 + 0xc);   // refresh end pointer? similar logic
            if (*(int **)(param_1 + 8) <= piVar3 || piVar3 == (int *)0x0) break;
            if (*piVar3 == 3) break;              // type 3: acceptable
            if (*piVar3 == 4 && (iVar2 = FUN_00636850(&local_10), iVar2 != 0)) {
                // type 4 with successful random condition -> treat as type 3
                break;
            }
            // skip this entry? iterate? Actually the while loop continues, but piVar3 is not advanced?
            // The original decompiled shows a while loop with no increment. Possibly the read pointer
            // is advanced inside FUN_00627ac0? But that seems unlikely. Possibly a bug in decompilation.
            // We'll assume it advances the read pointer somewhere, maybe through a function call.
            FUN_00627ac0(PTR_s_number_00e2a8a8); // log "number" error
        }
        // After loop, if we broke successfully, piVar3 points to a valid entry
        local_14 = (float)piVar3[1];
        if (piVar3 == (int *)0x0) {
            local_14 = 0.0f;
        }
    }
    puVar1 = *(undefined4 **)(param_1 + 8);   // current write pointer
    *puVar1 = 3;                              // write type 3 (float)
    dVar4 = (double)local_14;
    FUN_00b9be2b();                            // unknown math function (maybe float to double conversion?)
    puVar1[1] = (float)dVar4;                 // write the float value
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8; // advance write pointer by 8 bytes
    return 1;
LAB_00631dcb:
    local_14 = 0.0f;                          // default value on error
}