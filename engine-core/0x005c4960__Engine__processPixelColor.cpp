// FUNC_NAME: Engine::processPixelColor
void __fastcall ColorProcessor::processPixel(uint32_t* color)
{
    // Global toggle: if non-zero, just rotate byte order (left rotate by 8 bits)
    if (*(uint8_t*)PTR_DAT_00f17650 != 0) {
        *color = (*color << 8) | (*color >> 24); // left rotate by 8 bits (likely BGRA to ARGB or similar)
        return;
    }

    // Extract 4 bytes (assuming packed RGBA in little-endian: byte0=R, byte1=G, byte2=B, byte3=A)
    // Actually from code: byte0 = *color & 0xFF; byte1 = *(byte*)((int)color+1); byte2 = *(byte*)((int)color+2); byte3 = *color >> 24
    uint8_t r = *color & 0xFF;
    uint8_t g = *((uint8_t*)color + 1);
    uint8_t b = *((uint8_t*)color + 2);
    uint8_t a = *color >> 24;

    // Convert to float and apply color transformation (e.g., linearize, grade, or gamma correction)
    __m128 values;
    values.m128_f32[0] = (float)r * _DAT_00e2b300 * _DAT_0119d0b0 + DAT_0119d0c0;
    values.m128_f32[1] = (float)g * _UNK_00e2b304 * _DAT_0119d0b4 + _DAT_0119d0c4;
    values.m128_f32[2] = (float)b * _UNK_00e2b308 * _DAT_0119d0b8 + _DAT_0119d0c8;
    values.m128_f32[3] = (float)a * _UNK_00e2b30c * DAT_0119d0bc + _DAT_0119d0cc;

    // Clamp to [0,1] range (SSE minps/maxps)
    values = _mm_min_ps(values, _DAT_00e2b2e0);
    values = _mm_max_ps(values, _DAT_00e2b2d0);

    // Scale and round to integer (pack back)
    uint32_t packedR = (uint32_t)(long long)(values.m128_f32[0] * _DAT_00e2b2f0);
    uint32_t packedG = (uint32_t)(long long)(values.m128_f32[1] * _UNK_00e2b2f4);
    uint32_t packedB = (uint32_t)(long long)(values.m128_f32[2] * _UNK_00e2b2f8);
    uint32_t packedA = (uint32_t)(long long)(values.m128_f32[3] * _UNK_00e2b2fc);

    // Combine back into uint32 (little-endian order: R in lowest byte)
    *color = (packedR) | (packedG << 8) | (packedB << 16) | (packedA << 24);
}