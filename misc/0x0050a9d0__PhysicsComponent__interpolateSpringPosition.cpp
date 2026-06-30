// FUNC_NAME: PhysicsComponent::interpolateSpringPosition

void PhysicsComponent::interpolateSpringPosition(
    int* dataArray,   // param_2 - pointer to array of per-index data structures
    float* outPosVel, // param_3 - output position (and maybe velocity) 
    int index,        // in_EAX - index into data array
    float deltaTime,   // in_XMM5_Da - time step or spring acceleration factor
    float* outPos2,   // unaff_EDI - secondary output (position + velocity adjusted)
    int tlsOffset)    // unaff_FS_OFFSET - thread local storage offset (0x2c) used for global pointer
{
    float* globCoeff1 = (float*)0x00e2da94;   // polynomial coefficients
    float* globCoeff2 = (float*)0x00e2da84;
    float* globCoeff3 = (float*)0x00e2daa4;
    float* globCoeff4 = (float*)0x00e2dab4;
    float* globCoeff5 = (float*)0x00e2da90;
    float* globCoeff6 = (float*)0x00e2da80;
    float* globCoeff7 = (float*)0x00e2daa0;
    float* globCoeff8 = (float*)0x00e2dab0;
    float* globClamp = (float*)0x00e4492c;     // max force clamp
    float* globConst = (float*)0x00e2b1a4;     // constant floating value

    // Access global pointer via TLS (typical EARS engine pattern)
    int** globalDataPtr = *(int***)((int*)tlsOffset + 0x2c);
    int* globalData = *globalDataPtr;
    int* someArray = *(int**)(globalData + 8); // +8: offset to some data array

    // Compute base value from dataArray
    float baseVal = *(float*)(*dataArray + index * 4 + (int)someArray);

    // Get spring parameters from this object's data
    float* springParams = *(float**)(this + 0x28);
    float speedLimit = springParams[0x19]; // +0x64 (0x19 * 4)
    float damping = springParams[0x18];    // +0x60

    // Compute clamped deltaTime
    if (deltaTime >= 0.0f) {
        if (baseVal >= speedLimit) {
            deltaTime = baseVal - speedLimit;
        }
    } else {
        deltaTime = baseVal - speedLimit;
        if (deltaTime >= 0.0f) {
            deltaTime = 0.0f;
        }
    }

    // Apply damping
    float springForce = damping * deltaTime;
    float maxForce = *globClamp;
    if (springForce > maxForce) {
        springForce = maxForce;
    }

    // Polynomial interpolation coefficients (likely for ease-in-out)
    float forceSq = springForce * springForce;
    float coeffA = forceSq * *globCoeff1;
    float coeffB = forceSq * springForce * *globCoeff2;
    float coeffC = springForce * *globCoeff3;
    float coeffD = *globConst * *globCoeff4;
    float interpFactor = forceSq * *globCoeff5 + forceSq * springForce * *globCoeff6 + springForce * *globCoeff7 + *globConst * *globCoeff8;

    // Get current position from springParams
    float curX = springParams[1];  // +0x04
    float curY = springParams[2];  // +0x08
    float curZ = springParams[3];  // +0x0c

    // Compute displacement from target (dataArray entry)
    float* targetPos = (float*)(*dataArray + index * 0x50 + 0x20 + (int)someArray);
    float dispX = targetPos[4] - springParams[0]; // +0x10 offset? Actually targetPos[4] is at index 4
    float dispY = targetPos[5] - curX;
    float dispZ = targetPos[6] - curY;
    float dispW = targetPos[7] - curZ; // w component

    // Interpolate output position (outPosVel)
    outPosVel[0] = interpFactor * dispX + springParams[0];
    outPosVel[1] = interpFactor * dispY + curX;
    outPosVel[2] = interpFactor * dispZ + curY;
    outPosVel[3] = interpFactor * dispW + curZ;

    // Compute velocity component
    float velocityScale = *(float*)(*(int*)(this + 0x28) + 0x6c) * (coeffA + coeffB + coeffC + coeffD) * springForce;
    float velX = velocityScale * dispX + targetPos[0];
    float velY = velocityScale * dispY + targetPos[1];
    float velZ = velocityScale * dispZ + targetPos[2];
    float velW = velocityScale * dispW + targetPos[3];

    // Output to secondary array (outPos2)
    outPos2[0] = velX;
    outPos2[1] = velY;
    outPos2[2] = velZ;
    outPos2[3] = velW;

    // Re-read springParams for the final blended output
    springParams = *(float**)(this + 0x28);
    float blendX = springParams[1];
    float blendY = springParams[2];
    float blendZ = springParams[3];
    outPos2[0] = springParams[0] * deltaTime + velX;
    outPos2[1] = blendX * deltaTime + velY;
    outPos2[2] = blendY * deltaTime + velZ;
    outPos2[3] = blendZ * deltaTime + velW;

    // Set constant glob value in outputs
    outPosVel[3] = *globConst;
    outPos2[3] = *globConst;

    // If flag is set, apply additional correction via helper function
    if (*(int*)(this + 0xa8) != 0) {
        float temp[4];
        FUN_004f3aa0(outPosVel, outPos2, temp); // likely a rotation or constraint function

        float adjustX = deltaTime * temp[0] + outPosVel[0];
        float adjustY = deltaTime * temp[1] + outPosVel[1];
        float adjustZ = deltaTime * temp[2] + outPosVel[2];
        float adjustW = deltaTime * temp[3] + outPosVel[3];

        outPosVel[0] = adjustX;
        outPosVel[1] = adjustY;
        outPosVel[2] = adjustZ;
        outPosVel[3] = adjustW;

        outPos2[0] = adjustX * deltaTime + outPos2[0];
        outPos2[1] = adjustY * deltaTime + outPos2[1];
        outPos2[2] = adjustZ * deltaTime + outPos2[2];
        outPos2[3] = adjustW * deltaTime + outPos2[3];
    }
}