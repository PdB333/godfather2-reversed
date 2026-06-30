// FUNC_NAME: InputDeviceManager::initializeControllerSlots
// Address: 0x00566fb0
// Role: Allocates and initializes the 16-slot controller state array (each 0x44 bytes, total 0x440 bytes)
//        Copies initial data from param_2, then triggers a readiness callback and sets flags

void __thiscall InputDeviceManager::initializeControllerSlots(int thisPtr, undefined4 *pInitialData)
{
  undefined4 *pNewArray;
  int managerObj;
  undefined4 *pSrc;
  undefined4 *pDst;
  int i;

  if (pInitialData != (undefined4 *)0x0) {
    // Allocate memory for 16 XInput controller slots (16 * 0x44 = 0x440 bytes)
    pNewArray = (undefined4 *)allocMem(0x440);  // FUN_009c8e50
    if (pNewArray != (undefined4 *)0x0) {
      // Copy initial data (0x440 bytes = 0x110 dwords)
      pDst = pNewArray;
      pSrc = pInitialData;
      for (i = 0x110; i != 0; i--) {
        *pDst = *pSrc;
        pSrc++;
        pDst++;
      }
    }
    // Store the allocated array pointer at offset +0x11c
    *(undefined4 **)(thisPtr + 0x11c) = pNewArray;
  }

  // Fetch a singleton object (likely a manager, e.g., EventManager)
  managerObj = getSingletonManager();  // FUN_00ad8d40
  if ((managerObj != 0) && (*(code **)(thisPtr + 0x54) != (code *)0x0)) {
    // If a callback function pointer exists at +0x54, call it with the manager object
    (**(code **)(thisPtr + 0x54))(managerObj);
  }

  // Set flag at offset +0x2c: bit 5 (0x20) - mark controller array as initialized
  *(uint *)(thisPtr + 0x2c) |= 0x20;

  // Set state at offset +0x10 to 8 (likely a state enum value)
  *(undefined4 *)(thisPtr + 0x10) = 8;

  return;
}