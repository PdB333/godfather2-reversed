// FUNC_NAME: Entity::updateVisibilityFlag
// Function address: 0x00763460
// Identified role: Updates a visibility/contact flag at +0xe8 based on a dot product test between positions and some direction vectors.
// The function checks if a state derived from this->+0x58->+0x2014 is a valid non-zero value not equal to 0x48.
// If valid, it retrieves two transforms (positions) and three additional vectors, computes a dot product, and sets/clears bit 7 (0x80) of the flags at +0xe8.

int __fastcall Entity::updateVisibilityFlag(int thisObj)
{
    int state;
    int ptrA;  // first transform pointer
    int ptrB;  // second transform pointer
    float posA_x, posA_y, posA_z;  // position from ptrB
    float posB_x, posB_y, posB_z;  // position from ptrA
    float* dirVecX;  // pointer to first float (x component of some direction)
    int dirVecY;     // pointer to struct used with offset +4
    int dirVecZ;     // pointer to struct used with offset +8
    float dx, dy, dz;
    float dot;

    // +0x58 points to a manager (e.g., WorldManager, CameraManager)
    // +0x2014 is a large offset within that manager, possibly a state or handle
    state = *(int *)(*(int *)(thisObj + 0x58) + 0x2014);
    if ((state != 0) && (state != 0x48))
    {
        // GET_TRANSFORM_POINTER (FUN_00471610) – returns a pointer to an object with a position at +0x30
        ptrA = FUN_00471610();   // first transform (e.g., camera)
        ptrB = FUN_00471610();   // second transform (e.g., this entity)

        posA_x = *(float *)(ptrB + 0x30);  // x from second transform
        posA_y = *(float *)(ptrB + 0x34);  // y
        posA_z = *(float *)(ptrB + 0x38);  // z

        posB_x = *(float *)(ptrA + 0x30);  // x from first transform
        posB_y = *(float *)(ptrA + 0x34);
        posB_z = *(float *)(ptrA + 0x38);

        // Three more GET_TRANSFORM_POINTER calls – likely for direction vectors
        dirVecX = (float *)FUN_00471610();   // pointer to a float (maybe x of normal/forward)
        dirVecY = FUN_00471610();            // used with offset +4 (maybe y component)
        dirVecZ = FUN_00471610();            // used with offset +8 (maybe z component)

        dx = posA_x - posB_x;
        dy = posA_y - posB_y;
        dz = posA_z - posB_z;

        // Dot product with a permuted combination of the three direction components
        dot = *(float *)(dirVecY + 4) * dy   // a*dy
            + (*dirVecX) * dx                  // b*dx
            + *(float *)(dirVecZ + 8) * dz;   // c*dz

        if (dot < 0.0f)
        {
            *(unsigned int *)(thisObj + 0xe8) |= 0x80;   // set visible/contact flag
            return 1;
        }
        else
        {
            *(unsigned int *)(thisObj + 0xe8) &= 0xFFFFFF7F;  // clear flag
            return 1;
        }
    }
    *(unsigned int *)(thisObj + 0xe8) &= 0xFFFFFF7F;  // clear flag on invalid state
    return 0;
}