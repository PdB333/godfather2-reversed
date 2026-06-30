// FUNC_NAME: Character::checkPelvisState
int Character::checkPelvisState() {
    // param_1 is the this pointer (int*)
    if (this == 0) return 0;

    // Virtual call at vtable+0x10 – likely a condition check (e.g., isAlive, isActive)
    if (!((bool(*)(int*))(this->vtable[0x10]))(this)) {
        return 0;
    }

    // piStack_4 is actually m_skeleton or a similar bone/ragdoll manager
    // In the original code, it came from an uninitialized stack variable,
    // but likely it's a member accessed through a register (EBX) or global.
    // We'll assume it's a member pointer named m_pelvisBone.
    if (this->m_skeleton != 0) {
        void* stackVar1;  // Address of local buffer for bone name
        // Virtual call vtable+0x94 – probably getBoneNode or findBone
        // Passes a pointer to store result and the bone name "m_pelvis"
        if ((*(bool(**)(void**, const char*))(this->m_skeleton->vtable[0x94]))(&stackVar1, "m_pelvis")) {
            char buffer[24]; // Used as temporary storage
            // Virtual call vtable+0xa4 – likely getBoneTransform or getWorldMatrix
            // Arguments: buffer, some stack address, the bone pointer, bone name, and a magic hash (0x55859efa)
            (*(void(**)(char*, void*, void**, const char*, uint64_t))(this->m_skeleton->vtable[0xa4]))(
                buffer, &stackVar1, stackVar1, "m_pelvis", 0x55859efa);

            int someResult = FUN_00471610(); // Returns a pointer or handle

            // unaff_EBX is a float value (possibly a member or global like character height or distance)
            // The decompiler shows a strange shift: (float)((ulonglong)*(undefined8 *)(result+0x30) >> 0x20)
            // This likely reads a 64-bit float (double) at result+0x30 and extracts the high 32 bits.
            // In practice, this may be a float stored at result+0x30, but the decompiler misinterpreted.
            // We'll treat it as a float from result+0x30.
            float diff = unaff_EBX - *(float*)(someResult + 0x30);

            // Global thresholds from .data section (0x00e51210 and 0x00e5120c)
            float thresholdLow = *(float*)0x00e51210;
            float thresholdHigh = *(float*)0x00e5120c;

            if (thresholdLow <= diff) return 0;
            if (thresholdHigh <= diff) return 1;
            return 3;
        }
    }
    return 0;
}