// Xbox PDB: EARS::Modules::F2FCamera::GetEntityLowerPos
// FUNC_NAME: Character::computeAimTransform
void __thiscall Character::computeAimTransform(Character* this, Skeleton* skeleton, Transform* outTransform) {
    bool bHasWeapon = false;
    if (skeleton != nullptr && skeleton->hasWeaponFlag() != 0) { // byte at offset 0x6e3*4? or actual byte offset?
        bHasWeapon = true;
    }

    // Get base transform from global (camera or root)
    int* baseTransform = FUN_00471610(); // returns pointer to some transform source
    *outTransform = *(Transform*)(baseTransform + 0x30); // copy 8 bytes (position+quaternion?) 
    *(float*)((int)outTransform + 8) = *(float*)(baseTransform + 0x38); // copy extra float

    // Try "m_neck1" bone
    int boneId = skeleton->getBoneId("m_neck1"); // vtable offset 0x94
    if (boneId != -1) {
        skeleton->getBoneWorldTransform(boneId, &localTransform); // vtable offset 0xa4
        // Overwrite part of output with something from the call? (actually unaff_ESI, register from caller)
        *(int*)((int)outTransform + 4) = unaff_ESI; // not clearly defined, likely a blend factor
    }

    uint flags = *(uint*)((char*)this + 0xdc); // state flags

    if (((flags >> 9) & 1) != 0 || ((flags >> 8) & 1) != 0 || bHasWeapon) {
        // Use "eye_R" bone
        boneId = skeleton->getBoneId("eye_R");
        if (boneId != -1) {
            skeleton->getBoneWorldTransform(boneId, &eyeTransform);
            // Copy eye transform rotation (4 bytes) into output offset 4
            *(int*)((int)outTransform + 4) = *(int*)&eyeTransform;
        }
    } else if (((flags >> 7) & 1) != 0) {
        // Use "m_pelvis" bone with blending
        boneId = skeleton->getBoneId("m_pelvis");
        if (boneId != -1) {
            skeleton->getBoneWorldTransform(boneId, &pelvisTransform);
            // Blend: outTransform's Y component = pelvis Y * blendA + currentY * blendB
            *(float*)((int)outTransform + 4) = DAT_00e51094 * *(float*)((int)&pelvisTransform + 0) + 
                                                *(float*)((int)outTransform + 4) * _DAT_00d5f0e8;
        }
        return;
    } else if (((flags >> 6) & 1) != 0) {
        // No bone, just return (base transform already set)
        return;
    } else if (((flags >> 5) & 1) != 0) {
        // Reset output to base transform again
        *outTransform = *(Transform*)(baseTransform + 0x30);
        *(float*)((int)outTransform + 8) = *(float*)(baseTransform + 0x38);
        return;
    } else {
        return;
    }
}