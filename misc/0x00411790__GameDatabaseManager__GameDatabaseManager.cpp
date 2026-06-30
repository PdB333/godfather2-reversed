// FUNC_NAME: GameDatabaseManager::GameDatabaseManager
void GameDatabaseManager::GameDatabaseManager(void)
{
  // +0x00: vtable pointer (set to &PTR_FUN_00e2f4c8)
  // +0x04: some flag (set to 1)
  // +0x08: some flag (set to 0)
  // +0x0C: pointer to a label (initially set to &PTR_LAB_00e2f4dc, then overwritten with &PTR_LAB_00e2f4d8)
  // +0x10: some flag (set to 0)
  // +0x94: some flag (set to 0)
  // Global DAT_012233b8 stores the singleton instance pointer.

  this->field_0x04 = 1;                                      // unaff_ESI[1] = 1
  this->field_0x08 = 0;                                      // unaff_ESI[2] = 0
  this->field_0x0C = &PTR_LAB_00e2f4dc;                      // unaff_ESI[3] = &PTR_LAB_00e2f4dc
  this->vtable = &PTR_FUN_00e2f4c8;                          // *unaff_ESI = &PTR_FUN_00e2f4c8
  this->field_0x0C = &PTR_LAB_00e2f4d8;                      // unaff_ESI[3] = &PTR_LAB_00e2f4d8 (override)
  this->field_0x10 = 0;                                      // unaff_ESI[4] = 0
  DAT_012233b8 = this;                                       // store singleton pointer

  this->field_0x94 = 0;                                      // unaff_ESI[0x25] = 0 (0x25*4 = 0x94)

  // Register message handlers for game database loading events
  uint32_t msgLoaded = FUN_004dafd0("iMsgGameDatabaseLoaded");
  FUN_00408260(&DAT_01206a20, msgLoaded);   // likely MessageSystem::registerMessage or Observer pattern

  uint32_t msgLoading = FUN_004dafd0("iMsgGameDatabaseLoading");
  FUN_00408260(&DAT_01206a28, msgLoading);
}