// FUNC_NAME: SystemManager::initializeSystem
void __fastcall SystemManager::initializeSystem(SystemManager* self)
{
    self->field04 = 1;                      // +0x04: e.g., bActive
    self->field08 = 0;                      // +0x08: e.g., iCount
    self->field0C = &PTR_LAB_00d5d9ac;      // +0x0C: temporary pointer (see below)
    g_systemManagerInstance = self;         // store global singleton
    self->vtable = &PTR_FUN_00d5d9b8;       // +0x00: virtual function table
    self->field0C = &PTR_LAB_00d5d9b4;      // +0x0C: final pointer (overwrites previous)
    self->field10 = 0;                      // +0x10: some handle or counter
    self->field14 = 0;                      // +0x14
    self->field18 = 0;                      // +0x18
    self->field1C = 0xFFFFFFFF;             // +0x1C: e.g., invalid index
    self->field20 = 0;                      // +0x20
}