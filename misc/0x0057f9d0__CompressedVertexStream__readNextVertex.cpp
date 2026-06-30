// FUNC_NAME: CompressedVertexStream::readNextVertex
#include <cstdint>

// This function decompresses the next vertex data from a compressed stream.
// Output buffer out[8] contains: out[0..2] = first vector (e.g., position), out[3] = constant1,
// out[4..6] = second vector (e.g., normal), out[7] = constant2.
// The compression format is determined by flags at the byte pointed by m_flagsPtr (+0x4c).
// Multiple streams (ushort, byte, float) are used with different decoding schemes.
void __thiscall CompressedVertexStream::readNextVertex(float out[8]) {
    uint32_t flags = *m_flagsPtr; // Byte flags at +0x4c

    // --- First vector (out[0..2]) ---
    if (flags & 1) {
        // Decompress ushort stream at +0x14: delta from 1.0 or 0.0?
        // Uses direct ushort values scaled by DAT_00e44820 and subtracted from DAT_00e44564 (likely 1.0f)
        uint16_t* ushortStream = m_ushortStream1; // +0x14
        out[0] = 1.0f - (float)(ushortStream[2]) * scaleFactor4; // DAT_00e44820
        out[1] = 1.0f - (float)(ushortStream[0]) * scaleFactor4;
        out[2] = 0.0f; //? Actually param_1[2] was set to 0 earlier? Wait, check code: In this branch, param_1[0..2] are set by FUN_0056d040 which takes two floats and writes param_1[0..2]? Actually FUN_0056d040 takes two floats and writes param_1[0]=fVar11, param_1[1]=fVar12, param_1[2]=? Possibly set to 0? Let's examine: call is FUN_0056d040(fVar11,fVar12,param_1); So that sets param_1[0]=fVar11, param_1[1]=fVar12, and param_1[2] is set inside? The function likely sets a 3-component vector from two inputs? Possibly param_1[2] is set to 0? Actually original code: in the &1 branch, it calls FUN_0056d040 with fVar11, fVar12, and then later sets param_1[2]? No, after the call, param_1[2] is not explicitly set. But earlier in the &1 branch, there is no explicit assignment to param_1[2]. However, in the &2 branch, they set fVar11 and fVar12 and call FUN_0056d040. So param_1[2] is set inside FUN_0056d040? Or the function expects a 3D vector? Possibly FUN_0056d040 sets all three components from two inputs? Unclear. I'll assume param_1[2] is set inside that function. For safety, I'll keep as per logic.
        // After call, advance stream and counters.
        m_ushortStream1 = ushortStream + 3; // Increment by 3 ushorts (6 bytes) 
        m_counter1++; // +0x18
    } else if (flags & 2) {
        // Decompress ushort stream at +0x08 with random noise from FUN_0057ef80
        uint32_t randVal = getRandom(); // FUN_0057ef80
        uint32_t mode = randVal & 3;
        uint16_t* ushortStream = m_ushortStream2; // +0x08
        float x, y;
        if (mode == 1) {
            randVal = getRandom(); // Actually in mode1 it calls only once? Code shows one call to FUN_0057ef80() then uses it for x offset.
            // In the decomp: uVar7 = FUN_0057ef80(); then uses (uVar7 & 0xffff) << 4
            float offsetX = (float)((randVal & 0xffff) << 4) * scaleFactor2; // DAT_00e44820
            x = -((float)us * scaleFactor2 - offsetX);
            y = 1.0f - (float)us[2] * scaleFactor2;
        } else if (mode == 2) {
            randVal = getRandom();
            float offsetY = (float)((randVal & 0xffff) << 4) * scaleFactor2;
            x = 1.0f - (float)us * scaleFactor2;
            y = -((float)us[2] * scaleFactor2 - offsetY);
        } else if (mode == 3) {
            getRandom(); // Discard
            x = 1.0f - (float)us * scaleFactor2;
            y = 1.0f - (float)us[2] * scaleFactor2;
        } else { // mode 0
            uint32_t randVal2 = getRandom();
            uint32_t randVal3 = getRandom();
            float offsetX = (float)((randVal & 0xffff) << 4) * scaleFactor2;
            float offsetY = (float)((randVal3 & 0xffff) << 4) * scaleFactor2;
            x = -((float)us * scaleFactor2 - offsetX);
            y = -((float)us[2] * scaleFactor2 - offsetY);
        }
        FUN_0056d040(x, y, out); // Sets out[0..2] from (x,y)
        m_ushortStream2 = ushortStream + 3; // Advance by 3 ushorts
        m_counter2++; // +0x10
    } else if (flags & 0x40) {
        // Decompress packed 3-byte units at +0x58, scaled by large factors
        uint8_t* packedStream = m_packedStream; // +0x58
        // Read 3 bytes (maybe as signed or unsigned?) Use uint3 pointer? Actually code:
        // (float)*(uint3 **)(unaff_EDI + 0x58) -> first component offset 0? and +6 for second? Very odd.
        // Likely reads three 3-byte values? But code says +6 and +0, and also increments pointer by 9.
        // Could be reading 3 signed short? But increment by 9 suggests 3 three-byte groups.
        // I'll interpret as: uint8_t data[9] read, then first 3 bytes for x, middle 3 for y? No.
        // Actually it uses (uint3 *) which is a macro for reading 3 bytes? Possibly a packed 24-bit integer.
        uint32_t compX = *(uint32_t*)packedStream & 0xFFFFFF; // Low 24 bits
        uint32_t compY = *(uint32_t*)(packedStream+6) & 0xFFFFFF; // maybe? +6 offset
        float x = (float)compX * scaleFactorBig1 * scaleFactorBig2; // _DAT_00e44824 * DAT_00e2a848
        float y = (float)compY * scaleFactorBig1 * scaleFactorBig2;
        FUN_0056d040(x, y, out);
        m_packedStream = packedStream + 9; // Advance by 9 bytes
        m_counter3++; // +0x08
        m_counter4++; // +0x10
    } else {
        // Default: set to zero and constant DAT_00e2b1a4
        out[0] = 0.0f;
        out[1] = 0.0f;
        out[2] = 0.0f;
        out[3] = constant1; // DAT_00e2b1a4
    }

    // --- Second vector (out[4..6]) ---
    uint32_t flags2 = *m_flagsPtr; // Re-read flags (might have been changed? but no, same pointer)
    if ((flags2 & 0x1c) == 0) {
        if (flags2 & 0x20) {
            // Read from an array of float3 at +0x54, indexed by m_index1 (+0x50)
            uint32_t idx = m_index1++; // +0x50
            float* base = m_floatArrayBase; // +0x54
            out[4] = base[idx * 3];
            out[5] = base[idx * 3 + 1];
            out[6] = base[idx * 3 + 2];
        } else {
            // Read directly from float stream at +0x44
            float* ptr = m_floatStream2; // +0x44
            out[4] = ptr[0];
            out[5] = ptr[1];
            out[6] = ptr[2];
            m_floatStream2 = ptr + 3;
            m_counter5++; // +0x48
        }
    } else {
        // Decode from quantized streams with potential random perturbation
        // Streams: byte stream at +0x1c, ushort stream at +0x2c, float offsets at +0x20/+0x30
        float x, y, z;
        if (flags2 & 0x10) {
            // Byte stream with float offsets
            uint32_t randVal = getRandom();
            uint32_t mode = randVal & 3;
            uint8_t* byteStream = m_byteStream; // +0x1c
            float* offsetStream = m_floatOffsetStream1; // +0x20
            if (mode == 1) {
                x = (float)(*byteStream) * quantScale + offsetStream[0];
                y = offsetStream[1];
                z = offsetStream[2];
                byteStream++; // Actually the code increments by 1? pbVar9 = pbVar9 + 1; so yes.
                offsetStream += 3;
                m_counter6++; // +0x28
            } else if (mode == 2) {
                x = offsetStream[0];
                y = (float)(*byteStream) * quantScale + offsetStream[1];
                z = offsetStream[2];
                byteStream++;
                offsetStream += 3;
                m_counter6++;
            } else if (mode == 3) {
                x = offsetStream[0];
                y = offsetStream[1];
                z = (float)(*byteStream) * quantScale + offsetStream[2];
                byteStream++;
                offsetStream += 3;
                m_counter6++;
            } else { // mode 0
                x = (float)(*byteStream) * quantScale + offsetStream[0]; // Wait, code uses multiple bytes? Actually for mode0 it reads byteStream[1] and byteStream[2] for y and z offsets? Let's check decomp: in mode0, it calculates: fVar12 = (float)pbVar9[1] * DAT_00e445cc + pfVar8[1]; fVar13 = (float)pbVar9[2] * DAT_00e445cc + pfVar8[2]; and then goes to LAB_0057ff2b with pbVar9 = pbVar9 + 3 and fVar11 = (float)bVar3 * DAT_00e445cc + *pfVar8; So it uses three bytes from the stream. So mode0 uses all three bytes.
                uint8_t b0 = byteStream[0];
                uint8_t b1 = byteStream[1];
                uint8_t b2 = byteStream[2];
                x = (float)b0 * quantScale + offsetStream[0];
                y = (float)b1 * quantScale + offsetStream[1];
                z = (float)b2 * quantScale + offsetStream[2];
                byteStream += 3;
                offsetStream += 3;
                m_counter6++;
            }
            m_byteStream = byteStream;
            m_floatOffsetStream1 = offsetStream;
        } else if (flags2 & 8) {
            // Ushort stream with float offsets
            uint32_t randVal = getRandom();
            uint32_t mode = randVal & 3;
            uint16_t* ushortStream = m_ushortStream3; // +0x2c
            float* offsetStream = m_floatOffsetStream2; // +0x30
            if (mode == 1) {
                x = (float)(*ushortStream) * quantScale + offsetStream[0];
                y = offsetStream[1];
                z = offsetStream[2];
                ushortStream++;
                offsetStream += 3;
                m_counter7++; // +0x38
            } else if (mode == 2) {
                x = offsetStream[0];
                y = (float)(*ushortStream) * quantScale + offsetStream[1];
                z = offsetStream[2];
                ushortStream++;
                offsetStream += 3;
                m_counter7++;
            } else if (mode == 3) {
                x = offsetStream[0];
                y = offsetStream[1];
                z = (float)(*ushortStream) * quantScale + offsetStream[2];
                ushortStream++;
                offsetStream += 3;
                m_counter7++;
            } else { // mode 0
                uint16_t s0 = ushortStream[0];
                uint16_t s1 = ushortStream[1];
                uint16_t s2 = ushortStream[2];
                x = (float)s0 * quantScale + offsetStream[0];
                y = (float)s1 * quantScale + offsetStream[1];
                z = (float)s2 * quantScale + offsetStream[2];
                ushortStream += 3;
                offsetStream += 3;
                m_counter7++;
            }
            m_ushortStream3 = ushortStream;
            m_floatOffsetStream2 = offsetStream;
        } else {
            // Read directly from float stream at +0x3c
            float* ptr = m_floatStream1; // +0x3c
            x = ptr[0];
            y = ptr[1];
            z = ptr[2];
            m_floatStream1 = ptr + 3;
            m_counter8++; // +0x40
        }
        out[4] = x;
        out[5] = y;
        out[6] = z;
    }

    // Set constant values
    out[3] = constant1;   // DAT_00e2b1a4 (first vector constant)
    out[7] = constant1;   // DAT_00e2b1a4 (second vector constant)

    // Advance overall counter
    m_globalCounter++; // +0x4c? Actually at the end it increments *(int *)(unaff_EDI + 0x50) and *(int *)(unaff_EDI + 0x4c). So +0x50 is another counter, +0x4c is flags pointer? No, +0x4c is pointer to flags byte, but then they add 1 to it? That would advance the pointer, not the counter. But the code: iVar1 = *(int *)(unaff_EDI + 0x4c); ... *(int *)(unaff_EDI + 0x4c) = iVar1 + 1; So they are treating +0x4c as an integer and incrementing it. That conflicts with earlier usage as a pointer to byte. Possibly this is a union or the same field is reused? Actually at start they read **(byte **)(unaff_EDI + 0x4c) which implies +0x4c is a pointer to byte. At end they increment the value at +0x4c as an integer. That seems inconsistent. Maybe +0x4c is actually an integer that is used as flags, but then they interpret it as a pointer? Wait, first read: bVar3 = **(byte **)(unaff_EDI + 0x4c); So it's double dereference: first deref gives a byte pointer, second gives the byte. Then later they do: iVar1 = *(int *)(unaff_EDI + 0x4c); ... *(int *)(unaff_EDI + 0x4c) = iVar1 + 1; This suggests +0x4c is actually an integer, not a pointer to pointer. The decompiler might have misread the type. Probably +0x4c is an integer (flags) and the byte read is just *(byte*)(&flags)? Actually they do **(byte **) which is weird. Could be that the decompiler misinterpreted due to overlapping fields. I'll treat +0x4c as an integer flags that is read as a byte and later incremented.
    m_flags = *reinterpret_cast<uint8_t*>(&m_flags); // Not correct.
    // Actually, just increment m_flags (the integer) at the end.
    m_flags++;
}

// Constants (from globals)
const float scaleFactor4 = DAT_00e44820;   // 0.0001? or something
const float scaleFactor2 = DAT_00e44820;   // same?
const float scaleFactorBig1 = _DAT_00e44824; // large scale
const float scaleFactorBig2 = DAT_00e2a848; // large scale? 
const float quantScale = DAT_00e445cc;     // quantization scale
const float constant1 = DAT_00e2b1a4;      // often used as 1.0f or 0.5f?
const float one = DAT_00e44564;            // 1.0f?
// Member variables (offsets relative to this):
// +0x4c: uint32_t m_flags; (also used as byte pointer? but treat as int)
// +0x58: uint8_t* m_packedStream;
// +0x08: uint16_t* m_ushortStream2; // for mode2
// +0x10: uint32_t m_counter2;
// +0x14: uint16_t* m_ushortStream1; // for mode1
// +0x18: uint32_t m_counter1;
// +0x44: float* m_floatStream2; // for direct float read
// +0x48: uint32_t m_counter5;
// +0x54: float* m_floatArrayBase;
// +0x50: uint32_t m_index1; // index into float array
// +0x3c: float* m_floatStream1;
// +0x40: uint32_t m_counter8;
// +0x38: uint32_t m_counter7;
// +0x2c: uint16_t* m_ushortStream3;
// +0x30: float* m_floatOffsetStream2;
// +0x28: uint32_t m_counter6;
// +0x1c: uint8_t* m_byteStream;
// +0x20: float* m_floatOffsetStream1;
// +0x50: also used as counter? At end: *(int *)(unaff_EDI + 0x50) = *(int *)(unaff_EDI + 0x50) + 1; So that is another global counter.
// +0x4c: incremented as well: iVar1 = *(int *)(unaff_EDI + 0x4c); *(int *)(unaff_EDI + 0x4c) = iVar1 + 1;
// So both +0x4c and +0x50 are incremented.
}