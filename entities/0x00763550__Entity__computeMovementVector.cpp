// FUNC_NAME: Entity::computeMovementVector
void __thiscall Entity::computeMovementVector(int *this, int *inputState, MovementOutput *output)
{
    float *velocity; // points to output->velocity (offset 12)
    int *inp; // inputState copy
    MovementOutput *out; // output copy
    char valid;
    int global;

    out = output;
    inp = inputState;
    if (inputState != (int *)0x0) {
        // Store the input pointer for later use
        *(int **)((int)output + 0x1c) = inputState;
        // Clear output->heading (offset 24)
        *(undefined4 *)(output + 3) = 0;

        // Copy current world transformation? (8 bytes at offset 0 and 4 at offset 8)
        global = FUN_00471610(); // get some global object pointer (likely PhysicsManager or similar)
        *output = *(undefined8 *)(global + 0x30); // copy two floats (maybe position or orientation)
        *(undefined4 *)(output + 1) = *(undefined4 *)(global + 0x38); // copy third float

        // Initialize velocity to zero
        velocity = (float *)((int)output + 0xc);
        *(undefined4 *)((int)output + 0x14) = 0; // velocity.z (offset 20)
        *(undefined4 *)(output + 2) = 0; // velocity.y (offset 16)
        *velocity = 0.0; // velocity.x (offset 12)

        inp = (int *)0x0;
        // Check if inputState has a specific flag (0x55859efa)
        valid = (**(code **)(*inputState + 0x10))(0x55859efa, &inp);
        if ((valid != '\0') && (this != (int *)0x0)) {
            // Get heading from this object via vtable (offset 0x2c4)
            float heading = (float10)(**(code **)(*this + 0x2c4))();
            *(float *)(output + 3) = heading; // store heading at output+24

            // Check a global game state flag (bit 5 of some flag)
            if ((*(uint *)(*(int *)(unaff_EBP + 0x58) + 0x8e8) >> 5 & 1) != 0) {
                // this[0x16a] is the current angle (likely from input or entity)
                float angle = (float)this[0x16a];
                double dAngle = (double)angle;
                FUN_00b99fcb(); // probably cosf
                *velocity = (float)dAngle; // velocity.x = cos(angle)
                dAngle = (double)angle;
                FUN_00b99e20(); // probably sinf
                *(float *)((int)output + 0x14) = (float)dAngle; // velocity.z = sin(angle)
                *(undefined4 *)(output + 2) = 0; // velocity.y = 0

                // Normalize the velocity vector (now (cos,0,sin))
                FUN_0043a210(velocity, velocity);

                // this[0x158] is the speed scalar
                float speed = (float)this[0x158];
                if (speed < 0.0) {
                    speed = 0.0;
                }
                // Scale velocity by speed
                *velocity = *velocity * speed;
                *(float *)(output + 2) = *(float *)(output + 2) * speed; // velocity.y
                *(float *)((int)output + 0x14) = *(float *)((int)output + 0x14) * speed; // velocity.z
                return;
            }
        }
        // Fallback: it seems the velocity pointer is passed to a cleanup/release function in inputState
        (**(code **)(*inputState + 0x4c))(velocity);
    }
}