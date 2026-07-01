// FUNC_NAME: resetTwoFields
void __thiscall resetTwoFields(void* this) {
    // +0x04: first field (e.g., m_startTime or m_x)
    *(int*)((char*)this + 4) = 0;
    // +0x08: second field (e.g., m_duration or m_y)
    *(int*)((char*)this + 8) = 0;
}