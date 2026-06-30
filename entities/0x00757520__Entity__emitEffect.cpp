// FUNC_NAME: Entity::emitEffect
//
// Function address: 0x00757520
// Role: Copies two 3-component vectors from input parameters and passes them to an engine function,
// presumably to emit an effect (audio/visual) at a position with direction/orientation.
// The object at `this` has a pointer at offset +0xAC (likely to a sound/effect manager).

void Entity::emitEffect(float *pVec1, float *pVec2) // __thiscall
{
    // Local vector storage (copy of input vectors)
    float local_vec1[3];
    float local_vec2[3];

    // Copy first 3‑float vector
    local_vec1[0] = pVec1[0];
    local_vec1[1] = pVec1[1];
    local_vec1[2] = pVec1[2];

    // Copy second 3‑float vector
    local_vec2[0] = pVec2[0];
    local_vec2[1] = pVec2[1];
    local_vec2[2] = pVec2[2];

    // Call engine effect function
    // First argument: pointer from this+0xAC (e.g., a sound/effect manager)
    // Remaining: two vectors, flags (0x40102, 0x20001), and additional parameters
    FUN_009a7aa0(
        *(int*)(this + 0xAC),                  // +0xAC: manager pointer
        local_vec1,
        local_vec2,
        0x40102,                                // effect type flags
        0x20001,                                // sub‑type flags
        0,                                      // ?
        0,                                      // ?
        1,                                      // bool (true)
        0,                                      // ?
        0                                       // ?
    );
}