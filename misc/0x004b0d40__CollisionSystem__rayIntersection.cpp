// FUNC_NAME: CollisionSystem::rayIntersection

bool __fastcall CollisionSystem::rayIntersection(Vector3* param1)
{
    // this represents a direction vector (3 floats) or a transform?
    Vector3 local_d0;
    Vector3 local_cc;
    Vector3 local_c8;
    uint32_t local_ac;
    RayQueryStructure local_a0; // stack-allocated query struct
    void** local_80;            // function table pointer
    uint32_t local_7c;
    uint32_t local_60;
    uint32_t local_5c;
    uint32_t local_50;
    uint32_t local_30;
    int32_t local_20;           // result flag

    // Copy direction from this (first 3 floats)
    local_c0 = this->x;
    local_bc = this->y;
    local_b8 = this->z;

    // Copy origin from param1 (first 3 floats)
    local_d0 = param1->x;
    local_cc = param1->y;
    local_c8 = param1->z;

    // Encode pointer to query structure with allocation flag
    local_ac = (reinterpret_cast<uint32_t>(&local_a0) >> 2) | 0x40000000;

    // Initialize query structure
    // +0x00: collision mask type (0x3E0 = EARS_COLLISION_STATIC?)
    local_a0.collisionType = 0x3E0;
    // +0x04: another mask (0x3E2 = EARS_COLLISION_SPECIAL?)
    local_a0.subType = 0x3E2;
    // +0x08: flags (0x80000000 = high priority?)
    local_a0.flags = 0x80000000;
    // +0x0C: result code
    local_a0.resultCode = 0;
    // +0x10: distance?
    local_a0.distance = 0;

    // +0x14: enable hit detection
    local_b0 = 1; // bool

    // Set function pointer table to global collision handler
    local_80 = &PTR_FUN_00e32a8c;

    // Initialize global context values
    local_60 = DAT_00e2b1a4;
    local_30 = 0;
    local_7c = DAT_00e2b1a4;

    local_5c = 0xFFFFFFFF;
    local_50 = 0xFFFFFFFF;

    local_20 = 0;

    // Perform the actual ray intersection test
    FUN_009e5ed0(&local_d0, &local_80);

    return local_20 != 0;
}