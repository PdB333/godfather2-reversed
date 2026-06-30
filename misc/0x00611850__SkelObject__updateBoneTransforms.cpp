// FUNC_NAME: SkelObject::updateBoneTransforms
void __thiscall SkelObject::updateBoneTransforms(int this)
{
    int iVar1;
    float* sourceScale;
    float scaleTransform[4];

    // Update base transform (e.g., root bone or world space)
    updateBaseTransform();

    // Check for bones at offsets 0xfc, 0x104, 0x10c, 0x114 (likely bone child pointers)
    // If non-null, detach or remove (FUN_006063b0 might be detach/remove)
    if (*(int*)(this + 0xfc) != 0) {
        removeBoneChild(this + 0xfc);
    }
    if (*(int*)(this + 0x104) != 0) {
        removeBoneChild(this + 0x104);
    }
    if (*(int*)(this + 0x10c) != 0) {
        removeBoneChild(this + 0x10c);
    }
    if (*(int*)(this + 0x114) != 0) {
        removeBoneChild(this + 0x114);
    }

    // Bone transform at 0xc0? (possibly blend transform) with constant 2 flag
    if (*(int*)(this + 0xc0) != 0) {
        applyTransformWithFlag(*(int*)(this + 0x14), *(int*)(this + 0xc0), this + 0xd0, 2);
    }

    // Bone transform at 0xa4
    if (*(int*)(this + 0xa4) != 0) {
        applyTransform(*(int*)(this + 0x14), *(int*)(this + 0xa4), this + 0xb0);
    }

    // Bone transform at 0xf0
    if (*(int*)(this + 0xf0) != 0) {
        applySubTransform(*(int*)(this + 0x14), *(int*)(this + 0xf0), this + 0xf4);
    }

    // Linked bones at 0x11c and 0x120
    if ((*(int*)(this + 0x11c) != 0) || (*(int*)(this + 0x120) != 0)) {
        updateLinkedBoneTransforms();
    }

    // Bone at offset 300 (0x12c)
    if (*(int*)(this + 300) != 0) {
        applySubTransform(*(int*)(this + 0x10), *(int*)(this + 300), this + 0x130);
    }

    // Bone at 0x1e0 with optional scaling from 0x1e4
    if (*(int*)(this + 0x1e0) != 0) {
        if (*(int*)(this + 0x1e4) == 0) {
            sourceScale = (float*)&gZeroVector; // DAT_011f6680 (presumed zero vector)
        } else {
            sourceScale = scaleTransform;
            scaleTransform[0] = 0.0f;
            scaleTransform[1] = 0.0f;
            scaleTransform[2] = 0.0f;
            scaleTransform[3] = 0.0f;
        }
        applyTransform(*(int*)(this + 0x10), *(int*)(this + 0x1e0), sourceScale);
    }

    // Scaling bone at 0x1e4 (if present and bone index < 0x1000)
    if ((*(int*)(this + 0x1e4) != 0) && (*(uint*)(this + 0x100) < 0x1000)) {
        iVar1 = *(uint*)(this + 0x100) * 0x38;
        // Safety check (avoid negative index)
        if (iVar1 != -0x11a0f28) {
            scaleTransform[0] = gScaleFactor / (float)*(ushort*)(&boneScaleArrayX + iVar1); // DAT_011a0f2a
            scaleTransform[1] = gScaleFactor / (float)*(ushort*)(&boneScaleArrayY + iVar1); // DAT_011a0f2c
            scaleTransform[2] = scaleTransform[0];
            scaleTransform[3] = scaleTransform[1];
            applyTransform(*(int*)(this + 0x14), *(int*)(this + 0x1e4), scaleTransform);
        }
    }
    return;
}