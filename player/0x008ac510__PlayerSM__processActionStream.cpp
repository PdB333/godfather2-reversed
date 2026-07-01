//FUNC_NAME: PlayerSM::processActionStream
void __thiscall PlayerSM::processActionStream(int thisPtr, int buffer, uint bitStreamPtr)
{
    byte bitByte;
    uint currentBitPos;
    bool bVar3;
    uint randomValue;
    
    randomValue = bitStreamPtr; // decompiler artifact, actually local
    bVar3 = false;
    // Initialize bitstream from buffer? (FUN_00481590)
    FUN_00481590(buffer, bitStreamPtr);
    
    // Read first bit
    currentBitPos = *(uint *)(bitStreamPtr + 0x18); // current bit position
    if (*(uint *)(bitStreamPtr + 0x2c) < currentBitPos) { // total bits
        *(byte *)(bitStreamPtr + 0x1c) = 1; // set overflow flag
    } else {
        bitByte = *(byte *)((currentBitPos >> 3) + *(int *)(bitStreamPtr + 0xc)); // byte array
        *(int *)(bitStreamPtr + 0x18) = *(int *)(bitStreamPtr + 0x18) + 1; // advance bit position
        if ((bitByte & (byte)(1 << ((byte)currentBitPos & 7))) != 0) {
            // Bit is set: generate random number in [0, 0x20)
            FUN_0064b9e0(0x20, &randomValue);
            currentBitPos = randomValue;
            if (randomValue < 3) {
                // Small random: enter state 0,1,2
                if (*(int *)(thisPtr + 0x10) == 0) {
                    FUN_008b0130(thisPtr + -0x50); // parent object initialization
                }
                *(uint *)(thisPtr + 0x88) = currentBitPos; // state index
                *(int *)(thisPtr + 0xcc) = 1; // flag
                FUN_004baec0(); // some engine call
                *(uint *)(thisPtr + 0x2c) = *(uint *)(thisPtr + 0x2c) & 0xffffffbf; // clear bit 6
                FUN_0064b9e0(0x20, &randomValue);
                *(uint *)(thisPtr + 0x40) = randomValue; // another random parameter
            } else {
                bVar3 = true;
                FUN_0064b9e0(0x20, &randomValue);
                if (DAT_01223484 != 0) {
                    // Global flag set: trigger special actions
                    FUN_008a2d40(0);
                    FUN_008a2a40(1);
                    FUN_008a4ae0(0);
                    FUN_008a2a20(1);
                }
            }
        }
    }
    
    // Read second bit
    currentBitPos = *(uint *)(bitStreamPtr + 0x18);
    if (*(uint *)(bitStreamPtr + 0x2c) < currentBitPos) {
        *(byte *)(bitStreamPtr + 0x1c) = 1;
        return;
    }
    bitByte = *(byte *)((currentBitPos >> 3) + *(int *)(bitStreamPtr + 0xc));
    *(int *)(bitStreamPtr + 0x18) = *(int *)(bitStreamPtr + 0x18) + 1;
    if ((bitByte & (byte)(1 << ((byte)currentBitPos & 7))) != 0) {
        FUN_0064b9e0(0x20, &randomValue);
        *(uint *)(thisPtr + 0xbc) = randomValue; // store random value
        if ((!bVar3) && (*(int *)(thisPtr + 0xc0) != -1)) {
            // Cancel existing timer if not already cancelled
            if (*(int *)(thisPtr + 0xc0) != -1) {
                FUN_0090dff0(*(int *)(thisPtr + 0xc0)); // cancel timer
                *(int *)(thisPtr + 0xc0) = -1;
            }
            if (*(int *)(thisPtr + 0x88) == 2) {
                FUN_008ac410(); // state-specific action
            }
        }
    }
    return;
}