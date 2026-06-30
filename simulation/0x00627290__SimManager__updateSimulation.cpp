// FUNC_NAME: SimManager::updateSimulation
undefined4 SimManager::updateSimulation(void)
{
  undefined4 *puVar1;
  int in_EAX;
  undefined4 uVar2;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  int local_4;
  
  // Get the simulation time from the object at offset +0x10
  local_4 = *(int *)(in_EAX + 0x10);
  
  // Initialize a time delta structure (likely a timer or frame delta)
  local_14 = 0;
  local_c = 0;
  local_10 = 0;
  local_8 = 0;
  
  // Call functions to set up the time delta
  FUN_00627220(&local_14);  // Likely getCurrentTime or similar
  FUN_00626d10(&local_14);  // Likely calculateDeltaTime
  FUN_00626e20();           // Likely beginFrame or preUpdate
  FUN_00626e20();           // Another preUpdate call (maybe for different systems)
  
  // Reset the time delta for simulation
  local_8 = 0;
  local_c = 0;
  
  // Get the current simulation state
  uVar2 = FUN_006266e0();   // Likely getSimulationState or isSimulationRunning
  
  // Iterate through a linked list of objects (likely sim objects or entities)
  // The list head is at offset +0x14 from the simulation time pointer
  for (puVar1 = *(undefined4 **)(local_4 + 0x14); puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)*puVar1) {
    // Clear a flag at offset +0x5 (bit 0) - likely a "dirty" or "updated" flag
    *(byte *)((int)puVar1 + 5) = *(byte *)((int)puVar1 + 5) & 0xfe;
    // Call update on each object
    FUN_00626640();          // Likely updateObject or processObject
  }
  
  // Finalize the time delta and perform post-update operations
  FUN_00626d10(&local_14);  // Likely finalizeDeltaTime
  FUN_00626dc0();           // Likely endFrame or postUpdate
  FUN_00626dc0();           // Another postUpdate call
  FUN_00626e20();           // Likely swapBuffers or present
  FUN_00626dc0();           // Another postUpdate
  FUN_00626e20();           // Final swap/present
  
  return uVar2;
}