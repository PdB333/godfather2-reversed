// FUNC_NAME: DebugMenuHandler::selectItem
void __thiscall selectItem(int this, char *name)
{
  int iVar1;
  char *_Str1;
  uint *puVar2;
  bool bVar3;
  uint uVar4;
  uint uVar5;
  uint local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  uVar4 = (uint)name;
  iVar1 = *(int *)(this + 0x20);
  if ((name < *(uint *)(iVar1 + 0xa4)) && ((char *)*(uint *)(this + 0x3c) != name)) {
    *(char **)(this + 0x3c) = name;
    if (name < *(uint *)(iVar1 + 0xa4)) {
      name = (char *)((int)name * 0x61 + *(int *)(iVar1 + 0xac));
    }
    else {
      name = &DAT_01222260;
    }
    uVar5 = 0;
    if (*(int *)(this + 0x34) != 0) {
      do {
        if (1 < *(uint *)(*(int *)(*(int *)(*(int *)(this + 0x30) + uVar5 * 4) + 4) + 0x14)) {
          FUN_00605c70(uVar4, name);
        }
        uVar5 = uVar5 + 1;
      } while (uVar5 < *(uint *)(this + 0x34));
    }
    local_10 = 0;
    if (*(int *)(this + 0x28) != 0) {
      do {
        iVar1 = *(int *)(*(int *)(this + 0x24) + local_10 * 4);
        if ((name == (char *)0x0) || (*name == '\0')) {
          bVar3 = false;
        }
        else {
          bVar3 = true;
        }
        if (*(int *)(iVar1 + 0x28) == 0) {
          uVar4 = (uint)bVar3;
        }
        else if (bVar3) {
          _Str1 = *(char **)(iVar1 + 0x24);
          if ((_Str1 == (char *)0x0) || (name == (char *)0x0)) {
            if (_Str1 >= name && _Str1 != name) goto LAB_00604429;
            uVar4 = (uint)(_Str1 < name);
          }
          else {
            uVar4 = __stricmp(_Str1, name);
          }
        }
        else {
LAB_00604429:
          uVar4 = 0xffffffff;
        }
        if (uVar4 != 0) {
          uVar4 = *(uint *)(iVar1 + 0x34);
          if (uVar4 != 0) {
            for (puVar2 = *(uint **)(*(int *)(DAT_0122337c + 0x50) +
                                    (uVar4 % *(uint *)(DAT_0122337c + 0x54)) * 4);
                puVar2 != (uint *)0x0; puVar2 = (uint *)puVar2[2]) {
              if (*puVar2 == uVar4) {
                if ((puVar2 != (uint *)0x0) && (puVar2[1] != 0)) {
                  FUN_004048c0(puVar2[1], 0);
                }
                break;
              }
            }
            *(undefined4 *)(iVar1 + 0x34) = 0;
            *(undefined4 *)(iVar1 + 0x28) = 0;
            if (*(undefined1 **)(iVar1 + 0x24) != (undefined1 *)0x0) {
              **(undefined1 **)(iVar1 + 0x24) = 0;
            }
          }
          FUN_006059c0(name);
        }
        local_10 = local_10 + 1;
      } while (local_10 < *(uint *)(this + 0x28));
    }
    *(undefined1 *)(this + 0x54) = 0;
    *(undefined1 *)(this + 100) = 0;
    *(undefined1 *)(this + 0x74) = 0;
    *(uint *)(this + 0x4c) = *(uint *)(this + 0x4c) & 0xfffffffd;
    *(undefined1 *)(this + 0x84) = 0;
    *(undefined1 *)(this + 0x94) = 0;
    *(uint *)(this + 0x4c) = *(uint *)(this + 0x4c) & 0xfffffffb;
    *(undefined1 *)(this + 0xa4) = 0;
    *(undefined1 *)(this + 0xb4) = 0;
    *(undefined1 *)(this + 0xc4) = 0;
    *(undefined1 *)(this + 0xd4) = 0;
    *(undefined1 *)(this + 0xe4) = 0;
    *(uint *)(this + 0x4c) = *(uint *)(this + 0x4c) & 0xfffffff7;
    local_c = DAT_01222240;
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c, 0);
  }
  return;
}