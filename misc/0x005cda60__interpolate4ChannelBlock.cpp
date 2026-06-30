// FUNC_NAME: interpolate4ChannelBlock
void __thiscall interpolate4ChannelBlock(uint8_t* dest, int destStride, int srcStride, int count)
{
    // Registers: EAX = source pointer (initialized by caller), ESI = blend factor (0-0xFFFF, fixed-point with 15 fractional bits)
    uint8_t* src;                // in_EAX (register)
    int16_t blendFactor;         // unaff_ESI (register)
    int iVar1, iVar2, iVar3, iVar4; // channel accumulators (16.16 fixed-point? actually 8.8)

    // Initialize accumulators from first source sample (scale up by 256)
    iVar3 = (uint)*src << 8;           // channel 0
    iVar4 = (uint)src[3] << 8;         // channel 3
    iVar2 = (uint)src[1] << 8;         // channel 1
    iVar1 = (uint)src[2] << 8;         // channel 2

    if (count != 0) {
        do {
            // Write current accumulator values as 4 bytes (fixed-point 8.8, discard fractional part)
            *dest = (uint8_t)((uint)iVar3 >> 8);
            dest[1] = (uint8_t)((uint)iVar2 >> 8);
            dest[2] = (uint8_t)((uint)iVar1 >> 8);
            dest[3] = (uint8_t)((uint)iVar4 >> 8);

            // Advance input pointer by srcStride bytes
            src += srcStride;

            // One-pole low-pass filter / linear interpolation for each channel:
            // new = old + ((target - old) * blendFactor) >> 15
            // where target = src_channel * 256 (scaled)
            iVar3 = iVar3 + (( (int)(((uint)*src << 8) - iVar3) * blendFactor) >> 0xf);
            iVar2 = iVar2 + (( (int)(((uint)src[1] << 8) - iVar2) * blendFactor) >> 0xf);
            iVar1 = iVar1 + (( (int)(((uint)src[2] << 8) - iVar1) * blendFactor) >> 0xf);
            iVar4 = iVar4 + (( (int)(((uint)src[3] << 8) - iVar4) * blendFactor) >> 0xf);

            count--;
            dest += destStride;
        } while (count != 0);
    }
}