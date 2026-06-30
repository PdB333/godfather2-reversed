// FUNC_NAME: buildOrientationMatrixFromDirectionAndAngle
void buildOrientationMatrixFromDirectionAndAngle(int* objectPtr, float angle)
{
    float* direction = (float*)in_EAX; // input direction vector (x,y,z)
    float* matrix = (float*)unaff_ESI; // output 3x4 matrix (12 floats)

    float epsilon = DAT_00e2cbe0; // small threshold
    float upComponent = DAT_00e2b1a4; // likely 1.0 or up vector component
    float* thresholdPtr = PTR_FUN_00e4462c; // pointer to a float threshold

    float x = direction[0];
    float y = direction[1];
    float z = direction[2];

    float lengthSq = x*x + y*y + z*z;
    float length;
    float invLength;

    if (lengthSq <= epsilon) {
        invLength = 0.0f;
        length = 0.0f;
    } else {
        length = sqrtf(lengthSq);
        invLength = upComponent / length; // upComponent is likely 1.0
    }

    // Normalized direction (stored in matrix rows 1-3? Actually matrix[4..7] is second row)
    matrix[4] = x * invLength;
    matrix[5] = y * invLength;
    matrix[6] = z * invLength;
    matrix[7] = 0.0f;

    // If length is very small, snap direction to a specific axis based on object flag
    if (length < *thresholdPtr) {
        int objectBase = objectPtr[0];
        char flag = *(char*)(objectBase + 0x157); // +0x157: some flag
        matrix[6] = 0.0f;
        matrix[5] = 0.0f;
        matrix[4] = 0.0f;
        matrix[flag + 4] = upComponent; // set one component to upComponent
    }

    float yComponent = matrix[5];
    float zComponent = matrix[6];
    float xComponent = matrix[4];

    float crossX, crossY, crossZ; // cross product components
    float refX, refY, refZ; // reference vector (maybe up)

    if ((_DAT_00e44888 < yComponent) || (yComponent < DAT_00e44884)) {
        // Direction is not aligned with up vector
        refX = 0.0f;
        refY = 0.0f;
        refZ = DAT_00e44564; // likely 0.0 or 1.0
        float diffZ = refZ - zComponent;
        float crossLenSq = yComponent*yComponent + diffZ*diffZ;
        float crossInvLen;
        if (crossLenSq <= epsilon) {
            crossInvLen = 0.0f;
        } else {
            crossInvLen = upComponent / sqrtf(crossLenSq);
        }
        // Cross product: (0, y, z) x (0,0,refZ) = (y*refZ, 0, -y*0?) Actually compute properly
        // The code computes: local_30 = crossInvLen * 0.0; fStack_28 = crossInvLen * yComponent; fStack_2c = crossInvLen * diffZ;
        // Then cross: local_50 = yComponent * fStack_28 - zComponent * fStack_2c;
        // fStack_4c = zComponent * local_30 - xComponent * fStack_28;
        // fStack_48 = xComponent * fStack_2c - yComponent * local_30;
        // This is cross product of (x,y,z) with (0, yComponent, diffZ)?? Actually it's confusing.
        // Let's just use the computed values.
        float tempX = crossInvLen * 0.0f;
        float tempY = crossInvLen * yComponent;
        float tempZ = crossInvLen * diffZ;
        crossX = yComponent * tempY - zComponent * tempZ;
        crossY = zComponent * tempX - xComponent * tempY;
        crossZ = xComponent * tempZ - yComponent * tempX;
    } else {
        // Direction is aligned with up vector
        refX = 0.0f;
        refY = 0.0f;
        refZ = DAT_00e44564;
        float diffZ = refZ - zComponent;
        float crossLenSq = xComponent*xComponent + diffZ*diffZ;
        float crossInvLen;
        if (crossLenSq <= epsilon) {
            crossInvLen = 0.0f;
        } else {
            crossInvLen = upComponent / sqrtf(crossLenSq);
        }
        float tempX = crossInvLen * diffZ;
        float tempY = crossInvLen * xComponent;
        float tempZ = crossInvLen * 0.0f;
        crossX = tempY * yComponent - tempZ * zComponent;
        crossY = tempX * zComponent - tempY * xComponent;
        crossZ = tempZ * xComponent - tempX * yComponent;
    }

    // Compute sin and cos of the angle
    float sinAngle = (float)sin((double)angle);
    float cosAngle = (float)cos((double)angle);

    // Build rotation matrix from axis-angle (cross product axis)
    // First row (matrix[0..3]) = cosAngle * cross + sinAngle * (something)?? Actually the code:
    // matrix[8] = sinAngle * crossX + cosAngle * tempX; etc.
    // matrix[0] = (1 - cosAngle?) * tempX + sinAngle * crossX? Wait, it's different.
    // The code: unaff_ESI[8] = fVar5 * local_50 + fVar6 * local_30; where fVar5=sinAngle, fVar6=cosAngle, local_50=crossX, local_30=tempX
    // So matrix[8] = sinAngle * crossX + cosAngle * tempX
    // matrix[9] = sinAngle * crossY + cosAngle * tempY
    // matrix[10] = sinAngle * crossZ + cosAngle * tempZ
    // matrix[11] = 0
    // Then matrix[0] = (1 - cosAngle?) * tempX + sinAngle * crossX? Actually: fVar5 = DAT_00e44564 - fVar5; (so fVar5 = 0 - sinAngle? if DAT_00e44564=0)
    // Then *unaff_ESI = fVar5 * local_30 + fVar6 * local_50; = (-sinAngle)*tempX + cosAngle*crossX
    // So matrix[0] = cosAngle * crossX - sinAngle * tempX
    // matrix[1] = cosAngle * crossY - sinAngle * tempY
    // matrix[2] = cosAngle * crossZ - sinAngle * tempZ
    // matrix[3] = 0
    // This is a rotation matrix around axis (tempX,tempY,tempZ) by angle? Actually it's a Rodrigues' rotation formula.
    // But we'll just assign.

    float sinA = sinAngle;
    float cosA = cosAngle;

    matrix[8] = sinA * crossX + cosA * tempX;
    matrix[9] = sinA * crossY + cosA * tempY;
    matrix[10] = sinA * crossZ + cosA * tempZ;
    matrix[11] = 0.0f;

    float negSinA = DAT_00e44564 - sinA; // likely -sinA
    matrix[0] = negSinA * tempX + cosA * crossX;
    matrix[1] = negSinA * tempY + cosA * crossY;
    matrix[2] = negSinA * tempZ + cosA * crossZ;
    matrix[3] = 0.0f;
}