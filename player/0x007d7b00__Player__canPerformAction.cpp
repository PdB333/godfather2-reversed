//FUNC_NAME: Player::canPerformAction
// Function at 0x007d7b00: Checks if a specific action (actionId) can be performed by the player.
// param_1 = this (Player*), param_2, param_3 = unused?, param_4 = actionId (0x13..0x21)
// Returns true if the action is allowed, false otherwise.

char __thiscall Player::canPerformAction(int actionId)
{
    char result;
    char tempChar;
    int playerStatePtr; // iVar8, from this+0x58
    bool bVar9;
    int someInt;
    undefined4 uVar7;
    undefined8 *puVar5;
    undefined4 local_54;
    undefined4 uStack_50;
    undefined4 local_4c;
    undefined4 uStack_48;
    undefined8 local_44;
    undefined4 local_3c;

    playerStatePtr = *(int *)(this + 0x58); // +0x58: pointer to player state/context
    result = '\0';
    tempChar = '\0';

    switch(actionId - 0x13) {
    case 0: // actionId == 0x13 (19)
        tempChar = FUN_007d62f0(); // some condition check
        goto LAB_007d7b2f;
    case 1: // actionId == 0x14 (20)
        playerStatePtr = FUN_007ab140(); // get global state?
        if ((*(byte *)(playerStatePtr + 4) & 0x10) == 0) {
            return false;
        }
        playerStatePtr = FUN_007ab160(); // get another state?
        if ((*(byte *)(playerStatePtr + 4) & 2) == 0) {
            return false;
        }
        tempChar = FUN_007ab560(); // check if in vehicle?
        if ((tempChar != '\0') && (tempChar = FUN_007abd90(), tempChar == '\0')) {
            return false;
        }
        tempChar = FUN_007aefe0(0x30); // check combat state?
        if (tempChar == '\0') {
            FUN_00716c30(); // some setup
            tempChar = FUN_007bb540(); // check combat active?
            bVar9 = tempChar == '\0';
        } else {
            FUN_0079d7c0(); // start combat?
            tempChar = FUN_007bb540();
            bVar9 = tempChar == '\0';
        }
        goto LAB_007d7b51;
    case 2: // actionId == 0x15 (21)
        someInt = FUN_007ab140();
        if ((*(byte *)(someInt + 4) & 0x40) == 0) {
            return false;
        }
        someInt = FUN_007ab160();
        if ((*(byte *)(someInt + 4) & 2) == 0) {
            return false;
        }
        someInt = FUN_007ab160();
        if ((*(byte *)(someInt + 4) & 0x20) == 0) {
            return false;
        }
        someInt = FUN_007ab1e0(); // check something?
        if ((someInt != 0) && (someInt = FUN_007ab1f0(), someInt != 0)) {
            return false;
        }
        tempChar = FUN_007ada20(playerStatePtr); // check with playerStatePtr
        if (tempChar == '\0') {
            return false;
        }
        tempChar = FUN_007ab9a0(); // check something else
        if (tempChar == '\0') {
            return false;
        }
        if (*(float *)(this + 0x30) <= _DAT_00d577a0) { // +0x30: some timer/cooldown
            return false;
        }
        return true;
    case 3: // actionId == 0x16 (22)
        result = FUN_007d6750(1);
        return result;
    case 4: // actionId == 0x17 (23)
        result = FUN_007d79f0(1);
        return result;
    case 5: // actionId == 0x18 (24)
        tempChar = FUN_007d6250();
        if (tempChar == '\0') {
            return false;
        }
        if (*(float *)(this + 0x30) <= _DAT_00d577a0) {
            return false;
        }
        return true;
    case 6: // actionId == 0x19 (25)
        result = FUN_007d6280();
        return result;
    case 7: // actionId == 0x1A (26)
        tempChar = FUN_007d66b0();
        if (tempChar == '\0') {
            return false;
        }
        tempChar = FUN_007ab9a0();
        if (tempChar == '\0') {
            return false;
        }
        return true;
    default:
        tempChar = FUN_007ab790(); // default condition
        break;
    case 9: // actionId == 0x1C (28)
        tempChar = FUN_007d6480();
        if ((tempChar == '\0') || (tempChar = FUN_00690150(0x30), tempChar != '\0')) {
            tempChar = '\0';
        } else {
            tempChar = '\x01';
            tempChar = FUN_00481660(); // check if player is local?
            if (tempChar != '\0') {
                uStack_50 = 0;
                local_4c = 0;
                uStack_48 = 0;
                local_54 = CONCAT31(local_54._1_3_,1);
                FUN_0079fb90(0x15, local_54, 0, local_44, local_3c); // send event?
                return true;
            }
        }
        tempChar = FUN_00481640(); // check if player is AI?
        if ((tempChar != '\0') && (*(char *)(playerStatePtr + 0x23e4) == '\0')) {
            *(undefined1 *)(playerStatePtr + 0x23e4) = 1; // set flag
            return true;
        }
        break;
    case 10: // actionId == 0x1D (29)
        result = FUN_007ebb00(playerStatePtr);
        return result;
    case 11: // actionId == 0x1E (30)
        result = FUN_007d6660();
        return result;
    case 12: // actionId == 0x1F (31)
        tempChar = FUN_007d64d0();
        if ((tempChar != '\0') && (tempChar = FUN_00690150(0x30), tempChar == '\0')) {
            return true;
        }
        break;
    case 13: // actionId == 0x20 (32)
        tempChar = FUN_00690210(0x28);
        if (tempChar != '\0') {
            return false;
        }
        tempChar = FUN_007f47a0(); // check if in mission?
        if (tempChar != '\0') {
            return false;
        }
        tempChar = FUN_00481640();
        if (tempChar == '\0') {
            return true;
        }
        if (*(char *)(playerStatePtr + 0x241c) == '\0') {
            return false;
        }
        if (*(char *)(playerStatePtr + 0x2438) == '\0') {
            return false;
        }
        return true;
    case 14: // actionId == 0x21 (33)
        result = FUN_007d6700();
        return result;
    case 15: // actionId == 0x22 (34)
        tempChar = FUN_00690210(0x1e);
        if (((tempChar == '\0') && (tempChar = FUN_00690150(0x30), tempChar == '\0')) &&
           (tempChar = FUN_007d7a90(), tempChar != '\0')) {
            uVar7 = FUN_007ab370(); // get some object?
            FUN_004a8f30(uVar7); // set something?
            puVar5 = (undefined8 *)FUN_0079b3d0(&local_54);
            FUN_0079fb90(0x11, *puVar5, puVar5[1], puVar5[2], *(undefined4 *)(puVar5 + 3)); // send event
            return true;
        }
        tempChar = '\0';
        tempChar = FUN_00481640();
        if (((tempChar != '\0') && (*(char *)(playerStatePtr + 0x2374) == '\0')) &&
           (someInt = FUN_004a8f80(), someInt != 0)) {
            uVar7 = FUN_004a8f80();
            uVar7 = FUN_007d7970(uVar7);
            *(undefined4 *)(this + 0x74) = uVar7; // store something
            *(undefined1 *)(playerStatePtr + 0x2374) = 1; // set flag
            return true;
        }
        break;
    case 16: // actionId == 0x23 (35)
        tempChar = FUN_007f47a0();
        if (tempChar == '\0') {
            return false;
        }
        tempChar = FUN_00481640();
        if (tempChar != '\0') {
            return false;
        }
        if (*(int *)(this + 0x78) == 0) { // +0x78: pointer to something
            return false;
        }
        if ((*(uint *)(*(int *)(this + 0x78) + 0x4c) >> 1 & 1) == 0) { // check bit 1 of field at +0x4c
            return false;
        }
        return true;
    case 17: // actionId == 0x24 (36)
        tempChar = FUN_00690150(0x5c);
        if (((tempChar == '\0') && (tempChar = FUN_00690150(0x30), tempChar == '\0')) &&
           (tempChar = FUN_007d6520(), tempChar != '\0')) {
            tempChar = '\x01';
            tempChar = FUN_00481620(); // check if player is local?
            if (tempChar != '\0') {
                uVar7 = FUN_007ab380(); // get some object?
                FUN_004a8f30(uVar7);
                puVar5 = (undefined8 *)FUN_0079b3d0(&local_54);
                FUN_0079fb90(4, *puVar5, puVar5[1], puVar5[2], *(undefined4 *)(puVar5 + 3)); // send event
                return true;
            }
        } else {
            tempChar = '\0';
            tempChar = FUN_00481640();
            if (((tempChar != '\0') && (*(char *)(playerStatePtr + 0x2208) == '\0')) &&
               (someInt = FUN_004a8f80(), someInt != 0)) {
                FUN_007ab3f0(someInt); // set something?
                *(undefined1 *)(playerStatePtr + 0x2208) = 1; // set flag
                return true;
            }
        }
        break;
    case 18: // actionId == 0x25 (37)
        if (*(int *)(this + 0x20) != 0) { // +0x20: some state flag
            return false;
        }
        tempChar = FUN_007f47a0();
        if (tempChar == '\0') {
            return false;
        }
        tempChar = FUN_00481640();
        if (tempChar != '\0') {
            return false;
        }
        if (*(int *)(this + 0x78) == 0) {
            return false;
        }
        if ((*(uint *)(*(int *)(this + 0x78) + 0x4c) >> 1 & 1) == 0) {
            return false;
        }
        return true;
    case 19: // actionId == 0x26 (38)
        if (*(int *)(this + 0x20) == 0) {
            tempChar = FUN_00481640();
            if (tempChar == '\0') {
                return false;
            }
            if (*(char *)(playerStatePtr + 0x2438) != '\0') {
                return false;
            }
            return true;
        }
        break;
    case 20: // actionId == 0x27 (39)
        if (*(int *)(this + 0x20) != 0) {
            return false;
        }
        tempChar = FUN_007f47a0();
        if (tempChar == '\0') {
            return false;
        }
        return true;
    case 21: // actionId == 0x28 (40)
        return DAT_0112fc84 == '\0'; // global flag
    case 22: // actionId == 0x29 (41)
        tempChar = FUN_007ab500(8);
        return tempChar == '\0';
    case 23: // actionId == 0x2A (42)
        tempChar = FUN_007ab500(8);
        if (((tempChar != '\0') && (tempChar = FUN_007aefe0(0x10), tempChar == '\0')) &&
           (tempChar = FUN_007aefe0(0x11), tempChar == '\0')) {
            return true;
        }
        return false;
    case 24: // actionId == 0x2B (43)
        playerStatePtr = FUN_007a49d0(); // get some object?
        tempChar = FUN_00690210(0x1c);
        if (tempChar != '\0') {
            FUN_006901e0(0x1c);
            return playerStatePtr != 0;
        }
        break;
    case 25: // actionId == 0x2C (44)
        tempChar = FUN_007d6350();
LAB_007d7b2f:
        if ((tempChar != '\0') && (tempChar = FUN_00690150(0x30), tempChar == '\0')) {
            playerStatePtr = FUN_007a49d0();
            bVar9 = playerStatePtr == 0;
            tempChar = result;
LAB_007d7b51:
            if (!bVar9) {
                result = FUN_007ab9a0();
                return result;
            }
        }
        break;
    case 26: // actionId == 0x2D (45)
        playerStatePtr = FUN_007a49d0();
        if (playerStatePtr == 0) {
            return true;
        }
        if (*(int *)(playerStatePtr + 0xb74) != 0) {
            return true;
        }
        tempChar = '\0';
        playerStatePtr = FUN_006c12a0();
        if (playerStatePtr != 0) {
            result = FUN_007d6020();
            return result;
        }
        break;
    case 27: // actionId == 0x2E (46)
        uVar7 = FUN_00798f50(1);
        tempChar = FUN_0079e970(uVar7);
        if (((tempChar != '\0') && (tempChar = FUN_00690210(0x14), tempChar == '\0')) &&
           (_DAT_00d577a0 < *(float *)(this + 0x30))) {
            FUN_007ab9a0();
            return true;
        }
        break;
    case 28: // actionId == 0x2F (47)
        someInt = FUN_007ab170();
        if (((((*(byte *)(someInt + 4) & 0x10) != 0) && (someInt = FUN_00691810(), someInt != 0)) &&
            (someInt = FUN_00691810(), *(char *)(someInt + 0x1ad) == '\x1a')) &&
           ((*(uint *)(playerStatePtr + 0x8e0) >> 10 & 1) != 0)) {
            return true;
        }
        break;
    case 29: // actionId == 0x30 (48)
        tempChar = FUN_007d6570();
        result = tempChar;
        if (((tempChar != '\0') && (_DAT_00d577a0 < *(float *)(this + 0x30))) &&
           (tempChar = FUN_00690150(0x30), tempChar == '\0')) {
            result = '\x01';
            tempChar = FUN_00481660();
            if (tempChar != '\0') {
                playerStatePtr = FUN_007ab390();
                if (playerStatePtr == 0) {
                    playerStatePtr = 0;
                } else {
                    playerStatePtr = playerStatePtr + 0x58;
                }
                FUN_004a8ec0(playerStatePtr);
                local_54 = CONCAT31(local_54._1_3_,1);
                uStack_50 = 5;
                FUN_0079fb90(0xd, CONCAT44(5, local_54), CONCAT44(uStack_68, uStack_6c), local_44, local_3c); // send event
                return true;
            }
        }
        tempChar = FUN_00481640();
        if (((tempChar != '\0') && (*(char *)(playerStatePtr + 0x2304) == '\0')) &&
           (someInt = FUN_004a8f00(), someInt != 0)) {
            someInt = FUN_004a8f00();
            if (someInt == 0) {
                FUN_007ab410(0);
                *(undefined1 *)(playerStatePtr + 0x2304) = 1;
                return true;
            }
            FUN_007ab410(someInt + -0x58);
            *(undefined1 *)(playerStatePtr + 0x2304) = 1;
            return true;
        }
        break;
    case 30: // actionId == 0x31 (49)
        tempChar = FUN_00481660();
        if (((tempChar != '\0') || (tempChar = FUN_00481640(), tempChar != '\0')) &&
           (result = '\0', *(char *)(playerStatePtr + 0x2454) == '\0')) {
            return true;
        }
        break;
    case 31: // actionId == 0x32 (50)
        result = FUN_007d6750(0);
        return result;
    case 32: // actionId == 0x33 (51)
        result = FUN_007d79f0(0);
        return result;
    case 33: // actionId == 0x34 (52)
        tempChar = FUN_004ac260();
        if ((tempChar == '\0') && (playerStatePtr = FUN_0045eea0(), playerStatePtr == *(int *)(this + 0x7c))) {
            return false;
        }
        return true;
    }
    return result;
}