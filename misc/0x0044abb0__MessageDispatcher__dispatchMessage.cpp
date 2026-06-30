// FUNC_NAME: MessageDispatcher::dispatchMessage
void __fastcall MessageDispatcher::dispatchMessage(Message* pMessage)
{
  int* piVar1;
  code* callbackFunc;
  int iVar3;
  uint uVar4;
  undefined4* puVar5;
  int* piVar6;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;

  // pMessage->type == 0 or == 0x48 (MESSAGE_TYPE_STANDARD)
  if ((*(int*)(pMessage + 0xc) == 0) || (*(int*)(pMessage + 0xc) == 0x48)) {
    piVar1 = *(int**)(pMessage + 4);  // +0x04: message id pointer
    uVar4 = 0;
    // g_MessageManager at DAT_01223410
    if (*(uint*)(g_MessageManager + 0x2d0) != 0) {  // +0x2d0: number of registered callbacks
      piVar6 = (int*)(g_MessageManager + 0xd0);  // +0xd0: array of (id, callback) pairs
      while (*piVar6 != *piVar1) {
        uVar4 = uVar4 + 1;
        piVar6 = piVar6 + 2;
        if (*(uint*)(g_MessageManager + 0x2d0) <= uVar4) {
          return;  // No matching callback found
        }
      }
      callbackFunc = (code*)piVar6[1];  // callback function pointer
      if (callbackFunc != (code*)0x0) {
        // Call virtual method at vtable+0x1c on object pointed by pMessage+0x08
        (**(code**)(**(int**)(*(int*)(pMessage + 8) + 8) + 0x1c))();
        
        // Prepare stack with debug markers
        uStack_28 = 0xbadbadba;
        uStack_24 = 0xbeefbeef;
        uStack_20 = 0xeac15a55;
        uStack_1c = 0x91100911;
        
        // Get message data from a helper (FUN_00449be0)
        puVar5 = (undefined4*)getMessageData(*(undefined2*)(pMessage + 0x18));  // +0x18: message data key (short)
        uStack_28 = *puVar5;
        uStack_24 = puVar5[1];
        uStack_20 = puVar5[2];
        uStack_1c = puVar5[3];
        
        // Call the registered callback with message id, data buffer, and zero arguments
        (*callbackFunc)(*piVar1, &uStack_28, 0, 0, 4);
      }
    }
  } else {
    // Other message types: offset 0x48 indicates a different object layout
    if (*(int*)(pMessage + 0xc) == 0) {
      iVar3 = 0;
    } else {
      iVar3 = *(int*)(pMessage + 0xc) - 0x48;
    }
    // Check if object at offset +0x130 has a vtable with method at offset 100 (0x64)
    if (*(int**)(iVar3 + 0x130) != (int*)0x0) {
      (**(code**)(**(int**)(iVar3 + 0x130) + 100))();  // virtual call at offset 100
    }
  }
  return;
}