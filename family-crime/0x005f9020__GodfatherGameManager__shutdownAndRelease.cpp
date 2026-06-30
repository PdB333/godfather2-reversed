// FUNC_NAME: GodfatherGameManager::shutdownAndRelease
void GodfatherGameManager::shutdownAndRelease(void)
{
  FUN_005f9c80();  // some cleanup method, perhaps destroyVehicleManager or destroyAudioManager
  (**(code **)(*(int *)*in_EAX + 4))(in_EAX[6],0xc);  // release with delete/operator delete(?, 0xc) – size 12
  in_EAX[6] = 0;  // pointer nulled – likely a manager object (e.g., m_vehicleManager)
  if (in_EAX[5] != 0) {
    (**(code **)(*(int *)in_EAX[4] + 4))(in_EAX[5],0);  // release (probably free with size=0 or using operator delete)
    in_EAX[5] = 0;  // pointer nulled – e.g., m_audioManager
  }
  (**(code **)(*(int *)in_EAX[4] + 0xc))();  // vtable call at offset 0x0c – likely shutdown() or releaseAssets()
  FUN_005f94d0();  // cleanup rest (maybe destroy singletons)
  return;
}