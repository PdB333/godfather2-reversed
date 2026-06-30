// FUNC_NAME: TextParser::parseText
void TextParser::parseText(int param_1, undefined4 *param_2, char *param_3, char *param_4)

{
  char cVar1;
  undefined1 *puVar2;
  int iVar3;
  char *pcVar4;
  char *local_38;
  int local_34;
  char *local_2c;
  int local_28;
  undefined4 local_24;
  undefined4 local_20;
  code *local_1c;
  undefined1 *local_18;
  undefined4 local_14;
  undefined4 local_10;
  code *local_c;
  
  iVar3 = 0;
  param_2[1] = 0;
  if ((undefined1 *)*param_2 != (undefined1 *)0x0) {
    *(undefined1 *)*param_2 = 0;
  }
  local_38 = param_3;
  local_34 = 0;
  if (param_3 != (char *)0x0) {
    do {
      cVar1 = *param_3;
      if ((cVar1 == '\\0') || ((param_4 != (char *)0x0 && (param_4 <= param_3)))) break;
      if (cVar1 == '\\x1e') {
        local_34 = local_34 + 1;
LAB_00603672:
        if (iVar3 != 0) {
          FUN_004d43f0(local_38,0,iVar3);
          iVar3 = 0;
        }
        pcVar4 = param_3 + 1;
        local_38 = pcVar4;
      }
      else {
        if (cVar1 == '\\x1f') {
          local_34 = local_34 + -1;
          goto LAB_00603672;
        }
        if (local_34 < 1) {
          if (cVar1 == '#') {
            pcVar4 = (char *)FUN_00603490();
            if (pcVar4 == (char *)0x0) {
LAB_00603870:
              pcVar4 = param_3 + 1;
              iVar3 = iVar3 + 1;
            }
            else {
              if (iVar3 != 0) {
                FUN_004d43f0(local_38,0,iVar3);
                iVar3 = 0;
              }
              local_2c = (char *)0x0;
              _strtoul(param_3 + 1,&local_2c,10);
              FUN_00603510(param_1,param_2);
              local_38 = pcVar4;
            }
          }
          else if (cVar1 == '$') {
            pcVar4 = (char *)FUN_00603430();
            if (pcVar4 == (char *)0x0) goto LAB_00603870;
            if (iVar3 != 0) {
              FUN_004d43f0(local_38,0,iVar3);
              iVar3 = 0;
            }
            FUN_004db060(param_3 + 1,pcVar4);
            FUN_00603510(param_1,param_2);
            local_38 = pcVar4;
          }
          else if (cVar1 == '{') {
            pcVar4 = (char *)FUN_006034d0();
            if (pcVar4 == (char *)0x0) goto LAB_00603870;
            if (iVar3 != 0) {
              FUN_004d43f0(local_38,0,iVar3);
              iVar3 = 0;
            }
            if (param_3[2] == ':') {
              local_18 = (undefined1 *)0x0;
              local_14 = 0;
              local_10 = 0;
              local_c = (code *)0x0;
              FUN_00603610(param_1,&local_18,param_3 + 3,pcVar4);
              puVar2 = local_18;
              if (local_18 == (undefined1 *)0x0) {
                puVar2 = &DAT_0120546e;
              }
              FUN_00604c10(param_3[1],puVar2);
              if (local_18 == (undefined1 *)0x0) {
LAB_006037ba:
                pcVar4 = pcVar4 + 1;
                local_38 = pcVar4;
              }
              else {
                (*local_c)(local_18);
                pcVar4 = pcVar4 + 1;
                local_38 = pcVar4;
              }
            }
            else {
              if (param_3 + 2 != pcVar4) {
                local_28 = 0;
                local_24 = 0;
                local_20 = 0;
                local_1c = (code *)0x0;
                FUN_00603610(param_1,&local_28,param_3 + 1,pcVar4);
                FUN_004d43f0(local_28,0,local_24);
                if (local_28 != 0) {
                  (*local_1c)(local_28);
                }
                goto LAB_006037ba;
              }
              FUN_00604d60(param_2);
              pcVar4 = pcVar4 + 1;
              local_38 = pcVar4;
            }
          }
          else {
            iVar3 = iVar3 + 1;
            pcVar4 = param_3 + 1;
          }
        }
        else {
          iVar3 = iVar3 + 1;
          pcVar4 = param_3 + 1;
        }
      }
      param_3 = pcVar4;
    } while (pcVar4 != (char *)0x0);
    if (iVar3 != 0) {
      FUN_004d43f0(local_38,0,iVar3);
    }
  }
  return;
}