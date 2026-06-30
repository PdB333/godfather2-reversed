// FUNC_NAME: swapAndCopyConditional
void __fastcall swapAndCopyConditional(uint32_t* dest, uint32_t* src)
{
    // Swap first two fields: dest[0] = src[1], dest[1] = src[0]
    dest[0] = src[1];
    dest[1] = src[0];

    // Conditionally copy third field: if both src[1] and src[2] are non-null,
    // then dest[2] = *(uint32_t*)(src[2] + 4), else dest[2] = 0
    if ((src[1] != 0) && (src[2] != 0)) {
        dest[2] = *(uint32_t*)(src[2] + 4);
    } else {
        dest[2] = 0;
    }
}