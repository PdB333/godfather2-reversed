// FUNC_NAME: NetConnection::setGuidKey
void __thiscall NetConnection::setGuidKey(int *this, int *pKey)
{
  int *piVar1;
  int iVar2;
  int uVar3;
  int *piVar4;
  
  // Compare the 16-byte GUID with the incoming key
  piVar4 = this + 0xc53; // +0xc53: mGuid (16 bytes stored as 4 ints)
  if ((((this[0xc53] == *pKey) && (this[0xc54] == pKey[1])) &&
       (this[0xc55] == pKey[2])) && (this[0xc56] == pKey[3])) {
    // GUIDs match
    // Check if the current GUID is all zero (null GUID) and the key node pointer is null
    if ((*piVar4 == 0) && (this[0xc54] == 0) &&
       ((this[0xc55] == 0 && (this[0xc56] == 0)))) {
      // Null GUID case: if there is an existing key node, release it and flush
      if (this[0xc57] != 0) { // +0xc57: mKeyNodePtr
        FUN_004df600(); // releaseKeyNode(mKeyNodePtr)
        pKey = (int *)0x10000;
        // Virtual call: flushSender()
        (**(code **)(this[0x16] + 0x28))(); // this[0x16] is some sender object (e.g., NetSender*)
        return;
      }
    }
    else {
      // Non-null GUID but the key node pointer is null: need to allocate a new key node
      if (this[0xc57] == 0) { // mKeyNodePtr == NULL
        uVar3 = (**(code **)(*this + 0x58))(0, this, 0, 0); // getObjectId() or getHandle()
        uVar3 = FUN_00471610(uVar3); // maybe convert handle
        uVar3 = FUN_004df330(&pKey, piVar4, uVar3); // cloneOrCreateKeyNode(pKey, &mGuid, uVar3)
        FUN_00414db0(uVar3); // possibly a debug or ref count operation
        if (pKey != (int *)0x0) {
          pKey[2] = 0; // clear a field in the key (e.g., ref count)
        }
        pKey = (int *)0x10000;
        (**(code **)(this[0x16] + 0x28))(); // flush sender
        return;
      }
    }
    return; // GUIDs match, nothing more
  }
  
  // GUIDs differ: copy new key into mGuid
  *(undefined8 *)piVar4 = *(undefined8 *)pKey; // copy first 8 bytes
  piVar1 = this + 0xc57; // pointer to mKeyNodePtr
  *(undefined8 *)(this + 0xc55) = *(undefined8 *)(pKey + 2); // copy second 8 bytes
  
  // If there was an existing key node, release it
  if (this[0xc57] != 0) {
    FUN_004df600(); // releaseKeyNode(mKeyNodePtr)
  }
  
  // If the new GUID is not all zero, allocate a new key node and link it
  if (((*piVar4 != 0) || (this[0xc54] != 0)) ||
     ((this[0xc55] != 0 || (this[0xc56] != 0)))) {
    uVar3 = (**(code **)(*this + 0x58))(0, this, 0, 0);
    uVar3 = FUN_00471610(uVar3);
    piVar4 = (int *)FUN_004df330(&pKey, piVar4, uVar3); // allocateKeyNode
    // Detach old key node (if any) and attach new one
    if (*piVar1 != 0) { // if mKeyNodePtr was non-null
      *(undefined4 *)(*piVar1 + 8) = 0; // clear next pointer of old node
      *piVar1 = 0;
    }
    iVar2 = *piVar4;
    *piVar1 = iVar2; // set mKeyNodePtr to the new node
    if (iVar2 != 0) {
      *(int **)(iVar2 + 8) = piVar1; // set next pointer of new node to point back to mKeyNodePtr? (likely a singly linked list)
      *piVar4 = 0; // clear the returned pointer
    }
    if (pKey != (int *)0x0) {
      pKey[2] = 0;
    }
  }
  
  pKey = (int *)0x10000;
  (**(code **)(this[0x16] + 0x28))(); // flush sender
  return;
}