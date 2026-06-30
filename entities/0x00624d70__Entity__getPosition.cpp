// FUNC_NAME: Entity::getPosition
// Address: 0x00624d70
// Role: Retrieves the entity's position vector via virtual function dispatch. The virtual function (vtable+4) writes the result into the provided output buffer.

// Assuming a simple 3D vector structure
struct Vector3 {
    float x;
    float y;
    float z;
};

// Global vtable pointer (base address of class's virtual function table)
// DAT_012234ac: likely points to the vtable for Entity or its base class
extern int* gEntityVTable; // actually DAT_012234ac

void Entity::getPosition(Vector3& out) const
{
    // Zero-initialize the output buffer before calling the virtual function
    out.x = 0.0f;
    out.y = 0.0f;
    out.z = 0.0f;

    // Call the second virtual function (offset 4 from vtable start)
    // The function writes the position directly into 'out'
    (*(void (__thiscall**)(const Entity*, Vector3*))(
        *((int*)gEntityVTable) + 4)
    )(this, &out);
}