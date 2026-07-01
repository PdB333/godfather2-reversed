// FUNC_NAME: VehiclePhysics::computeWheelForces
void __thiscall VehiclePhysics::computeWheelForces(
    int this,
    undefined4 *outWheelForce1,
    undefined4 *outWheelForce2,
    int outSuspensionForce1,
    int outSuspensionForce2,
    float inputSteer,
    float inputAccel,
    int vehicleData
)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    float fVar8;
    float *pfVar9;
    float *pfVar10;
    float fVar11;
    float fVar12;
    float fVar13;
    float fVar14;
    float fVar15;
    float local_14;
    float local_10;
    float local_c;
    float local_8[2];
    
    fVar8 = DAT_00e44564; // gravity constant
    pfVar9 = &local_14;
    if (*(char *)(this + 0x5e0) != '\0') { // vehicle is active
        local_14 = _DAT_00d94c2c * DAT_00e445c8; // maxSteerAngle * deltaTime
        fVar1 = *(float *)(vehicleData + 0x118); // wheel forward direction X
        fVar2 = *(float *)(vehicleData + 0x11c); // wheel forward direction Y
        fVar3 = *(float *)(vehicleData + 0x120); // wheel forward direction Z
        local_10 = 0.0;
        if ((inputSteer <= local_14) && (pfVar9 = &local_10, 0.0 <= inputSteer)) {
            pfVar9 = &inputSteer;
        }
        local_c = _DAT_00d5780c; // 1.0f
        local_8[0] = 0.0;
        if (*pfVar9 / local_14 <= _DAT_00d5780c) {
            pfVar10 = local_8;
            if (0.0 <= *pfVar9 / local_14) {
                pfVar10 = &inputSteer;
            }
        } else {
            pfVar10 = &local_c;
        }
        fVar11 = *(float *)(vehicleData + 0x10c) * *pfVar10; // wheelRadius * steerFactor
        fVar15 = DAT_00e44564 - *(float *)(vehicleData + 0x158) * fVar1; // gravity - suspensionStiffness * forwardX
        fVar4 = *(float *)(vehicleData + 0x164); // wheel lateral friction X
        fVar5 = *(float *)(vehicleData + 0x168); // wheel lateral friction Y
        fVar6 = *(float *)(vehicleData + 0x160); // wheel longitudinal friction X
        fVar7 = *(float *)(vehicleData + 0x16c); // wheel longitudinal friction Z
        fVar13 = 0.0;
        fVar14 = 0.0;
        if (*(char *)(this + 0x5e4) == '\0') { // not braking
            if (inputAccel < 0.0) {
                fVar14 = inputAccel * DAT_00e445c8 * _DAT_00d700c8; // reverse acceleration
                fVar13 = 0.0;
            } else {
                fVar13 = inputAccel * DAT_00e445c8 * _DAT_00d700cc; // forward acceleration
                fVar14 = 0.0;
            }
        }
        fVar12 = DAT_00e53694; // max grip multiplier
        if (*(float *)(this + 0xf8) < DAT_00e5369c) { // speed < threshold
            fVar12 = (*(float *)(this + 0xf8) / DAT_00e5369c) * (DAT_00e53694 - DAT_00e53698) +
                     DAT_00e53698; // interpolate grip based on speed
        }
        outWheelForce1[5] = (fVar13 + (*(float *)(vehicleData + 0x15c) + fVar11) * fVar2) * fVar12; // lateral force Y
        outWheelForce1[6] = fVar12 * fVar6 * fVar3; // longitudinal force Z
        outWheelForce1[4] = fVar12 * fVar15; // vertical force X
        outWheelForce2[4] = fVar12 * fVar4 * fVar1; // vertical force X
        outWheelForce2[5] = (fVar14 + (fVar5 + fVar11) * fVar2) * fVar12; // lateral force Y
        outWheelForce2[6] = fVar12 * fVar7 * fVar3; // longitudinal force Z
        fVar3 = *(float *)(vehicleData + 0x148); // suspension damping
        fVar4 = *(float *)(vehicleData + 0x150); // suspension spring
        fVar5 = *(float *)(vehicleData + 0x14c); // suspension travel
        fVar6 = *(float *)(vehicleData + 0x154); // suspension force
        fVar7 = *(float *)(vehicleData + 0x140); // suspension rest length
        *(float *)(outSuspensionForce1 + 0x14) = fVar12 * *(float *)(vehicleData + 0x144) * fVar2; // suspension force Y
        *(float *)(outSuspensionForce1 + 0x18) = fVar12 * fVar3 * fVar2; // suspension force Z
        *(float *)(outSuspensionForce1 + 0x10) = (fVar8 - fVar7 * fVar1) * fVar12; // suspension force X
        *(float *)(outSuspensionForce2 + 0x10) = fVar12 * fVar5 * fVar1; // suspension force X
        *(float *)(outSuspensionForce2 + 0x18) = fVar12 * fVar6 * fVar2; // suspension force Z
        fVar8 = _DAT_00d5780c; // 1.0f
        *(float *)(outSuspensionForce2 + 0x14) = fVar12 * fVar4 * fVar2; // suspension force Y
        outWheelForce1[2] = 0;
        outWheelForce1[1] = 0;
        *outWheelForce1 = 0;
        outWheelForce1[3] = fVar8; // set w component to 1.0
        outWheelForce2[2] = 0;
        outWheelForce2[1] = 0;
        *outWheelForce2 = 0;
        outWheelForce2[3] = fVar8;
    }
    return;
}