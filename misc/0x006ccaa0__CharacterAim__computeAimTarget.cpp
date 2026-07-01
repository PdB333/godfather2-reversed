// FUNC_NAME: CharacterAim::computeAimTarget

// Reconstructed C++ for function 0x006ccaa0
// Purpose: Computes aim target direction vector based on character state and bone transforms.
// Input: this (AimComponent), param2 (character entity pointer), param3 (output float3 vector)
// Uses virtual calls via vtable offsets 0x94 (GetBoneTransform?) and 0xA4 (GetBoneWorldPosition?)
// Flags at this+0xDC control which bone (eye_R, m_pelvis) or default aim direction is used.

void __thiscall CharacterAim::computeAimTarget(int thisPtr, int* character, float* outVector)
{
    bool isAware = false;
    float interpolationWeight; // unaff_EDI from original
    int* localCharPtr = character;
    int* resultPtr; // for vtable calls
    char boneName[8]; // auStack_c
    char transformBuffer[8]; // auStack_14
    char temp[4]; // auStack_4

    // Check if character is non-null and has awareness flag at byte offset 0x6e3
    if ((character != nullptr) && (*((char*)character + 0x6e3) != '\0')) {
        isAware = true;
    }

    // Get default aim direction from a global manager (likely camera/player heading)
    int* manager = FUN_00471610();  // e.g., PlayerStateManager or CameraManager
    // Write 12 bytes: 8 bytes from +0x30 (two floats) and 4 bytes from +0x38 (one float)
    *outVector = *(float*)(manager + 0x30);
    outVector[2] = *(float*)(manager + 0x38);

    // First attempt: check neck bone? The original code stored "m_neck1" but the call seems to be with no args?
    // This might be a cached call or compiler optimization. We'll keep as GetBoneTransform with empty name.
    // vtable+0x94 is likely a method like "GetBoneHandle(const char* name)"
    // Since it's called with no explicit arg, maybe it uses a stored default name? We'll skip this and handle the later logic.
    // The decompiler shows a dead store: pcStack_2c = "m_neck1" then call vtable+0x94()
    // This might be a mistake; we'll ignore it and assume the real flow is as follows.

    // Actually, the first vtable call (vtable[0x94]()) with no args might be a different overload (e.g., GetAimBone())
    // but given the later calls with explicit strings, we treat it as a separate case.
    // For reliability, we replicate the exact pattern:
    {
        // Possibly a prologue that sets up name "m_neck1" and calls to get its index.
        char neckBoneName[] = "m_neck1";
        int* dummy = nullptr; // puStack_30
        // vtable+0x94
        (**(code**)(*character + 0x94))(); // call with no arguments? (This might be bug in decompiler)
        if (false) { // condition not checked properly? In original it's not used.
            return;
        }
    }

    // Actually, the real flow starts after the debug string "m_neck1". 
    // The following is the main logic based on flags.

    unsigned int flags = *(unsigned int*)(thisPtr + 0xDC);
    const char* targetBone = nullptr;

    if (((flags >> 9) & 1) || ((flags >> 8) & 1) || isAware) {
        targetBone = "eye_R";
    }
    else if ((flags >> 7) & 1) {
        // Use pelvis bone and interpolate with default direction
        // First get the pelvis bone handle
        // vtable+0x94 returns true if bone found, stores handle in boneName buffer
        char ret = (**(code**)(*character + 0x94))(boneName, "m_pelvis");
        if (ret == 0) return; // bone not found

        // vtable+0xA4 gets world transform of that bone into transformBuffer
        (**(code**)(*character + 0xA4))(&resultPtr, transformBuffer);
        // Interpolate the current output's Z component (index 2) with the bone's Z from transformation
        float boneZ = *(float*)(transformBuffer + 4); // assuming transformBuffer contains float[2]?
        outVector[2] = DAT_00e51094 * interpolationWeight + outVector[2] * _DAT_00d5f0e8;
        return;
    }
    else if ((flags >> 6) & 1) {
        targetBone = "m_pelvis";
    }
    else if ((flags >> 5) & 1) {
        // Use default from manager (already set above)
        return;
    }
    else {
        return; // no bits set, do nothing
    }

    // If targetBone is set, get its transform and overwrite outVector
    if (targetBone != nullptr) {
        char ret = (**(code**)(*character + 0x94))(boneName, targetBone);
        if (ret == 0) return;

        (**(code**)(*character + 0xA4))(&resultPtr, transformBuffer);
        // Overwrite outVector with the bone transform data
        // Assuming transformBuffer contains 12 bytes: first 8 bytes (two floats) go to outVector[0,1], next 4 to outVector[2]
        outVector[0] = *(float*)(transformBuffer);
        outVector[1] = *(float*)(transformBuffer + 4);
        outVector[2] = *(float*)(transformBuffer + 8); // might be in temp or elsewhere
    }

    return;
}