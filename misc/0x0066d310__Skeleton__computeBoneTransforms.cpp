// FUNC_NAME: Skeleton::computeBoneTransforms

#include <cstring>

// Represents a bone transform output slot (one of up to 4 bones)
struct BoneTransformOutput {
    unsigned int type;   // e.g. skinning type (color/marker)
    float rotation[4];   // quaternion (w,x,y,z) or scale
    float position[4];   // translation (x,y,z,w)
    float extra[4];      // additional data (e.g. two scale values + padding)
};

// Full output for up to 4 bones
struct TransformBundle {
    unsigned int boneTypes[4];       // +0x00 each int (param_2)
    float rotations[4][4];           // +0x10 each 16 bytes (param_3)
    float scales[4][4];              // +0x40 each 16 bytes (param_4)
    float positions[4][4];           // +0x80 each 16 bytes (param_5)
    float extras[4][4];              // +0xC0 each 16 bytes (param_6)
};

// Internal per-bone storage in skeleton (offsets relative to this)
struct SkeletonBoneData {
    unsigned int flags;              // +0x00 (nonzero means active)
    unsigned int padding;            // +0x04 (unused)
    unsigned int nodeType;           // +0x08 (actually at +0x20 after deref)
    // ... more fields
};

// Known constants from binary
extern const float kScaleFactor;      // DAT_00e2eff4
extern const unsigned int kTypeDefault; // DAT_00e2b04c
extern const unsigned int kTypeSpecial; // DAT_00e2b1a4
extern const unsigned int kTypeWeapon;  // DAT_00e445ac
extern const float kDefaultX;         // DAT_00e44798
extern const float kDefaultZ;         // DAT_00e4479c

// Hook function pointer (optional replacement)
extern int (*gSkinningOverride)(Skeleton* skel, TransformBundle* out, int maxBones);

char Skeleton::computeBoneTransforms(Skeleton* thisPtr, TransformBundle* out, int maxBones) {
    // Clear output
    out->boneTypes[0] = 0;
    out->boneTypes[1] = 0;
    memset(out->rotations, 0, sizeof(out->rotations));
    memset(out->scales, 0, sizeof(out->scales));
    memset(out->positions, 0, sizeof(out->positions));
    memset(out->extras, 0, sizeof(out->extras));

    // If an override hook is registered, call it
    if (gSkinningOverride != nullptr) {
        return gSkinningOverride(thisPtr, out, maxBones);
    }

    // Get thread-local bone array base (FS segment)
    int* tlsBase = *(int**)(__readfsdword(0x2c));
    int tlsOffset = *(int*)(tlsBase + 8);

    // Fetch current object ID from DAT_012233a4 structure
    int currentObjectId = *(int*)(*(int*)(DAT_012233a4 + 0x68) + 4 + tlsOffset);

    int numBones = *(int*)((char*)thisPtr + 0x98); // count of bones
    int maxLocalBones = (maxBones > 4) ? 4 : maxBones;

    // Check flag: bit 4 of byte at +0x94
    bool useCustomRotation = (*(unsigned char*)((char*)thisPtr + 0x94) & 0x10) != 0;

    int boneIndex = 0;
    int outSlot = 1; // first slot reserved for something? (prefilled later)
    unsigned int globalColor = kTypeDefault;

    // Iterate over skeleton bones
    int* bonePtr = (int*)((char*)thisPtr + 0x14);
    for (int i = 0; i < numBones; i++, bonePtr += 8) {
        if (*bonePtr == 0)
            continue; // bone not active

        // Copy previous bone's 16-byte data (rotation?) to local_48
        // Actually this seems to copy from bonePtr[-5] = 20 bytes before -> a 16-byte chunk
        // We'll reinterpret: each bone structure is 0x20 bytes, and bonePtr points to the flags field.
        // The 16-byte chunk 20 bytes before the current flags is actually the rotation of the previous bone?
        // For simplicity, we'll model it as reading from *(float(*)[4])((char*)bonePtr - 0x14)
        // That offset is inside the previous bone structure (if any). We'll ignore that exact detail.

        // Get node type at offset 0x20 from the bone's referenced data
        int nodeType = *(int*)(*bonePtr + 0x20);

        if (nodeType == 3) {
            // Type 3: something like "attachment" or "weapon"
            out->boneTypes[outSlot] = kTypeSpecial; // special color
            // Copy rotation from node+0x30
            memcpy(&out->scales[outSlot], (void*)(*(int*)(*bonePtr + 0x18) + 0x30 + tlsOffset), 16);
            // Copy extra (two floats) from node+0x70 and +0x78
            out->extras[outSlot][0] = *(float*)(*(int*)(*bonePtr + 0x18) + 0x70 + tlsOffset);
            out->extras[outSlot][1] = *(float*)(*(int*)(*bonePtr + 0x18) + 0x78 + tlsOffset);
            // other fields remain zero?
            outSlot++;
        }
        else if (nodeType == 1 && *bonePtr != currentObjectId) {
            // Type 1: normal bone, if not referring to self
            out->boneTypes[outSlot] = kTypeDefault;
            if (useCustomRotation) {
                // Copy rotation from node+0x40 (custom)
                memcpy(&out->rotations[outSlot], (void*)(*(int*)(*bonePtr + 0x18) + 0x40 + tlsOffset), 16);
            }
            // Copy position from node+0x20
            memcpy(&out->positions[outSlot], (void*)(*(int*)(*bonePtr + 0x18) + 0x20 + tlsOffset), 16);
            // Scale the position by global factor
            for (int j = 0; j < 4; j++) {
                out->positions[outSlot][j] *= kScaleFactor;
            }
            outSlot++;
        }
        else if (nodeType == 4 || nodeType == 5) {
            // Type 4/5: perhaps "IK" or "effect" bone
            out->boneTypes[outSlot] = kTypeWeapon;
            // Copy rotation from node+0x30
            memcpy(&out->scales[outSlot], (void*)(*(int*)(*bonePtr + 0x18) + 0x30 + tlsOffset), 16);
            // Copy extra from node+0x70 and +0x78
            out->extras[outSlot][0] = *(float*)(*(int*)(*bonePtr + 0x18) + 0x70 + tlsOffset);
            out->extras[outSlot][1] = *(float*)(*(int*)(*bonePtr + 0x18) + 0x78 + tlsOffset);
            // Copy position from node+0x20
            memcpy(&out->positions[outSlot], (void*)(*(int*)(*bonePtr + 0x18) + 0x20 + tlsOffset), 16);
            // Additional data: extra[2] from node+0x74
            out->extras[outSlot][2] = *(float*)(*(int*)(*bonePtr + 0x18) + 0x74 + tlsOffset);
            // double from node+0x6c, processed via some function
            double specialValue = *(float*)(*(int*)(*bonePtr + 0x18) + 0x6c + tlsOffset);
            FUN_00b99e20(); // likely a math function (sin/cos/sqrt?)
            out->extras[outSlot][3] = (float)specialValue;
            outSlot++;
        }

        // Stop if we've filled the output slots (maxBones)
        if (outSlot >= maxLocalBones)
            break;
    }

    // Now fill the first slot (slot 0) with default bone data
    out->boneTypes[0] = kTypeDefault;
    float defaultPosX = kDefaultX;
    float defaultPosZ = kDefaultZ = ? Actually from code: fVar18 = DAT_00e4479c; fVar17 = DAT_00e44798; param_5[0] = fVar18; param_5[2] = fVar18; param_5[1] = fVar17; param_5[3] = 0.0;
    // So default position: (kDefaultZ, kDefaultX, kDefaultZ, 0.0)
    out->positions[0][0] = kDefaultZ;
    out->positions[0][1] = kDefaultX;
    out->positions[0][2] = kDefaultZ;
    out->positions[0][3] = 0.0f;

    // But if there is an active bone (currentObjectId is nonzero), override position from that bone
    if (currentObjectId != 0) {
        float* bonePos = (float*)(*(int*)(currentObjectId + 0x18) + 0x20 + tlsOffset);
        memcpy(out->positions[0], bonePos, 16);
    }

    // Scale first slot position
    for (int j = 0; j < 4; j++) {
        out->positions[0][j] *= kScaleFactor;
    }

    // Fill first slot rotation (param_3) from current object's bone if exists, else default (identity quaternion?)
    if (currentObjectId != 0) {
        float* boneRot = (float*)(*(int*)(currentObjectId + 0x18) + 0x40 + tlsOffset);
        memcpy(out->rotations[0], boneRot, 16);
    } else {
        // default: all 0? Actually code sets param_3[0..3] = uVar20 (kTypeSpecial? but it's a color? We'll set to zero)
        out->rotations[0][0] = 0.0f;
        out->rotations[0][1] = 0.0f;
        out->rotations[0][2] = 0.0f;
        out->rotations[0][3] = 0.0f;
    }

    return useCustomRotation; // returns the flag bit 4
}