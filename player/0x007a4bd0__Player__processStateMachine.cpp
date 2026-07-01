// FUNC_NAME: Player::processStateMachine
void __thiscall Player::processStateMachine(int *thisPtr)
{
    char cVar1;
    int iVar2;
    int *piVar3;
    int stateIndex;
    float speed;
    float vecX;
    float vecY;
    float vecZ;
    float scalar0;
    float vec2X;
    float vec2Y;
    float resultX;
    float resultY;
    float resultZ;
    float otherFloat;
    char unknown[4];
    float finalFloat;

    // Check current state: +0xc30 is a pointer to some component (maybe action state)
    if ((thisPtr[0xc30] != 0) && (thisPtr[0xc30] != 0x48)) {
        // If not null and not a special value, exit early?
        FUN_007df690(); // unknown function, maybe log error
        return;
    }

    stateIndex = 0xb; // default state = 11

    // +0x1d3 is another component pointer (maybe movement or animation)
    if ((thisPtr[0x1d3] != 0) && (thisPtr[0x1d3] != 0x48)) {
        // Compute base pointer: component entries are 0x48 bytes apart?
        if (thisPtr[0x1d3] == 0) {
            iVar2 = 0;
        } else {
            iVar2 = thisPtr[0x1d3] - 0x48;
        }
        // +0x1ad is a byte field indicating a state
        if (*(char *)(iVar2 + 0x1ad) == '\x19') { // 25: maybe "running"
            stateIndex = 6;
        } else {
            if (thisPtr[0x1d3] == 0) {
                iVar2 = 0;
            } else {
                iVar2 = thisPtr[0x1d3] - 0x48;
            }
            if (*(char *)(iVar2 + 0x1ad) == '\x1a') { // 26: maybe "walking"
                stateIndex = 8;
            } else {
                if (thisPtr[0x1d3] == 0) {
                    iVar2 = 0;
                } else {
                    iVar2 = thisPtr[0x1d3] - 0x48;
                }
                if (*(char *)(iVar2 + 0x1ad) == '\x1b') { // 27: maybe "idle"
                    stateIndex = 7;
                }
            }
        }

        cVar1 = FUN_00481620(); // possibly isGamePaused
        if ((cVar1 != '\0') &&
            ((cVar1 = FUN_00481660(), cVar1 == '\0' || ((*(byte *)((int)thisPtr + 0x8e3) & 1) != 0)))) {
            // If not paused or flag set, perform action
            if (thisPtr[0x1d3] == 0) {
                iVar2 = 0;
            } else {
                iVar2 = thisPtr[0x1d3] - 0x48;
            }
            // Virtual call at +0x88: likely "preUpdate" or "reset"
            if ((*(int *)(iVar2 + 0x68) != 0) && (*(int *)(iVar2 + 0x68) != 0x48)) {
                if (thisPtr[0x1d3] == 0) {
                    piVar3 = (int *)0x0;
                } else {
                    piVar3 = (int *)(thisPtr[0x1d3] - 0x48);
                }
                (**(code **)(*piVar3 + 0x88))(); // vtable[0x88]
            }

            // Initialize vector to zero
            FUN_00424fb0(&scalar0, 0); // zeroes a float or vector? Possibly sets to identity
            FUN_0081e130(&vecX, 1, 0); // get direction? 1,0 arguments

            speed = DAT_00e52848 * vecX; // speed multiplier
            // Assume variables are organized as: vecX,vecY,vecZ; scalar0,vec2X,vec2Y; resultX,resultY,resultZ
            resultX = scalar0 + speed; // X component of new position
            vecY = DAT_00e52848 * vecY;
            vecZ = DAT_00e52848 * vecZ;
            resultY = vec2X + vecY;
            resultZ = vec2Y + vecZ;

            iVar2 = FUN_00471610(&scalar0, &resultX); // compute something (maybe angle or distance)
            FUN_004a08d0(unknown, iVar2 + 0x30); // set attribute or handle

            finalFloat = DAT_00e52844 + finalFloat; // add base offset

            if (thisPtr[0x1d3] == 0) {
                piVar3 = (int *)0x0;
            } else {
                piVar3 = (int *)(thisPtr[0x1d3] - 0x48);
            }
            // Virtual call at +0x1c: likely "updateTransform" or "move"
            (**(code **)(*piVar3 + 0x1c))(unknown);
        }
    }

    // Global update
    FUN_007f95c0();

    // Determine final state index
    if ((stateIndex == 0xb) || (stateIndex = FUN_00705ab0(stateIndex), stateIndex == 0)) {
        stateIndex = FUN_007057c0();
    }

    // Virtual call at offset 600 (0x258) - likely "setAnimationState" or "playAnimation"
    (**(code **)(*thisPtr + 600))(stateIndex);

    // Set flag if state is valid
    if (stateIndex != 0) {
        thisPtr[0x927] |= 0x20000; // flag at offset +0x927*4 = 0x249c
    }

    return;
}