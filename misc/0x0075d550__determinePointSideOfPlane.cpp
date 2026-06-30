// FUNC_NAME: determinePointSideOfPlane
// Address: 0x0075d550
// This function determines on which side of a plane (defined by two entity positions) a given point lies.
// It returns a packed value: low bit indicates side (1=front), high bytes encode a tag from the entity pointer.
// Offsets: +0x30 = position.x, +0x34 = position.y, +0x38 = position.z

int determinePointSideOfPlane(float* point) // point is a 3-element float array (x,y,z)
{
    // First call to getEntityPosition() likely returns pointer to player/camera entity
    int entityA = FUN_00471610(); // get pointer to entity A (e.g., player)
    int entityB = FUN_00471610(); // get pointer to entity B (e.g., enemy)

    // Compute vector from A to B
    float diffX = *(float*)(entityB + 0x30) - *(float*)(entityA + 0x30);
    float diffY = *(float*)(entityB + 0x34) - *(float*)(entityA + 0x34);
    float diffZ = *(float*)(entityB + 0x38) - *(float*)(entityA + 0x38);
    // Local dummy (unused)
    int dummy = 0;

    // Normalize the direction vector in-place
    FUN_0056afa0(&diffX, &diffX); // assumes (src, dst) or same pointer

    // Get another entity pointer (maybe the same as A, used as plane reference point)
    entityA = FUN_00471610(); // overwrites previous

    // Extract a tag from the entity pointer: shift address right by 8 bits, keep low 24 bits
    uint3 tag = (uint3)((uint)(entityA + 0x30) >> 8); // uint3 is a 3-byte unsigned int

    // Plane equation: dot(normal, point - referencePoint) < 0 => point is behind the plane
    // Reference point is entityA's position.
    float dot = diffX * (point[0] - *(float*)(entityA + 0x30)) +
                diffY * (point[1] - *(float*)(entityA + 0x34)) +
                diffZ * (point[2] - *(float*)(entityA + 0x38));

    if (dot < 0.0f) {
        // Point is on the negative side (e.g., behind)
        // Return tag with low byte set to 1
        return (int)((uint)tag << 8) | 1;
    }
    else {
        // Point is on the positive side (e.g., in front)
        // Return tag shifted left by 8 bits
        return (int)((uint)tag << 8);
    }
}