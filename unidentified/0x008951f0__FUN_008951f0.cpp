// FUNC_NAME: SomeClass::releaseOrFreeResources
void SomeClass::releaseOrFreeResources(void)
{
  // Free/release two global resources identified by their handles/pointers
  FUN_004086d0(&DAT_0112e31c);  // Release resource at 0x0112e31c
  FUN_004086d0(&DAT_01218048);  // Release resource at 0x01218048
  return;
}