// FUNC_NAME: Entity::initializePhysicsTransforms

void __fastcall Entity::initializePhysicsTransforms(float *matrixA, float *matrixB, void *entity, float *positionVec, float *velocityVec, uint32_t objectId)
{
    // Global identity/sentinel value (likely 1.0f or 0.0f)
    uint32_t identityValue = DAT_00e2b1a4;

    // Clear large animation state block at +0x49d00 (300KB sized area)
    *(uint32_t *)((char *)entity + 0x49d00) = 0;       // +0x49d00: animation state flags?
    *(uint16_t *)((char *)entity + 0x49d04) = 0;       // +0x49d04: animation sub-state
    *(uint16_t *)((char *)entity + 0x49d06) = 0;       // +0x49d06: padding
    *(uint16_t *)((char *)entity + 0x49d08) = 0;       // +0x49d08: animation timer?
    *(uint16_t *)((char *)entity + 0x49d0a) = 0;       // +0x49d0a: unknown
    *(uint16_t *)((char *)entity + 0x49d0c) = 0;       // +0x49d0c: unknown

    // Initialize transform-related fields (cluster at +0x18 to +0x19c)
    *(uint32_t *)((char *)entity + 0x18) = 0;          // +0x18: object ID or flags
    *(uint32_t *)((char *)entity + 0x60) = identityValue; // +0x60: identity/quaternion component
    *(uint32_t *)((char *)entity + 0x64) = 0;          // +0x64: translation x
    *(uint32_t *)((char *)entity + 0x68) = 0;          // +0x68: translation y
    *(uint32_t *)((char *)entity + 0x6c) = 0;          // +0x6c: translation z
    *(uint32_t *)((char *)entity + 0x70) = 0;          // +0x70: scale or rotation
    *(uint32_t *)((char *)entity + 0x74) = identityValue; // +0x74: identity
    *(uint32_t *)((char *)entity + 0x78) = 0;          // +0x78: ...
    *(uint32_t *)((char *)entity + 0x7c) = 0;
    *(uint32_t *)((char *)entity + 0x80) = 0;
    *(uint32_t *)((char *)entity + 0x84) = 0;
    *(uint32_t *)((char *)entity + 0x88) = identityValue;
    *(uint32_t *)((char *)entity + 0x8c) = 0;
    *(uint32_t *)((char *)entity + 0x90) = 0;
    *(uint32_t *)((char *)entity + 0x94) = 0;
    *(uint32_t *)((char *)entity + 0x98) = 0;
    *(uint32_t *)((char *)entity + 0x9c) = identityValue;

    // Copy position vector (4 floats) to +0xa0
    *(uint32_t *)((char *)entity + 0xa0) = *(uint32_t *)&positionVec[0];
    *(uint32_t *)((char *)entity + 0xa4) = *(uint32_t *)&positionVec[1];
    *(uint32_t *)((char *)entity + 0xa8) = *(uint32_t *)&positionVec[2];
    *(uint32_t *)((char *)entity + 0xac) = *(uint32_t *)&positionVec[3];

    // Copy velocity vector (4 floats) to +0xb0
    *(uint32_t *)((char *)entity + 0xb0) = *(uint32_t *)&velocityVec[0];
    *(uint32_t *)((char *)entity + 0xb4) = *(uint32_t *)&velocityVec[1];
    *(uint32_t *)((char *)entity + 0xb8) = *(uint32_t *)&velocityVec[2];
    *(uint32_t *)((char *)entity + 0xbc) = *(uint32_t *)&velocityVec[3];

    // Copy matrixB (16 floats) to +0xe0 (first 4x4 matrix, likely world transform)
    *(uint32_t *)((char *)entity + 0xe0) = *(uint32_t *)&matrixB[0];
    *(uint32_t *)((char *)entity + 0xe4) = *(uint32_t *)&matrixB[1];
    *(uint32_t *)((char *)entity + 0xe8) = *(uint32_t *)&matrixB[2];
    *(uint32_t *)((char *)entity + 0xec) = *(uint32_t *)&matrixB[3];
    *(uint32_t *)((char *)entity + 0xf0) = *(uint32_t *)&matrixB[4];
    *(uint32_t *)((char *)entity + 0xf4) = *(uint32_t *)&matrixB[5];
    *(uint32_t *)((char *)entity + 0xf8) = *(uint32_t *)&matrixB[6];
    *(uint32_t *)((char *)entity + 0xfc) = *(uint32_t *)&matrixB[7];
    *(uint32_t *)((char *)entity + 0x100) = *(uint32_t *)&matrixB[8];
    *(uint32_t *)((char *)entity + 0x104) = *(uint32_t *)&matrixB[9];
    *(uint32_t *)((char *)entity + 0x108) = *(uint32_t *)&matrixB[10];
    *(uint32_t *)((char *)entity + 0x10c) = *(uint32_t *)&matrixB[11];
    *(uint32_t *)((char *)entity + 0x110) = *(uint32_t *)&matrixB[12];
    *(uint32_t *)((char *)entity + 0x114) = *(uint32_t *)&matrixB[13];
    *(uint32_t *)((char *)entity + 0x118) = *(uint32_t *)&matrixB[14];
    *(uint32_t *)((char *)entity + 0x11c) = *(uint32_t *)&matrixB[15];

    // Copy matrixA (16 floats) to +0x120 (second 4x4 matrix, likely local/inverse)
    *(uint32_t *)((char *)entity + 0x120) = *(uint32_t *)&matrixA[0];
    *(uint32_t *)((char *)entity + 0x124) = *(uint32_t *)&matrixA[1];
    *(uint32_t *)((char *)entity + 0x128) = *(uint32_t *)&matrixA[2];
    *(uint32_t *)((char *)entity + 0x12c) = *(uint32_t *)&matrixA[3];
    *(uint32_t *)((char *)entity + 0x130) = *(uint32_t *)&matrixA[4];
    *(uint32_t *)((char *)entity + 0x134) = *(uint32_t *)&matrixA[5];
    *(uint32_t *)((char *)entity + 0x138) = *(uint32_t *)&matrixA[6];
    *(uint32_t *)((char *)entity + 0x13c) = *(uint32_t *)&matrixA[7];
    *(uint32_t *)((char *)entity + 0x140) = *(uint32_t *)&matrixA[8];
    *(uint32_t *)((char *)entity + 0x144) = *(uint32_t *)&matrixA[9];
    *(uint32_t *)((char *)entity + 0x148) = *(uint32_t *)&matrixA[10];
    *(uint32_t *)((char *)entity + 0x14c) = *(uint32_t *)&matrixA[11];
    *(uint32_t *)((char *)entity + 0x150) = *(uint32_t *)&matrixA[12];
    *(uint32_t *)((char *)entity + 0x154) = *(uint32_t *)&matrixA[13];
    *(uint32_t *)((char *)entity + 0x158) = *(uint32_t *)&matrixA[14];
    *(uint32_t *)((char *)entity + 0x15c) = *(uint32_t *)&matrixA[15];

    // Set additional identity/zero fields from +0x160 to +0x19c
    *(uint32_t *)((char *)entity + 0x160) = identityValue;
    *(uint32_t *)((char *)entity + 0x164) = 0;
    *(uint32_t *)((char *)entity + 0x168) = 0;
    *(uint32_t *)((char *)entity + 0x16c) = 0;
    *(uint32_t *)((char *)entity + 0x170) = 0;
    *(uint32_t *)((char *)entity + 0x174) = identityValue;
    *(uint32_t *)((char *)entity + 0x178) = 0;
    *(uint32_t *)((char *)entity + 0x17c) = 0;
    *(uint32_t *)((char *)entity + 0x180) = 0;
    *(uint32_t *)((char *)entity + 0x184) = 0;
    *(uint32_t *)((char *)entity + 0x188) = identityValue;
    *(uint32_t *)((char *)entity + 0x18c) = 0;
    *(uint32_t *)((char *)entity + 0x190) = 0;
    *(uint32_t *)((char *)entity + 0x194) = 0;
    *(uint32_t *)((char *)entity + 0x198) = 0;
    *(uint32_t *)((char *)entity + 0x19c) = identityValue;

    // Store object ID at +0x1c
    *(uint32_t *)((char *)entity + 0x1c) = objectId;
}