// FUNC_NAME: AptAnimation::initConstants
void AptAnimation::initConstants(void* parent, int param2, int param3) {
    // m_constantsOffset (+0x1c) stores a relative offset to constant data.
    // Assert that the offset is sane (< 0xfffff)
    if (*(uint32_t*)((uintptr_t)this + 0x1c) >= 0xfffffu) {
        char* expr = "(unsigned)(pConstFile->aConstants) < 0xfffff";
        char* file = "..\\source\\Apt\\AptAnimation.cpp";
        int line = 0xa7;
        int assertLevel = 2;
        char& assertGlobal = *reinterpret_cast<char*>(0x01128f8b);
        if (assertGlobal != '\0') {
            int* debugInfo = *(int**)(*(intptr_t*)(__readfsdword(0x2c) + 0x2c) + 0x30);
            uint flags = 1;
            if (debugInfo != nullptr) {
                flags = (*(uint(__cdecl**)(char**, char*))*debugInfo)(&expr, expr);
            }
            if ((flags & 2) != 0) {
                assertGlobal = 0;
            }
            if ((debugInfo == nullptr && assertLevel != 4) ||
                ((flags & 1) != 0 || (assertLevel == 0 || assertLevel == 1))) {
                __debugbreak(); // swi(3)
            }
        }
    }

    // Convert relative offset to absolute pointer if non-zero
    if (*(int32_t*)((uintptr_t)this + 0x1c) != 0) {
        *(int32_t*)((uintptr_t)this + 0x1c) += (int32_t)this;
    }

    // Clear parent field at +0x30
    *(int32_t*)((uintptr_t)parent + 0x30) = 0;

    // Call internal constant loading function
    sub_5a4850(parent, param2, this, param3);

    // Restore offset to relative form
    if (*(int32_t*)((uintptr_t)this + 0x1c) != 0) {
        *(int32_t*)((uintptr_t)this + 0x1c) -= (int32_t)this;
    }
}