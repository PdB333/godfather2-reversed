// FUNC_NAME: Projectile::updateTrajectory
void Projectile::updateTrajectory(void* target, float deltaTime, float someFactor)
{
    // +0x18: pointer to physics body (e.g., RigidBody)
    int bodyPtr = *(int*)(this + 0x18);
    // Body direction vector at +0x100, +0x104, +0x108
    float bodyDirX = *(float*)(bodyPtr + 0x100);
    float bodyDirY = *(float*)(bodyPtr + 0x104);
    float bodyDirZ = *(float*)(bodyPtr + 0x108);
    // Body speed at +0x10c
    float bodySpeed = *(float*)(bodyPtr + 0x10c);

    // in_EAX is a float pointer passed in EAX (likely target direction)
    float targetDirX = in_EAX[0];
    float targetDirY = in_EAX[1];
    float targetDirZ = in_EAX[2];
    float targetDirW = in_EAX[3]; // might be unused or a scalar

    // Dot product between body direction and target direction
    float dot = targetDirX * bodyDirX + targetDirY * bodyDirY + targetDirZ * bodyDirZ;
    float cosAngle = (float)FUN_0040f220(dot); // acos

    // DAT_00e446dc is likely a threshold (e.g., 0.999f)
    if ((float)DAT_00e446dc <= cosAngle) {
        // Already aligned, keep original direction
        // local_a4 = bodySpeed, local_b0 = bodyDirX, etc.
        float newDirX = bodyDirX;
        float newDirY = bodyDirY;
        float newDirZ = bodyDirZ;
        float newSpeed = bodySpeed;
    } else {
        // Interpolate towards target direction
        float lerpFactor = DAT_00e44564 - dot; // DAT_00e44564 is likely 1.0f
        float interpDirX = targetDirX * lerpFactor + bodyDirX;
        float interpDirY = targetDirY * lerpFactor + bodyDirY;
        float interpDirZ = targetDirZ * lerpFactor + bodyDirZ;
        float interpSpeed = targetDirW * lerpFactor + bodySpeed;

        // Normalize the interpolated direction
        float lenSq = interpDirX * interpDirX + interpDirY * interpDirY + interpDirZ * interpDirZ;
        float invLen;
        if (lenSq == 0.0f) {
            invLen = 0.0f;
        } else {
            float len = (float)FUN_00414a80(lenSq); // sqrt
            invLen = 1.0f / len;
        }
        newDirX = interpDirX * invLen;
        newDirY = interpDirY * invLen;
        newDirZ = interpDirZ * invLen;
        newSpeed = interpSpeed * invLen;
    }

    // Scale direction by deltaTime
    newDirX *= deltaTime;
    newDirY *= deltaTime;
    newDirZ *= deltaTime;
    newSpeed *= deltaTime;

    // Check flag at +0x110 >> 1 & 1 (bit 1 of flags)
    uint flags = *(uint*)(this + 0x110);
    if ((flags >> 1 & 1) == 0) {
        // Disable vertical movement
        newDirY = 0.0f;
    }

    // Count active entries in array at +0x48 (stride 0x30, check offset 0x24 for non-zero)
    int count = *(int*)(this + 0x4c);
    int activeCount = 0;
    if (count > 0) {
        int* arrayBase = (int*)(*(int*)(this + 0x48) + 0x24);
        for (int i = 0; i < count; i++) {
            if (arrayBase[i * 0x30] != 0) {
                activeCount++;
            }
        }
    }

    // If vertical movement allowed and no active entries, destroy target and return
    if ((flags >> 1 & 1) != 0 && activeCount < 1) {
        FUN_0053f390(target); // likely destroy/remove target
        int uVar1 = *(int*)(target + 8);
        int bodyPtr2 = *(int*)(this + 0x18);
        FUN_009f2000();
        (**(code**)(*(int*)(bodyPtr2 + 0xd0) + 0x58))(uVar1, &local_70);
        return;
    }

    // Compute new position based on someFactor
    float cosFactor = (float)FUN_0040f220(someFactor); // acos
    // DAT_00e44598 is a small threshold, DAT_00e446dc is the same as before
    if (cosFactor <= (float)DAT_00e44598 || (float)DAT_00e446dc <= cosAngle) {
        // Use default direction from body at +0x150
        newDirX = *(float*)(bodyPtr + 0x150);
        newDirY = *(float*)(bodyPtr + 0x154);
        newDirZ = *(float*)(bodyPtr + 0x158);
        newSpeed = *(float*)(bodyPtr + 0x15c);
    } else {
        // Complex rotation calculation
        float local_c0 = 0.0f, local_b8 = 0.0f, local_b4 = 0.0f;
        float local_bc = (float)DAT_00e2b1a4; // some constant
        double dVar10 = (double)someFactor;
        FUN_00b99fcb(); // unknown
        FUN_00aa36a0(&local_c0, (deltaTime / (*(float*)(this + 0x108) / (float)dVar10)) * *(float*)(target + 8));
        FUN_005439c0(bodyPtr + 0x150, local_30); // get orientation matrix

        // Cross product and rotation math (simplified)
        float fVar9 = newSpeed * newSpeed - DAT_00e2cd54;
        float fVar8 = fVar9 * 0.0f;
        float fVar11 = newDirZ + newDirY * 0.0f + newDirX * 0.0f;
        float local_20 = newDirY - newDirZ * 0.0f;
        fVar9 = ((newDirX * 0.0f - newDirY * 0.0f) * newSpeed + newDirZ * fVar11 + fVar9) * DAT_00e2b04c;
        float fVar12 = (newSpeed * local_20 + fVar11 * newDirX + fVar8) * DAT_00e2b04c;
        fVar8 = ((newDirZ * 0.0f - newDirX) * newSpeed + newDirY * fVar11 + fVar8) * DAT_00e2b04c;

        local_c0 = fVar9 * targetDirY - fVar8 * targetDirZ;
        local_bc = fVar12 * targetDirZ - fVar9 * targetDirX;
        local_b8 = fVar8 * targetDirX - fVar12 * targetDirY;

        float lenSq2 = local_c0 * local_c0 + local_b8 * local_b8 + local_bc * local_bc;
        float invLen2;
        if (lenSq2 == 0.0f) {
            invLen2 = 0.0f;
        } else {
            float len2 = (float)FUN_00414a80(lenSq2);
            invLen2 = 1.0f / len2;
        }
        float local_5c = local_bc * invLen2;
        local_b8 *= invLen2;
        float local_60 = invLen2 * local_c0;
        float local_b4 = invLen2 * 0.0f;

        // Build rotation matrix
        float local_40 = local_5c * targetDirZ - local_b8 * targetDirY;
        float local_50 = targetDirX;
        float local_3c = local_b8 * targetDirX - local_60 * targetDirZ;
        float local_4c = targetDirY;
        float local_48 = targetDirZ;
        float local_44 = targetDirW;
        float local_38 = local_60 * targetDirY - local_5c * local_50;
        int local_34 = 0;
        float local_58 = local_b8;
        float local_54 = local_b4;
        FUN_00aa3930(&local_60); // orthonormalize
    }

    // Compute final position
    float speedScale = *(float*)(target + 8);
    float finalX = newDirX * speedScale + *(float*)(bodyPtr + 0x110);
    float finalY = newDirY * speedScale + *(float*)(bodyPtr + 0x114);
    float finalZ = newDirZ * speedScale + *(float*)(bodyPtr + 0x118);
    float finalW = newSpeed * speedScale + *(float*)(bodyPtr + 0x11c);

    // Apply movement
    FUN_005605b0(this);
}