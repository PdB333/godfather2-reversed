// FUNC_NAME: SimSet::callOnUpdate
void SimSet::callOnUpdate() {
    uint32_t i = 0;
    // +0x0C: number of children (ushort)
    // +0x04: array of pointers to child objects (void**)
    if (*(int16_t*)((int)this + 0xC) != 0) {
        do {
            void* child = *(void**)((int)this + 4 + i * 4);
            // vtable +8: virtual method (likely onUpdate/process)
            (**(void(__thiscall***)(void*))((*(int*)child) + 8))(child);
            i++;
        } while (i < *(uint16_t*)((int)this + 0xC));
    }
}