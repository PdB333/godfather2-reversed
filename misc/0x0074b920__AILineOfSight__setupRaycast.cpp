// FUNC_NAME: AILineOfSight::setupRaycast
// Address: 0x0074b920
// Role: Initializes a line-of-sight ray from a source position to a target position, computes distance and an interpolated endpoint.
// Called by FUN_0074be10 (likely a higher-level LOS update)

void __thiscall AILineOfSight::setupRaycast(float* sourcePos, float* targetPos)
{
    float distance;
    float diffVec[3];
    float normalizedDiff[3]; // same storage as diffVec after normalization
    float someScale = DAT_00d5780c;   // global scale factor (e.g., game unit conversion)
    // local_cc also = someScale, but unused beyond initial read

    // Initialize collision/raycast query with source and target, flags 0x40002 (probably dynamic + static), mask 0x80, and zero padding
    FUN_00542650(sourcePos, targetPos, 0x40002, 0x80, 0, 0);

    // Zero out some temporary flags (likely unused)
    local_70 = 0;
    local_80 = 0;
    // Set invalid/initial sentinel values
    local_ac = 0xffffffff;
    local_a0 = 0xffffffff;

    // Set up a vtable pointer or function table for internal raycast object
    local_d0 = &PTR_FUN_00e32a8c;   // likely a vtable for an internal struct
    // Initialize internal raycast state (local_60) using the provided table and local variables
    FUN_009e5ed0(local_60, &local_d0);

    // Mark that this line-of-sight is active (has a target)
    this->active = 1;   // +0x70

    // Compute Euclidean distance between source and target, scaled by global factor
    float dx = targetPos[0] - sourcePos[0];
    float dy = targetPos[1] - sourcePos[1];
    float dz = targetPos[2] - sourcePos[2];
    distance = sqrtf(dx*dx + dy*dy + dz*dz) * someScale;
    this->distance = distance;   // +0x8c

    // Copy direction vector (probably from internal raycast initialization)
    this->direction[0] = local_c0;   // +0x80
    this->direction[1] = local_bc;   // +0x84
    this->direction[2] = local_b8;   // +0x88

    // Compute the difference vector (target - source)
    diffVec[0] = targetPos[0] - sourcePos[0];
    diffVec[1] = targetPos[1] - sourcePos[1];
    diffVec[2] = targetPos[2] - sourcePos[2];
    // Zero padding for normalization call
    local_d4 = 0;

    // Normalize the difference vector (in-place)
    FUN_0056afa0(diffVec, diffVec);   // normalize to unit vector

    // Compute the interpolated endpoint: source + (normalized vector) * distance
    // (since distance = actual length * someScale, this yields a point beyond the original target if someScale>1)
    this->endpoint[0] = diffVec[0] * distance + sourcePos[0];   // +0x74
    this->endpoint[1] = diffVec[1] * distance + sourcePos[1];   // +0x78
    this->endpoint[2] = diffVec[2] * distance + sourcePos[2];   // +0x7c
}