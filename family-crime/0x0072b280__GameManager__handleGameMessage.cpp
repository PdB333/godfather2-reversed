// FUNC_NAME: GameManager::handleGameMessage
// Function address: 0x0072b280
// Handles a game message/event, possibly for AI or mission logic.
// Checks a quad-word hash (4 ints at this+0x234c) for a non-default state.
// Copies time data from a global timer to a structure.
// Evaluates a message object (param_2) and potentially triggers actions.

void __thiscall GameManager::handleGameMessage(int thisPtr, int messagePtr)
{
    char boolResult;
    int handle;
    int iVar3;
    int iVar5;
    int* piVar6;
    int unaff_EBX;  // likely a global pointer (e.g., player controller)
    int iVar7;

    // Early processing of the message object
    FUN_007334f0(messagePtr);  // might be Message::process()

    // Check if the 4-int identifier (hash) at this+0x234c is non-zero
    // and not equal to a specific sentinel pattern
    if (((( *(int*)(thisPtr + 0x234c) != 0 ) ||
          ( *(int*)(thisPtr + 0x2350) != 0 ) ||
          ( *(int*)(thisPtr + 0x2354) != 0 ) ||
          ( *(int*)(thisPtr + 0x2358) != 0 )) &&
         (( *(int*)(thisPtr + 0x234c) != 0xBBDBADBA ||   // -0x45245246
           *(int*)(thisPtr + 0x2350) != 0xBEEFBEEF ||    // -0x41104111
           *(int*)(thisPtr + 0x2354) != 0xEAC15A55 ||    // -0x153ea5ab
           *(int*)(thisPtr + 0x2358) != 0x91100911 )))   // -0x6eeff6ef
    {
        // Get an object handle from the identifier and activate it
        handle = FUN_00446130((int*)(thisPtr + 0x234c), 0);  // likely createHandleOrGetObject
        FUN_0071d8a0(handle);  // activateObject, attach, etc.

        iVar5 = *(int*)(thisPtr + 0x235c);
        if ((iVar5 != 0) && (iVar5 != 0x48))
        {
            iVar3 = FUN_00471610();  // getCurrentTimeOrFrame()
            iVar5 = *(int*)(thisPtr + 0x235c);
            if (iVar5 == 0) {
                iVar5 = 0;
            } else {
                iVar5 = iVar5 - 0x48;  // adjust pointer to base of structure
            }
            // Copy time-related data (12 bytes) from global timer to structure
            *(undefined8*)(iVar5 + 0x130) = *(undefined8*)(iVar3 + 0x30);
            *(undefined4*)(iVar5 + 0x138) = *(undefined4*)(iVar3 + 0x38);
        }
    }

    // Process the message object's internal structure
    iVar5 = *(int*)(messagePtr + 0xC);
    if ((iVar5 != 0) && (iVar5 != 0x48))
    {
        iVar7 = *(int*)(messagePtr + 0xC);
        if (iVar7 == 0) {
            piVar6 = (int*)0;
        } else {
            piVar6 = (int*)(iVar7 - 0x48);
        }
        // Call a virtual method on the substructure (at vtable offset 0x10)
        // with a hash and address of messagePtr as arguments
        boolResult = (**(code**)(*piVar6 + 0x10))(0x55859efa, &messagePtr);
        if ((boolResult != 0) && (unaff_EBX != 0))
        {
            iVar7 = *(int*)(unaff_EBX + 0x1ED4);
            iVar3 = FUN_00806440();  // getCurrentGameMode()
            iVar5 = *(int*)(thisPtr + 0x1B40);
            iVar4 = FUN_00806440();
            if ((iVar7 != iVar5) &&
                ((iVar5 != 0x637B907 && (iVar3 == 3)) && (iVar4 == 3)))
            {
                // Log event with hash 0x3BB7CCD2
                FUN_008934e0(0x3BB7CCD2, &stack0xFFFFFFFC);
                // Destroy the object referenced by iVar7 and remove from camera
                FUN_006ebfd0(iVar7, 0);   // maybe deleteObject
                FUN_008c0e60(iVar7, 0);   // maybe removeFromRenderList
            }
        }
    }
    return;
}