// FUNC_NAME: IStreamManager::resetAndReleaseBanks
void __thiscall IStreamManager::resetAndReleaseBanks(void)
{
  // local array of 12 bytes (likely a buffer for bank stream name or ID)
  char streamBuffer[12];
  
  // FUN_005e0410: release bank streaming resources using the manager state
  // in_EAX points to the IStreamManager object
  // *(* (in_EAX+0x04) + 4) is a vtable call on the bank stream object at in_EAX+0x1c
  FUN_005e0410(streamBuffer, in_EAX, **(undefined4 **)(in_EAX + 0x1c), in_EAX,
               *(undefined4 **)(in_EAX + 0x1c));
  
  // Call vtable function at offset 4 on the bank stream object (usually a release/free)
  (**(code **)(**(int **)(in_EAX + 4) + 4))(*(undefined4 *)(in_EAX + 0x1c), 0x18);
  
  // Clear bank stream pointers at +0x1c and +0x20
  *(undefined4 *)(in_EAX + 0x1c) = 0;
  *(undefined4 *)(in_EAX + 0x20) = 0;
  
  // If there's a secondary buffer/stream at +0x18, release it via its vtable
  if (*(int *)(in_EAX + 0x18) != 0) {
    (**(code **)(**(int **)(in_EAX + 0x14) + 4))(*(int *)(in_EAX + 0x18), 0);
    *(undefined4 *)(in_EAX + 0x18) = 0;
  }
  
  // Call vtable function at offset 0xc on the object at +0x14 (likely a final cleanup)
  (**(code **)(**(int **)(in_EAX + 0x14) + 0xc))();
  
  // Reset any pending bank stream state (maybe clear queue or counters)
  FUN_005df430();
  
  return;
}