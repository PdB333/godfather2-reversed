// FUNC_NAME: OBBIntersector::testRayIntersection

ushort __thiscall OBBIntersector::testRayIntersection(int this, float *rayDirection, float *boxAxis, float *rayOrigin)
{
    // this+0x124: pointer to transform matrix? We subtract 0x48 to get base pointer.
    int transformBase;
    if (*(int *)(this + 0x124) == 0) {
        transformBase = 0;
    } else {
        transformBase = *(int *)(this + 0x124) - 0x48;
    }

    // Copy axes and origin
    float axisX = *boxAxis;          // local_c[0]
    float dirZ = rayDirection[2];    // local_10
    float dx = *(float *)(this + 0x20) - *rayOrigin;        // fVar6 = center.x - rayOrigin.x
    float dz = *(float *)(this + 0x28) - rayOrigin[2];      // local_4 = center.z - rayOrigin.z

    // Project ray origin onto box axis (ignore Y component)
    float dotAxis = axisX * dx + boxAxis[1] * 0.0f + boxAxis[2] * dz;   // fVar7

    // Distance along axis from origin to box (assuming DAT_00e44564 = 1.0f, _DAT_00d5f7b0 = 0.0f)
    float invDist = 1.0f - (dotAxis + 0.0f);  // local_1c = 1.0 - (dotAxis + gZero)

    // Scale axis by inverse distance
    float scaledAxisX = axisX * invDist;   // local_24
    float scaledAxisY = boxAxis[1] * invDist; // local_20
    float scaledAxisZ = boxAxis[2] * invDist; // local_1c

    // Determine half extent sign based on transform flags (bit 29)
    float halfExtent;
    if ((*(uint *)(transformBase + 0x8e0) >> 0x1d & 1) == 0) {
        halfExtent = 1.0f - *(float *)(this + 0x154);   // DAT_00e44564 - halfSize
    } else {
        halfExtent = *(float *)(this + 0x154);           // halfSize
    }

    // Scale direction by half extent
    float dirXScaled = rayDirection[0] * halfExtent;    // local_30
    float dirYScaled = rayDirection[1] * halfExtent;    // local_2c
    float dirZScaled = dirZ * halfExtent;                // local_28

    // Recompute dot products for ray direction
    float dirDot = 1.0f - (rayDirection[0] * dx + rayDirection[1] * 0.0f + dirZ * dz); // fVar6
    float axisDot = 1.0f - dotAxis; // fVar7 = 1.0 - dotAxis (already have this)

    // Scale direction and axis by their respective dot products
    float dirX1 = rayDirection[0] * dirDot;  // local_18
    float dirY1 = rayDirection[1] * dirDot;  // local_14
    float dirZ1 = dirZ * dirDot;             // local_10 (reused)
    float axisX1 = axisX * axisDot;          // local_c[0]
    float axisY1 = boxAxis[1] * axisDot;     // not stored? Actually local_c[0] is only axisX, unnecessary
    // but later uses param_3[1]*fVar7 and param_3[2]*fVar7 directly.

    // Compute intersection point guess (from origin minus contributions)
    float pointX = (*rayOrigin - axisX * axisDot) - dirX1;   // fVar8
    float pointY = (rayOrigin[1] - boxAxis[1] * axisDot) - dirY1; // fVar6 (reused)
    float pointZ = (rayOrigin[2] - boxAxis[2] * axisDot) - dirZ1; // local_34

    // Store as float2 (pointX, pointY) in local_3c
    undefined8 pointXY = CONCAT44(pointY, pointX);  // local_3c

    // Compute final test positions by adding scaled axes and scaled directions
    float testX = pointX + dirXScaled + dirX1;  // local_48
    float testY = pointY + dirYScaled + dirY1;  // fStack_44
    float testZ = pointZ + dirZScaled + dirZ1;  // local_40

    // First intersection test
    float result1 = FUN_006ca5e0(&pointXY, &testX, local_c); // local_c is axisX1 (only first element used?)
    float one = 1.0f;
    ushort flags = 0;
    if (result1 == one) {
        flags = (ushort)(byte)((1 << 6) | (isnan(result1) || isnan(one) ? (1<<2) : 0) | 2 | (result1 < one));
        flags <<= 8;
        // Second test: add scaled axis to test position
        pointXY = CONCAT44(testY, testX);  // reuse local_3c as (testX, testY)
        testX = testX + scaledAxisX;
        testY = testY + scaledAxisY;
        testZ = testZ + scaledAxisZ;
        float result2 = FUN_006ca5e0(&pointXY, &testX, local_c);
        if (result2 == one) {
            flags = (ushort)(byte)((1 << 6) | (isnan(result2) || isnan(one) ? (1<<2) : 0) | 2 | (result2 < one));
            flags <<= 8;
            // Third test: move back to original origin
            float originZ = rayOrigin[2]; // local_34 = param_4[2]
            undefined8 originXY = *(undefined8 *)rayOrigin;
            pointXY = originXY;
            testX = (float)originXY + dirXScaled + dirX1;
            testY = ((float)((ulonglong)originXY >> 0x20)) + dirYScaled + dirY1;
            testZ = originZ + dirZScaled + dirZ1;
            float result3 = FUN_006ca5e0(&pointXY, &testX, local_c);
            if (result3 == one) {
                // Build final flags with bit0 set (1)
                return (ushort)((byte)((1 << 6) | … ) | 1);
            }
        }
    }
    // Return only the high byte of flags
    return flags & 0xff00;
}