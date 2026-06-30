// FUN_0046dbd0: PhysicsObject::computeRelativeOrientation
void PhysicsObject::computeRelativeOrientation(void* outObject) // outObject at param_1; sourceA in ESI, sourceB in EDI
{
    // Global constants
    extern float DAT_00e2cbe0; // epsilon for magnitude check
    extern float DAT_00e2b1a4; // value to normalize quaternion (likely 1.0)
    extern float DAT_00e35654; // some parameter for FUN_0056db60

    // Quaternions (16 bytes each) from offsets +0x30
    // Offset +0x30: quaternion x, +0x34: y, +0x38: z, +0x3c: w
    struct Quat { float x, y, z, w; } *sourceA = (Quat*)unaff_ESI;
    struct Quat *sourceB = (Quat*)unaff_EDI;

    // Local quaternion storage
    Quat quatA;  // local_20..uStack_14
    Quat quatB;  // local_40..uStack_34
    Quat result; // local_70..local_64

    FUN_0056d530(); // likely identity setup, ignore
    quatA = *sourceA; // copy from EDI+0x30
    FUN_0056d530();
    quatB = *sourceB; // copy from ESI+0x30

    // Compute a quaternion from two (perhaps rotation) matrices? The call uses two 16-byte buffers not shown as initialized.
    // Assuming quatA and quatB are implicitly stored in local_30 and local_50 by earlier operations.
    FUN_0056db60(DAT_00e35654, &quatA, &quatB, &result); // compute relative quaternion

    // Normalize the result
    float magnitudeSq = result.x * result.x + result.y * result.y + result.z * result.z + result.w * result.w;
    float scale;
    if (magnitudeSq <= DAT_00e2cbe0) {
        scale = 0.0f;
    } else {
        scale = DAT_00e2b1a4 / sqrtf(magnitudeSq);
    }
    result.x *= scale;
    result.y *= scale;
    result.z *= scale;
    result.w *= scale;

    // Convert quaternion to output orientation (likely matrix or quaternion)
    Quat output; // local_60..uStack_54
    FUN_0056cef0(&result, &output); // transforms result into output quaternion

    // Write to outObject at offset +0x30
    *(Quat*)(outObject + 0x30) = output;

    // Force w component to 1.0 (already normalized, but explicit)
    *(float*)(outObject + 0x3c) = DAT_00e2b1a4;
}