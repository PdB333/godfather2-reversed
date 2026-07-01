// FUNC_NAME: GodfatherGameManager::shutdown
void __fastcall GodfatherGameManager::shutdown(GodfatherGameManager *this)
{
  *this = &PTR_FUN_00d82660;
  if (this->field_0x21f != (int *)0x0) {
    (**(code **)(*this->field_0x21f + 0x10))(1);
  }
  FUN_00906a60(); // likely cleanupAudio
  FUN_009064b0(); // likely cleanupInput
  this->field_0x86 = &PTR_FUN_00d82630;
  this->field_0x108 = &PTR_LAB_00d8262c;
  FUN_00905600(); // likely cleanupRendering
  FUN_00412230(); // likely cleanupMemory
  FUN_004c3460(); // likely cleanupNetworking
  *this = &PTR_LAB_00d825a0;
  DAT_01129894 = 0;
  return;
}