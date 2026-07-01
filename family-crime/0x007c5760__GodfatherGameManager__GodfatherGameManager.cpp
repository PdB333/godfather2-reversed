// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
undefined4 * __thiscall GodfatherGameManager::GodfatherGameManager(undefined4 *this, undefined4 param_2, undefined4 param_3)
{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;

  // Call base class constructor
  GameManager::GameManager(param_2, param_3);
  // Set vtable pointer
  *this = &PTR_LAB_00d6e7c4;
  // Initialize various fields to zero (offsets 0x74, 0x90, 0x80, 0x7C, 0x78, 0x8C, 0x88, 0x84)
  this[0x1d] = 0;
  this[0x24] = 0;
  this[0x20] = 0;
  this[0x1f] = 0;
  this[0x1e] = 0;
  this[0x23] = 0;
  this[0x22] = 0;
  this[0x21] = 0;
  // Debug/log call
  debugLog(0);
  // Set a flag (0x5D)
  setFlag(0x5d);
  // Get some manager instance
  iVar2 = getSomeManager();
  // Check if a feature is enabled at offset +0x10 in that manager
  cVar1 = isFeatureEnabled(iVar2 + 0x10);
  if (cVar1 != '\0') {
    // Set bit 0x400 at offset 0x24A4 in the structure pointed to by this[0x16] (offset 0x58)
    *(uint *)(this[0x16] + 0x24a4) = *(uint *)(this[0x16] + 0x24a4) | 0x400;
  }
  // Get input manager
  iVar2 = getInputManager();
  // Store its +4 value (likely an ID) at offset 0x94
  this[0x25] = *(undefined4 *)(iVar2 + 4);
  // Call a method on the input manager with argument 0x3F
  puVar3 = (undefined4 *)getInputManager();
  (**(code **)*puVar3)(0x3f);
  // Get audio manager
  iVar2 = getAudioManager();
  // Store its +4 value at offset 0x98
  this[0x26] = *(undefined4 *)(iVar2 + 4);
  // Call a method on the audio manager with argument 0x3FF
  puVar3 = (undefined4 *)getAudioManager();
  (**(code **)*puVar3)(0x3ff);
  // Get physics manager
  iVar2 = getPhysicsManager();
  // Store its +4 value at offset 0x9C
  this[0x27] = *(undefined4 *)(iVar2 + 4);
  // Call a method on the physics manager with argument 2
  puVar3 = (undefined4 *)getPhysicsManager();
  (**(code **)*puVar3)(2);
  // Call again with argument 1
  puVar3 = (undefined4 *)getPhysicsManager();
  (**(code **)*puVar3)(1);
  // Set another flag (0x31)
  setFlag(0x31);
  // Get resource manager and create a resource with ID 0x1FF
  uVar4 = 0x1ff;
  getResourceManager(0x1ff);
  uVar4 = createResource(uVar4);
  // Store the resource handle at offset 0xA0
  this[0x28] = uVar4;
  return this;
}