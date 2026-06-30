// FUNC_NAME: NetSession::NetSession
undefined4* __thiscall NetSession::NetSession(undefined4* this, undefined4 configParam)
{
    undefined4 handle;

    g_pNetSession = this;
    this[1] = 0;          // +0x04: m_networkHandle or similar
    this[2] = 0;          // +0x08: unknown field
    this[3] = 0;          // +0x0C: unknown field
    this[0] = &PTR_FUN_00e3aa80; // vtable
    handle = createNetworkInterface(configParam, 0);
    this[1] = handle;
    return this;
}