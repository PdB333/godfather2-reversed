// FUNC_NAME: ActionOptions::findActionByAnimationId
void __thiscall ActionOptions::findActionByAnimationId(int this, int animationId, undefined1 *outActionType, int *outActionBase)
{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  if (*(short *)(this + 0x12) != 0) {
    // Iterate through linked list of action groups (offset +0x8 = head, +0x4 = next)
    for (iVar1 = *(int *)(this + 8); iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
      iVar2 = *(int *)(iVar1 + 0xc);
      if (iVar2 != 0) {
        // +0x30 = animation list array
        iVar3 = *(int *)(iVar2 + 0x30);
        uVar4 = 0;
        if (*(uint *)(iVar2 + 0x38) != 0) {  // +0x38 = number of animations
          do {
            // Each animation entry is 0x18 bytes, +0x14 = animation ID
            if (*(int *)(iVar3 + 0x14) == animationId) {
              // +0x58 + slot*4 = action offset table
              iVar3 = *(int *)(iVar2 + 0x58 + *(int *)(iVar3 + 4) * 4);
              *outActionType = *(undefined1 *)(iVar2 + 4);  // +0x04 = action type
              *outActionBase = iVar1;  // Return the action group base
              if (iVar3 != 0) {
                return;
              }
              break;
            }
            uVar4 = uVar4 + 1;
            iVar3 = iVar3 + 0x18;
          } while (uVar4 < *(uint *)(iVar2 + 0x38));
        }
      }
    }
  }
  return;
}