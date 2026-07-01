// FUNC_NAME: SimNpc::isDeadOrDying
bool __fastcall SimNpc::isDeadOrDying(int this)
{
    uint flags = *(uint *)(*(int *)(this + 0x58) + 0x8e4); // +0x58: m_pSimObject, +0x8e4: m_npcStateFlags
    bool result = false;
    if (((flags >> 0x1e & 1) != 0) || ((int)flags < 0)) {
        result = true;
    }
    return result;
}