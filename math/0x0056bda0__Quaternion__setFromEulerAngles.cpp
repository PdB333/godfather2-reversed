// FUNC_NAME: Quaternion::setFromEulerAngles
void Quaternion::setFromEulerAngles(float pitch, float yaw, float roll)
{
    // Local quaternion components (w, x, y, z) stored in local arrays
    // local_d0 and local_90 are likely quaternion structs
    float q1[6]; // +0x00: w, +0x04: x, +0x08: y, +0x0c: z, +0x10: unused, +0x14: unused
    float q2[6]; // same layout
    
    // Initialize quaternions with identity (w=1, x=0, y=0, z=0)
    q1[0] = 1.0f;  // DAT_00e2b1a4 = 1.0
    q1[1] = 0.0f;
    q1[2] = 0.0f;
    q1[3] = 0.0f;
    q1[4] = 0.0f;
    q1[5] = 1.0f;
    
    q2[0] = 1.0f;
    q2[1] = 0.0f;
    q2[2] = 0.0f;
    q2[3] = 0.0f;
    q2[4] = 0.0f;
    q2[5] = 1.0f;
    
    // Build quaternion for pitch (around X axis)
    float sinHalfPitch = sinf(pitch * 0.5f);  // FUN_00b99fcb = sinf
    float cosHalfPitch = cosf(pitch * 0.5f);  // FUN_00b99e20 = cosf
    q1[1] = sinHalfPitch;  // x component
    q1[0] = cosHalfPitch;  // w component
    
    // Build quaternion for yaw (around Y axis)
    float sinHalfYaw = sinf(yaw * 0.5f);
    float cosHalfYaw = cosf(yaw * 0.5f);
    q1[5] = sinHalfYaw;  // y component (stored at offset 0x14)
    q1[4] = cosHalfYaw;  // w component (stored at offset 0x10)
    
    // Build quaternion for roll (around Z axis)
    float sinHalfRoll = sinf(roll * 0.5f);
    float cosHalfRoll = cosf(roll * 0.5f);
    q2[1] = sinHalfRoll;  // z component
    q2[0] = cosHalfRoll;  // w component
    
    // Combine quaternions: result = q_yaw * q_pitch (or similar order)
    q2[2] = 0.0f - q1[1];  // Negate x for inverse? Or combine
    q2[0] = q1[0];
    q1[2] = 0.0f - q1[5];  // Negate y
    q1[0] = q1[4];
    q2[3] = 0.0f - q2[1];  // Negate z
    q1[3] = q2[0];
    
    // Multiply quaternions (FUN_0056b230 is quaternion multiplication)
    multiplyQuaternions(q1, q2);  // q1 = q1 * q2
    multiplyQuaternions(&q2[1]);  // Normalize? Or finalize
    
    // Store result to this object (unaff_ESI is 'this')
    *(int*)(this + 0x2c) = 0;  // Clear some fields
    *(int*)(this + 0x1c) = 0;
    *(int*)(this + 0x0c) = 0;
}