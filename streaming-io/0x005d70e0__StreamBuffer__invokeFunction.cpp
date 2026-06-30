// FUNC_NAME: StreamBuffer::invokeFunction

// Reconstructed from 0x005d70e0
// Reads arguments from a streaming buffer and calls a function pointer.
// Buffer pointer stored at +0x18 (relative to this).
// Buffer layout: 4 aligned ints (unknown1, unknown2, size, alignment), then aligned data, then one more int.
// The function pointer is passed as param_2 (*param_2 is the function to call).

void __thiscall StreamBuffer::invokeFunction(StreamBuffer *this, void (**funcPtr)()) {
    unsigned int *buffer;          // puVar6
    unsigned int arg1, arg2;       // uVar1, uVar2
    int size;                      // iVar3
    int alignment;                 // iVar4
    unsigned int alignedBase;      // uVar7
    unsigned int *alignedData;     // puVar6 (second)
    unsigned int finalArg;         // uVar5

    // Get current buffer pointer and align to 4 bytes
    buffer = (unsigned int *)((*(unsigned int *)((char *)this + 0x18) + 3) & 0xFFFFFFFC);

    // Update stored buffer pointer to aligned start
    *(unsigned int **)((char *)this + 0x18) = buffer;

    // Read first 4 ints (16 bytes)
    arg1 = *buffer;
    *(unsigned int **)((char *)this + 0x18) = buffer + 1;

    arg2 = buffer[1];
    *(unsigned int **)((char *)this + 0x18) = buffer + 2;

    size = (int)buffer[2];
    *(unsigned int **)((char *)this + 0x18) = buffer + 3;

    alignment = (int)buffer[3];
    *(unsigned int **)((char *)this + 0x18) = buffer + 4;

    // Compute aligned address after the 4 ints: round up by adding alignment-1 and masking
    alignedBase = ((unsigned int)buffer + 16 + (alignment - 1)) & ~(alignment - 1);
    // Note: size is used in calculation but not directly as offset? Actually code computes:
    // uVar7 = (int)puVar6 + iVar4 + 0xf & ~(iVar4 - 1U); but we have read 4 ints, so puVar6 is now buffer+4.
    // So alignedBase = ((unsigned int)(buffer+4) + alignment + 0xF) & ~(alignment-1) ? That seems off. Let's re-check decompiled:
    // "uVar7 = (int)puVar6 + iVar4 + 0xf & ~(iVar4 - 1U);" where puVar6 is buffer (original) after reading 4 ints? Actually puVar6 is after reading? After each read, they update puVar6. The code: after reading iVar4, they set *(param_1+0x18)=puVar6+4; then compute uVar7 = (int)puVar6 + iVar4 + 0xf & ~(iVar4-1). At that point, puVar6 is the value before reading iVar4? Actually careful: they read iVar4 from puVar6[3] and then set pointer to puVar6+4. So puVar6 is the original aligned base (buffer). So computation: uVar7 = (int)buffer + alignment + 0xF & ~(alignment-1). Then they set puVar6 = (undefined4 *)((iVar3 + 3U & 0xfffffffc) + uVar7) and then read uVar5.
    // So the aligned base is buffer + alignment, then align to alignment, then add size aligned to 4 to get data area.
    // But this seems redundant. Possibly alignment is used as padding before the next section.
    // For simplicity, follow the decompiled logic exactly.

    // Calculate new aligned pointer for next data block
    alignedBase = ((unsigned int)buffer + alignment + 0xF) & ~(alignment - 1);

    // Calculate pointer to data block: align size to 4 and add to alignedBase
    alignedData = (unsigned int *)((size + 3) & 0xFFFFFFFC) + (unsigned int *)alignedBase;

    // Update stored buffer pointer to after reading finalArg
    *(unsigned int **)((char *)this + 0x18) = alignedData;

    // Read final argument from data block
    finalArg = *alignedData;
    *(unsigned int **)((char *)this + 0x18) = alignedData + 1;

    // Call the function pointer with extracted arguments
    // Note: The third argument is a 64-bit value: high = size, low = alignedBase (but with a sign extension trick)
    // Decompiled: CONCAT44(iVar3, -(uint)(iVar3 != 0) & uVar7)  -- this might be a mis-decompilation. Probably they meant (size, alignedBase)
    // In x86-64 convention for variadic, they might pass size and then the aligned base as two 32-bit parts but combined?
    // We'll replicate the decompiled logic:
    unsigned int loPart = ((unsigned int)(size != 0) - 1) & alignedBase; // -(uint)(iVar3 != 0) = (size!=0)?0xFFFFFFFF:0, & uVar7
    // Pass as two separate arguments? Actually the call uses CONCAT44, which is a 64-bit value. In 32-bit calling convention, this would be passed as two doubles? Unlikely.
    // More likely the actual function expects separate parameters. We'll pass arg1, arg2, size, alignedBase, alignment, finalArg.
    // But the decompiled shows only 5 arguments. Let's keep as written: (arg1, arg2, CONCAT44(size, loPart), alignment, finalArg)
    // However, CONCAT44 is not standard C. We'll just pass as two args (size, loPart) if the calling convention supports it.
    // Since this is x86 32-bit __thiscall? Actually the function pointer call is not part of a class, so it's __cdecl/stdcall. We'll assume __cdecl.
    // Better to match the exact decompiled output to avoid misinterpretation. Use a 64-bit integer.
    unsigned long long combinedArg = ((unsigned long long)size << 32) | (unsigned long long)loPart;

    // Call the function. The function pointer is stored at *param_2.
    (*funcPtr)(arg1, arg2, combinedArg, alignment, finalArg);
}