// FUNC_NAME: AudioStreamManager::processDecodedBlock

int AudioStreamManager::processDecodedBlock(AudioStreamManager* this, uint blockIndex, ushort* outSample, ushort* outVolume)
{
    short maxFrameIdx;
    short sVar2;
    short sVar3;
    ushort volume;
    int* piVar5;
    short* psVar6;
    int blockBase;
    int blockFlags;
    undefined1* src;
    undefined1* dst;
    int iVar11;
    uint copySize;
    uint flagWord;
    undefined2 uVar14;

    // +0x108: maxBlockPointer or baseBlockCount
    blockBase = this->field_0x108;
    // +0xA6: bSomeFlag1 (short)
    // +0xAD: bSomeFlag2 (byte)
    // +0xAC: bProcessing (byte) - flag for current block
    if ((*(short*)((int)this + 0xa6) != 0) &&
        (*(char*)((int)this + 0xad) != '\0') &&
        ((char)this->field_0xac == '\0'))
    {
        *(undefined1*)(&this->field_0xac) = 1;
    }

    blockFlags = FUN_00678100(this->basePointer, 0, 0, 0); // allocate block structure
    flagWord = blockIndex & 0xffff;
    this->currentBlock = blockFlags; // +0xFC
    *(undefined2*)(blockFlags + 0x34) = 3; // block type = 3

    if ((int)flagWord < (int)(short)blockBase)
    {
        // +0xC: framesInfo pointer (8-byte entries per frame)
        copySize = (uint)*(ushort*)(this->framesInfo + 2 + flagWord * 8);
        // +0x4: audioBuffer pointer
        *(int*)(this->audioBuffer + 4) =
            *(int*)(this->framesInfo + flagWord * 8 + 4) +
            *(int*)(this->audioBuffer + 0xc) +
            this->field_0x2c; // +0x2C: some offset

        dst = (undefined1*)FUN_00673070(); // allocate temp buffer
        if (dst != (undefined1*)0x0)
        {
            piVar5 = (int*)this->audioBuffer;
            if (copySize != 0)
            {
                blockBase = piVar5[1]; // buffer write offset
                blockFlags = *piVar5;  // buffer base
                if (copySize != 0)
                {
                    src = dst;
                    flagWord = copySize;
                    do
                    {
                        *src = src[(blockFlags + blockBase) - (int)dst];
                        src = src + 1;
                        flagWord = flagWord - 1;
                    } while (flagWord != 0);
                }
                piVar5[1] = blockBase + copySize;
            }
            FUN_0067ae20(this, dst,
                         *(undefined4*)(this->framesInfo + 4 + flagWord * 8),
                         copySize, 0x10000, 0x10000, 0, 0, 0);
            // +0x1C: bIsStereo or channel flag
            if ((char)this->field_0x1c == '\0')
            {
                // +0x90: leftSample
                this->leftSample = (uint)*(ushort*)(*(int*)(this->field_0x104 + 0x10) + flagWord * 2);
                // +0x94: rightSample (here unused)
                this->rightSample = 0;
            }
            else
            {
                this->leftSample = 0;
                this->rightSample = (uint)*(ushort*)(*(int*)(this->field_0x104 + 0x10) + flagWord * 2);
            }
            if ((*(short*)(this->currentBlock + 0x36) == 0) ||
                ((char)this->field_0x34 != '\0')) // +0x34: bForceReverb
            {
                FUN_00677e80(); // reset reverb/effect
                *(undefined1*)(&this->field_0x34) = 0;
            }
            blockBase = this->basePointer;
            *(undefined4*)(*(int*)(blockBase + 0xc) + *(int*)(dst + -8) * 4) = 0;
            piVar5 = (int*)(blockBase + 4);
            *piVar5 = *piVar5 + -1;
            (*free)(dst + -0x10);
        }
    }

    blockFlags = this->currentBlock;
    // Zero out two arrays at offsets inside block structure
    *(undefined2*)(*(int*)(blockFlags + 0x48) + *(short*)(blockFlags + 0x38) * 2) = 0;
    *(undefined2*)(*(int*)(blockFlags + 0x44) + *(short*)(blockFlags + 0x38) * 2) = 0;
    // Write right/left samples into those arrays
    *(short*)(*(int*)(blockFlags + 0x48) + 2 + *(short*)(blockFlags + 0x38) * 2) = (short)this->rightSample;
    *(short*)(*(int*)(blockFlags + 0x44) + 2 + *(short*)(blockFlags + 0x38) * 2) = (short)this->leftSample;

    blockBase = (int)*(short*)(blockFlags + 0x38); // current mix index
    *outSample = (short)this->leftSample;
    sVar1 = *(short*)(*(int*)(blockFlags + 0x44) + blockBase * 2);
    sVar2 = *(short*)(*(int*)(blockFlags + 0x44) + 2 + blockBase * 2);
    psVar6 = *(short**)(blockFlags + 0x48);
    sVar3 = *psVar6;
    iVar11 = 1;
    if (1 < blockBase)
    {
        do
        {
            if (sVar3 < psVar6[iVar11])
            {
                sVar3 = psVar6[iVar11];
            }
            iVar11 = iVar11 + 1;
        } while (iVar11 < blockBase);
    }
    // +0x10C: masterVolume
    volume = *(ushort*)(&this->field_0x10c);
    psVar6[*(short*)(blockFlags + 0x38) + 2] = volume / 10 + sVar3;

    uVar14 = (undefined2)((int)sVar2 + (int)sVar1 >> 1);
    *(undefined2*)(*(int*)(blockFlags + 0x44) + 4 + *(short*)(blockFlags + 0x38) * 2) = uVar14;
    psVar6[*(short*)(blockFlags + 0x38) + 3] = psVar6[*(short*)(blockFlags + 0x38) + 2] - volume;
    *(undefined2*)(*(int*)(blockFlags + 0x44) + 6 + *(short*)(blockFlags + 0x38) * 2) = uVar14;
    *outVolume = volume;

    this->currentBlock = 0;
    FUN_0067ba50(blockFlags); // schedule next block
    return blockFlags;
}