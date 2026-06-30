// FUNC_NAME: CharacterPoseManager::getCurrentPoses
// Address: 0x00713d40
// Role: Retrieves two blended pose transforms (position/orientation) for the character,
// avoiding recomputation if already computed in the current frame. Handles two code
// paths: one for normal animation blending and one for a specific state (e.g., car or cover).

void __thiscall CharacterPoseManager::getCurrentPoses(
    void* thisPtr,
    Vector3* outPos,         // param_2: pointer to first output (12 bytes)
    Vector3* outDir)         // param_3: pointer to second output (12 bytes)
{
    // Offsets on 'this':
    // +0x10  : m_pOwner (pointer to owning entity/character state)
    // +0xB0  : m_poseA (12 bytes, e.g., position)
    // +0xB8  : m_poseA_extra (4 bytes, part of struct)
    // +0xBC  : m_poseB (12 bytes, e.g., direction)
    // +0xC4  : m_poseB_extra (4 bytes)
    // +0xC8  : m_lastFrameCounter (int)

    int currentFrame = DAT_01205224; // global frame counter (likely GameManager::m_frame)
    void* owner = *(void**)((int)thisPtr + 0x10);

    // Skip recomputation if already done this frame or if bit 25 of owner flags is set
    if (*(int*)((int)thisPtr + 0xC8) == currentFrame ||
        ((*(uint*)((int)owner + 0x1F58) >> 0x19) & 1) != 0)
    {
        goto RETURN;
    }

    // Check if bit 14 of owner flags is clear OR the animation state pointer is null
    if (((*(uint*)((int)owner + 0x8E4) >> 0xE) & 1) == 0 ||
        *(int*)((int)owner + 0x21DC) == 0)
    {
        // Path 1: Normal animation blend
        FUN_007f7ed0((void*)((int)thisPtr + 0xB0)); // likely reset/init m_poseA

        uint* pSomeTable = *(uint**)((int)owner + 0x6E0); // owner+0x6E0? Actually it's (int*)(owner)[0x1B8] (index 0x1B8 = 440 = 0x1B8*4 = 0x6E0)
        uint blendValue = pSomeTable[0]; // value from vtable index 0x1B8 (maybe blend weight)
        if ((blendValue & 0xFFFFFFFC) == 0) // aligned? zero?
        {
            goto BLEND_DEFAULT;
        }

        // Local struct for vtable call
        Vector3 localVec1, localVec2, localVec3;
        localVec1.x = 0.0f; localVec1.y = 0.0f; localVec1.z = 0.0f;
        localVec2.x = 0.0f; localVec2.y = 0.0f; localVec2.z = 0.0f;
        localVec3.x = 0.0f; localVec3.y = 0.0f; localVec3.z = 0.0f;
        // Unknown constant (likely identity rotation)
        float identityQuat = *(float*)&DAT_00d5780c; // maybe 1.0f for quaternion w?

        // Virtual call: vtable offset 0x90 (likely getBlendTransforms)
        typedef void (*GetBlendFunc)(void*, void* out1, void* out2, void* out3, uint blendInfo);
        GetBlendFunc getBlend = (GetBlendFunc)(*(int*)(*(int*)owner + 0x90));
        getBlend(owner, &localVec1, &localVec2, &localVec3, blendValue);

        // Additional constants for the second blend
        uint const1 = DAT_00d619e0; // possibly time or weight
        uint const2 = DAT_00d619c0;
        uint const3 = DAT_00d619c8;
        uint const4 = 0;
        uint const5 = 0;
        uint const6 = 0;
        // ... many locals from global data

        // Call a blending function (FUN_00712b40) to compute final pose
        void* blendResult = FUN_00712b40(/*local structs*/); // returns some struct
        // Copy result to m_poseB
        *(Vector3*)((int)thisPtr + 0xBC) = *(Vector3*)blendResult;
        *(float*)((int)thisPtr + 0xC8) = *(float*)((int)blendResult + 8); // extra 4 bytes
    }
    else
    {
        // Path 2: Special state (e.g., car, cover) - direct blend from owner's animation state
        void* animState = *(void**)((int)owner + 0x21DC); // animation state pointer
        if (*(char*)((int)animState + 0x88) == 8) // specific animation type?
        {
            int r = rand();
            int val = 1;
            if ((float)r <= *(float*)&DAT_00d5c458) // threshold
                val = 2;
            void* randomPose = FUN_006e5dd0(val); // generate random pose?
            // Copy random pose into m_poseA
            *(Vector3*)((int)thisPtr + 0xB0) = *(Vector3*)randomPose;
            *(float*)((int)thisPtr + 0xB8) = *(float*)((int)randomPose + 8);
        }
        else
        {
            void* defaultPose = FUN_006e5dc0(); // get default pose
            *(Vector3*)((int)thisPtr + 0xB0) = *(Vector3*)defaultPose;
            *(float*)((int)thisPtr + 0xB8) = *(float*)((int)defaultPose + 8);
        }

BLEND_DEFAULT:
        // Get global time/update data (FUN_00471610 likely returns GameManager)
        void* gameManager = FUN_00471610();
        // Read offset 0x20 and 0x28 from gameManager (e.g., current pose offsets)
        *(Vector3*)((int)thisPtr + 0xBC) = *(Vector3*)((int)gameManager + 0x20);
        *(float*)((int)thisPtr + 0xC4) = *(float*)((int)gameManager + 0x28);
    }

    // Store current frame to avoid recomputation
    *(int*)((int)thisPtr + 0xC8) = currentFrame;

RETURN:
    // Output the stored poses
    *outPos = *(Vector3*)((int)thisPtr + 0xB0);
    *(float*)((int)outPos + 8) = *(float*)((int)thisPtr + 0xB8);
    *outDir = *(Vector3*)((int)thisPtr + 0xBC);
    *(float*)((int)outDir + 8) = *(float*)((int)thisPtr + 0xC4);
}