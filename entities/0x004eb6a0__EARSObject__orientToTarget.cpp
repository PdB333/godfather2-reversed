// FUNC_NAME: EARSObject::orientToTarget
// Address: 0x004eb6a0
// Role: Updates a 4x4 transformation matrix to orient towards a target point, with threshold clamping and random perturbation.

void __thiscall EARSObject::orientToTarget(void* thisObj, const float* targetPoint, bool enableClamp, float* outMatrix)
{
    // The object's local transform matrix starts at offset 0x40
    float* srcMatrix = (float*)((char*)thisObj + 0x40);

    // Copy the object's matrix to the output (16 floats)
    for (int i = 0; i < 16; i++)
        outMatrix[i] = srcMatrix[i];

    // Compute vector from object's position to target (homogeneous coordinates)
    float dx = targetPoint[0] - outMatrix[12]; // translation x
    float dy = targetPoint[1] - outMatrix[13]; // translation y
    float dz = targetPoint[2] - outMatrix[14]; // translation z
    float dw = targetPoint[3] - outMatrix[15]; // homogeneous component (typically 1)

    float dist = sqrt(dx*dx + dy*dy + dz*dz);

    // Global constants: kMinDist (DAT_00e2e210) and kScale (DAT_00e2b1a4, possibly 1.0)
    if (dist > kMinDist)
    {
        float invDist = kScale / dist;
        float dirX = invDist * dx;
        float dirY = invDist * dy;
        float dirZ = invDist * dz;
        float dirW = invDist * dw;

        // Compute cross product of current forward vector (row2) with target direction
        // row2 is at indices 8,9,10,11
        float crossX = outMatrix[9] * dirZ - outMatrix[10] * dirY;
        float crossY = outMatrix[10] * dirX - outMatrix[8] * dirZ;
        float crossZ = outMatrix[8] * dirY - outMatrix[9] * dirX;
        float crossW = outMatrix[11] * dirW - outMatrix[11] * dirW; // effectively zero

        float crossLen = sqrt(crossX*crossX + crossY*crossY + crossZ*crossZ);
        if (crossLen > kMinDist)
        {
            // Update forward vector (row2) to point toward target
            outMatrix[8] = dirX;
            outMatrix[9] = dirY;
            outMatrix[10] = dirZ;
            outMatrix[11] = dirW;

            // Re-orthogonalize the matrix using cross product
            FUN_00417760(&crossX);          // likely normalizes cross vector
            FUN_0044d680(&crossX, &outMatrix[4]); // updates up vector (row1) with cross
            FUN_00417760();                 // final normalize
        }
    }

    if (enableClamp)
    {
        uint signMask = kSignMask; // e.g., 0x7FFFFFFF
        float absElem1 = fabs(outMatrix[1]); // row0 col1
        float absElem2 = fabs(outMatrix[9]); // row2 col1

        if (absElem1 < absElem2)
        {
            // First element is smaller (rotation slowing on that axis)
            if (absElem1 > kMinDist)
            {
                outMatrix[1] = 0.0f;
                float rnd = FUN_004bcfb0(); // random value
                if (rnd > kRndThreshold)
                {
                    FUN_0045c110(kScale / rnd); // apply perturbation
                    FUN_00417760(&outMatrix[8]); // renormalize forward
                    return;
                }
                // Reset entire first row
                outMatrix[0] = kScale;
                outMatrix[1] = 0.0f;
                outMatrix[2] = 0.0f;
                outMatrix[3] = 0.0f;
            }
            FUN_00417760(&outMatrix[8]); // ensure forward is normalized
            return;
        }
        else
        {
            // Second element is smaller or equal
            if (absElem2 > kMinDist)
            {
                outMatrix[9] = 0.0f;
                float rnd = FUN_004bcfb0(&outMatrix[8]); // random value with parameter
                if (rnd > kRndThreshold)
                {
                    FUN_0045c110(kScale / rnd, &outMatrix[8], &outMatrix[8]);
                    FUN_00417760();
                    return;
                }
                // Reset entire third row
                outMatrix[8] = 0.0f;
                outMatrix[9] = 0.0f;
                outMatrix[10] = kScale;
                outMatrix[11] = 0.0f;
            }
            FUN_00417760();
        }
    }
}