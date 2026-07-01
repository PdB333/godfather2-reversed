// FUNC_NAME: ChaseCamera::updateFollow
// Address: 0x007fc5d0
// This function updates the camera's yaw and pitch angles smoothly towards a target direction,
// applying clamping and interpolation with delta time. It then builds a final rotation matrix.

class ChaseCamera {
public:
    void updateFollow(float deltaTime);
    // Member offsets (relative to this):
    // +0x71e: gameState (int, pause check)
    // +0x6e2: targetPositionZ (float, actually integer stored as int)
    // +0x6e0: targetLookX (float) and +0x6e4: targetLookY? (8 bytes, likely 2 floats)
    // +0x28c: lockOnTarget (byte/bool)
    // +0x28d: currentYaw (int, stored as int of float bits)
    // +0x28e: currentPitch (int)
    // +0x248: someIndexOrHandle (int)
    // +0x290: finalMatrix (matrix, 4x4?)
    // +0xa31: useExternalCamera (byte)
    // +0x1c4: flags (int)
};

// Helper functions with guessed names based on usage
void FUN_007fc520(void*);                 // likely cartesianToAngle, takes 2D vector and returns angle
float FUN_0056aee0(float, float);         // likely angleDifference, wraps around constant DAT_00d5d70c
void FUN_0056d6f0(int, float*);           // likely setVectorFromScalar? (converts int to float array)
void FUN_0056d750(float, float*);         // likely createRotationMatrixY (from yaw)
void FUN_0056d7b0(float, float*);         // likely createRotationMatrixX (from pitch)
void FUN_0056d6b0(float*, float*, float*, float*); // combine transforms
void FUN_0056cba0(float*, float*, int*);  // set final matrix

// External globals (constants from data segment)
extern float DAT_00d5f00c;    // time scale factor
extern float DAT_00d71bbc;    // max yaw
extern float DAT_00d71e7c;    // min yaw
extern float DAT_00d5ef84;    // angle epsilon for large rotations
extern float DAT_00d5d70c;    // wrap constant (2*PI or 360 degrees)
extern int DAT_00e44680;      // FLOAT_ABS_MASK (0x7FFFFFFF)
extern float DAT_00e44564;    // some offset angle (maybe 90 degrees?)
extern float DAT_00e447a4;    // max pitch
extern float DAT_00d69acc;    // min pitch
extern float _DAT_00d5780c;   // identity matrix? (used as placeholder)
extern int DAT_00d71bbc;      // same as above? duplicates
extern int DAT_00d71e7c;
extern float DAT_00d5ef84;
extern float DAT_00e44680_asFloat; // same as above for float? (reused)
extern float DAT_00d5f00c;

void __thiscall ChaseCamera::updateFollow(float deltaTime)
{
    int iVar1;
    float fVal;
    float absAngle;
    double tempDouble;
    float dx, dz;
    float local_a8;         // finalPitch
    float targetYaw, targetPitch;
    float currentYaw, currentPitch;
    // local vectors and matrices
    float vecLocal[2];      // 8 bytes for 2D vector?
    float vecAnother[2];
    float matYaw[16];       // assumed 4x4 matrix (16 bytes? actually 16 floats?)
    float matPitch[16];
    // Stack arrays for intermediate matrices
    uint8_t stackMat1[16];
    uint8_t stackMat2[16];
    uint8_t stackMat3[12];
    // other temporaries
    float local_88, local_98;
    uint64_t local_a0, local_90; // 8-byte containers for 2D vectors (float x, y)
    // placeholder for unused variables (some local_44 etc. are not used meaningfully)

    // --- Initialization ---
    local_a8 = 0.0f;
    targetYaw = 0.0f;
    targetPitch = 0.0f;

    // Check if game is not paused and state is not 0x48 (some special state)
    if ( *(int*)(this + 0x71e) != 0 && *(int*)(this + 0x71e) != 0x48 )
    {
        // Get target position (z component) - offset 0x6e2
        local_88 = (float)*(int*)(this + 0x6e2);  // targetZ as float (stored as int bits)
        local_98 = 0.0f;                          // assumed targetZ? Actually set to zero.

        // Copy target look direction (2D vector) from this+0x6e0
        local_a0 = *(uint64_t*)(this + 0x6e0);    // likely two floats: x and z
        local_90 = local_a0;                       // copy as reference

        // Convert the 2D vector to an angle (probably atan2(y,x) returning a single angle?)
        FUN_007fc520(&local_a0);   // modifies local_a0? Actually it takes a pointer to 8-byte structure?

        // Compute difference between original vector and the vector after angle conversion?
        // This is odd: local_a0 is now reinterpreted as two floats (lower and upper halves)
        // Assuming FUN_007fc520 returns an angle stored as float in first 4 bytes? But it takes pointer.
        // Let's assume FUN_007fc520 converts the vector to polar, storing angle in first float and zero in second?
        // Then local_80[0] = angle - originalX? Actually we have:
        // local_80[0] = (float)local_a0 - (float)local_90;
        // (float) might be casting the 8-byte value to float? That's nonsense.
        // More likely local_a0 and local_90 are 8-byte structs of two floats. The cast (float) takes first 4 bytes.
        // So local_a0._0_4_ is the angle computed, local_90._0_4_ is original x.
        // So local_80[0] = angle - originalX? Probably not.

        // Let's reinterpret: FUN_007fc520 calculates a 2D angle from the vector and stores result as two floats? Unclear.

        // For reconstruction, we'll assume it computes a direction angle (yaw) and the difference is used to get delta.
        dx = *(float*)&local_a0 - *(float*)&local_90;
        dz = local_98 - local_88;  // since local_98 was set to 0.0 earlier, dz = -targetZ? Actually local_98 is declared as float but initialized to 0.0 locally? Wait local_98 is part of the local struct? It's a float variable.

        // Actually local_98 is a separate float (from decomp: float local_98;). So dz = local_98 - local_88 => -targetZ

        // Check if lock-on target flag is non-zero (param_1[0x28c] as byte)
        if ( *(char*)(this + 0x28c) == '\0' )
        {
            targetYaw = 0.0f;
        }
        else
        {
            // Use something from the computed angle? Actually:
            // dVar4 = (double)(local_a0._4_4_ - local_90._4_4_); // difference of second floats
            // FUN_00b9a9fa(); // some math library function? (maybe calculates sin/cos or just a nop?)
            // targetYaw = DAT_00e44564 - (float)dVar4;
            tempDouble = (double)( ((float*)&local_a0)[1] - ((float*)&local_90)[1] );
            FUN_00b9a9fa();  // stub or state-saving
            targetYaw = DAT_00e44564 - (float)tempDouble;
        }

        // Get current pitch stored as int bits
        currentPitch = (float)*(int*)(this + 0x28d);  // Actually param_1[0x28d] is used for targetYaw later? Wait: fVar3 = (float)param_1[0x28d]; That is currentYaw maybe? Let's check: later it stores param_1[0x28d] = (int)fVar5; so fVar5 is new yaw, and param_1[0x28e] is new pitch. So initially fVar3 is assigned from param_1[0x28d] which is current yaw. So fVar3 = currentYaw. But later fVar3 is used as targetPitch? Actually fVar3 is reused. Let's keep track:

        // After the above, fVar3 = (float)param_1[0x28d]; // currentYaw
        // Then param_2 = deltaTime * DAT_00d5f00c;
        // if (param_2 <= (float)((uint)(targetYaw - fVar3) & DAT_00e44680)) { ... }
        // So fVar3 here is currentYaw. So targetYaw is computed, variable fVar3 is currentYaw.

        // Let's correct variable naming: we have local variable fVar3 that initially holds currentYaw, but later gets reused.

        fVar3 = (float)*(int*)(this + 0x28d);  // currentYaw
        deltaTime = deltaTime * DAT_00d5f00c;   // scale delta time

        // Clamp angular velocity: if deltaTime is within the absolute difference between target and current
        if ( deltaTime <= (float)( (uint)(targetYaw - fVar3) & DAT_00e44680 ) )
        {
            if ( targetYaw - fVar3 >= 0.0f )
                targetYaw = deltaTime + fVar3;
            else
                targetYaw = fVar3 - deltaTime;
        }

        // Apply yaw clamping
        if ( DAT_00d71bbc < targetYaw || ( targetYaw < DAT_00d71e7c ) )
        {
            targetYaw = (DAT_00d71bbc < targetYaw) ? DAT_00d71bbc : DAT_00d71e7c;
        }

        // Handle external camera update if flag set (offset +0xa31)
        if ( *(char*)(this + 0xa31) != '\0' )
        {
            iVar1 = FUN_00471610();  // get some external camera controller or input
            local_a0 = *(uint64_t*)(iVar1 + 0x20);  // copy 8-byte from that object (likely look vector)
            local_98 = *(float*)(iVar1 + 0x28);      // another float (maybe pitch offset?)

            // If flags at offset 0x1c4 have any bits set (lower 2 bits clear)
            if ( (*(int*)(this + 0x1c4) & 0xfffffffcU) != 0 )
            {
                // Construct a new vector from identity matrix? Actually local_44, local_34, etc are initialized to 0.
                // Then a virtual call: (**(code **)(*this + 0x90))(stackMat3, this+0x1c4, 1);
                // This likely gets a transform matrix from some component.
                // Then local_a0 and local_98 are overwritten from stack variables (uStack_30, fStack_28)
                // We'll skip detail and assume it gets a new look direction.
                // For reconstruction, we just note that it overrides local_a0 and local_98.
            }

            // Check if the new look vector's components exceed epsilon DAT_00d5ef84
            if ( DAT_00d5ef84 <= (float)( (uint)*(float*)&local_a0 & DAT_00e44680 ) ||
                 DAT_00d5ef84 <= (float)( (uint)local_98 & DAT_00e44680 ) )
            {
                // Compute pitch from the X component? Actually:
                // dVar4 = (double)*(float*)&local_a0;
                // FUN_00b9a9fa();
                // local_a8 = (float)dVar4;
                tempDouble = (double)*(float*)&local_a0;
                FUN_00b9a9fa();
                local_a8 = (float)tempDouble;
            }
            else
            {
                local_a8 = 0.0f;
            }

            // Similarly for dx and dz computed earlier (local_80[0] and local_78)
            if ( DAT_00d5ef84 <= (float)( (uint)*(float*)&local_80[0] & DAT_00e44680 ) ||
                 DAT_00d5ef84 <= (float)( (uint)local_78 & DAT_00e44680 ) )
            {
                tempDouble = (double)*(float*)&local_80[0];
                FUN_00b9a9fa();
                fVar3 = (float)tempDouble;
            }
            else
            {
                fVar3 = 0.0f;
            }

            // Compute angle difference between fVar3 and local_a8 using FUN_0056aee0
            // DAT_00d5d70c is the wrap constant (e.g., 2*PI)
            local_a8 = FUN_0056aee0(fVar3 - local_a8, DAT_00d5d70c);
        }

        // Interpolate pitch towards targetPitch (which is calculated in the external camera portion? Actually local_a8 is used as targetPitch)
        // But first, check if stored pitch (param_1[0x28e]) differs from a constant? The code: 
        // if ( (float)param_1[0x28e] != _DAT_00d71bb4 )
        // Actually _DAT_00d71bb4 is a float constant? But param_1[0x28e] is currentPitch (int bits). So it checks if currentPitch != some default value.
        // Then it computes angle difference between local_a8 (targetPitch) and currentPitch, and if > deltaTime, interpolate.
        if ( (float)*(int*)(this + 0x28e) != _DAT_00d71bb4 )
        {
            absAngle = FUN_0056aee0( local_a8 - (float)*(int*)(this + 0x28e), DAT_00d5d70c );
            if ( deltaTime <= fabs(absAngle) ) // Note: ABS is used as comparison? Actually the code compares param_2 (deltaTime) to ABS(fVar2) after ABS call? The decomp: (float10)param_2 <= ABS(fVar2). So we use fabs.
            {
                absAngle = FUN_0056aee0( local_a8 - (float)*(int*)(this + 0x28e), DAT_00d5d70c );
                if ( absAngle >= 0.0f )
                    local_a8 = (float)*(int*)(this + 0x28e) + deltaTime;
                else
                    local_a8 = (float)*(int*)(this + 0x28e) - deltaTime;
            }
        }

        // Clamp final pitch local_a8 between DAT_00e447a4 (max) and DAT_00d69acc (min)
        if ( DAT_00e447a4 < local_a8 || local_a8 < DAT_00d69acc )
        {
            local_a8 = (DAT_00e447a4 < local_a8) ? DAT_00e447a4 : DAT_00d69acc;
        }
    }

    // Store new yaw and pitch as integers (bit-cast)
    *(int*)(this + 0x28d) = (int)targetYaw;
    *(int*)(this + 0x28e) = (int)local_a8;

    // Build final matrix: 
    // 1. Get some handle/ID from offset 0x248 and convert to vector? (local_80)
    FUN_0056d6f0( *(int*)(this + 0x248), &local_80[0] );
    // 2. Get something else? (unknown constant minus current yaw? Actually DAT_00e44564 - (float)param_1[0x248] used as argument)
    FUN_0056d6f0( DAT_00e44564 - (float)*(int*)(this + 0x248), &local_a0 );
    // 3. Create rotation matrix from yaw
    FUN_0056d750( (float)*(int*)(this + 0x28e), &stackMat1[0] );
    // 4. Create rotation matrix from pitch (but using yaw? Actually uses param_1[0x28d] which is yaw)
    FUN_0056d7b0( (float)*(int*)(this + 0x28d), &stackMat2[0] );
    // 5. Combine two matrices? (local_a0 and local_90 as arguments, output to local_80 and stackMat1? Actually FUN_0056d6b0(&local_a0, &local_90, &local_80[0], &stackMat1[0]); )
    FUN_0056d6b0( &local_a0, &local_90, &local_80[0], &stackMat1[0] );
    // 6. Set final matrix at offset 0x290
    FUN_0056cba0( &stackMat1[0], &stackMat2[0], this + 0x290 );

    return;
}