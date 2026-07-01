// FUNC_NAME: SomeManager::releaseSomeResources
void SomeManager::releaseSomeResources(void)
{
  // Release four resources at offsets 0x0112db64, 0x0112db74, 0x0112db6c, 0x0112db7c
  // These are likely static or global resource handles/pointers
  FUN_00408310(&DAT_0112db64);
  FUN_00408310(&DAT_0112db74);
  FUN_00408310(&DAT_0112db6c);
  FUN_00408310(&DAT_0112db7c);
  return;
}