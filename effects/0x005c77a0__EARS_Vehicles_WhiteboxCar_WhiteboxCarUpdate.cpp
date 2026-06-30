// Xbox PDB: EARS::Vehicles::WhiteboxCar::WhiteboxCarUpdate
// FUNC_NAME: ParticleSystem::update

void __thiscall ParticleSystem::update(int thisPtr, undefined4 param2, undefined4 param3, int* geometryData, char* description, int* particleParamsPtr, undefined4 param7, undefined4 param8)
{
    float fVar1, fVar2, fVar3, fVar4;
    float fVar21, fVar22, fVar23, fVar24, fVar25, fVar27, fVar28, fVar29, fVar30;
    double dVar26;
    undefined4 uVar5, uVar6, uVar7, uVar8;
    undefined4 uVar9, uVar10, uVar11, uVar12, uVar13, uVar14, uVar15;
    int* piVar19;
    char* pcVar17;
    int iVar18;
    float* particleParams; // pointer to float array after allocation

    // --- First time initialization: parse description and allocate particle parameters ---
    if (*particleParamsPtr == 0) {
        // Allocate 15 floats (0x3c bytes) for particle parameters
        particleParams = (float*)FUN_009c8e50(0x3c);
        float defaultVal = DAT_00e2b1a4; // likely 1.0f or 0.5f
        if (particleParams == (float*)0x0) {
            particleParams = (float*)0x0;
        } else {
            particleParams[0] = 0.0f;           // motionType: default 0
            particleParams[1] = defaultVal;     // minAlpha
            particleParams[2] = defaultVal;     // maxAlpha
            particleParams[3] = defaultVal;     // rateAlpha
            particleParams[4] = 0.0f;           // yDirection
            particleParams[5] = 0.0f;           // xDirection
            particleParams[6] = 0.0f;           // offset
            particleParams[7] = 0.0f;           // scaleAmount
            particleParams[8] = 0.0f;           // rotSpeed
            particleParams[9] = defaultVal;     // redMax
            particleParams[10] = defaultVal;    // redMin
            particleParams[11] = defaultVal;    // blueMax
            particleParams[12] = defaultVal;    // blueMin
            particleParams[13] = defaultVal;    // greenMax
            particleParams[14] = defaultVal;    // greenMin
        }
        *particleParamsPtr = (int)particleParams;

        // Parse motion type string
        pcVar17 = (char*)FUN_005c7540(description, 0x26); // extract token at position 0x26? Or parse key?
        if (pcVar17 != (char*)0x0) {
            iVar18 = __stricmp(pcVar17, "linear");
            if (iVar18 == 0) {
                particleParams[0] = 1.0f; // linear
            }
            iVar18 = __stricmp(pcVar17, "circular");
            if (iVar18 == 0) {
                particleParams[0] = 2.0f; // circular
            }
            iVar18 = __stricmp(pcVar17, "loopy");
            if (iVar18 == 0) {
                particleParams[0] = 3.0f; // loopy
            }
            iVar18 = __stricmp(pcVar17, "aurora");
            if (iVar18 == 0) {
                particleParams[0] = 4.0f; // aurora
            }
        }

        // Parse alpha min
        float parsedVal;
        pcVar17 = _strstr(description, "_minalpha=");
        if ((pcVar17 == (char*)0x0) || (pcVar17 == (char*)0xfffffff6)) {
            parsedVal = 0.0f;
        } else {
            parsedVal = FUN_005c7270(); // parse float from string
        }
        particleParams[1] = parsedVal * DAT_00e2e780; // scale factor

        // Parse alpha max
        pcVar17 = _strstr(description, "_maxalpha=");
        if ((pcVar17 == (char*)0x0) || (pcVar17 == (char*)0xfffffff6)) {
            parsedVal = 0.0f;
        } else {
            parsedVal = FUN_005c7270();
        }
        particleParams[2] = parsedVal * DAT_00e2e780;

        // Parse red min
        pcVar17 = _strstr(description, "_redmin=");
        if ((pcVar17 == (char*)0x0) || (pcVar17 == (char*)0xfffffff8)) {
            parsedVal = 0.0f;
        } else {
            parsedVal = FUN_005c7270();
        }
        particleParams[10] = parsedVal * DAT_00e2e780;

        // Parse red max
        pcVar17 = _strstr(description, "_redmax=");
        if ((pcVar17 == (char*)0x0) || (pcVar17 == (char*)0xfffffff8)) {
            parsedVal = 0.0f;
        } else {
            parsedVal = FUN_005c7270();
        }
        particleParams[9] = parsedVal * DAT_00e2e780;

        // Parse green min
        pcVar17 = _strstr(description, "_greenmin=");
        if ((pcVar17 == (char*)0x0) || (pcVar17 == (char*)0xfffffff6)) {
            parsedVal = 0.0f;
        } else {
            parsedVal = FUN_005c7270();
        }
        particleParams[14] = parsedVal * DAT_00e2e780;

        // Parse green max
        pcVar17 = _strstr(description, "_greenmax=");
        if ((pcVar17 == (char*)0x0) || (pcVar17 == (char*)0xfffffff6)) {
            parsedVal = 0.0f;
        } else {
            parsedVal = FUN_005c7270();
        }
        particleParams[13] = parsedVal * DAT_00e2e780;

        // Parse blue min
        pcVar17 = _strstr(description, "_bluemin=");
        if ((pcVar17 == (char*)0x0) || (pcVar17 == (char*)0xfffffff7)) {
            parsedVal = 0.0f;
        } else {
            parsedVal = FUN_005c7270();
        }
        particleParams[12] = parsedVal * DAT_00e2e780;

        // Parse blue max
        pcVar17 = _strstr(description, "_bluemax=");
        if ((pcVar17 == (char*)0x0) || (pcVar17 == (char*)0xfffffff7)) {
            parsedVal = 0.0f;
        } else {
            parsedVal = FUN_005c7270();
        }
        particleParams[11] = parsedVal * DAT_00e2e780;

        // Parse rate alpha
        pcVar17 = _strstr(description, "_ratealpha=");
        if ((pcVar17 == (char*)0x0) || (pcVar17 == (char*)0xfffffff5)) {
            parsedVal = 0.0f;
        } else {
            parsedVal = FUN_005c7270();
        }
        particleParams[3] = parsedVal;

        // Parse x direction
        pcVar17 = _strstr(description, "_xdirection=");
        if ((pcVar17 == (char*)0x0) || (pcVar17 == (char*)0xfffffff4)) {
            parsedVal = 0.0f;
        } else {
            parsedVal = FUN_005c7270();
        }
        particleParams[5] = parsedVal;

        // Parse y direction
        pcVar17 = _strstr(description, "_ydirection=");
        if ((pcVar17 == (char*)0x0) || (pcVar17 == (char*)0xfffffff4)) {
            parsedVal = 0.0f;
        } else {
            parsedVal = FUN_005c7270();
        }
        particleParams[4] = parsedVal;

        // Parse offset
        pcVar17 = _strstr(description, "_offset=");
        if ((pcVar17 == (char*)0x0) || (pcVar17 == (char*)0xfffffff8)) {
            parsedVal = 0.0f;
        } else {
            parsedVal = FUN_005c7270();
        }
        particleParams[6] = parsedVal;

        // Parse scale amount
        pcVar17 = _strstr(description, "_scaleamount=");
        if ((pcVar17 == (char*)0x0) || (pcVar17 == (char*)0xfffffff3)) {
            parsedVal = 0.0f;
        } else {
            parsedVal = FUN_005c7270();
        }
        particleParams[7] = parsedVal;

        // Parse rotation speed
        pcVar17 = _strstr(description, "_rotspeed=");
        if ((pcVar17 == (char*)0x0) || (pcVar17 == (char*)0xfffffff6)) {
            parsedVal = 0.0f;
        } else {
            parsedVal = FUN_005c7270();
        }
        particleParams[8] = parsedVal;
    }

    // --- Per-frame update ---
    float deltaTime = DAT_00e2cd54; // frame time constant? Or actually from global
    particleParams = (float*)*particleParamsPtr;
    iVar18 = DAT_01205210 - *(int*)(thisPtr + 4); // time delta
    float dt = (float)iVar18;
    if (iVar18 < 0) {
        dt = dt + DAT_00e44578; // handle wrapping
    }
    dt = dt * DAT_00e2e210; // scale to seconds? Or frame count?
    *(int*)(thisPtr + 4) = DAT_01205210; // update last time

    iVar18 = geometryData[1]; // pointer to vertex data? (struct with positions/colors)
    fVar27 = (particleParams[2] - particleParams[1]) * deltaTime; // alpha change
    fVar28 = (particleParams[9] - particleParams[10]) * deltaTime; // red change
    fVar29 = (particleParams[13] - particleParams[14]) * deltaTime; // green change
    fVar30 = (particleParams[11] - particleParams[12]) * deltaTime; // blue change

    geometryData[3] = 0; // flag? reset

    // Save original vertex attributes
    fVar1 = *(float*)(iVar18 + 0x14); // original x?
    fVar2 = *(float*)(iVar18 + 0x18); // original y?
    fVar3 = *(float*)(iVar18 + 0x24); // original u? or another coordinate
    fVar4 = *(float*)(iVar18 + 0x28); // original v?
    uVar5 = *(undefined4*)(iVar18 + 0x1c); // original?
    uVar6 = *(undefined4*)(iVar18 + 0x2c); // original?

    // Compute angle based on offset and time
    float offset = particleParams[6];
    float timeVar = offset + DAT_012056a4; // global time accumulator
    dVar26 = (double)timeVar;
    FUN_00b99fcb(); // cos?
    float cosVal = (float)dVar26;
    dVar26 = (double)timeVar;
    FUN_00b99e20(); // sin?
    float sinVal = (float)dVar26;

    // Apply rotation if rotSpeed != 0 and not aurora type
    if ((particleParams[8] != DAT_00e2b05c) && (*(int*)particleParams != 4)) {
        float rotTime = particleParams[8] * DAT_012056a4 + offset;
        dVar26 = (double)rotTime;
        FUN_00b99fcb();
        float cosRot = (float)dVar26;
        dVar26 = (double)rotTime;
        FUN_00b99e20();
        float sinRot = (float)dVar26;
        // Apply rotation to position
        *(float*)(iVar18 + 0x14) = cosRot * fVar2 + sinRot * fVar1;
        *(float*)(iVar18 + 0x18) = sinRot * fVar2 - cosRot * fVar1;
        *(float*)(iVar18 + 0x24) = cosRot * fVar4 + sinRot * fVar3;
        *(float*)(iVar18 + 0x28) = sinRot * fVar4 - cosRot * fVar3;
    }

    float one = DAT_00e2b1a4; // 1.0f
    // Apply scale if scaleAmount != 0 and not aurora
    if ((particleParams[7] != DAT_00e2b05c) && (*(int*)particleParams != 4)) {
        *(float*)(iVar18 + 0x14) = (sinVal * particleParams[7] + one) * *(float*)(iVar18 + 0x14);
        *(float*)(iVar18 + 0x18) = (cosVal * particleParams[7] + one) * *(float*)(iVar18 + 0x18);
        *(float*)(iVar18 + 0x24) = (one - cosVal * particleParams[7]) * *(float*)(iVar18 + 0x24);
        *(float*)(iVar18 + 0x28) = (sinVal * particleParams[7] + one) * *(float*)(iVar18 + 0x28);
    }

    // Update position based on motion type
    switch (*(int*)particleParams) {
    case 1: // linear
        *(float*)(iVar18 + 0x1c) = particleParams[5] * DAT_012056a4 + particleParams[6]; // x movement
        *(float*)(iVar18 + 0x2c) = particleParams[4] * DAT_012056a4 + particleParams[6]; // y movement
        break;
    case 2: // circular
        *(float*)(iVar18 + 0x1c) = particleParams[5] * cosVal;
        *(float*)(iVar18 + 0x2c) = particleParams[4] * sinVal;
        break;
    case 3: // loopy
        dVar26 = (double)sinVal;
        FUN_00b99fcb();
        float cosSin = (float)dVar26;
        *(float*)(iVar18 + 0x1c) = (cosSin + cosVal) * particleParams[5]; // combination
        dVar26 = (double)cosVal;
        FUN_00b99e20();
        float sinCos = (float)dVar26;
        *(float*)(iVar18 + 0x2c) = (sinCos + sinVal) * particleParams[4];
        break;
    case 4: // aurora
        *(float*)(iVar18 + 0x1c) = particleParams[5] * DAT_012056a4 + particleParams[6];
        *(float*)(iVar18 + 0x2c) = particleParams[4] * DAT_012056a4 + particleParams[6];
        // Also set scale directly
        *(float*)(iVar18 + 0x14) = particleParams[7];
        *(float*)(iVar18 + 0x18) = particleParams[7];
        *(float*)(iVar18 + 0x24) = particleParams[7];
        *(float*)(iVar18 + 0x28) = particleParams[7];
        break;
    }

    // Clamp x,y positions to valid range [globalMin, globalMax] or randomize
    if ((DAT_00e446f0 <= *(float*)(iVar18 + 0x1c)) || (*(float*)(iVar18 + 0x1c) <= DAT_00e44998)) {
        float10 randVal = (float10)FUN_00b9dbba(); // random float
        *(float*)(iVar18 + 0x1c) = (float)randVal;
    }
    if ((DAT_00e446f0 <= *(float*)(iVar18 + 0x2c)) || (*(float*)(iVar18 + 0x2c) <= DAT_00e44998)) {
        float10 randVal = (float10)FUN_00b9dbba();
        *(float*)(iVar18 + 0x2c) = (float)randVal;
    }

    // Save global state before calling render
    uVar15 = _DAT_0119d0cc;
    uVar14 = _DAT_0119d0c8;
    uVar13 = _DAT_0119d0c4;
    uVar12 = DAT_0119d0c0;
    fVar23 = DAT_0119d0bc;
    uVar11 = _DAT_0119d0b8;
    uVar10 = _DAT_0119d0b4;
    uVar9 = _DAT_0119d0b0;
    uVar8 = PTR_DAT_00f17650._0_1_;
    DAT_012056a4 = DAT_012056a4 + dt; // advance global time
    PTR_DAT_00f17650._0_1_ = 0;

    // Compute alpha interpolation based on rate
    dVar26 = (double)(particleParams[3] * DAT_012056a4 + particleParams[6]);
    FUN_00b99e20(); // sin? probably interpolation factor
    float alphaFactor = (float)dVar26;
    DAT_0119d0bc = ((particleParams[2] - fVar27) + alphaFactor * fVar27) * DAT_0119d0bc;
    _DAT_0119d0b8 = (particleParams[11] - fVar30) + alphaFactor * fVar30;
    _DAT_0119d0b4 = (particleParams[13] - fVar29) + alphaFactor * fVar29;
    _DAT_0119d0b0 = (particleParams[9] - fVar28) + alphaFactor * fVar28;

    // Get some vertex data index
    uVar7 = *(undefined4*)(*(int*)(*geometryData * 0xd4 + 0xc4 + DAT_012234f4) + -4 + *(int*)(iVar18 + 0x34) * 4);

    // Update vertex buffer pointer?
    piVar19 = (int*)(DAT_01206880 + 0x14);
    **(undefined4**)(DAT_01206880 + 0x14) = &PTR_LAB_01126d98;
    *piVar19 = *piVar19 + 4;
    *(undefined4*)*piVar19 = uVar7;
    *piVar19 = *piVar19 + 4;
    *(undefined4*)*piVar19 = 0x30000; // primitive type? triangles?
    *piVar19 = *piVar19 + 4;

    // Call render submission
    FUN_005c63a0(geometryData, param7, param8);

    // Update vertex buffer pointer again for second batch?
    piVar19 = (int*)(DAT_01206880 + 0x14);
    **(undefined4**)(DAT_01206880 + 0x14) = &PTR_LAB_01126d98;
    *piVar19 = *piVar19 + 4;
    *(undefined4*)*piVar19 = uVar7;
    *piVar19 = *piVar19 + 4;
    *(undefined4*)*piVar19 = 0x230000; // different primitive type? lines?
    *piVar19 = *piVar19 + 4;

    // Restore original vertex attributes (they were modified in place)
    *(float*)(iVar18 + 0x14) = fVar1;
    *(float*)(iVar18 + 0x24) = fVar3;
    *(float*)(iVar18 + 0x18) = fVar2;
    *(float*)(iVar18 + 0x28) = fVar4;
    *(undefined4*)(iVar18 + 0x1c) = uVar5;
    *(undefined4*)(iVar18 + 0x2c) = uVar6;

    // Restore global state
    _DAT_0119d0b0 = (float)uVar9;
    _DAT_0119d0b4 = (float)uVar10;
    _DAT_0119d0b8 = (float)uVar11;
    DAT_0119d0bc = fVar23;
    DAT_0119d0c0 = uVar12;
    _DAT_0119d0c4 = uVar13;
    _DAT_0119d0c8 = uVar14;
    _DAT_0119d0cc = uVar15;
    PTR_DAT_00f17650._0_1_ = uVar8;

    return;
}