// FUNC_NAME: NPCManager::updateAnimTimer

void __thiscall NPCManager::updateAnimTimer(int *this, void *context)
{
  int iVar1;
  char cVar2;
  int unaff_ESI;
  int local_c[2];
  int *piStack_4;

  if ((this[0x4c] != 0) && ((float)this[0x7a6] != DAT_00d577a0)) {
    cVar2 = isAnimationActive();
    if (cVar2 != '\0') {
      (**(code **)(*this + 0xa4))(local_c);
      iVar1 = this[0x7a6];
      *piStack_4 = (int)(this + 0x1b9);
      piStack_4[1] = unaff_ESI;
      piStack_4[2] = local_c[0];
      piStack_4[3] = iVar1;
      processAnimationEvent(piStack_4);
      return;
    }
  }
  updateTimerFromDelta(context);
  this[0x7a6] = *(int *)((int)context + 0xc);
  return;
}