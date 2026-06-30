// FUNC_NAME: Sentient::followTarget
bool __fastcall Sentient::followTarget(int thisPtr)
{
    char moveResult;
    bool moved;
    float dx, dy, dz, distSq;
    float targetPos[3]; // [0]=x, [1]=y, [2]=z (local_c, fStack_8, local_4)

    // State at +0x9c: 0=idle? 0x48=dead? If in these states, can't follow
    if (*(int*)(thisPtr + 0x9c) == 0 || *(int*)(thisPtr + 0x9c) == 0x48) {
        return false;
    }

    // Retrieve target position (likely player or leader)
    // FUN_0075bd60(targetPos, 0): second arg may be slot index or target type
    FUN_0075bd60(targetPos, 0);

    // Get current position (x,y,z at +0x58, +0x5c, +0x60)
    dx = targetPos[0] - *(float*)(thisPtr + 0x58);
    dy = targetPos[1] - *(float*)(thisPtr + 0x5c);
    dz = targetPos[2] - *(float*)(thisPtr + 0x60);
    distSq = dx*dx + dy*dy + dz*dz;

    // Distance thresholds (squared)
    // _DAT_00d6514c: max follow distance – if beyond, snap immediately
    // _DAT_00d65150: min follow distance – if within, don't move
    if (_DAT_00d6514c < distSq) {
        moved = true;
        goto updatePosition;
    }
    if (distSq <= _DAT_00d65150) {
        return false; // close enough, no movement
    }

    // Interpolate toward target
    // FUN_009a7550(speedOrFlags at +0x98, current pos pointer, target pos array)
    moveResult = FUN_009a7550(*(undefined4*)(thisPtr + 0x98), (undefined8*)(thisPtr + 0x58), targetPos);
    moved = (moveResult == 0); // if function returns 0, position was updated
    if (!moved) {
        return false; // no movement
    }

updatePosition:
    // Write new position (pack x and y in one 8-byte write)
    *(undefined8*)(thisPtr + 0x58) = CONCAT44(targetPos[1], targetPos[0]);
    *(float*)(thisPtr + 0x60) = targetPos[2];
    return moved;
}