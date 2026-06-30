// FUNC_NAME: Camera::cullAndAddVisibleObjects

void Camera::cullAndAddVisibleObjects(int param_2, undefined4 param_3, Scene* scene, byte param_5, code* callback)
{
  float fVar1;
  int iVar2;
  char cVar3;
  uint frameFlags;
  uint uVar4;
  byte bVar5;
  uint uVar6;
  int objIndex;
  int index;
  int local_8;

  enterCriticalSection(1);
  uVar4 = getFrameFlags();                      // FUN_0042e5e0
  uVar6 = frameFlags >> 0xc;                    // probably bits from EAX
  bVar5 = (byte)uVar6 & 1;
  if ((param_2 != 0) && (*(int *)(this + 0x39f8) == 0)) {
    uVar4 = uVar4 | (uint)DAT_012053d8 << 8;
  }
  setSomeGlobalState(uVar4);                    // FUN_0042a3f0

  if (((((uVar6 & 1) == 0) && (param_5 == bVar5)) &&
      (((byte)(frameFlags >> 4) & 1) == bVar5)) &&
     (callback == (code *)0x0)) {
    // Fast path: no callback, simple iteration
    if (objIndex == 0) goto LAB_0043042d;
    do {
      cVar3 = testVisibility(*(undefined4 *)(objIndex + 0x10), *(undefined4 *)(objIndex + 0xc),
                             *(undefined4 *)(objIndex + 8), param_3);
      if (cVar3 != '\0') {
        addToVisibleList();
      }
      index = index + 1;
    } while ((index < (int)(uint)*(ushort *)(scene + 0x1a)) &&
            (objIndex = (uint)*(ushort *)(*(int *)(scene + 0x1c) + index * 2) * 0x20 +
                        *(int *)(scene + 0x10), objIndex != 0));
  } else {
    // Full path with filtering
    local_8 = index;                             // local_8 is the loop counter, was unused
    if (objIndex == 0) goto LAB_0043042d;
    do {
      iVar2 = *(int *)(objIndex + 0x10);
      if (((((((uVar6 & 1) == 0) || ((*(uint *)(iVar2 + 8) & 0x1000) == 0)) &&
            ((param_5 == 0 ||
             (fVar1 = *(float *)(*(int *)(objIndex + 0xc) + 0x34),
             fVar1 < *(float *)(this + 0x39f4) || fVar1 == *(float *)(this + 0x39f4))))) &&
           (((frameFlags >> 4 & 1) == 0 || ((*(byte *)(iVar2 + 8) & 0x10) != 0)))) &&
          ((callback == (code *)0x0 ||
           (cVar3 = (*callback)(*(undefined4 *)(iVar2 + 0x5c), param_2), cVar3 == '\0')))) &&
         (cVar3 = testVisibility(iVar2, *(undefined4 *)(objIndex + 0xc), *(undefined4 *)(objIndex + 8),
                                 param_3), cVar3 != '\0')) {
        addToVisibleList();
      }
      local_8 = local_8 + 1;
    } while ((local_8 < (int)(uint)*(ushort *)(scene + 0x1a)) &&
            (objIndex = (uint)*(ushort *)(*(int *)(scene + 0x1c) + local_8 * 2) * 0x20 +
                        *(int *)(scene + 0x10), objIndex != 0));
  }
  finishVisibilityCheck();                      // FUN_0042f240
LAB_0043042d:
  leaveCriticalSection(1);
  return;
}