// FUNC_NAME: VehiclePhysics::resolveCollisionAndSlide
void VehiclePhysics::resolveCollisionAndSlide(int mode, VehicleEntity* vehicle, float* newPosition, uint flags)
{
    float oldTargetPos[4];
    float posToContact[4];
    float oldTargetToPos[4];
    float newPosToContact[4];
    float contactPos[4];
    float slideDir[4];
    float vecNormal[4];
    float vecOther[4];
    float distSqPosToContact, distSqNewToContact, distSqOldTargetToPos;
    float projCoeff;
    float dist;
    bool bVar;

    // Save current position at +0x50 (target position)
    oldTargetPos[0] = *(float*)(vehicle + 0x50);
    oldTargetPos[1] = *(float*)(vehicle + 0x54);
    oldTargetPos[2] = *(float*)(vehicle + 0x58);
    oldTargetPos[3] = *(float*)(vehicle + 0x5c);

    // Set new target position from input
    *(float*)(vehicle + 0x50) = newPosition[0];
    *(float*)(vehicle + 0x54) = newPosition[1];
    *(float*)(vehicle + 0x58) = newPosition[2];
    // +0x5c is unchanged? Actually only first three are set

    // Load contact point (old position at +0xd0)
    contactPos[0] = *(float*)(vehicle + 0xd0);
    contactPos[1] = *(float*)(vehicle + 0xd4);
    contactPos[2] = *(float*)(vehicle + 0xd8);
    contactPos[3] = *(float*)(vehicle + 0xdc);

    // Vector from contact point to current position (+0x90)
    posToContact[0] = *(float*)(vehicle + 0x90) - contactPos[0];
    posToContact[1] = *(float*)(vehicle + 0x94) - contactPos[1];
    posToContact[2] = *(float*)(vehicle + 0x98) - contactPos[2];
    posToContact[3] = *(float*)(vehicle + 0x9c) - contactPos[3];

    // Vector from current position to old target position
    oldTargetToPos[0] = oldTargetPos[0] - *(float*)(vehicle + 0x90);
    oldTargetToPos[1] = oldTargetPos[1] - *(float*)(vehicle + 0x94);
    oldTargetToPos[2] = oldTargetPos[2] - *(float*)(vehicle + 0x98);
    oldTargetToPos[3] = oldTargetPos[3] - *(float*)(vehicle + 0x9c);

    // Vector from contact point to new target position
    newPosToContact[0] = *(float*)(vehicle + 0x50) - contactPos[0];
    newPosToContact[1] = *(float*)(vehicle + 0x54) - contactPos[1];
    newPosToContact[2] = *(float*)(vehicle + 0x58) - contactPos[2];
    newPosToContact[3] = *(float*)(vehicle + 0x5c) - contactPos[3];

    // Squared distances
    distSqOldTargetToPos = oldTargetToPos[0]*oldTargetToPos[0] + oldTargetToPos[1]*oldTargetToPos[1] + oldTargetToPos[2]*oldTargetToPos[2];
    distSqPosToContact = posToContact[0]*posToContact[0] + posToContact[1]*posToContact[1] + posToContact[2]*posToContact[2];
    distSqNewToContact = newPosToContact[0]*newPosToContact[0] + newPosToContact[1]*newPosToContact[1] + newPosToContact[2]*newPosToContact[2];

    float invDistSqNew = DAT_00e2b1a4 / distSqNewToContact; // some constant / squared distance
    projCoeff = ((distSqNewToContact + distSqPosToContact) - distSqOldTargetToPos) * invDistSqNew * DAT_00e2cd54;

    // Check collision condition based on flags bit 1
    if ((flags >> 1 & 1) == 0) {
        bVar = distSqNewToContact * DAT_00e2cd54 < distSqPosToContact + distSqOldTargetToPos;
    } else {
        bVar = distSqNewToContact * DAT_00e2cd14 < distSqPosToContact + distSqOldTargetToPos;
    }

    // If no collision or projection out of range, revert and exit
    if (!bVar || (projCoeff < 0.0f) || (DAT_00e2b1a4 < projCoeff)) {
        *(float*)(vehicle + 0x50) = oldTargetPos[0];
        *(float*)(vehicle + 0x54) = oldTargetPos[1];
        *(float*)(vehicle + 0x58) = oldTargetPos[2];
        return;
    }

    // Compute perpendicular distance to the line of motion
    distSqPosToContact = distSqPosToContact - projCoeff * projCoeff * distSqNewToContact;
    if (distSqPosToContact <= 0.0f) {
        distSqPosToContact = 0.0f;
        dist = distSqNewToContact; // not used
    } else {
        distSqPosToContact = sqrt(distSqPosToContact);
        dist = distSqPosToContact;
    }

    // Compute the closest point on the motion line (contact point)
    float newContactPos[4];
    newContactPos[0] = projCoeff * newPosToContact[0] + contactPos[0];
    newContactPos[1] = projCoeff * newPosToContact[1] + contactPos[1];
    newContactPos[2] = projCoeff * newPosToContact[2] + contactPos[2];
    newContactPos[3] = projCoeff * newPosToContact[3] + contactPos[3];

    // Save vectors for later use
    float slideNormal[4], otherNormal[4];
    for(int i=0; i<4; i++) {
        slideNormal[i] = oldTargetToPos[i];
        otherNormal[i] = posToContact[i];
    }

    // Switch on collision mode
    switch(mode) {
    case 0: {
        // Compute slide direction using dot product
        float dot = newPosToContact[0]*otherNormal[0] + newPosToContact[1]*otherNormal[1] + newPosToContact[2]*otherNormal[2];
        vectorScaleAndAdd(&otherNormal[0], &newPosToContact[0], DAT_00e44564 - invDistSqNew * dot, &slideDir[0]);
        normalizeVector(&slideDir[0], &slideDir[0]);

        // Check if vectors are parallel (bit trick to detect special case)
        float temp = dot * dot - distSqNewToContact;
        uint tempBits = *(uint*)&temp & DAT_00e44680;
        if (DAT_00e2e210 <= *(float*)&tempBits) {
            bVar = true;
        } else {
            bVar = false;
        }
        break;
    }
    case 1: {
        // Negate the slide normal (reverse direction)
        slideNormal[0] = -slideNormal[0];
        slideNormal[1] = -slideNormal[1];
        slideNormal[2] = -slideNormal[2];
        slideNormal[3] = -slideNormal[3];

        float dot = slideNormal[0]*newPosToContact[0] + slideNormal[1]*newPosToContact[1] + slideNormal[2]*newPosToContact[2];
        vectorScaleAndAdd(&slideNormal[0], &newPosToContact[0], DAT_00e44564 - invDistSqNew * dot, &slideDir[0]);
        normalizeVector(&slideDir[0], &slideDir[0]);

        // Check parallel condition
        float temp = dot * dot - distSqNewToContact;
        uint tempBits = *(uint*)&temp & DAT_00e44680;
        bVar = *(float*)&tempBits < DAT_00e2e210;
        break;
    }
    case 2: {
        copyVector(&oldTargetPos[0], &oldTargetPos[0]);
        copyVector(&slideDir[0], &slideDir[0]);
        someMatrixOp();
        bVar = dist < DAT_00e2e210;
        break;
    }
    default: {
        // Compute vector from contact to old target
        slideDir[0] = oldTargetPos[0] - contactPos[0];
        slideDir[1] = oldTargetPos[1] - contactPos[1];
        slideDir[2] = oldTargetPos[2] - contactPos[2];
        slideDir[3] = oldTargetPos[3] - contactPos[3];

        copyVector(&oldTargetPos[0], &oldTargetPos[0]);
        copyVector(&slideNormal[0], &slideNormal[0]);

        float dot = slideNormal[0]*newPosToContact[0] + slideNormal[1]*newPosToContact[1] + slideNormal[2]*newPosToContact[2];
        float scale = DAT_00e44564 - invDistSqNew * dot;
        slideDir[0] = scale * newPosToContact[0] + slideNormal[0];
        slideDir[1] = scale * newPosToContact[1] + slideNormal[1];
        slideDir[2] = scale * newPosToContact[2] + slideNormal[2];
        slideDir[3] = scale * newPosToContact[3] + slideNormal[3];
        normalizeVector(&slideDir[0], &slideDir[0]);

        float temp = dot * dot - distSqNewToContact;
        uint tempBits = *(uint*)&temp & DAT_00e44680;
        bVar = *(float*)&tempBits < DAT_00e2e210;
        break;
    }
    }

    // Update position
    uint uVar1 = *(uint*)(vehicle + 0x9c); // preserve w component?
    *(float*)(vehicle + 0x90) = distSqPosToContact * slideDir[0] + newContactPos[0];
    *(float*)(vehicle + 0x94) = distSqPosToContact * slideDir[1] + newContactPos[1];
    *(float*)(vehicle + 0x98) = distSqPosToContact * slideDir[2] + newContactPos[2];
    *(float*)(vehicle + 0x9c) = distSqPosToContact * slideDir[3] + newContactPos[3];
    *(uint*)(vehicle + 0x9c) = uVar1; // restore w

    if (!bVar) {
        // If not parallel, adjust position along normal
        *(float*)(vehicle + 0x90) = newContactPos[0];
        *(float*)(vehicle + 0x94) = newContactPos[1];
        *(float*)(vehicle + 0x98) = newContactPos[2] + distSqPosToContact;
    }

    // Recompute vectors for orientation update
    float currentPos[4];
    currentPos[0] = *(float*)(vehicle + 0x50);
    currentPos[1] = *(float*)(vehicle + 0x54);
    currentPos[2] = *(float*)(vehicle + 0x58);
    currentPos[3] = *(float*)(vehicle + 0x5c);

    float newPos[4];
    newPos[0] = *(float*)(vehicle + 0x90);
    newPos[1] = *(float*)(vehicle + 0x94);
    newPos[2] = *(float*)(vehicle + 0x98);
    newPos[3] = *(float*)(vehicle + 0x9c);

    // Normalize vectors
    normalizeVector(&otherNormal[0], &otherNormal[0]);
    normalizeVector(&slideNormal[0], &slideNormal[0]);

    // Compute direction of motion and normal to surface
    float motionDir[4];
    motionDir[0] = newPos[0] - contactPos[0];
    motionDir[1] = newPos[1] - contactPos[1];
    motionDir[2] = newPos[2] - contactPos[2];
    normalizeVector(&motionDir[0], &motionDir[0]);

    float slideVec[4];
    slideVec[0] = currentPos[0] - newPos[0];
    slideVec[1] = currentPos[1] - newPos[1];
    slideVec[2] = currentPos[2] - newPos[2];
    normalizeVector(&slideVec[0], &slideVec[0]);

    // Compute normal vectors from cross product (using helper functions)
    crossProduct(&otherNormal[0], &motionDir[0], &newPosToContact[0]); // actually output to third arg
    crossProduct(&slideNormal[0], &slideVec[0], &oldTargetToPos[0]);

    // Normalize and update orientation if velocity is significant
    float velMag = newPosToContact[0]*newPosToContact[0] + newPosToContact[1]*newPosToContact[1] + newPosToContact[2]*newPosToContact[2];
    if (DAT_00e2b05c < velMag) {
        velMag = sqrt(velMag);
        double dVar = (double)velMag;
        getReciprocalSqrt(); // probably
        velMag = (float)dVar / velMag;
        newPosToContact[0] *= velMag;
        newPosToContact[1] *= velMag;
        newPosToContact[2] *= velMag;
        normalizeQuaternion(&contactPos[0]); // maybe
        buildRotationMatrix(&newPosToContact[0], vehicle + 0x140, &slideNormal[0]);
        setRotationPart(&slideNormal[0], vehicle + 0xa0);
    }

    // Similarly for slide normal direction
    float slideMag = oldTargetToPos[0]*oldTargetToPos[0] + oldTargetToPos[1]*oldTargetToPos[1] + oldTargetToPos[2]*oldTargetToPos[2];
    if (DAT_00e2b05c < slideMag) {
        slideMag = sqrt(slideMag);
        double dVar = (double)slideMag;
        getReciprocalSqrt();
        slideMag = (float)dVar / slideMag;
        oldTargetToPos[0] *= slideMag;
        oldTargetToPos[1] *= slideMag;
        oldTargetToPos[2] *= slideMag;
        // Keep w unchanged
        normalizeQuaternion(&contactPos[0]);
        buildRotationMatrix(&slideNormal[0], vehicle + 0x130, &contactPos[0]);
        setRotationPart(&contactPos[0], vehicle + 0x60);

        if ((flags & 1) != 0) {
            buildRotationMatrix(&slideNormal[0], vehicle + 0x120, &contactPos[0]);
            setRotationPart(&contactPos[0], vehicle + 0x20);
        }
    }

    // Finalize transforms
    finalizeTransform(vehicle + 0xa0);
    finalizeTransform(vehicle + 0x60);
    finalizeTransform(vehicle + 0x20);
}