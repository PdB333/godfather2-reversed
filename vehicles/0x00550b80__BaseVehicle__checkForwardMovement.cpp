// FUNC_NAME: BaseVehicle::checkForwardMovement
bool BaseVehicle::checkForwardMovement(void)
{
    // This function checks if the vehicle's velocity projected onto its forward direction
    // is above a threshold. If so, it likely performs a raycast to check if forward path is clear.
    // Returns true if movement is valid (dot product < threshold? Actually < means too slow?
    // Or it's checking if dot product is less than threshold, meaning not aligned? Wait:
    // If dot(v, dir) < threshold, then we go into the branch that returns true if raycast fails.
    // So probably threshold is a minimum speed: if velocity.forward < threshold, then no movement.
    // But the condition: if (dot < threshold) then do raycast and return local_20==0;
    // So if speed low, we attempt something? That seems reversed. Maybe it's checking if 
    // the dot product is *greater* than threshold? The decompiled shows <, so maybe 
    // threshold is a small negative or zero, and if dot is less (more negative), it's backward?
    // Or maybe it's checking if the dot product with the negative forward? Unclear.
    // For now, assume threshold is minimum speed, and we proceed only if speed is below that?
    // Let's keep the logic as is.

    // Field offsets (relative to this):
    // +0x40: velocity X
    // +0x44: velocity Y
    // +0x48: velocity Z
    // +0x90: forward direction X
    // +0x94: forward direction Y
    // +0x98: forward direction Z
    // +0xAC: speed threshold (scalar)

    // Note: In EARS engine, vectors are often stored as (x,y,z) with no padding.
    float velocityX = *(float *)((int)this + 0x40);
    float velocityY = *(float *)((int)this + 0x44);
    float velocityZ = *(float *)((int)this + 0x48);
    float forwardX  = *(float *)((int)this + 0x90);
    float forwardY  = *(float *)((int)this + 0x94);
    float forwardZ  = *(float *)((int)this + 0x98);
    float threshold = *(float *)((int)this + 0xAC);

    // Dot product of velocity and forward direction
    float forwardSpeed = velocityX * forwardX + velocityY * forwardY + velocityZ * forwardZ;

    if (forwardSpeed < threshold) {
        // Prepare raycast or query parameters
        struct RaycastInput {
            int key;          // offset 0? - maybe some id
            int bitfield;     // offset 4? - 0xffffffff means ignore?
            int layer;        // offset 8? - 0xffffffff means all?
            int flags;        // offset 12? - 0 initially
        } rayInput;

        // Set up raycast input with default values
        rayInput.key = 0;                // local_30
        rayInput.bitfield = 0xffffffff;   // local_5c - maybe "ignore self" flag
        rayInput.layer = 0xffffffff;      // local_50 - maybe "all layers"
        rayInput.flags = DAT_00e2b1a4;    // local_60 - some constant from data section

        // Output for raycast - 16 bytes buffer (local_70)
        RaycastOutput rayOutput; // size 16? We'll define as unknown.

        // Call raycast function, passing address of rayOutput
        bool hadCollision = FUN_00550c50(&rayOutput); // local_20 becomes 0 if no collision?

        // Returns true if no collision (local_20 == 0)
        return hadCollision == false;
    }
    else {
        return false;
    }
}