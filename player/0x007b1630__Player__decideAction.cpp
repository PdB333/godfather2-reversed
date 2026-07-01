// FUNC_NAME: Player::decideAction
uint __fastcall Player::decideAction(int this) {
    uint someValue = *(uint*)(*(int*)(this + 0x58) + 0xff0);   // +0x58: pointer to game manager; +0xff0: some state flag
    if (someValue != 0) {
        someValue -= 0x48;
        if (someValue != 0) {
            uint bitField = *(uint*)(*(int*)(this + 0x58) + 0x249c); // +0x249c: bitfield
            if ((bitField >> 0x1d) & 1) {
                uint randomByte = getRandomByte(); // FUN_00800be0: returns a random byte
                switch (randomByte & 0xff) {
                case 3:
                case 7:
                    *(int*)(this + 0x74) = 5;   // action type: run?
                    return 1;
                case 4:
                    *(int*)(this + 0x74) = 6;
                    return 1;
                case 6:
                    *(int*)(this + 0x74) = 4;
                    return 1;
                case 10:
                    *(int*)(this + 0x74) = 8;
                    return 1;
                case 12:
                case 14:
                case 15:
                    *(int*)(this + 0x74) = 7;
                    return 1;
                case 0x15:
                case 0x20:
                    *(int*)(this + 0x74) = 10;
                    return 1;
                case 0x16:
                    *(int*)(this + 0x74) = 11;
                    return 1;
                case 0x18:
                    *(int*)(this + 0x74) = 9;
                    return 1;
                case 0x21:
                    *(int*)(this + 0x74) = 12;
                    return 1;
                default:
                    break;
                }
            }
        }
    }
    // return the high 24 bits of someValue (after subtraction if possible)
    return someValue & 0xffffff00;
}