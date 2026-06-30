// FUNC_NAME: PlayerActionHandler::handleCommand

#include <cstdint>

// ---------------------------------------------------------------------------
// 0x007617d0 - PlayerActionHandler::handleCommand
// ---------------------------------------------------------------------------
// Overrides InputHandler::handleCommand for cases 0x23-0x26 (button/LUA events?)
// Cases:
//   0x23 - Set a float parameter (e.g., health, timer)
//   0x24 - Reset state & clear a flag
//   0x25 - Trigger some action
//   0x26 - Facing direction check / proximity timer accumulate
//   default - forward to base InputHandler::handleCommand

int32_t __thiscall PlayerActionHandler::handleCommand(
    void* thisPtr,          // this
    uint32_t unkParam,      // param_2
    float deltaTime,        // param_3
    uint32_t unkParam2,     // param_4
    uint32_t commandId,     // param_5
    uint32_t unkParam3)     // param_6
{
    // Local stack vectors
    float vecA[3];   // local_18 (X,Y,Z) but Y unused
    float vecB[3];   // local_c, local_8, local_4 (dx,dy,dz)

    switch (commandId)
    {
    case 0x23:  // Set a float (e.g., health value, timer)
        FUN_00761780(deltaTime);           // likely sets a member float from param_3
        return 1;

    case 0x24:  // Reset / clear
        FUN_007165a0();                    // e.g., resetState()
        FUN_004abdd0(0x40000);             // e.g., clearFlag(0x40000) – maybe a bitfield
        return 1;

    case 0x25:  // Trigger immediate action
        FUN_00760b80();                    // e.g., performAction()
        break;                             // fall through to return 1

    case 0x26:  // Facing direction proximity / timer logic
        {
            // Global pointer to some manager (e.g., PlayerManager)
            void** g_manager = *(void***)(DAT_012233a0 + 4);
            if (g_manager != nullptr)
            {
                // Compare manager pointer to a known constant (0x1f30)
                if (g_manager == (void*)0x1f30)
                    return 0x1f01;   // return that constant (maybe an error code)

                // Get two objects from some global functions (e.g., getPlayer(), getTarget())
                int32_t objA = FUN_00471610();   // e.g., getSourceObject()
                int32_t objB = FUN_00471610();   // e.g., getTargetObject()

                // Read a facing direction value from the "this" object's child
                // +0x5c likely points to a character/transform struct
                float facingValue = *(float*)(*(int32_t*)(thisPtr + 0x5c) + 0x5a8);

                // Get forward vector components (two calls to different “get dir” helpers? decompilation artifact)
                double tempD;
                tempD = (double)facingValue;
                FUN_00b99fcb();   // might be getForwardX() etc.
                vecA[0] = (float)tempD;

                tempD = (double)facingValue;
                FUN_00b99e20();   // might be getForwardZ()
                vecA[2] = (float)tempD;

                vecA[1] = 0.0f;  // Y component unused?

                // Vector from objA to objB
                vecB[0] = *(float*)(objB + 0x30) - *(float*)(objA + 0x30);
                vecB[1] = *(float*)(objB + 0x34) - *(float*)(objA + 0x34);
                vecB[2] = *(float*)(objB + 0x38) - *(float*)(objA + 0x38);

                // Normalize both vectors (dot product with themselves)
                FUN_0043a210(vecA, vecA);   // normalize vecA
                FUN_0043a210(vecB, vecB);   // normalize vecB

                // Dot product to determine if facing the target
                float dot = vecA[0]*vecB[0] + vecA[1]*vecB[1] + vecA[2]*vecB[2];
                if ((double)dot < DAT_00d654a8)   // threshold (e.g., cos of max angle)
                {
                    // Not facing target – reset timer
                    *(uint32_t*)(thisPtr + 0xb0) = 0;  // accumulated time (seconds)
                    return 1;
                }

                // If accumulated time exceeds a maximum
                if (*(float*)(thisPtr + 0xb0) > _DAT_00e51b20)   // max duration
                {
                    FUN_005ff860();   // trigger some event (e.g., start action)
                    *(int32_t*)(thisPtr + 0xb4) += 1;  // increment trigger count
                    *(uint32_t*)(thisPtr + 0xb0) = 0;  // reset timer
                }

                // Accumulate delta time
                *(float*)(thisPtr + 0xb0) += deltaTime;
                return 1;
            }
        }
        break;  // if g_manager is null, fall through

    default:
        // Forward to base InputHandler::handleCommand
        return FUN_0073e610(unkParam, deltaTime, unkParam2, commandId, unkParam3);
    }

    return 1;
}