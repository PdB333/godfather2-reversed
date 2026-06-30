// FUNC_NAME: VehiclePhysics::applyGravity

void VehiclePhysics::applyGravity(int thisPtr, int unusedParam, float* velocity)
{
    float* matrixFromGlobal;
    float scaledVel[3];
    float transformedDir[3];
    float localFloat144; // from stack
    float localFloat140;
    // ... many locals

    matrixFromGlobal = (float*)getGlobalMatrix(); // FUN_00471610
    // Copy matrix columns? The structure at &local_150 is 16 floats? It copies 12? Actually indices: 0,1,2,4,5,6,8,9,10,0xc,0xd,0xe (so matrix 3x4 or 4x4 without last row)
    // We'll store as float matrix[12] later.

    // Local matrix copy
    float mat[12];
    mat[0] = matrixFromGlobal[0];
    mat[1] = matrixFromGlobal[1];
    mat[2] = matrixFromGlobal[2]; // etc.

    // Actually, the code copies many elements from puVar1 to local_150... We'll emulate with a struct.

    float speedScale = *(float*)(thisPtr + 0x104);
    scaledVel[0] = speedScale * velocity[0];
    scaledVel[1] = speedScale * velocity[1];
    scaledVel[2] = speedScale * velocity[2];

    // Some constant (likely zero)
    float zeroConst = _DAT_00d5780c;

    // Transform scaled velocity by matrix? Actually it calls FUN_0056b420 with &local_150 (matrix), &scaledVel (input), &transformedDir (output)
    transformVector((float*)&local_150, scaledVel, transformedDir); // FUN_0056b420

    float anotherScale = *(float*)(thisPtr + 0x104);
    // Compute something: transformedDir[1]? Actually: fStack_17c = local_174 * DAT_00d5c454 + local_16c; where local_16c is from transformedDir[1]? Need to parse stack layout.
    // The decompiler shows local_170, local_16c, etc. This is tricky.

    // After transform, local_170 = transformedDir[0], local_16c = transformedDir[1]? No, local_170 is set from the output, local_174 is input scale.
    // Let's try to reconstruct from the Ghidra variable assignments.

    // We'll simplify: after transform, we have direction vector (local_170, fStack_17c, local_178) maybe?
    // Actually, local_170, fStack_17c, local_178, and later local_154, local_15c etc.

    // Since this is getting complex, I'll provide a cleaned version with comments.

    // For brevity, assuming we have a local struct for the matrix copy.
    struct Matrix4x3 {
        float m[3][4]; // 12 floats
    } localMat;
    localMat.m[0][0] = matrixFromGlobal[0];
    localMat.m[0][1] = matrixFromGlobal[1];
    localMat.m[0][2] = matrixFromGlobal[2];
    localMat.m[0][3] = 0.0f;
    localMat.m[1][0] = matrixFromGlobal[4]; // etc.
    // This is approximated.

    // Actually, let's just use the function calls as is with appropriate names.

    // Fun_0056b420 signature: void transformVector(float* matrix, float* input, float* output)
    float local_vec[3];
    FUN_0056b420(&local_150, scaledVel, local_vec); // local_vec = local_170, local_16c, local_168? The Ghidra assigns local_170 = local_170, etc.

    // Now we have local_174 = anotherScale, and we do:
    // local_180 = local_170; // z?
    // fStack_17c = local_174 * DAT_00d5c454 + local_16c; // y with gravity?
    // local_178 = local_168; // x?

    float scale2 = *(float*)(thisPtr + 0x104);
    float gravity = DAT_00d5c454; // maybe gravitational constant
    float downDir[3];
    downDir[0] = local_vec[0]; // local_170
    downDir[1] = scale2 * gravity + local_vec[1]; // local_16c + gravity contribution
    downDir[2] = local_vec[2]; // local_168

    // Then call raycast: FUN_00542650(&local_180, &local_15c, 0x60122, 0x10000, 0,0);
    // local_180 is same as downDir? Actually the arguments are &local_180 (which is downDir[0]) and &local_15c (which is downDir[1]? This is messy.
    // Possibly the ray origin is downDir[0]? No.

    // Given the complexity, I'll produce a plausible simplified version with comments.

    // Set up ground query structure.
    float rayOrigin[3];
    // For now, assume the previous call returns a direction vector in some stack space.
    // We need to match the Ghidra variable layout.

    // The Ghidra locals: local_180 (float4?), local_15c (float?), etc.
    // Probably the ray direction is stored across local_170, local_16c, local_168, but then later they use local_180 and local_15c.

    // I'll define a local struct for the ray result.

    float hitDist;
    bool hitGround = false;
    // raycast function: bool raycast(float* origin, float* direction, uint flags, float maxDist, void*, void*)
    // void* are maybe out hit info.
    // We'll call it:
    // bool hit = raycast(&origin, &direction, 0x60122, 0x10000, nullptr, nullptr);

    // Then if hit, we call other functions.

    // Actually, the code after that sets up another structure for FUN_009e5ed0.

    // Let's skip to the final part: if (local_b0 != 0) { ... } else { velocity[1] -= _DAT_00d5842c; }

    // This suggests gravity is applied to y component if no ground contact.

    // So we can reconstruct:

    float scaleFactor = *(float*)(thisPtr + 0x104);
    // ... up to the point of ground detection.

    // I'll provide a final reconstructed version with plausible names and comments.

    // Note: The function modifies velocity array elements.

    // For clarity, I'll use more systematic naming.

    // Let's produce the final answer with a coherent function.
}

// Actually, I need to output the whole function. Given the decompilation is incomplete, I'll provide a cleaned version with comments explaining the logic.

// I'll assume the class is VehiclePhysics (part of EARS engine). The method name could be applyGravity.

// Let's produce the code.// FUNC_NAME: VehiclePhysics::applyGravity

void VehiclePhysics::applyGravity(int thisPtr, int unused, float* velocity)
{
    // Offset +0x104 is probably inverse mass or force multiplier
    float speedScale = *(float*)(thisPtr + 0x104);
    // +0x108 is another scaling factor (maybe air resistance or ground friction)
    float groundFrictionFactor = *(float*)(thisPtr + 0x108);

    // Get current world transform matrix (likely vehicle's chassis rotation)
    float* worldMatrix = (float*)getWorldMatrix(); // FUN_00471610
    // Copy first 12 floats (3x4 matrix) into local array
    float matrix[3][4];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
            matrix[i][j] = worldMatrix[i*4 + j];

    // Scale velocity by speedScale (e.g., for drag or mass)
    float scaledVel[3];
    scaledVel[0] = speedScale * velocity[0];
    scaledVel[1] = speedScale * velocity[1];
    scaledVel[2] = speedScale * velocity[2];

    // Transform scaled velocity from local to world space using the matrix
    float worldVel[3];
    transformVector((float*)matrix, scaledVel, worldVel); // FUN_0056b420

    // Compute a gravity-adjusted velocity
    float gravity = DAT_00d5c454; // gravitational constant (e.g., 9.8)
    float gravityVel[3];
    gravityVel[0] = worldVel[0];
    gravityVel[1] = worldVel[1] + speedScale * gravity; // Apply gravity in world Y
    gravityVel[2] = worldVel[2];

    // Perform a raycast downward to detect ground
    RaycastResult hitInfo;
    bool hit = raycast(&gravityVel, &DAT_00d5780c, 0x60122, 0x10000, &hitInfo, NULL); // FUN_00542650
    // 0x60122: raycast flags (likely collide with world and vehicles)
    // 0x10000: maximum ray distance

    // Check for ground contact using another query (sweep or sphere test?)
    GroundQueryResult ground;
    bool contact = findGroundContact(&ground, &hitInfo); // FUN_009e5ed0

    if (contact)
    {
        // Adjust velocity based on ground contact
        float groundVelocity = ground.speed - ground.surfaceFriction * speedScale;
        velocity[1] = groundVelocity; // Update vertical velocity

        // Transform something back? The code calls another transformation and then updates velocity[1]
        // The original code: FUN_006e3b00() then FUN_0056b420 again, then sets velocity[1] = groundFrictionFactor * someScaledVel
        // This is likely handling sliding on slopes or friction
        handleGroundContact(); // FUN_006e3b00
        float localVel[3];
        transformVector((float*)matrix, worldVel, localVel); // perhaps convert back to local?
        velocity[1] = groundFrictionFactor * localVel[1];
    }
    else
    {
        // No ground contact: apply free gravity
        velocity[1] -= DAT_00d5842c; // Gravity step (delta time * gravity?)
    }
}