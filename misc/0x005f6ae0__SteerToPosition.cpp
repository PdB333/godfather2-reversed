// FUNC_NAME: SteerToPosition
float* SteerToPosition(float* outputPos, float* currentPos, float* targetPos, int agentData, int obstacleData, int depth, char useAlternateTurnRate, char allowSnapToTarget)
{
    float targetRadius = *(float*)(agentData + 0x18); // target radius
    if (*(int*)(obstacleData + 0xc) != 0) {
        targetRadius = *(float*)(*(int*)(obstacleData + 0xc) + 0x18) + targetRadius;
    }

    float currentX = currentPos[0];
    float currentY = currentPos[1];
    float targetX = targetPos[0];
    float targetY = targetPos[1];
    float agentPosX = *(float*)(agentData + 0x10);
    float agentPosY = *(float*)(agentData + 0x14);

    float dx = currentY - agentPosY;
    float dyTarget = targetY - agentPosY;
    float dy = currentX - agentPosX;

    float turnRate = 0.0f;
    if (useAlternateTurnRate != '\0') {
        turnRate = DAT_00e2eff4;
    } else {
        turnRate = DAT_00e2b1a4;
    }

    float distanceSq = dx*dx + dy*dy;
    *outputPos = 0.0f;
    outputPos[1] = 0.0f;
    bool snappedToTarget = false;

    float distanceToTarget = sqrtf((dyTarget*dyTarget) + ((targetX - agentPosX)*(targetX - agentPosX)));
    if ((distanceToTarget < targetRadius) && (allowSnapToTarget != '\0')) {
        float targetToCurrentDX = currentX - targetX;
        float targetToCurrentDY = currentY - targetY;
        snappedToTarget = ((agentPosY - targetY) * targetToCurrentDY + (agentPosX - targetX) * targetToCurrentDX) <= 0.0f;
        if (snappedToTarget) {
            *outputPos = targetX;
            outputPos[1] = targetY;
        }
    }

    float distanceToAgent = sqrtf(distanceSq);
    if (distanceToAgent < targetRadius) {
        // push current position away from agent point
        float invDist = turnRate / distanceToAgent;
        float offsetX = invDist * dx * targetRadius * _DAT_00e407a0;
        float offsetY = invDist * dy * targetRadius * _DAT_00e407a0;
        currentPos[0] = agentPosX + offsetY; // note: swapped x/y? Possibly orientation
        currentPos[1] = agentPosY + offsetX;
    }

    if (targetRadius * _DAT_00e407a0 <= distanceToAgent) {
        if (!snappedToTarget) {
            float angle = turnRate / distanceToAgent;
            double dAngle = (double)(angle * targetRadius);
            float sinAngle = sinf(dAngle); // FUN_00b9b988
            float cosAngle = cosf(dAngle); // FUN_00b9c766
            // Normalize angle using bitmask (likely a fixed-point trick)
            float normAngle = (float)((uint)dy & DAT_00e44680) * angle;
            if ((dy <= 0.0f) || (0.0f <= dx)) {
                if (dy < 0.0f) {
                    if (0.0f <= dx) {
                        if (0.0f < dx) {
                            normAngle = (DAT_00e44808 - normAngle) + _DAT_00e44804;
                        }
                    } else {
                        normAngle = normAngle + _DAT_00e44644;
                    }
                }
            } else {
                normAngle = (DAT_00e44808 - normAngle) + DAT_00e44808;
            }
            float finalAngle = (float)dAngle * turnRate + normAngle;
            double dFinalAngle = (double)finalAngle;
            float cosResult = cosf(dFinalAngle); // FUN_00b99fcb
            *outputPos = (float)(dFinalAngle) * targetRadius * DAT_00e2b294 + *(float*)(agentData + 0x10); // note: cosResult not used? Possibly function side-effects
            float sinResult = sinf(dFinalAngle); // FUN_00b99e20
            outputPos[1] = (float)(dFinalAngle) * targetRadius * DAT_00e2b294 + *(float*)(agentData + 0x14);
        }
    } else {
        // else: just move in direction of agent
        float newY = currentPos[1];
        *outputPos = turnRate * dx + currentPos[0];
        outputPos[1] = newY - turnRate * dy;
    }

    if ((depth < 5) && (FUN_005f6ee0(currentPos, outputPos, agentData, obstacleData, *(undefined4*)(agentData + 0xc)) != 0)) {
        float* newOutput = SteerToPosition(local_30, currentPos, outputPos, agentData, obstacleData, depth + 1, useAlternateTurnRate, 0);
        outputPos[0] = newOutput[0];
        outputPos[1] = newOutput[1];
    }

    return outputPos;
}