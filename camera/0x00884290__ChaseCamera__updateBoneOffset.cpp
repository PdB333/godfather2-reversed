// FUNC_NAME: ChaseCamera::updateBoneOffset
void __fastcall ChaseCamera::updateBoneOffset(CChaseCamera* this)
{
    // Local stack for matrix operations (16x16? Actually 4x4)
    float rootPos[4]; // local_e4
    float cameraPos[3]; // fStack_28, fStack_24, fStack_20 (plus w)
    float localMatrix[12]; // auStack_58 (48 bytes = 12 floats, 3x4 matrix)
    float invLocal[16]; // auStack_88 (64 bytes? actually 16 floats)
    float localToWorld[16]; // auStack_78 (16 floats)
    float worldToLocal[16]; // auStack_68 (16 floats)
    float offset[4]; // param_1 + 0xd0

    // Get world position of root bone "m_root"
    rootPos[0] = 0.0f;
    (*(void (__thiscall**)(float*, const char*))(**(int**)this->m_pSkeleton + 0x94))(&rootPos, "m_root");

    // Copy identity matrix from this->m_transform (offset 0x60)
    FUN_0045f8d0(localMatrix, &this->m_transform, 1); // likely copies 48 bytes

    // Get camera world position (from a global function)
    float cameraWorld[3]; // uStack_98 etc.
    cameraWorld[0] = 0.0f;
    cameraWorld[1] = _DAT_00d5780c; // some constant, likely 0
    cameraWorld[2] = 0.0f;

    // Get world transform from this->m_worldPos (offset 0xe0)
    FUN_008831a0(&this->m_worldPos, &cameraWorld);

    // Get local matrix from this->m_localPos (offset 0xf0)
    FUN_00883b50(&this->m_localPos, &cameraPos);

    // Copy world position to offset 0x100 (presumably previous frame)
    this->m_previousWorldPos.x = this->m_worldPos.x;
    this->m_previousWorldPos.y = this->m_worldPos.y;
    this->m_previousWorldPos.z = this->m_worldPos.z;
    this->m_previousWorldPos.w = this->m_worldPos.w;
    this->m_unknown0 = 0;
    this->m_unknown1 = 0;
    this->m_unknown2 = 0;

    // Get camera position from global function (maybe player or camera)
    int* pCam = (int*)FUN_00471610();
    float camPos[3];
    camPos[0] = *(float*)(pCam + 0x30);
    camPos[1] = *(float*)(pCam + 0x34);
    camPos[2] = *(float*)(pCam + 0x38);
    // Actually the code reads: local_e4 = *(float *)(iVar2 + 0x34); fStack_e0 = *(float *)(iVar2 + 0x38); fStack_dc = _DAT_00d5780c;

    // Compute offset from camera to root
    offset[0] = cameraPos[0] - camPos[0];
    offset[1] = cameraPos[1] - *(float*)(pCam + 0x34);
    offset[2] = cameraPos[2] - *(float*)(pCam + 0x38);
    offset[3] = 0.0f; // fStack_1c was set to 0

    // Get the full camera transform matrix
    unsigned int* pCamMatrix = (unsigned int*)FUN_00471610();
    // Build a matrix from camera's columns (format unknown, but rows?)
    // Using values from pCamMatrix at offsets 0,1,2; then 4,5,6; etc.
    float camMatrix[4][4]; // Actually the stack uses array of 12 floats?
    // The decompiled code shows 16 assignments (uStack_d8 ... fStack_9c)
    // This likely builds a 4x4 matrix from the camera's axes and position
    // We'll simplify by calling the functions directly

    // Multiply matrices to get world-to-local of the root?
    FUN_0056d530(&camMatrix, worldToLocal); // likely worldToLocal = camMatrix * ?
    FUN_0056d530(localMatrix, localToWorld); // localToWorld = localMatrix * ?
    FUN_0056ce40(localToWorld, invLocal); // invLocal = inverse(localToWorld)
    FUN_0056cba0(invLocal, worldToLocal, &this->m_something); // multiply and store at +0xc0
    FUN_0056ce80(invLocal, offset, offset); // transform offset vector

    // Negate the offset (for camera behind)
    this->m_boneOffset.x = -offset[0];
    this->m_boneOffset.y = -offset[1];
    this->m_boneOffset.z = -offset[2];
    this->m_boneOffset.w = -offset[3]; // though w was 0

    // Apply the offset to a bone if valid
    int boneIndex;
    if (this->m_boneID != 0)
        boneIndex = this->m_boneID - 0x48; // convert to zero-based?
    else
        boneIndex = 0;

    // Call vtable slot +0x80 to set bone transform
    (*(void (__thiscall**)(int, void*, void*, int, void*))(**(int**)this->m_pSkeleton + 0x80))
        (boneIndex, &this->m_transform, &stackBuffer, 0, &this->m_unknownBuffer);

    // Set flag bit 3 (0x8) to indicate offset updated
    this->m_flags |= 8;
}