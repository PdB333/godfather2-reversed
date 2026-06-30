// FUNC_NAME: MessageWriter::writeMessageHeader
void __thiscall MessageWriter::writeMessageHeader(int* this, int a, int b, unsigned __int64 c, int d, int e, int f)
{
    // this points to a structure containing a buffer pointer at +0x00? Actually *this is a pointer to internal context.
    // The internal context has a current write pointer at offset 0x14.
    int* context = *this; // dereference this to get context pointer
    int* curPtr = *(int**)(context + 0x14); // +0x14: current buffer position (pointer)

    // Write a constant handler/type pointer (probably vtable or function table)
    **((int**)(curPtr) + 0x14?) No, careful. The code: **(undefined4 **)(iVar2 + 0x14) = &PTR_FUN_01124d3c;
    // Actually it writes the address of a global pointer into the buffer at the current position.
    *(int*)curPtr = (int)&PTR_FUN_01124d3c;
    curPtr++; // advance by 4 bytes

    // Align to next 4-byte boundary (since pointer was incremented, it may already be aligned)
    curPtr = (int*)((int)curPtr & 0xfffffffc); // not needed after increment, but code does it after writing param_2.

    // Write second 4-byte value (param_2 in original, here 'a')
    *curPtr = a;
    // Align to 4-byte boundary for the next write (always aligns up)
    curPtr = (int*)(((int)curPtr + 7) & 0xfffffffc); // round up to multiple of 4

    // Write third 4-byte value (param_3 -> 'b')
    *curPtr = b;
    // Align to 8-byte boundary for the 64-bit write? Actually code uses same 4-byte alignment, but writes 8 bytes.
    curPtr = (int*)(((int)curPtr + 7) & 0xfffffffc);

    // Write 64-bit value: high 32 bits from 'd', low 32 bits from 'c' (c is a 64-bit param, but we treat low part separately)
    *(unsigned __int64*)curPtr = ((unsigned __int64)d << 32) | (unsigned int)c;
    // Then overwrite the high part with 'd' again? Actually code does: *puVar4 = param_4; *(puVar4+1) = param_5;
    // That means the stored 64-bit is (param_5 << 32) | (low 32 of param_4)
    // So we store (d << 32) | (c & 0xFFFFFFFF)
    curPtr = (int*)((int)curPtr + 8); // advance by 8

    // Align again to 8-byte boundary for next 64-bit write? Code uses alignment to 16? Actually (ptr + 0xfU) & 0xfffffffc -> aligns to 4? No, that masks to 4? 0xf & 0xfffffffc = 0xc? Actually 0xfU & 0xfffffffc = 0xc, which rounds down to multiple of 4? No, it's wrong. Wait: (ptr + 0xf) & 0xfffffffc rounds up to next multiple of 4? Example ptr=0, (0+15)&0xfffffffc = 12, that's not correct. Actually for 8-byte alignment, you'd use (ptr+7)&0xfffffff8. The code uses 0xfU & 0xfffffffc, which is 0xc, but then it's used as a pointer? Let's re-examine:
    // puVar4 = (undefined8 *)(*(int *)(iVar2 + 0x14) + 0xfU & 0xfffffffc);
    // This takes the current pointer, adds 0xf, then masks with 0xfffffffc. That actually rounds up to next 4-byte boundary? No, because add 0xf (15) then mask lower 2 bits to 0 gives a multiple of 4 that is at least (original+15) & ~3. Example: original=0 -> (0+15)&~3 = 12 (0xc). That skips 12 bytes, not aligned to 8.
    // Possibly it's a bug in decompilation or it's meant to align to 16? Anyway, the original code uses 0xf, which suggests 16-byte alignment. But the mask 0xfffffffc only clears 2 bits, so alignment to 4. This might be an error in Ghidra. We'll follow the actual code.
    // After writing the previous 64-bit, they do: puVar4 = (undefined8 *)(*(int *)(iVar2 + 0x14) + 0xfU & 0xfffffffc);
    // This is likely a macro to align to 4 bytes (since 0xfU rounds up to multiple of 4, but 0xf itself is not a power of 2 minus 1 for 4, it should be 3). So it might be a mistake. I'll assume it's aligning to 4 bytes as earlier.
    // Then they write CONCAT44(param_7, param_6) as a 64-bit value.
    // Let's simplify: after writing the first 64-bit, they align to 4? Then write another 64-bit.
    // I'll keep the alignment as the code does: (ptr + 0xf) & 0xfffffffc -> which is (ptr+15)&~3, effectively rounding up to the next multiple of 4? Actually it might be (ptr+15)&~3, which gives a number that is a multiple of 4 and at least ptr+15. That could be correct for writing an 8-byte value with 4-byte alignment? Unclear.
    // Since we can't be sure, we'll stick to the exact sequence.

    // After writing first 64-bit, do alignment: curPtr = (int*)(((int)curPtr + 0xf) & 0xfffffffc);
    curPtr = (int*)(((int)curPtr + 0xf) & 0xfffffffc); // crude alignment

    // Write last 64-bit value: high from 'f', low from 'e'
    *(unsigned __int64*)curPtr = ((unsigned __int64)f << 32) | (unsigned int)e;
    curPtr = (int*)((int)curPtr + 8);

    // Update the context's current pointer
    *(int**)(context + 0x14) = curPtr;
}