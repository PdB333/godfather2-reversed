// FUNC_NAME: Trajectory::Initialize
// Address: 0x0054e530
// Reconstructed C++ for The Godfather 2 (2008, EA EARS engine)

void __thiscall Trajectory::Initialize(int thisPtr, int parentSceneNode, int emitterType1, int emitterType2,
                                       float param5, float param6, const TrajectoryData* data,
                                       int instanceId, unsigned char param9)
{
    // Offset definitions for the Trajectory class
    // +0x14: int32   m_meshIndex;          (0 if uninitialized)
    // +0x18: void*    m_pChild1;            (primary child effect object)
    // +0x1c: void*    m_pChild2;            (secondary child effect object)
    // +0x20: void*    m_pChild3;            (tertiary child effect object)
    // +0x30: uint8    m_flags0;              (clear at end)
    // +0x31: uint8    m_flags1;              (clear at end)
    // +0x68..+0x7c:  float[6] m_unknownFloats; (zeroed)
    // +0x80: float    m_positionMagnitude;
    // +0x84: float    m_directionMagnitude;
    // +0x88: float    m_angularMagnitude;
    // +0x90..+0x9c:  float[4] m_direction;   (normalized vector with extra component)
    // +0xd4: int32    m_instanceId;
    // +0xbc: ???     m_someBufferEntry;
    // +0xc0: Trajectory* m_selfPointer;
    // +0xe8: int32    m_clearFlag;

    // Release existing child objects if any
    if (*(int*)(thisPtr + 0x18) != 0) {
        FUN_009e7530(*(int*)(thisPtr + 0x18)); // releaseChild
    }
    *(int*)(thisPtr + 0x18) = 0;

    // Release child2 and child3 if they exist
    if (*(int*)(thisPtr + 0x1c) != 0) {
        int* refCountPtr = *(int**)(*(int*)(thisPtr + 0x1c) + 0x10);
        if (*(short*)(refCountPtr + 1) != 0) {
            *(short*)((int)refCountPtr + 6) = *(short*)((int)refCountPtr + 6) - 1;
            if (*(short*)((int)refCountPtr + 6) == 0) {
                (**(code**)*refCountPtr)(1); // destructor?
            }
        }
        FUN_009f01a0(); // release generic
    }
    if (*(int*)(thisPtr + 0x20) != 0) {
        int* refCountPtr = *(int**)(*(int*)(thisPtr + 0x20) + 0x10);
        if (*(short*)(refCountPtr + 1) != 0) {
            *(short*)((int)refCountPtr + 6) = *(short*)((int)refCountPtr + 6) - 1;
            if (*(short*)((int)refCountPtr + 6) == 0) {
                (**(code**)*refCountPtr)(1);
            }
        }
        FUN_009f01a0();
    }

    // Extract direction and normalize it
    float dirX = data->direction[0];   // param_7[4]
    float dirY = data->direction[1];   // param_7[5]
    float dirZ = data->direction[2];   // param_7[6]
    *(float*)(thisPtr + 0x90) = dirX;
    *(float*)(thisPtr + 0x94) = dirY;
    *(float*)(thisPtr + 0x98) = dirZ;
    *(float*)(thisPtr + 0x9c) = 1.0f;  // DAT_00e2b1a4

    float dx = *(float*)(thisPtr + 0x90);
    float dy = *(float*)(thisPtr + 0x94);
    float dz = *(float*)(thisPtr + 0x98);
    float dirLen = sqrt(dx*dx + dy*dy + dz*dz);
    float invDirLen = 1.0f / dirLen;   // DAT_00e2b1a4 / dirLen
    *(float*)(thisPtr + 0x90) = dx * invDirLen;
    *(float*)(thisPtr + 0x94) = dy * invDirLen;
    *(float*)(thisPtr + 0x98) = dz * invDirLen;
    *(float*)(thisPtr + 0x9c) = 1.0f * invDirLen;

    // Compute magnitudes from data
    float posX = data->position[0];
    float posY = data->position[1];
    float posZ = data->position[2];
    uint64_t quatPair = *(uint64_t*)(&data->quaternionLow); // data[0xc] as 2 floats
    float angularW = data->angularW; // data[0xe]

    float posMag = sqrt(posX*posX + posY*posY + posZ*posZ);
    float angMag = sqrt(data->angular[0]*data->angular[0] + data->angular[1]*data->angular[1] + data->angular[2]*data->angular[2]);

    *(float*)(thisPtr + 0x84) = dirLen;        // direction magnitude
    *(float*)(thisPtr + 0x80) = posMag;        // position magnitude
    *(float*)(thisPtr + 0x88) = angMag;        // angular magnitude

    *(int*)(thisPtr + 0xd4) = instanceId;

    // Create two child effect objects
    int child2 = FUN_0054dd80(parentSceneNode, emitterType1, param5, instanceId);
    int child3 = FUN_0054dd80(parentSceneNode, emitterType2, param6, instanceId);
    *(int*)(thisPtr + 0x1c) = child2;
    *(int*)(thisPtr + 0x20) = child3;
    *(int*)(thisPtr + 0x18) = child2; // primary child = child2

    FUN_009e7450(*(int*)(thisPtr + 0x1c)); // initialize child2

    // Build a descriptor struct on stack for mesh creation
    struct {
        uint32_t quatLow;     // +0x00
        uint32_t quatHigh;    // +0x04
        int32_t zeros1[2];    // +0x08, +0x0c
        float angularW;       // +0x10 (from data[0xe])
        float unknown[8];     // +0x14..+0x30? Actually layout varies from decomp.
        int32_t pChild1;      // +0x28? Offset from decomp? We'll follow code.
    } descriptor;

    // Fill descriptor from decompiled stack layout
    descriptor.pChild1 = *(int*)(thisPtr + 0x18);
    float someFloat = 1.0f;                     // DAT_00e2b1a4
    float scaledParam5 = *(float*)(thisPtr + 0x80) * param5;
    int constantID = 0;                         // DAT_00e2e780 (maybe 0)
    descriptor.quatLow = (uint32_t)(quatPair & 0xFFFFFFFF);
    descriptor.quatHigh = (uint32_t)(quatPair >> 32);
    // Zeros at offsets +0x08, +0x0c, +0x1c, etc.
    // From decomp: uStack_60, uStack_5c, uStack_58, uStack_54 = 0
    // uStack_30, uStack_2c, uStack_4c, uStack_64 = 0
    // uStack_28 = pChild1, uStack_50 = 1.0f, uStack_20 = scaledParam5, uStack_24 = constantID
    // uStack_7c = quatLow, uStack_70 = quatLow, uStack_78 = quatHigh, uStack_6c = quatHigh
    // Then negative direction:
    float negDirX = -*(float*)(thisPtr + 0x90);  // DAT_00e44564 is -1.0f
    float negDirY = -*(float*)(thisPtr + 0x94);
    float negDirZ = -*(float*)(thisPtr + 0x98);
    float negDirW = -*(float*)(thisPtr + 0x9c);
    // Stack offsets: fStack_40 = negDirX, fStack_3c = negDirY, fStack_38 = negDirZ, fStack_34 = negDirW
    // uStack_1c = 4, uStack_18 = param9, fStack_68 = angularW

    // The descriptor is used in a call to create mesh. We'll pass it as a struct.

    // If mesh index is 0, create new mesh
    if (*(int*)(thisPtr + 0x14) == 0) {
        TlsGetValue(*(int*)0x01139810); // thread-local storage (maybe pool context)
        int allocSize = 0xa0;
        int meshData = FUN_00aa2680(allocSize, 0x34); // allocate
        *(short*)(meshData + 4) = 0xa0; // size field?
        int meshIndex = FUN_00552280(&descriptor); // create mesh from descriptor
        *(int*)(thisPtr + 0x14) = meshIndex;

        // Add entry to a ring buffer residing in the mesh data
        int* buffer = *(int**)(meshIndex + 0x70);
        int bufferCount = *(int*)(meshIndex + 0x74);
        int bufferSize = *(int*)(meshIndex + 0x78) & 0x3FFFFFFF;
        if (bufferCount == bufferSize) {
            FUN_00aa4190((int*)(meshIndex + 0x70), 4); // grow buffer
            buffer = *(int**)(meshIndex + 0x70);
        }
        buffer[bufferCount] = thisPtr + 0xbc;
        *(int*)(meshIndex + 0x74) = bufferCount + 1;
        *(int*)(thisPtr + 0xc0) = thisPtr;
    } else {
        FUN_005523c0(); // update existing mesh
    }

    // Clear flags and fields
    *(unsigned char*)(thisPtr + 0x31) = 0;
    *(unsigned char*)(thisPtr + 0x30) = 0;
    *(int*)(thisPtr + 0x7c) = 0;
    *(int*)(thisPtr + 0x78) = 0;
    *(int*)(thisPtr + 0x74) = 0;
    *(int*)(thisPtr + 0x70) = 0;
    *(int*)(thisPtr + 0x6c) = 0;
    *(int*)(thisPtr + 0x68) = 0;
    *(int*)(thisPtr + 100) = 0; // +0x64?
    *(int*)(thisPtr + 0xe8) = 0;

    // Set instance ID on the primary child
    *(int*)(*(int*)(thisPtr + 0x18) + 0x2c) = *(int*)(thisPtr + 0xd4);
    FUN_009e9c50(*(int*)(thisPtr + 0x18), 1); // enable child
}

// Helper struct for input data (TrajectoryData)
struct TrajectoryData {
    float position[3];      // +0x00
    float padding0;         // +0x0c
    float direction[3];     // +0x10
    float padding1;         // +0x1c
    float angular[3];       // +0x20
    float padding2;         // +0x2c (?)
    float quaternionLow;    // +0x30
    float quaternionHigh;   // +0x34
    float angularW;         // +0x38
    // Total size: 0x3c = 60 bytes
};