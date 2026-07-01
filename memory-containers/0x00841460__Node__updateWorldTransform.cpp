// FUNC_NAME: Node::updateWorldTransform

// Function at 0x00841460: Updates global world transform (position, rotation quaternion, scale) from this node's local transform.
// Node object layout (offsets):
//   +0x8c : position (float[3])
//   +0x98 : rotation euler angles (float[3], pitch, yaw, roll)
//   +0xa4 : scale (float)
//   +0xb0 : bone/pivot handle (returned by FUN_00424cf0)
//
// Global outputs (set by this function):
//   DAT_0112dc80 : position (float[3])
//   DAT_0112dc90 : scale (float)
//   DAT_0112dca0 : rotation quaternion (float[4], w set to constant 1.0f)

void __fastcall Node::updateWorldTransform()
{
    // Static initialization flag
    static bool s_initialized = false; // DAT_0112dcb0
    // Pivot base offset (0 if not yet set)
    static int s_pivotBase = DAT_0112dcb4;

    if (!s_initialized)
    {
        // Initialize pivot node linkage
        int pivotOffset = (s_pivotBase != 0) ? (s_pivotBase - 0x48) : 0;

        // Set pointers to global arrays at pivot node offsets
        *(void**)(pivotOffset + 0x58) = &DAT_0112dc80; // world position
        *(void**)(pivotOffset + 0x5c) = &DAT_0112dca0; // world rotation quat
        *(void**)(pivotOffset + 0x60) = &DAT_0112dc90; // world scale

        // Enable flags
        *(int*)(pivotOffset + 100) = 1;
        *(int*)(pivotOffset + 0x68) = 1;

        // Create a bone/pivot handle and attach this node
        this->boneHandle = FUN_00424cf0(0);
        FUN_00424dc0(this->boneHandle, pivotOffset, 0, 1, 0);

        s_initialized = true;
    }

    // Output global position
    _DAT_0112dc80 = this->position.x; // +0x8c
    _DAT_0112dc84 = this->position.y; // +0x90
    _DAT_0112dc88 = this->position.z; // +0x94

    // Extract euler angles
    float pitch = this->rotation.x; // +0x98
    float yaw   = this->rotation.y; // +0x9c
    float roll  = this->rotation.z; // +0xa0

    // Compute sin/cos of each angle (x87 FPU calls)
    double t;
    t = (double)pitch;
    FUN_00b99fcb(); // sine
    float sinPitch = (float)t;
    t = (double)pitch;
    FUN_00b99e20(); // cosine
    float cosPitch = (float)t;

    t = (double)yaw;
    FUN_00b99fcb();
    float sinYaw = (float)t;
    t = (double)yaw;
    FUN_00b99e20();
    float cosYaw = (float)t;

    t = (double)roll;
    FUN_00b99fcb();
    float sinRoll = (float)t;
    t = (double)roll;
    FUN_00b99e20();
    float cosRoll = (float)t;

    // Build rotation matrix (ZYX euler order assumed: roll->pitch->yaw)
    // Matrix elements:
    float m00 = cosRoll * cosYaw;                         // local_e0
    float m01 = cosRoll * sinPitch * sinYaw - sinRoll * cosPitch; // local_d0
    float m02 = cosRoll * cosPitch * sinYaw + sinRoll * sinPitch; // local_c0
    float m10 = sinRoll * cosYaw;                         // fStack_dc
    float m11 = sinRoll * sinPitch * sinYaw + cosRoll * cosPitch; // fStack_cc
    float m12 = sinRoll * cosPitch * sinYaw - cosRoll * sinPitch; // fStack_bc
    float m20 = -sinYaw;                                  // fStack_d8 (DAT_00e44564 assumed 0)
    float m21 = cosYaw * sinPitch;                       // fStack_c8
    float m22 = cosYaw * cosPitch;                       // fStack_b8

    // Constants
    float one = _DAT_00d5780c; // likely 1.0f
    float zero = 0.0f;

    // Build a 4x4 identity matrix with rotation and translation (position zero for now)
    // local_60 = one; uStack_5c = 0; uStack_58 = 0; uStack_54 = 0; (first row)
    // ... (many variables set to one/zero)
    // We'll represent the matrix as a 4x4 array for clarity
    float matrix[4][4] = {
        { m00, m01, m02, 0.0f },
        { m10, m11, m12, 0.0f },
        { m20, m21, m22, 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f }
    };

    // Perform matrix multiplication with a constant transform (DAT_00d74660, DAT_00e44600)
    // This likely combines the node's rotation with a parent transform
    FUN_0046cf70(&matrix, &DAT_00d74660, DAT_00e44600, 0);

    // Convert the resulting rotation matrix to a quaternion (12-byte representation)
    // local_50 is a 12-byte rotation descriptor (e.g., axis-angle or 3x3 matrix)
    FUN_00841050(&matrix); // fills local_50

    // Extract quaternion components from the 12-byte rotation
    float quatX, quatY, quatZ, quatW;
    FUN_0056c180(&matrix, &quatX, &quatY, &quatZ); // outputs x,y,z; w is set to constant

    // Store global rotation quaternion
    _DAT_0112dca0 = quatX;
    _DAT_0112dca4 = quatY;
    _DAT_0112dca8 = quatZ;
    _DAT_0112dcac = one; // w = 1.0f

    // Store global scale
    _DAT_0112dc90 = this->scale; // +0xa4

    return;
}