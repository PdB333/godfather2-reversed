// FUNC_NAME: getObjectTransform
void getObjectTransform(void* obj, float* outTransform) {
    // Access thread-local storage (FS segment offset 0x2c) to get global game data pointer
    // Then offset by +8 to reach some base array pointer, then +0x80 to reach transform table
    // Use offset from obj+0x10 as index into that table
    uint32_t* transformSource = (uint32_t*)(
        *(uint32_t*)(
            *(uint32_t*)(__readfsdword(0x2c) + 8)  // Global game data base
        ) + 0x80 + *(uint32_t*)((char*)obj + 0x10) // Index from object field at +0x10
    );

    // Copy 16 bytes (4 floats) – likely a 4x4 matrix row, quaternion, or 4D vector
    outTransform[0] = *(float*)&transformSource[0];
    outTransform[1] = *(float*)&transformSource[1];
    outTransform[2] = *(float*)&transformSource[2];
    outTransform[3] = *(float*)&transformSource[3];
}