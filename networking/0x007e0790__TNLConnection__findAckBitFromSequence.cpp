// FUNC_NAME: TNLConnection::findAckBitFromSequence

uint __thiscall TNLConnection::findAckBitFromSequence(TNLConnection *this, int sequenceNumber)
{
    uint uVar1;
    uint uVar2;
    ulonglong uVar3;
    
    uVar2 = 1;
    do {
        if (sequenceNumber == 0) {
LAB_007e07b1:
            uVar1 = uVar2 & 0xffff502f;
            if ((uVar1 != 0) && ((*(uint *)(this + 4) & uVar1) == uVar1)) {
                return uVar2;
            }
        }
        else {
            uVar3 = FUN_007e04a0(uVar2);  // convertBitToSequence?(uVar2) returns {high: nextBit, low: seqForBit}
            uVar2 = (uint)(uVar3 >> 0x20);
            if ((int)uVar3 == sequenceNumber) {
                goto LAB_007e07b1;
            }
        }
        uVar2 = uVar2 * 2;
        if (0x40000000 < uVar2) {
            return 0;
        }
    } while (true);
}