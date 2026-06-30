// FUNC_NAME: WheeledVehicle::updateWheelForces

void __thiscall WheeledVehicle::updateWheelForces(int* thisPtr, undefined4 param_2, int vehiclePtr, int wheelStatesArray)
{
    float* wheelData;
    float fVar2, fVar3, fVar6, fVar9, fVar10, fVar11, fVar12, fVar13;
    char charLoopIndex;
    int intVar5, intVar8;
    uint loopIndex;
    int* tempPtr;
    int* otherObjPtr;
    float localStack_b4, localStack_b0, localStack_ac, localStack_a8, localStack_a4, localStack_a0, localStack_94, localStack_90, localStack_8c, localStack_84;
    undefined4 localStack_80;
    float localStack_74[8];
    undefined4 localStack_54;
    int localStack_44;
    float localStack_34, localStack_20;

    otherObjPtr = thisPtr;
    // Call virtual preUpdate on vehicle
    (**(code**)(*thisPtr + 0x28))(vehiclePtr);

    loopIndex = loopIndex & 0xFFFFFF00; // Clear lower byte
    localStack_84 = DAT_00e2b1a4; // Some constant, perhaps gravity

    // Get numWheels from a nested struct: vehiclePtr+0x1c -> struct -> +0x20
    char* wheelCountPtr = *(char**)(*(int*)(vehiclePtr + 0x1c) + 0x20);
    if (*wheelCountPtr <= 0) {
        return;
    }

    do {
        intVar5 = (int)(char)loopIndex; // Wheel index as signed char
        // vehiclePtr+0x48 points to an array of wheel transforms (each 0xC0 bytes)
        intVar8 = intVar5 * 0xC0 + *(int*)(vehiclePtr + 0x48);
        
        localStack_54 = 0;
        localStack_44 = 0;
        localStack_80 = 0xFFFFFFFF;
        localStack_74[0] = -NAN; // Sentinel value
        // wheelStatesArray is array of 0x40 bytes per wheel (our output)
        wheelData = (float*)(intVar5 * 0x40 + wheelStatesArray);

        // Call virtual getWheelTransform(vehiclePtr, &wheelTransform[6 floats])
        (**(code**)(*otherObjPtr + 0x24))(intVar8, vehiclePtr, &localStack_94);

        // Get data from some other structure at vehiclePtr+0x34 -> +8 -> offset +0x20
        fVar10 = *(float*)(*(int*)(*(int*)(vehiclePtr + 0x34) + 8) + 0x20 + intVar5 * 0x30);
        // Get another value from vehiclePtr+0x1c -> +0x8C -> offset +0x28 per wheel
        fVar11 = *(float*)(*(int*)(*(int*)(vehiclePtr + 0x1c) + 0x8C) + intVar5 * 0x28);

        fVar6 = 0.0f;
        if (localStack_44 == 0) {
            // First time initialization branch (localStack_44 is 0 initially)
            wheelData[0xB] = fVar10;   // +0x2C
            fVar6 = DAT_00e44564;      // Some constant, maybe 1.0f
            wheelData[9] = 0.0f;       // +0x24
            wheelData[0xC] = 0.0f;     // +0x30
            wheelData[0] = *(float*)(intVar8 + 0x40);   // +0x00
            wheelData[1] = *(float*)(intVar8 + 0x44);   // +0x04
            wheelData[2] = *(float*)(intVar8 + 0x48);   // +0x08
            wheelData[3] = *(float*)(intVar8 + 0x4C);   // +0x0C
            fVar10 = *(float*)(intVar8 + 100);           // +0x64
            fVar11 = *(float*)(intVar8 + 0x68);          // +0x68
            wheelData[4] = fVar6 - *(float*)(intVar8 + 0x60);  // +0x10
            localStack_84 = DAT_00e2b1a4;
            wheelData[5] = fVar6 - fVar10;               // +0x14
            wheelData[6] = fVar6 - fVar11;               // +0x18
            wheelData[8] = 0.0f;                         // +0x20
        } else {
            wheelData[4] = localStack_94;   // +0x10
            wheelData[5] = localStack_90;   // +0x14
            wheelData[6] = localStack_8C;   // +0x18
            intVar5 = 0;
            do {
                float* pStackVal = localStack_74 + intVar5;
                if (*pStackVal == -NAN) break;
                intVar5 = intVar5 + 1;
                wheelData[10] = *pStackVal; // +0x28
            } while (intVar5 < 8);
            // localStack_44 is an object pointer; check its byte at +0x18
            if (*(char*)(localStack_44 + 0x18) == '\x01') {
                fVar6 = (float)(*(char*)(localStack_44 + 0x10) + localStack_44);
            }
            wheelData[9] = fVar6;  // +0x24
            fVar9 = (fVar11 + fVar10) * localStack_84;
            wheelData[0xB] = fVar9 - fVar11; // +0x2C

            fVar10 = *(float*)(intVar8 + 100);  // +0x64
            fVar11 = *(float*)(intVar8 + 0x68); // +0x68
            fVar12 = *(float*)(intVar8 + 0x6C); // +0x6C
            fVar13 = *(float*)(intVar8 + 0x34); // +0x34
            fVar2  = *(float*)(intVar8 + 0x38); // +0x38
            fVar3  = *(float*)(intVar8 + 0x3C); // +0x3C

            wheelData[0] = *(float*)(intVar8 + 0x60) * fVar9 + *(float*)(intVar8 + 0x30); // +0x00
            wheelData[1] = fVar10 * fVar9 + fVar13; // +0x04
            wheelData[2] = fVar11 * fVar9 + fVar2;  // +0x08
            wheelData[3] = fVar12 * fVar9 + fVar3;  // +0x0C

            otherObjPtr = *(int**)((int)fVar6 + 0x84); // Update pointer from some object

            // Call virtual getWheelContactInfo(vehiclePtr, wheelIndex, &resultQuat, &contactCount)
            (**(code**)(*otherObjPtr + 0x20))(vehiclePtr, loopIndex, &localStack_94, &otherObjPtr);

            localStack_ac = wheelData[1]; // +0x04
            localStack_b4 = wheelData[2]; // +0x08
            wheelData[8] = (float)(int)otherObjPtr; // +0x20 store contact count as float? weird

            intVar5 = *(int*)(vehiclePtr + 0x18); // Some transform or body pointer
            // Cross product like computation for torque/force
            fVar10 = *(float*)(intVar8 + 0x68) * wheelData[6] + 
                     *(float*)(intVar8 + 100)  * wheelData[5] + 
                     *(float*)(intVar8 + 0x60) * wheelData[4];

            localStack_b0 = *(float*)(intVar5 + 0x1B4);
            localStack_20 = localStack_ac - *(float*)(intVar5 + 0x134);
            fVar13 = localStack_b4 - *(float*)(intVar5 + 0x138);
            localStack_34 = (localStack_b0 * fVar13 - *(float*)(intVar5 + 0x1B8) * localStack_20) + 
                            *(float*)(intVar5 + 0x1A0);

            fVar12 = wheelData[0] - *(float*)(intVar5 + 0x130);

            // Same for other object (otherObjPtr now points to some other body?)
            localStack_a4 = wheelData[0] - *(float*)((int)fVar6 + 0x130);
            localStack_a0 = localStack_ac - *(float*)((int)fVar6 + 0x134);
            fVar11 = localStack_b4 - *(float*)((int)fVar6 + 0x138);
            localStack_a8 = *(float*)((int)fVar6 + 0x1B4);

            if (fVar10 < DAT_00e44564 - *(float*)(*(int*)(vehiclePtr + 0x1C) + 0x84)) {
                // If force magnitude is below a threshold, compute constraint impulse
                fVar10 = DAT_00e2eff4 / fVar10; // Some constant over force magnitude
                // Complex expression computing impulse along constraint axes
                wheelData[0xC] = fVar10 * (
                    wheelData[6] * (
                        (*(float*)(intVar5 + 0x1A8) + (*(float*)(intVar5 + 0x1B0) * localStack_20 - localStack_b0 * fVar12)) -
                        (*(float*)((int)fVar6 + 0x1A8) + (*(float*)((int)fVar6 + 0x1B0) * localStack_a0 - localStack_a8 * localStack_a4))
                    ) +
                    wheelData[5] * (
                        (*(float*)(intVar5 + 0x1A4) + (*(float*)(intVar5 + 0x1B8) * fVar12 - *(float*)(intVar5 + 0x1B0) * fVar13)) -
                        (*(float*)((int)fVar6 + 0x1A4) + (*(float*)((int)fVar6 + 0x1B8) * localStack_a4 - *(float*)((int)fVar6 + 0x1B0) * fVar11))
                    ) +
                    wheelData[4] * (
                        localStack_34 - 
                        ((localStack_a8 * fVar11 - *(float*)((int)fVar6 + 0x1B8) * localStack_a0) + *(float*)((int)fVar6 + 0x1A0))
                    )
                );
                localStack_84 = DAT_00e2b1a4;
                wheelData[0xD] = fVar10; // +0x34
            } else {
                wheelData[0xC] = 0.0f; // +0x30
                localStack_84 = DAT_00e2b1a4;
                wheelData[0xD] = DAT_00e2b1a4 / *(float*)(*(int*)(vehiclePtr + 0x1C) + 0x84); // +0x34
            }
        }
        wheelData[0xD] = localStack_84; // Overwrite? Might be final stiffness or damping
        charLoopIndex = (char)loopIndex + 1;
        loopIndex = CONCAT31(loopIndex._1_3_, charLoopIndex);
    } while (charLoopIndex < *(char*)(*(int*)(vehiclePtr + 0x1C) + 0x20));
    return;
}