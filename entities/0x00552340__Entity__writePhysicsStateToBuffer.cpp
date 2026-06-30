// FUNC_NAME: Entity::writePhysicsStateToBuffer

#include <cstdint>

// Function at 0x00552340 – Writes physics state (position, rotation, velocity, flags) to an output buffer for network replication.
// Offsets (assuming "this" is an entity object):
//   this+0x10  : world position (4 floats)
//   this+0x30  : pointer to physics component
//   component+0x18: pointer to transform state
//   transformState+0x30: rotation quaternion (4 floats)
//   this+0x30,0x34,0x38: additional rotation data (e.g., local orientation)
//   this+0x50,0x54,0x58,0x5c,0x60: linear/angular velocity (5 floats)
//   this+0x94  : flags byte (e.g., airborne, grounded)

void Entity::writePhysicsStateToBuffer(void* outBuffer)
{
    // Retrieve transform state through two levels of indirection
    int physicsComponent = *(int*)(this + 0x30);
    int transformState   = *(int*)(physicsComponent + 0x18);

    float* dest = (float*)outBuffer;

    // Rotation quaternion (source: transformState+0x30..0x3C)
    dest[0] = *(float*)(transformState + 0x30);
    dest[1] = *(float*)(transformState + 0x34);
    dest[2] = *(float*)(transformState + 0x38);
    dest[3] = *(float*)(transformState + 0x3C);

    // World position (source: this+0x10..0x1C)
    dest[4] = *(float*)(this + 0x10);
    dest[5] = *(float*)(this + 0x14);
    dest[6] = *(float*)(this + 0x18);
    dest[7] = *(float*)(this + 0x1C);

    // Additional rotation data (source: this+0x30,0x34,0x38)
    dest[0x12] = *(float*)(this + 0x30);
    dest[8]    = *(float*)(this + 0x34);
    dest[9]    = *(float*)(this + 0x38);

    // Velocity data (source: this+0x50..0x60)
    dest[0x10] = *(float*)(this + 0x50);
    dest[0x11] = *(float*)(this + 0x54);
    dest[0x13] = *(float*)(this + 0x58);
    dest[0x14] = *(float*)(this + 0x5C);
    dest[0x15] = *(float*)(this + 0x60);

    // Flags byte (source: this+0x94) written at byte offset 0x58 from dest
    uint8_t* byteDest = (uint8_t*)(dest + 0x16); // equal to (uint8_t*)dest + 0x58
    *byteDest = *(uint8_t*)(this + 0x94);
}