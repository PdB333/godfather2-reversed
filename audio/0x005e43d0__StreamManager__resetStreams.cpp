// FUNC_NAME: StreamManager::resetStreams
void StreamManager::resetStreams(void)
{
  // Call base class destructor or reset
  StreamManager::resetStream(unaff_ESI);
  
  // Clear stream slot 0
  *(undefined4 *)(unaff_ESI + 0x6018) = 0;  // Stream slot 0 state
  FUN_009c8f10(*(undefined4 *)(unaff_ESI + 0x6014));  // Free stream slot 0 buffer
  *(undefined4 *)(unaff_ESI + 0x6014) = 0;  // Clear stream slot 0 buffer pointer
  
  // Clear stream slot 1
  *(undefined4 *)(unaff_ESI + 0x601c) = 0;  // Stream slot 1 state
  *(undefined4 *)(unaff_ESI + 0x6024) = 0;  // Stream slot 1 state (duplicate?)
  FUN_009c8f10(*(undefined4 *)(unaff_ESI + 0x6020));  // Free stream slot 1 buffer
  *(undefined4 *)(unaff_ESI + 0x6020) = 0;  // Clear stream slot 1 buffer pointer
  
  // Clear stream slot 2
  *(undefined4 *)(unaff_ESI + 0x6028) = 0;  // Stream slot 2 state
  *(undefined4 *)(unaff_ESI + 0x6030) = 0;  // Stream slot 2 state (duplicate?)
  FUN_009c8f10(*(undefined4 *)(unaff_ESI + 0x602c));  // Free stream slot 2 buffer
  piVar1 = DAT_01223510;
  *(undefined4 *)(unaff_ESI + 0x602c) = 0;  // Clear stream slot 2 buffer pointer
  
  // Clear stream slot 3
  *(undefined4 *)(unaff_ESI + 0x6034) = 0;  // Stream slot 3 state
  
  // Call virtual function to finalize reset
  (**(code **)(*piVar1 + 0xc))();
  return;
}