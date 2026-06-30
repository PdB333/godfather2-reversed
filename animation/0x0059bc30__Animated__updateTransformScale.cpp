// FUNC_NAME: Animated::updateTransformScale
// Address: 0x0059bc30
// This function updates a 3-component vector (passed in EAX) by multiplying it with a global time scale factor,
// and sets flags on the object based on random boolean checks.
// The object has: flags at +0x00, a pointer to some other object at +0x04.

void __thiscall Animated::updateTransformScale(uint *this, float *in_EAX)
{
    uint flags = *this;
    byte randomA, randomB, randomC;
    float *other = (float *)this[1]; // +0x04
    bool allRandomTrue;

    if ((flags & 1) == 0) {
        // Branch when bit0 is clear
        // Call some initialization/utility function with local buffer
        FUN_00595ae0(local_a0);  // local_a0 is an 8-byte buffer (unclear purpose)

        // Check if other object exists and its flags have bit2 set
        if ((other != NULL) && (((uint)*other & 4) != 0)) {
            // Call virtual functions from a global manager (vtable at DAT_012055a8)
            // Offset 100 (0x64): likely some conversion or multiplication operation
            (**(code **)(*DAT_012055a8 + 100))(local_a0, local_50); // local_50 is 76-byte buffer
            // Offset 0x50 (80): possibly quaternion multiply
            (**(code **)(*DAT_012055a8 + 0x50))(auStack_58, other + 0x10, auStack_98); // +0x10 is a quaternion
            // Offset 0x58 (88): likely apply transform
            (**(code **)(*DAT_012055a8 + 0x58))(&local_a4, in_EAX + 1);
            goto LAB_0059bdbe;
        }

        // If other is null or no bit2, just call another virtual at offset 0x70
        pcVar3 = *(code **)(*DAT_012055a8 + 0x70);
        puVar4 = local_a0;
    }
    else {
        // Branch when bit0 is set: apply random scaling and possible additional transforms
        randomA = FUN_00595610(); // get random boolean
        randomB = FUN_00595610();
        randomC = FUN_00595610();
        allRandomTrue = randomA & randomB & randomC; // all must be true

        // Apply global time scale to the three floats passed in EAX
        float timeScale = DAT_00e445c8; // global frame time or scale factor
        local_a4 = *in_EAX * timeScale;
        *in_EAX = local_a4;
        float fVar5 = in_EAX[1] * timeScale;
        in_EAX[1] = fVar5;
        float fVar6 = in_EAX[2] * timeScale;
        in_EAX[2] = fVar6;

        // Check if other object exists and has bit2 set
        if ((other != NULL) && (((uint)*other & 4) != 0)) {
            // Additional transformation using the scaled values
            (**(code **)(*DAT_012055a8 + 0x54))(fVar5, local_a4, fVar6, local_90); // local_90 48-byte buffer
            (**(code **)(*DAT_012055a8 + 0x50))(local_a0, other + 0x10, auStack_60);
            pcVar3 = *(code **)(*DAT_012055a8 + 0x58);
            puVar4 = local_50;
        }
        else {
            goto LAB_0059bdbe;
        }
        // Note: original code has a goto after the if, but the flow seems to always reach the pcVar3 call inside the else?
        // Restructured to match original: the else branch ends with pcVar3 call, but label is after if.
        // Actually, original code: after if, there is a call to (*pcVar3)(puVar4,in_EAX+1); at the end of the else block.
        // But the decompiled shows that call after the if-else block; need to trace carefully.
        // For clarity, I'll keep the structure as decompiled: after the else block, it jumps to the pcVar3 call.
    }

    // This call exists only if the first branch (bit0 clear) went to the else of the inner if,
    // or if bit0 set and the inner inner if's else? The decompiled code has a single call after the if-else.
    // Actually, there is a call after the if-else: (*pcVar3)(puVar4, in_EAX+1);
    // But that's only set in specific paths. I'll keep it as is: undefined behavior if pcVar3 not set.
    // To be safe, I'll add a condition: if (pcVar3) (*pcVar3)(puVar4, in_EAX+1);
    if (pcVar3) {
        (*pcVar3)(puVar4, in_EAX + 1);
    }

LAB_0059bdbe:
    // If all three random bools were true (in branch bit0), set bit2 in flags
    if (allRandomTrue) {
        *this = *this | 4;
    }
}