// Xbox PDB: EARS::Apt::Apt1By1AnimationSubscriber::UpdateAnimation
// FUNC_NAME: FlashMoviePlayer::handleStateChange
void __fastcall FlashMoviePlayer::handleStateChange(int this)
{
  int in_EAX;
  uint uVar1;
  int iVar2;
  size_t _Size;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_44 [4];
  char local_40 [64];
  
  iVar4 = param_1 * 0x114 + *(int *)(in_EAX + 0x10);
  uVar1 = *(uint *)(iVar4 + 0x10c) & 0x38;
  *(uint *)(iVar4 + 0x10c) = uVar1 | 4;
  if (uVar1 == 8) {
    // State: Loading -> copy default data
    FUN_0059f8d0(iVar4 + 0x44,iVar4 + 0x44,0x40);
    uVar3 = FUN_005cde50(0x7fffffff);
    *(undefined4 *)(iVar4 + 0x104) = uVar3;
    *(undefined4 *)(iVar4 + 0x108) = 0xffffffff;
    FUN_005ca250();
  }
  else if (uVar1 == 0x10) {
    // State: Playing -> save variable file
    __snprintf(local_40,0x40,"%s/%s%d.var",iVar4 + 4,iVar4 + 0x84,*(undefined4 *)(iVar4 + 0x108));
    iVar2 = FUN_005cde50(*(undefined4 *)(iVar4 + 0x108));
    _Size = FUN_005cde50(1);
    if (0 < (int)_Size) {
      _memcpy(local_44,(void *)(iVar2 + 0x44 + iVar4),_Size);
    }
    local_44[_Size] = 0;
    FUN_0059eb30(local_40,local_44);
    __snprintf(local_40,0x40,"%s/%s%d",iVar4 + 4,iVar4 + 0x84,*(undefined4 *)(iVar4 + 0x108));
    FUN_005a04a0("gotoAndPlay",0,local_40,1,"lStart");
    *(uint *)(iVar4 + 0x10c) = *(uint *)(iVar4 + 0x10c) & 6 | 0x20;
    return;
  }
  return;
}