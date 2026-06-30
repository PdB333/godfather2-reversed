// FUNC_NAME: WaypointData::initialize
// Function address: 0x00542570
// Role: Initialize a waypoint structure with position, target, and an extra parameter.
// Structure layout:
//   0x00: position (float x,y,z)
//   0x0C: padding (always 0)
//   0x10: target (float x,y,z)
//   0x1C: padding (always 0)
//   0x20: active flag (byte)
//   0x24: extraParam

struct Vector3 {
    float x, y, z;
};

class WaypointData {
public:
    Vector3 position;    // +0x00
    int pad1;            // +0x0C (always 0)
    Vector3 target;      // +0x10
    int pad2;            // +0x1C (always 0)
    bool active;         // +0x20 (byte)
    int extraParam;       // +0x24

    void __thiscall initialize(const Vector3* pos, const Vector3* tgt, int extra);
};

void __thiscall WaypointData::initialize(const Vector3* pos, const Vector3* tgt, int extra)
{
    // Set inactive initially while copying data
    active = false;
    extraParam = 0;

    // Copy position vector (3 floats) and zero pad
    position = *pos;
    pad1 = 0;

    // Copy target vector and zero pad
    target = *tgt;
    pad2 = 0;

    // Mark as active and store the extra parameter
    active = true;
    extraParam = extra;
}