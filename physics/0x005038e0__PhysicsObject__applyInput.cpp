// FUNC_NAME: PhysicsObject::applyInput
undefined4* __thiscall PhysicsObject::applyInput(undefined4* thisPtr, InputPacket* packet)
{
    int* piVar1;
    int iVar2;
    int iVar3;
    int in_EAX;
    int iVar4;
    int unaff_FS_OFFSET;
    Vec3 local_30;  // local_30 is a vector composed of local_30, local_2c, local_28
    float local_28;
    float local_24;
    float local_20;
    int local_14;   // some int used later

    FUN_00533cc0(); // unknown init/sync

    *thisPtr = &PTR_FUN_00e37ea0; // set vtable

    // Check some thread-local flag at offset 0xd of something (in_EAX)
    if (*(char*)(in_EAX + 0xd) == '\0')
    {
        // Get thread-local storage pointer
        iVar4 = **(int**)(unaff_FS_OFFSET + 0x2c);
        iVar2 = thisPtr[4]; // thisPtr->physicsState (sub-object)
        thisPtr[9] = packet; // store packet pointer
        iVar3 = *(int*)(iVar4 + 8); // some index/counter
        piVar1 = (int*)(iVar4 + 8);

        // Check bit 0 of packet->flags (offset 0x8)
        if ((*(byte*)(packet + 0x8) & 1) == 0)
        {
            // Absolute assignment
            *(float*)(iVar2 + 0x40 + iVar3) = (float)packet[0xb]; // packet->inputX
            *(float*)(thisPtr[4] + 0x44 + *piVar1) = (float)packet[0xc]; // packet->inputY
            *(float*)(thisPtr[4] + 0x48 + *piVar1) = (float)packet[0xd]; // packet->inputZ
        }
        else
        {
            // Accumulative (relative) mode
            *(float*)(iVar2 + 0x40 + iVar3) = (float)packet[0xb] + *(float*)(iVar2 + 0x40 + iVar3);
            *(float*)(thisPtr[4] + 0x44 + *piVar1) = (float)packet[0xc] + *(float*)(thisPtr[4] + 0x44 + *piVar1);
            *(float*)(thisPtr[4] + 0x48 + *piVar1) = (float)packet[0xd] + *(float*)(thisPtr[4] + 0x48 + *piVar1);
        }

        // Set a constant (likely identity quaternion w=1) at offset 0x4c
        *(float*)(thisPtr[4] + 0x4c + *piVar1) = DAT_00e2b1a4; // 1.0f

        // Scale another input vector by DAT_00e445c8 and store to physicsState + 0x10 + *piVar1
        FUN_0056b8a0(
            (float)packet[0xe] * DAT_00e445c8,
            (float)packet[0xf] * DAT_00e445c8,
            (float)packet[0x10] * DAT_00e445c8,
            thisPtr[4] + 0x10 + *piVar1
        );

        FUN_00533fb0(); // unknown post-processing

        thisPtr[10] = 0; // clear some flag (offset 0x28)

        iVar4 = FUN_005190e0(); // check some condition
        if (iVar4 != 0)
        {
            // Build a local struct/vector from packet
            local_20 = *(float*)&packet[0];  // packet->position.x
            float tmp1 = *(float*)&packet[1]; // packet->position.y
            local_1c = tmp1;                  // Not used later? Actually it's part of local_20 vector?
            // Reinterpreting locals: we have local_30, local_2c, local_28 as a 3-vec (input direction?)
            local_30 = *(Vec3*)&packet[10];   // packet->direction (offset 0x28?)
            local_28 = local_30.z;
            local_2c = local_30.y;
            local_14 = thisPtr[1]; // some pointer/ID

            // Check bit 1 of packet->flags
            if ((*(byte*)(packet + 0x8) & 2) != 0)
            {
                local_2c = packet[0x14]; // override y
                local_28 = packet[0x15]; // override z
            }

            local_24 = DAT_00e2b1a4; // 1.0f again

            // Call validation/collision function with addresses, and store result
            iVar4 = FUN_005196f0(
                &local_20,   // start position
                &local_30,   // end direction/offset
                thisPtr[4] + *piVar1 + 0x50, // some force buffer
                *(undefined4*)(*(int*)(local_14 + 0x10) + 0x20) // collision mask?
            );

            thisPtr[10] = iVar4; // store result

            if (iVar4 != 0)
            {
                // Success: store some additional data and return
                thisPtr[0xb] = packet[9]; // packet->someID
                thisPtr[0xc] = 0;
                return thisPtr;
            }
        }

        // If validation failed or not executed, set a flag
        *(uint*)(thisPtr[4] + *piVar1) |= 1; // mark dirty or invalid
    }

    return thisPtr;
}