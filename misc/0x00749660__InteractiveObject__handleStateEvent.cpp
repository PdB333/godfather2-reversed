// FUNC_NAME: InteractiveObject::handleStateEvent
// Address: 0x00749660
// This function appears to handle state transitions for an interactive object (door, container, etc.)
// It uses a switch on event ID (param_5 - 10) to process open, close, lock, unlock, and sound events.
// Class fields offset:
//   +0x00: vtable
//   +0x0c: some parameter (likely position/index)
//   +0x14: state flags (bit0: open, bit1: locked, bit2: interaction in progress, bit3: forced, bit4: available)
//   +0x15: pointer to associated object (e.g. door physics object)
//   +0x16: object type ID (0 = generic, 0x48 = special type like door)
//   +0x18: another parameter
//   +0x19: counter (used for opening animation?)
// The function calls vtable methods at offset 0x2c (playEvent?) and on the associated object.

undefined1 __thiscall InteractiveObject::handleStateEvent(int *thisObj, 
                                                         undefined4 param2, 
                                                         undefined4 param3, 
                                                         undefined4 param4, 
                                                         int eventId,          // event ID starting from 10
                                                         undefined4 param6)
{
    char boolResult;
    undefined1 defaultRet;
    undefined4 hashedArg;
    int intVar;
    int *piVar5;
    float10 floatVar;
    undefined4 soundId;

    defaultRet = 1; // default success

    // Event IDs are offset by -10
    switch (eventId - 10) {
        case 0: // open/activate
            // Play event (e.g. "open start") - hash: 0xd8ee28f4
            (*(code **)(*thisObj + 0x2c))(0xd8ee28f4, 1, 1, 0, 0x3f800000, 0x3f800000);

            // Check if associated object has a specific flag (bit 10 in field at +0x238)
            if (((uint)((int *)thisObj[0x15])[0x238] >> 10 & 1) != 0) {
                // Call method at vtable+0x260 on associated object
                (*(code **)(*(int *)thisObj[0x15] + 0x260))();
            }

            // Check if associated object has flag at +0x4a4 bit 6
            if ((*(uint *)(thisObj[0x15] + 0x4a4) >> 6 & 1) != 0) {
                thisObj[0x14] |= 8; // set forced flag (bit 3)
                // Call method with arguments (0,1) - vtable+0x290
                (*(code **)(*(int *)thisObj[0x15] + 0x290))(0, 1);
            }

            // If object type is set and not 0x48 (door type)
            if ((thisObj[0x16] != 0) && (thisObj[0x16] != 0x48)) {
                // Stop sound 0x14 (open loop?)
                FUN_007f63e0(0x14);

                // Check if object is locked (bit 1)
                if (((uint)thisObj[0x14] >> 1 & 1) == 0) {
                    // Play unlock sound
                    FUN_007f63e0(0x12);
                    soundId = 0;
                    hashedArg = FUN_006fbc40(0, 0);
                    // Play sound with hash 0xd9267de0 (unlock sound)
                    FUN_007f96a0(0xd9267de0, 0x75, hashedArg, soundId);
                }
                else {
                    // Play lock sound
                    FUN_007f63e0(0x13);
                    soundId = 0;
                    hashedArg = FUN_006fbc40(0, 0);
                    // Play sound with hash 0x940c64be (lock sound)
                    FUN_007f96a0(0x940c64be, 0x75, hashedArg, soundId);
                }
                FUN_006fbc70(); // cleanup
            }

            // If not already open (bit 0)
            if ((*(byte *)(thisObj + 0x14) & 1) == 0) {
                // Call function on associated object (likely open)
                FUN_006bea40(thisObj[0x15]);
                // Update global state (1 = open)
                FUN_009ae900(1);
                thisObj[0x14] |= 1; // set open flag
                return 1;
            }
            break;

        case 1: // close
            // If forced flag is set (bit 3)
            if (((uint)thisObj[0x14] >> 3 & 1) != 0) {
                thisObj[0x14] &= 0xfffffff7; // clear forced flag
                // Call method on associated object (close)
                (*(code **)(*(int *)thisObj[0x15] + 0x290))(1, 1);
                return 1;
            }
            break;

        default:
            // Default handler (possibly base class)
            defaultRet = FUN_004ac700(param2, param3, param4, eventId, param6);
            break;

        case 3: // opening animation step?
            intVar = *thisObj;
            hashedArg = FUN_007347e0(1, 0, 0, 0x3f800000, 0x3f800000);
            // Play event - hash 0x? (function modifies)
            (*(code **)(intVar + 0x2c))(hashedArg);
            thisObj[0x19]++; // increment counter
            return 1;

        case 4: // sound on close?
            if ((thisObj[0x16] != 0) && (thisObj[0x16] != 0x48)) {
                soundId = 0;
                // If locked, play lock sound
                if (((uint)thisObj[0x14] >> 1 & 1) != 0) {
                    hashedArg = FUN_006fbc40(0, 0);
                    FUN_007f96a0(0x99353a71, 0x75, hashedArg, soundId);
                } else {
                    // Play unlock sound
                    hashedArg = FUN_006fbc40(0, 0);
                    FUN_007f96a0(0xde4f5393, 0x75, hashedArg, soundId);
                }
                FUN_006fbc70();
                return 1;
            }
            break;

        case 5: // lock/unlock check
            if ((thisObj[0x16] != 0) && (thisObj[0x16] != 0x48)) {
                if (thisObj[0x16] == 0) {
                    intVar = 0;
                } else {
                    intVar = thisObj[0x16] - 0x48;
                }
                // Check if object is locked (hash 0x383225a1)
                intVar = FUN_006c9470(intVar, 0x383225a1);
                if (intVar != 0) {
                    thisObj[0x14] |= 2; // set locked flag
                    return 1;
                }
                thisObj[0x14] &= 0xfffffffd; // clear locked flag
                return 1;
            }
            break;

        case 6: // interaction check (e.g. for door open)
            // If object is not locked
            if (((uint)thisObj[0x14] >> 1 & 1) != 0) {
                // Check if object type is valid and not 0x48, and check if busy
                if (((thisObj[0x16] != 0) && (thisObj[0x16] != 0x48)) &&
                    (boolResult = FUN_007a8c50(0, thisObj[0x15]), boolResult != '\0')) {
                    thisObj[0x14] |= 4; // set interaction in progress
                    return 1;
                }
                // Get associated object
                piVar5 = (int *)FUN_006bc8b0(thisObj[0x15]);
                // Check if object is not explicitly asked (bit 0 in byte at +0x4A) and has capacity (method at vtable+0x1c with 0x100)
                if (((piVar5 != (int *)0x0) && ((*(byte *)((int)piVar5 + 0x4a) & 1) == 0)) &&
                    (boolResult = (**(code **)(*piVar5 + 0x1c))(0x100), boolResult != '\0')) {
                    thunk_FUN_009b1d10();
                    thisObj[0x14] |= 0x10; // set available flag
                    return 1;
                }
            }
            break;

        case 7: // close cleanup
            // If open
            if ((*(byte *)(thisObj + 0x14) & 1) != 0) {
                // Call function on associated object (close)
                FUN_006bea40(thisObj[0x15]);
                FUN_009ae900(0); // update global state (0 = closed)
                thisObj[0x14] &= 0xfffffffe; // clear open flag
            }
            // If object type is valid and not 0x48
            if ((thisObj[0x16] != 0) && (thisObj[0x16] != 0x48)) {
                // Start sound 0x14 (close loop?)
                FUN_007f6420(0x14);
                if (thisObj[0x16] == 0) {
                    intVar = 0;
                } else {
                    intVar = thisObj[0x16] - 0x48;
                }
                piVar5 = (int *)FUN_006bea40(intVar);
                if (piVar5 != (int *)0x0) {
                    intVar = *piVar5;
                    floatVar = (float10)(**(code **)(intVar + 0x2c))();
                    (**(code **)(intVar + 0x3c))((float)floatVar);
                }
            }
            FUN_007f6420(0x12); // stop sound 0x12
            FUN_007f6420(0x13); // stop sound 0x13
            return 1;

        case 8: // play sound event (hash 0x3667b832)
            (*(code **)(*thisObj + 0x2c))(0x3667b832, 1, 1, 0, 0x3f800000, 0x3f800000);
            return 1;

        case 9: // play sound event (hash 0x96f0caed)
            (*(code **)(*thisObj + 0x2c))(0x96f0caed, 1, 1, 0, 0x3f800000, 0x3f800000);
            return 1;

        case 10: // lock function on associated object
            FUN_00939620(thisObj[0x15], 0x40);
            return 1;

        case 11: // unlock function on associated object
            FUN_00939670(thisObj[0x15], 0x40);
            return 1;

        case 12: // toggle lock?
            FUN_009396c0(thisObj[0x15]);
            return 1;

        case 13: // set lock state from parameters
            FUN_00939760(thisObj[0x15], thisObj[0xc], thisObj[0x18]);
            return 1;

        case 14: // reset lock
            FUN_00939710(thisObj[0x15]);
            return 1;

        case 15: // some global reset
            FUN_00749070();
            return 1;
    }

    return defaultRet;
}