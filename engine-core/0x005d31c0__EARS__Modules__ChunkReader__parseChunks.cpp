// FUNC_NAME: EARS::Modules::ChunkReader::parseChunks
uint EARS::Modules::ChunkReader::parseChunks(uint param_1)

{
  char cVar1;
  uint uVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  uint *in_EAX;
  char *pcVar6;
  int iVar7;
  uint uVar8;
  char *_String;
  uint uVar9;
  char local_c;
  char local_b;
  undefined4 local_8;
  undefined4 local_4;
  
  in_EAX[4] = 0; // currentOffset = 0
  iVar7 = *(int *)*in_EAX; // read magic from buffer
  in_EAX[4] = 4; // advance past magic
  if (iVar7 != 0x61707866) { // check magic "apxf" (EA chunk magic)
    return *in_EAX & 0xffffff00; // return error
  }
  in_EAX[4] = 0; // reset offset
  in_EAX[7] = param_1; // store output pointer
  *(undefined4 *)(param_1 + 0xb4) = 0; // clear some field
  bVar3 = false; // hasName
  local_b = '\0'; // hasSomething
  bVar4 = false; // hasCons
  bVar5 = false; // hasEnd
  local_c = '\0'; // hasOther
  uVar9 = param_1;
  if ((int)in_EAX[4] < (int)(in_EAX[3] - 8)) { // while offset < bufferSize - 8
    do {
      uVar8 = in_EAX[4];
      uVar2 = *in_EAX;
      local_8 = (undefined1 *)
                CONCAT13(*(undefined1 *)(uVar2 + 3 + uVar8),
                         CONCAT12(*(undefined1 *)(uVar2 + 2 + uVar8),
                                  CONCAT11(*(undefined1 *)(uVar2 + 1 + uVar8),
                                           *(undefined1 *)(uVar2 + uVar8))));
      in_EAX[4] = uVar8 + 4; // read chunk ID (4 bytes)
      if (local_8 < (undefined1 *)0x70736865) {
        if (local_8 == (undefined1 *)0x70736864) { // "pshd" - push data
          local_c = FUN_005d34d0(); // handle push data
        }
        else if (local_8 < (undefined1 *)0x6170786d) {
          if (local_8 == (undefined1 *)0x6170786c) { // "apxl" - something
            bVar5 = true;
          }
          else if (local_8 < (undefined1 *)0x6170746a) {
            if (local_8 == (undefined1 *)0x61707469) { // "apti" - something
              local_b = FUN_005d3660(); // handle apti
            }
            else if ((local_8 != (undefined1 *)0x616c6967) && (local_8 == (undefined1 *)0x616c7068))
            {
              FUN_005d35d0(); // handle "alph"
            }
          }
          else if ((local_8 == (undefined1 *)0x61707866) && (!bVar3)) { // "apxf" - name chunk
            uVar8 = uVar8 + 8;
            in_EAX[4] = uVar8;
            FUN_005d2f70(); // skip some data
            in_EAX[4] = in_EAX[4] + 4;
            _String = (char *)(*in_EAX + in_EAX[4]); // get string pointer
            __strlwr(_String); // lowercase the string
            FUN_005be330(); // some init
            FUN_005be380(); // some init
            pcVar6 = _String;
            do {
              cVar1 = *pcVar6;
              pcVar6[(param_1 - (int)_String) + 0x34] = cVar1; // copy string to output at offset 0x34
              pcVar6 = pcVar6 + 1;
            } while (cVar1 != '\0');
            in_EAX[8] = (uint)_String; // store string pointer
            bVar3 = true;
            uVar9 = param_1;
          }
        }
        else if (local_8 == (undefined1 *)0x636f6e73) { // "cons" - constant data
          in_EAX[4] = uVar8 + 8;
          *(uint *)(in_EAX[7] + 0xc) = uVar8 + 8 + uVar2; // store data pointer at +0x0C
          bVar4 = true;
        }
        else if (local_8 == (undefined1 *)0x656e645f) break; // "end_" - end marker
      }
      else if (local_8 < (undefined1 *)0x74783475) {
        if (((local_8 != (undefined1 *)0x74783474) && (local_8 < (undefined1 *)0x74783360)) &&
           (local_8 != (undefined1 *)0x7478335f)) {
          if (local_8 == (undefined1 *)0x72756269) { // "rubi" - ruby script
            FUN_005d38f0(in_EAX); // handle ruby
          }
          else if (local_8 == (undefined1 *)0x73637265) { // "scre" - script
            FUN_005d3610(); // handle script
          }
        }
      }
      else if (((local_8 != (undefined1 *)0x7478775f) && (local_8 != (undefined1 *)0x74787a5f)) &&
              (local_8 == (undefined1 *)0x76657273)) { // "vers" - version
        FUN_005d3570(); // handle version
      }
      uVar2 = uVar8 + 4;
      in_EAX[4] = uVar2;
      iVar7 = uVar2 + *in_EAX;
      local_4 = CONCAT13(*(undefined1 *)(iVar7 + 3),
                         CONCAT12(*(undefined1 *)(iVar7 + 2),
                                  CONCAT11(*(undefined1 *)(iVar7 + 1),
                                           *(undefined1 *)(uVar2 + *in_EAX))));
      local_8 = (undefined1 *)(local_4 + uVar8); // compute next chunk offset
      in_EAX[4] = (uint)local_8;
    } while ((int)local_8 < (int)(in_EAX[3] - 8)); // while within bounds
    if (local_c != '\0') goto LAB_005d3443;
  }
  if (DAT_012058a4 < 0x1000) {
    local_8 = &DAT_011a0f28 + DAT_012058a4 * 0x38;
  }
  else {
    local_8 = (undefined1 *)0x0;
  }
  if (*(ushort *)(local_8 + 2) < 0x281) {
    local_8 = (undefined1 *)in_EAX[7];
    *(undefined4 *)(local_8 + 0xbc) = 0; // clear some field at +0xBC
  }
LAB_005d3443:
  if (((local_b == '\0') || (!bVar4)) && (!bVar5)) {
    return (uint)local_8 & 0xffffff00; // return error if required chunks missing
  }
  FUN_005d3ed0(in_EAX,&param_1,uVar9); // finalize parsing
  *(uint *)(uVar9 + 0xd0) = param_1; // store something at +0xD0
  uVar8 = *in_EAX;
  *(uint *)(uVar9 + 4) = uVar8; // store buffer pointer at +0x04
  *(undefined4 *)(uVar9 + 0x30) = 3; // set state to 3
  return CONCAT31((int3)(uVar8 >> 8),1); // return success
}