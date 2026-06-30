// FUNC_NAME: Decompressor::unpackArrays
// 0x006783f0 - Decompresses two arrays of uint16 from a bitstream.
// Context at `this` has a flag at +0x08 (non-zero = alternate mode).
// Flags param_2 control bit packing (bits 0-1: size mode, bit 2: padding, bits 4-5: per-group flags).
// Input: *ppInput is on input a pointer to compressed data, gets advanced.
// Output: out[0] = number of small values, out[0x41] = number of large values,
//         small values at out[1..smallCount], large values at out[0x42..0x42+largeCount-1].

void __thiscall Decompressor::unpackArrays(byte flags, byte*& ppInput, ushort* out)
{
    byte* pInput = *ppInput;
    ushort smallCount = 0;
    byte tmpByte = 0;
    ushort largeCount = 0;
    ushort largeCount2 = 0;

    if (*(char*)(this + 8) == '\0')
    {
        // Simple nibble-based delta decoding
        smallCount = 0;
        largeCount2 = 0;
        largeCount = 0;

        if ((flags & 4) == 0)
        {
            if ((flags & 1) != 0)
            {
                largeCount = (ushort)*pInput;
                pInput++;
            }
            if ((flags & 2) != 0)
            {
                tmpByte = *pInput;
                goto read_nibble;
            }
        }
        else
        {
            largeCount = (ushort)(*pInput & 0xf);
            tmpByte = *pInput >> 4;
read_nibble:
            largeCount2 = (ushort)tmpByte;
            smallCount = (ushort)tmpByte;
            pInput++;
        }

        short smallIdx = 0;
        short largeIdx = 0;
        if ((short)smallCount + (short)largeCount != 0)
        {
            ushort sum = 0;
            do
            {
                byte controlByte = *pInput;
                pInput++;
                int bitOffset = 0;
                do
                {
                    if (smallIdx < (short)largeCount)
                    {
                        if ((controlByte & 1) == 0)
                        {
                            sum += *pInput;
                            pInput++;
                            out[smallIdx + 1] = sum;
                            smallIdx++;
                        }
                        else
                        {
                            byte low = *pInput;
                            byte high = *(pInput + 1);
                            pInput += 2;
                            sum = (ushort)low * 0x100 + (ushort)high;
                            out[smallIdx + 1] = sum;
                            smallIdx++;
                        }
                    }
                    else
                    {
                        if ((short)largeCount2 <= largeIdx) break;
                        if ((controlByte & 1) == 0)
                        {
                            sum += *pInput;
                            pInput++;
                        }
                        else
                        {
                            byte low = *pInput;
                            byte high = *(pInput + 1);
                            pInput += 2;
                            sum = (ushort)low * 0x100 + (ushort)high;
                        }
                        out[largeIdx + 0x42] = sum;
                        largeIdx++;
                    }

                    // bit 1
                    if (smallIdx < (short)largeCount)
                    {
                        if ((controlByte >> 1 & 1) == 0)
                        {
                            sum += *pInput;
                            pInput++;
                            out[smallIdx + 1] = sum;
                            smallIdx++;
                        }
                        else
                        {
                            byte low = *pInput;
                            byte high = *(pInput + 1);
                            pInput += 2;
                            sum = (ushort)low * 0x100 + (ushort)high;
                            out[smallIdx + 1] = sum;
                            smallIdx++;
                        }
                    }
                    else
                    {
                        if ((short)largeCount2 <= largeIdx) break;
                        if ((controlByte >> 1 & 1) == 0)
                        {
                            sum += *pInput;
                            pInput++;
                        }
                        else
                        {
                            byte low = *pInput;
                            byte high = *(pInput + 1);
                            pInput += 2;
                            sum = (ushort)low * 0x100 + (ushort)high;
                        }
                        out[largeIdx + 0x42] = sum;
                        largeIdx++;
                    }

                    // bit 2
                    if (smallIdx < (short)largeCount)
                    {
                        if ((controlByte >> 2 & 1) == 0)
                        {
                            sum += *pInput;
                            pInput++;
                            out[smallIdx + 1] = sum;
                            smallIdx++;
                        }
                        else
                        {
                            byte low = *pInput;
                            byte high = *(pInput + 1);
                            pInput += 2;
                            sum = (ushort)low * 0x100 + (ushort)high;
                            out[smallIdx + 1] = sum;
                            smallIdx++;
                        }
                    }
                    else
                    {
                        if ((short)largeCount2 <= largeIdx) break;
                        if ((controlByte >> 2 & 1) == 0)
                        {
                            sum += *pInput;
                            pInput++;
                        }
                        else
                        {
                            byte low = *pInput;
                            byte high = *(pInput + 1);
                            pInput += 2;
                            sum = (ushort)low * 0x100 + (ushort)high;
                        }
                        out[largeIdx + 0x42] = sum;
                        largeIdx++;
                    }

                    // bit 3
                    if (smallIdx < (short)largeCount)
                    {
                        if ((controlByte >> 3 & 1) == 0)
                        {
                            sum += *pInput;
                            pInput++;
                            out[smallIdx + 1] = sum;
                            smallIdx++;
                        }
                        else
                        {
                            byte low = *pInput;
                            byte high = *(pInput + 1);
                            pInput += 2;
                            sum = (ushort)low * 0x100 + (ushort)high;
                            out[smallIdx + 1] = sum;
                            smallIdx++;
                        }
                    }
                    else
                    {
                        if ((short)largeCount2 <= largeIdx) break;
                        if ((controlByte >> 3 & 1) == 0)
                        {
                            sum += *pInput;
                            pInput++;
                        }
                        else
                        {
                            byte low = *pInput;
                            byte high = *(pInput + 1);
                            pInput += 2;
                            sum = (ushort)low * 0x100 + (ushort)high;
                        }
                        out[largeIdx + 0x42] = sum;
                        largeIdx++;
                    }

                    bitOffset += 4;
                    controlByte >>= 4;
                }
                while (bitOffset < 8);
            }
            while ((int)largeIdx + (int)smallIdx < (short)smallCount + (short)largeCount);
        }

        // write header
        *out = largeCount;
        out[0x41] = largeCount2;
        *ppInput = pInput;
        return;
    }

    // Alternate bit-packing mode
    byte tmpHigh = 0;
    bool oddByte = false;
    byte tmpLow;
    byte tmpMid;
    switch (flags & 3)
    {
    case 0:
        largeCount2 = 0;
        largeCount = 0;
        goto default_switch;
    case 1:
        tmpLow = *pInput & 0xf;
        tmpMid = *pInput >> 4;
        break;
    case 3:
        oddByte = true;
        // fallthrough
    case 2:
        tmpLow = *pInput;
        pInput++;
        tmpMid = *pInput;
        break;
    default:
        goto default_switch;
    }
    largeCount = (ushort)tmpLow;
    largeCount2 = (ushort)tmpMid;
    pInput++;
default_switch:
    byte nibbleRemain = 0;
    short outIdx = 0;
    ushort* curOut = out + 1;
    short largeIdx2 = 0;
    short smallIdx2 = 0;
    bool halfByteFlag = false;
    byte bitCounter = 0;

    do
    {
        if (outIdx < (short)largeCount)
        {
            int curIdx = (int)outIdx;
            outIdx = outIdx + 1;
            bool isFirst = (curIdx == 0);
            if (isFirst)
            {
                curOut = out + 1;
                smallCount = 0;
                tmpByte = (flags >> 4) & 1;
            }
            else
            {
                goto process_bit;
            }
        }
        else
        {
            if ((short)largeCount2 <= largeIdx2) break;
            int curIdx = (int)largeIdx2;
            largeIdx2 = largeIdx2 + 1;
            bool isFirst = (curIdx == 0);
            if (!isFirst) goto process_bit;
            curOut = out + 0x42;
            tmpByte = (flags >> 5) & 1;
            smallCount = 0;
        }

process_bit:
        ushort delta;
        if ((tmpByte & 1) == 0)
        {
            if (halfByteFlag)
            {
                delta = (ushort)(byte)(*pInput << 4) + (pInput[1] >> 4);
            }
            else
            {
                delta = (ushort)*pInput;
            }
        }
        else if (oddByte)
        {
            if (halfByteFlag)
            {
                delta = (ushort)(byte)(*pInput << 4) * 0x100 + (ushort)pInput[1] * 0x10 +
                    (ushort)(pInput[2] >> 4);
                tmpByte = nibbleRemain;
            }
            else
            {
                delta = (ushort)*pInput * 0x100 + (ushort)pInput[1];
            }
        }
        else
        {
            if (halfByteFlag)
            {
                delta = (char)(*pInput << 4) * 0x10 + (ushort)pInput[1];
                halfByteFlag = false;
            }
            else
            {
                delta = (char)*pInput * 0x10 + (ushort)(pInput[1] >> 4);
                halfByteFlag = true;
            }
        }

        smallCount = smallCount + delta;
        curOut[curIdx] = smallCount;

        // Advance pInput accordingly
        if ((tmpByte & 1) == 0)
        {
            if (halfByteFlag)
                pInput = pInput + 1; // Actually we consumed 2 half bytes, but pointer advanced in delta calc
            else
                pInput = pInput + 1;
        }
        else if (oddByte)
        {
            if (halfByteFlag)
                pInput = pInput + 2;
            else
                pInput = pInput + 2;
        }
        else
        {
            if (halfByteFlag)
                pInput = pInput + 2;
            else
                pInput = pInput + 1;
        }
    }
    while (true);

    // post-process: duplicate last if needed
    if ((flags & 4) != 0)
    {
        int i = (int)(short)largeCount2;
        while (i - 1 >= 0)
        {
            out[i + 0x42] = out[i + 0x41];
            i--;
        }
        largeCount2 = largeCount2 + 1;
    }

    if ((largeCount2 & 1) != 0)
    {
        int i = (int)(short)largeCount2;
        largeCount2 = largeCount2 + 1;
        out[i + 0x42] = out[i + 0x41];
    }

    if (halfByteFlag)
    {
        pInput++;
    }

    *out = largeCount;
    out[0x41] = largeCount2;
    *ppInput = pInput;
}