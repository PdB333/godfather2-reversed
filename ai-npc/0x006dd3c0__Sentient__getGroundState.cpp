// FUNC_NAME: Sentient::getGroundState
int Sentient::getGroundState()
{
    // Check if this object is valid
    if (this == nullptr)
        return 0;

    // Virtual call at vtable+0x10: likely isAlive() or isActive()
    if (!this->vtable->isAlive())
        return 0;

    // piStack_4 is likely a member pointer to a skeleton/bone manager (e.g., m_pSkeleton)
    // It is used without initialization in the decompiled code, but assumed to be a member.
    if (m_pSkeleton == nullptr)
        return 0;

    // Hash constant for "m_pelvis" (likely a bone name hash)
    const uint32_t pelvisHash = 0x55859efa;

    // Prepare a buffer for bone transform (e.g., matrix or position)
    char transformBuffer[24]; // auStack_1c
    void* transformOut = &transformBuffer; // puVar4

    // Call virtual at vtable+0x94: likely findBoneIndex or getBoneTransform
    // Returns true if bone found
    if (!m_pSkeleton->vtable->findBone(transformOut, "m_pelvis"))
        return 0;

    // Call virtual at vtable+0xa4: likely getBoneWorldTransform
    // Parameters: output buffer, some stack variable, bone index, bone name, hash
    m_pSkeleton->vtable->getBoneWorldTransform(transformBuffer, &stackVar, transformOut, "m_pelvis", pelvisHash);

    // Get current game time (FUN_00471610)
    int* timeData = getGameTime(); // returns pointer to time structure

    // Extract time value from offset 0x30 (likely a double or float)
    // The decompiled code shows a complex cast, but we simplify to a float read
    float lastPelvisTime = *(float*)(timeData + 0x30); // assume float at +0x30

    // unaff_EBX is likely a float register containing current time or a height value
    // We'll assume it's current time (passed in EBX or global)
    float currentTime = unaff_EBX; // from register

    // Compute elapsed time since last pelvis update
    float elapsed = currentTime - lastPelvisTime;

    // Compare with thresholds (global variables)
    if (elapsed <= g_fGroundThreshold) // _DAT_00e51210
        return 0;
    if (elapsed <= g_fAirThreshold) // _DAT_00e5120c
        return 1;
    return 3;
}