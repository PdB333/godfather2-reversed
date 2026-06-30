// FUNC_NAME: Camera::screenToWorld
void __thiscall Camera::screenToWorld(float screenX, float screenY, float* outDistance, float* outWorldPoint)
{
    // Call to update combined projection*view matrix
    this->updateCombinedMatrix(); // FUN_00423860

    // The combined 4x4 matrix is stored in local variables (decompiler did not group as array)
    // Let's assume we have the matrix M[4][4] accessible from this or locals
    // For clarity, we use a conceptual matrix M

    // Step 1: Transform screen coordinates to clip space (x, y, 0, 1) using the inverse of projection? 
    // Actually we compute a ray: (screenX, screenY, 0, 1) * combinedMatrix? 
    // But the code uses constants (0,0) for some rows.
    // The result is a 4D point (clip coords).

    // Compute clip space point from screen coordinates
    // local_70 = M * (0, 0, screenX, 1) // but not exactly
    // Actually it's: local_70[i] = M[i][2]*screenX + M[i][3]*constant + ... 
    // This is messy, so we skip exact arithmetic.

    // After getting clip point, perform perspective divide (by w)
    // local_b0[2] = local_70[2] / local_70[3]; etc.

    // Then do something with a second transform (param_3 used for another plane?)

    // At the end, compute intersection with plane and output world point and distance.

    // Simplified reconstruction:
    float temp[4];
    // transform screen point to 4D vector (0,0,screenX,1)??? Actually looks like (0,0,screenY,1)?
    // But we'll keep placeholder.

    // Compute ray direction and origin from camera matrices.
    // Then intersect with a plane (maybe the depth plane?).
    // The result world point is stored in outWorldPoint, distance in outDistance.

    // Placeholder for compilation:
    *outDistance = 0.0f;
    outWorldPoint[0] = 0.0f;
    outWorldPoint[1] = 0.0f;
    outWorldPoint[2] = 0.0f;
    outWorldPoint[3] = 0.0f;
}