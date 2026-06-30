// FUNC_NAME: Presentation::updateReflectionMatrices
void __fastcall Presentation::updateReflectionMatrices(Presentation *this)
{
    uint index;
    int *slotPtr;
    int *renderTargetFlagPtr;
    float matrix[8];
    // matrix layout: row0: matrix[0..3], row1: ?, row2: matrix[4..7], row3: ignored? Actually 8 floats -> 2 rows of 4 floats, likely for reflection transformation.
    // Auxiliary buffer for unknown computation
    byte auxBuffer[16]; // auStack_60, possibly matrix multiply temporary
    int resultInt0, resultInt1, resultInt2;
    float constant1 = *(float*)0x00e44564; // inverse value for odd passes (approx 1.0)
    float constant2 = *(float*)0x00e2b1a4; // some fixed value (likely near 0 or 1)

    // Check if reflection processing is enabled (param_1[0x121] == 0 -> not disabled)
    if (this->m_bDisableReflection != 0) {
        return;
    }

    slotPtr = &this->m_reflectionSlotData[0]; // param_1+0xf6 (offset 0x3D8) - array of 4 slots, each 48 bytes
    index = 0;
    renderTargetFlagPtr = &this->m_renderTargetFlags[0]; // param_1+0x148 (offset 0x520) - array of 4 bool/int flags, each 40 bytes? Actually step 0x28 (40 ints?) but increment as int* by 0x28? That would be 40 ints = 160 bytes, but our step is per iteration: piVar2 = piVar2 + 0x28; and it's an int*, so it moves by 0x28 (40) ints = 160 bytes. That's huge for a flag array. Possibly it's an array of larger structures; we'll keep unknown.

    do {
        // Check if either the global enable flag is set, or the per-slot render target flag is nonzero
        if (this->m_bEnableRenderPass != 0 || (*renderTargetFlagPtr != 0)) {
            // Get the projection/reflection matrix for this pass index
            // Virtual function at vtable offset 0x254 (0x254/4 = 0x95)
            // Signature: void getPassMatrix(uint index, float outMatrix[8]);
            (*(void (__thiscall **)(Presentation *, uint, float *))(*(int *)this + 0x254))(this, index, matrix);

            // If render target is set and this is an odd pass, flip the matrix components (for reflection: mirror the world)
            if ((*renderTargetFlagPtr != 0) && ((index & 1) != 0)) {
                matrix[0] = constant1 - matrix[0];
                matrix[1] = constant1 - matrix[1];
                matrix[2] = constant1 - matrix[2];
                matrix[3] = constant1 - matrix[3];
                matrix[4] = constant1 - matrix[4];
                matrix[5] = constant1 - matrix[5];
                matrix[6] = constant1 - matrix[6];
                matrix[7] = constant1 - matrix[7];
            }

            // If global render pass is enabled, perform additional transformation
            if (this->m_bEnableRenderPass != 0) {
                // Multiply matrix by some other matrix? (FUN_00aa3930)
                FUN_00aa3930(matrix);
                // Build a sub‑matrix into previous slot? (FUN_0055ab30)
                // Parameter: auxBuffer (output?), and slotPtr - 6 (points 24 bytes before current slot)
                FUN_0055ab30(auxBuffer, slotPtr - 6);
                // Copy 3 ints from the result into the current slot's first fields
                // (slotPtr[-2], slotPtr[-1], slotPtr[0]) are the first 3 ints of the slot? Actually offset indices: -2 -> slot start, -1 -> slot start+4, 0 -> slot start+8
                slotPtr[-2] = resultInt0;
                slotPtr[-1] = resultInt1;
                slotPtr[0] = resultInt2;
                // Write constant to slot+12 (slotPtr[1] -> offset +12 from slot start)
                slotPtr[1] = *(int*)&constant2;
            }
        }
        // Advance to next slot (48 bytes = 12 ints)
        slotPtr += 12;
        index++;
        // Advance render target flag pointer by 0x28 ints (unknown stride)
        renderTargetFlagPtr += 0x28;
    } while (index < 4);
}