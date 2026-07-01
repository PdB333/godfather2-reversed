// FUNC_NAME: EARSObject::handleDeathEvent
void __thiscall EARSObject::handleDeathEvent(int *this, int eventType, int eventData)
{
  byte *pbVar1;
  int iVar2;
  byte local_c [12];
  
  // 0x20e5862 appears to be a specific death event type or hash
  if ((eventType == 0x20e5862) && (eventData != 0)) {
    iVar2 = this[5];  // +0x14 - health or state value
    pbVar1 = (byte *)(this + 5);  // +0x14
    FUN_004a3d60(local_c, pbVar1, this[4]);  // function to serialize/get state info
    
    if (iVar2 != *(int *)pbVar1) {
      if (this[3] != 0) {  // +0x0C - object pointer (player/entity)
        FUN_009d3070(*(int *)pbVar1);  // notify death to object
      }
      if ((*pbVar1 & 0x3f) != 0) {
        // non-zero state bits - call event handler at vtable+100 (0x64)
        (**(code **)(*this + 100))();  // vtable[25] - handleStateChange
        return;
      }
      // zero state bits - call dead handler at vtable+0x68 (104)
      (**(code **)(*this + 0x68))();  // vtable[26] - handleDeath
    }
  }
  return;
}