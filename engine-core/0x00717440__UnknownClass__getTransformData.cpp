// FUNC_NAME: UnknownClass::getTransformData
bool __thiscall UnknownClass::getTransformData(void* this, float out[3]) {
    int* member_ptr = *(int**)((char*)this + 0x18);
    void* obj;

    if (member_ptr != nullptr) {
        obj = FUN_0043b870(g_GlobalDAT_0113105c);
        if (obj != nullptr && ((*(uint8_t*)((char*)obj + 0x78) >> 2 & 1) != 0)) {
            void* result = FUN_009b2900();
            if (result == nullptr) {
                return false;
            }
            void* data = FUN_00471610();
            // Copy 12 bytes: offsets 0x30 and 0x38 from data
            *(uint64_t*)out = *(uint64_t*)((char*)data + 0x30);
            *(uint32_t*)((uint8_t*)out + 8) = *(uint32_t*)((char*)data + 0x38);
            return true;
        }

        // Fallback to second global source
        obj = FUN_0043b870(g_GlobalDAT_01131064);
        if (obj != nullptr && ((*(uint8_t*)((char*)obj + 0x2c) & 1) != 0) && ((int8_t)*(uint8_t*)((char*)obj + 0x2c) >= 0)) {
            // Copy 12 bytes: offsets 0x18 and 0x20 from obj
            *(uint64_t*)out = *(uint64_t*)((char*)obj + 0x18);
            *(uint32_t*)((uint8_t*)out + 8) = *(uint32_t*)((char*)obj + 0x20);
            return true;
        }
    }
    return false;
}