// FUNC_NAME: BitStream::writeTransformPacked
void __thiscall BitStream::writeTransformPacked(void *this, const float *vec1, const float *vec2, const float *vec3)
{
    // Structure offsets:
    // +0x00: buffer base pointer (not used here)
    // +0x08: current write pointer (uint8_t**)
    // +0x18: buffer end pointer (uint8_t**)
    uint8_t** writePtr = *(uint8_t***)((uint8_t*)this + 0x8);
    float* dest = (float*)*writePtr;

    // Copy three 8-byte vectors (each two floats) into the write buffer
    dest[0] = vec1[0]; dest[1] = vec1[1];
    dest[2] = vec2[0]; dest[3] = vec2[1];
    dest[4] = vec3[0]; dest[5] = vec3[1];

    uint8_t* currentWrite = *(uint8_t**)((uint8_t*)this + 0x8);
    // Check if there is enough space (0x18 bytes + some safety margin)
    if ((*(uint8_t**)((uint8_t*)this + 0x18) - currentWrite) < 0x19) {
        expandBuffer();  // FUN_00635c70 - increase buffer capacity
    }

    // Advance write pointer by 24 bytes (three 8-byte vectors)
    *(uint8_t**)((uint8_t*)this + 0x8) = currentWrite + 0x18;
    // Encode the just-written 24-byte block using delta compression (flag=1)
    encodeDeltaBlock(this, currentWrite, 1);  // FUN_006362d0
    // After encoding, the block is compressed; adjust write pointer back by 8 bytes
    // (actual consumed space = 16 bytes)
    *(uint8_t**)((uint8_t*)this + 0x8) = currentWrite + 0x10;
}