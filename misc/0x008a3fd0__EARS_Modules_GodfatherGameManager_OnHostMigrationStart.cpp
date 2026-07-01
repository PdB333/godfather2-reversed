// Xbox PDB: EARS_Modules_GodfatherGameManager_OnHostMigrationStart
// FUNC_NAME: MultiplayerScenarioManager::hostMigration
void MultiplayerScenarioManager::hostMigration(int param_1)

{
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  FUN_0040c1f0(0xff000000,DAT_00d5c454,1,1);
  if (DAT_01129c4c != 0) {
    FUN_0093c210();
    FUN_00983190();
  }
  local_c = DAT_0112b2a4;
  local_8 = 0;
  local_4 = 0;
  FUN_00408a00(&local_c,0);
  FUN_004bf0f0(param_1);
  FUN_00983120("$mp_host_migrating",0,0);
  return;
}