// FUN_0064c430: GhostEntity::writeCompressedPosition
void GhostEntity::writeCompressedPosition(const float* pos, float scale)
{
    // offsets from this
    // +0x1d: bool useDistanceCompression (flag)
    // +0x20: float positionX (stored reference position)
    // +0x24: float positionY
    // +0x28: float positionZ
    float dx, dy, dz;
    float level;  // encoded as subnormal float: 0.0f, 1.4013e-45f, 2.8026e-45f, 4.2039e-45f

    dx = 0.0f;
    dy = 0.0f;
    dz = 0.0f;

    if (*(char*)(this + 0x1d) != '\0') {
        // Compute vector from stored position to the given position
        dx = pos[0] - *(float*)(this + 0x20);
        dy = pos[1] - *(float*)(this + 0x24);
        dz = pos[2] - *(float*)(this + 0x28);

        float dist = sqrtf(dx*dx + dy*dy + dz*dz);
        float scaledDist = dist * (DAT_00e2b1a4 / scale);  // DAT_00e2b1a4 is likely a global scale factor

        if (scaledDist < DAT_00e44690) {
            level = 0.0f;
            goto write_level;
        }
        if (scaledDist < DAT_00e448b4) {
            level = 1.4013e-45f;     // subnormal for integer 1
            goto write_level;
        }
        level = 2.8026e-45f;         // subnormal for integer 2
        if (scaledDist < DAT_00e448b0) {
            goto write_level;
        }
    }
    level = 4.2039e-45f;             // subnormal for integer 3 (full precision)

write_level:
    // Write the chosen level (2-bit value) into the bitstream
    writeBits(2, &level);  // FUN_0064b810: writeBitstreamData

    if (level != 4.2039e-45f) {
        // Compressed representation: look up offset or index from a global table
        uint32_t index = (uint32_t)level;  // subnormal -> integer cast gives 0,1,2
        uint32_t uVar1 = DAT_00f0cdc4[index];
        // Write the compressed vector using three calls (probably component encoding)
        writeCompressedVector(uVar1);  // FUN_0064be30 called three times
        writeCompressedVector(uVar1);
        writeCompressedVector(uVar1);
        return;
    }

    // Full precision: write each component as 32-bit float
    writeBits(0x20, &pos[0]);  // size = 32 bits
    writeBits(0x20, &pos[1]);
    writeBits(0x20, &pos[2]);
}