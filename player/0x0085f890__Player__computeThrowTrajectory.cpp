// FUNC_NAME: Player::computeThrowTrajectory
void __thiscall Player::computeThrowTrajectory(Player* this, float* outVelocity, float* outAngle, int* outFlags) {
    float fVar1;
    float fVar2;
    int iVar3, iVar4, iVar5;
    float10 fVar6;
    double dVar7;
    float deltaX, deltaY;
    int unusedInt;
    float stack_c[3]; // actually used as fStack_c, fStack_8, fStack_4

    // Load player state fields
    deltaX = (float)this->field_414;   // +0x414: aim start X or something
    fVar1  = (float)this->field_452;   // +0x452: time or speed scalar
    unusedInt = this->field_415;        // +0x415: integer part, maybe unused
    deltaY = (float)this->field_416;   // +0x416: aim start Y
    fVar2  = (float)this->field_3F1;   // +0x3F1: gravity factor or multiplier

    if (fVar2 != someGlobalFactor) { // _DAT_00d577a0
        dVar7 = (double)fVar1;
        unknownMultiplyByConst1(); // FUN_00b99e20
        deltaX -= (float)dVar7 * fVar2; // adjust X by time*gravity
        dVar7 = (double)fVar1;
        unknownMultiplyByConst2(); // FUN_00b99fcb
        deltaY += (float)dVar7 * fVar2; // adjust Y
    }

    fVar6 = (float10)getVectorLength(&deltaX); // FUN_00470250, return magnitude of 2D vector (deltaX, deltaY)
    *outAngle = (float)fVar6;
    float maxAngle = someGlobalAngleThreshold; // DAT_00d75830
    *outFlags = 0;
    if (*outAngle <= maxAngle && maxAngle != *outAngle) {
        *outVelocity = 0.0f;
        return;
    }

    vectorToAngle(&deltaX, outVelocity, outFlags); // FUN_008767c0: converts vector to angle and maybe sets outVelocity and outFlags

    // Check a specific flag bit in player state
    if ((this->field_322 >> 11) & 1) { // +0x322 bit 11: some mode flag (aiming/throwing)
        fVar6 = (float10)(*(code**)*this + 0x1a8)(); // virtual call: returns random factor (wind/error?)
        if ((float10)someWindFactorThreshold < fVar6) { // DAT_00e446c0
            unknownGetWindVars(fVar1, stack_c); // FUN_00601970: passes timeScale and array for wind components
            iVar3 = getSomeRandomId(); // FUN_00471610
            iVar4 = getSomeRandomId(); // FUN_00471610
            iVar5 = getSomeRandomId(); // FUN_00471610

            // Dot product of wind/random vectors with some predefined axes
            float dot = *(float*)(iVar4 + 0x24) * stack_c[1] + *(float*)(iVar3 + 0x20) * stack_c[0] + *(float*)(iVar5 + 0x28) * stack_c[2];
            if (dot < someDotThreshold) { // _DAT_00d63d70
                float factor = someWindFactorThreshold / (float)fVar6;
                *outVelocity = (factor * factor) * *outVelocity; // scale velocity based on random wind
            }
        }
    }
}