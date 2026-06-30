// FUNC_NAME: TNLConnection::processPacket
void TNLConnection::processPacket(int *connection, byte *packetData, undefined4 param_3, ushort packetSize, undefined4 param_5,
                 undefined4 param_6, int param_7, int param_8, undefined4 param_9)

{
  int *piVar1;
  byte bVar2;
  byte bVar3;
  short sVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  int iVar7;
  uint uVar8;
  byte *pbVar9;
  uint uVar10;
  short sVar11;
  int iVar12;
  int local_170;
  int local_16c;
  uint local_168;
  uint local_164;
  byte *local_160;
  int *local_15c;
  int local_158;
  byte *local_154;
  uint local_150;
  int local_14c;
  byte *local_148;
  short local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  int local_130;
  uint local_12c;
  undefined8 local_128;
  undefined8 local_120;
  undefined8 local_118;
  undefined2 local_110;
  short asStack_10e [64];
  undefined2 local_8e;
  undefined2 auStack_8c [64];
  short local_c;
  undefined2 local_a;
  undefined2 local_8;
  undefined2 local_6;
  
  bVar2 = *packetData; // First byte: flags/type
  local_154 = packetData + 1; // Advance past header byte
  sVar4 = 0;
  local_148 = (byte *)0x0;
  local_150 = 0;
  local_164 = 0;
  local_160 = (byte *)0x0;
  local_13c = 0;
  local_140 = 1;
  local_168 = CONCAT31(local_168._1_3_,bVar2); // Store flags
  if ((char)bVar2 < '\\0') { // High bit set: compressed/notify packet
    if ((bVar2 & 0x40) != 0) { // Bit 6: has notify acks
      bVar3 = *local_154;
      uVar10 = (uint)bVar3;
      local_154 = packetData + 2;
      if (bVar3 != 0) {
        do {
          uVar10 = uVar10 - 1;
          local_154 = local_154 + *local_154 + 2; // Skip notify ack entries
        } while (uVar10 != 0);
      }
    }
    local_168 = (uint)(short)(ushort)(bVar2 & 0x3f); // Lower 6 bits: ghost count
    if (local_168 != 0) {
      do {
        FUN_00678a20(connection,&local_154,&local_140,&param_3); // Read ghost update header
        uVar10 = local_12c & 0xffff;
        *(int *)(connection[1] + 4) = *(int *)(connection[1] + 0xc) + connection[0xb] + local_130; // Update buffer position
        puVar5 = (undefined1 *)FUN_00673070(); // Allocate temp buffer
        local_15c = (int *)connection[1];
        if (uVar10 != 0) {
          local_158 = local_15c[1];
          iVar7 = *local_15c;
          if (uVar10 != 0) {
            puVar6 = puVar5;
            uVar8 = uVar10;
            do {
              *puVar6 = puVar6[(iVar7 + local_158) - (int)puVar5]; // Copy ghost data
              puVar6 = puVar6 + 1;
              uVar8 = uVar8 - 1;
            } while (uVar8 != 0);
          }
          local_15c[1] = local_158 + uVar10;
        }
        FUN_0067ae20(connection,puVar5,local_130,local_12c,local_140,local_138,local_13c,local_134,
                     param_9); // Recursively process ghost updates
        iVar7 = *connection;
        if (puVar5 != (undefined1 *)0x0) {
          *(undefined4 *)(*(int *)(iVar7 + 0xc) + *(int *)(puVar5 + -8) * 4) = 0; // Free temp buffer
          piVar1 = (int *)(iVar7 + 4);
          *piVar1 = *piVar1 + -1;
          (*DAT_01206694)(puVar5 + -0x10);
        }
        local_168 = local_168 - 1;
      } while (local_168 != 0);
      return;
    }
  }
  else { // Normal packet (no compression)
    local_110 = 0;
    local_8e = 0;
    local_c = 0;
    local_a = 0;
    FUN_006783f0(connection,local_168,&local_154,&local_110); // Read packet header
    if ((local_168 & 8) != 0) { // Bit 3: has notify acks
      bVar2 = *local_154;
      uVar10 = (uint)bVar2;
      local_154 = local_154 + 1;
      if (bVar2 != 0) {
        do {
          uVar10 = uVar10 - 1;
          local_154 = local_154 + *local_154 + 2; // Skip notify ack entries
        } while (uVar10 != 0);
      }
    }
    local_128 = *(undefined8 *)(connection + 0x38); // Save connection state
    local_120 = *(undefined8 *)(connection + 0x3a);
    local_118 = *(undefined8 *)(connection + 0x3c);
    FUN_0067bc80(param_5,param_6,param_7,param_8); // Process packet data
    *(undefined1 *)(connection + 0xd) = 0; // Clear flag
    if ((char)connection[2] == '\\0') { // Not a ghost update
LAB_0067b2e1:
      bVar2 = *local_154;
      pbVar9 = local_154 + 1;
      switch(bVar2 >> 4) { // Packet type (high nibble)
      case 0: // End of packet
        if ((char)connection[0xd] != '\\0') {
          local_154 = pbVar9;
          FUN_00677e80(); // Flush
          *(undefined1 *)(connection + 0xd) = 0;
        }
        *(undefined8 *)(connection + 0x38) = local_128; // Restore state
        *(undefined8 *)(connection + 0x3a) = local_120;
        *(undefined8 *)(connection + 0x3c) = local_118;
        return;
      case 1: // Move to
        break;
      case 2: // Move to with delta
        local_c = asStack_10e[bVar2 & 0xf];
        local_154 = pbVar9;
        FUN_0067bd40((int)local_c << 0x10,&local_170,&local_16c);
        sVar11 = (short)((uint)local_16c >> 0x10);
        sVar4 = (short)((uint)local_170 >> 0x10);
        goto LAB_0067b2d5;
      case 3: // Line to
        local_a = auStack_8c[bVar2 & 0xf];
        sVar4 = local_c;
        break;
      case 4: // Fill rect
        local_154 = pbVar9;
        if ((char)connection[0xd] != '\\0') {
          FUN_00677e80(); // Flush
        }
        FUN_0067bd40((int)sVar4 << 0x10,&local_170,&local_16c);
        sVar4 = (short)((uint)local_170 >> 0x10);
        FUN_00677f80((int)sVar4,(int)(short)((uint)local_16c >> 0x10),1); // Draw filled rect
        *(undefined1 *)(connection + 0xd) = 1;
        goto LAB_0067b2e1;
      case 5: // Draw rect
        goto switchD_0067b2ff_caseD_5;
      case 6: // Draw text
        local_154 = pbVar9;
        FUN_0067bd40((int)sVar4 << 0x10,&local_170,&local_16c);
        uVar10 = (uint)local_16c >> 0x10;
        sVar4 = (short)((uint)local_170 >> 0x10);
        FUN_0067bd40((int)(short)local_148 << 0x10,&local_14c,&local_158);
        local_148 = (byte *)(local_14c >> 0x10 & 0xffff);
        local_150 = local_158 >> 0x10 & 0xffff;
        FUN_0067bd40((int)(short)local_164 << 0x10,&local_15c,&local_168);
        local_164 = (int)local_15c >> 0x10 & 0xffff;
        local_160 = (byte *)((int)local_168 >> 0x10 & 0xffff);
        FUN_00677f80((int)sVar4,(int)(short)uVar10,0); // Draw text
        FUN_00677f80((int)(short)local_148,(int)(short)local_150,0);
        iVar7 = (int)(short)local_160;
        iVar12 = (int)(short)local_164;
        goto LAB_0067b2d9;
      case 7: // Draw bitmap
        local_154 = pbVar9;
        FUN_0067bd40((int)sVar4 << 0x10,&local_170,&local_16c);
        sVar11 = (short)((uint)local_16c >> 0x10);
        sVar4 = (short)((uint)local_170 >> 0x10);
        FUN_0067bd40((int)(short)local_148 << 0x10,&local_14c,&local_158);
        local_148 = (byte *)(local_14c >> 0x10 & 0xffff);
        local_150 = local_158 >> 0x10 & 0xffff;
        FUN_0067bd40((int)(short)local_164 << 0x10,&local_15c,&local_168);
        goto LAB_0067b618;
      default: // Draw with absolute coordinates
        local_154 = local_154 + 2;
        local_168 = FUN_00676010(); // Read coordinate
        iVar7 = FUN_00676010();
        iVar7 = iVar7 + local_168 + connection[0x3c]; // Add offset
        local_170 = iVar7;
        iVar12 = FUN_00676010();
        local_16c = FUN_00676010();
        local_16c = local_16c + iVar12 + connection[0x3d];
        sVar4 = (short)((uint)iVar7 >> 0x10);
        sVar11 = (short)((uint)local_16c >> 0x10);
        local_158 = (int)(short)local_148 << 0x10;
        local_15c = (int *)((int)(short)local_150 << 0x10);
        local_168 = FUN_00676010();
        local_14c = FUN_00676010();
        local_14c = local_14c + local_168 + connection[0x3c];
        iVar7 = FUN_00676010();
        local_158 = FUN_00676010();
        local_158 = local_158 + iVar7 + connection[0x3d];
        local_150 = local_158 >> 0x10 & 0xffff;
        local_148 = (byte *)(local_14c >> 0x10 & 0xffff);
        local_160 = (byte *)((int)(short)local_160 << 0x10);
        local_164 = (int)(short)local_164 << 0x10;
        local_168 = FUN_00676010();
        iVar7 = FUN_00676010();
        local_15c = (int *)(iVar7 + local_168 + connection[0x3c]);
        iVar7 = FUN_00676010();
        iVar12 = FUN_00676010();
        local_168 = iVar12 + iVar7 + connection[0x3d];
LAB_0067b618:
        local_164 = (int)local_15c >> 0x10 & 0xffff;
        local_160 = (byte *)((int)local_168 >> 0x10 & 0xffff);
        FUN_00677f80((int)sVar4,(int)sVar11,0); // Draw bitmap
        FUN_00677f80((int)(short)local_148,(int)(short)local_150,0);
        iVar7 = (int)(short)local_160;
        iVar12 = (int)(short)local_164;
        goto LAB_0067b2d9;
      }
      local_154 = pbVar9;
      FUN_0067bd40((int)sVar4 << 0x10,&local_170,&local_16c);
      sVar11 = (short)((uint)local_16c >> 0x10);
      sVar4 = (short)((uint)local_170 >> 0x10);
LAB_0067b2d5:
      iVar7 = (int)sVar11;
      iVar12 = (int)sVar4;
LAB_0067b2d9:
      FUN_00677f80(iVar12,iVar7,1); // Draw line
      goto LAB_0067b2e1;
    }
    // Ghost update processing
    local_160 = packetData + (packetSize - 1);
    local_8 = 0;
    local_6 = 0;
    local_c = 0;
    local_a = 0;
    local_148 = local_154;
    local_144 = 0;
    local_164 = 0xffffffff;
    pbVar9 = local_160;
    while ((local_148 < pbVar9 || ((local_148 == pbVar9 && (local_144 == 0))))) {
      FUN_00678e60(&local_110,&local_164); // Read ghost update type
      if ((short)local_164 == 0) { // Ghost destroy
        if ((char)connection[0xd] != '\\0') {
          FUN_00677e80(); // Flush
        }
        FUN_0067bd40((int)(short)local_140 << 0x10,&local_170,&local_16c);
        FUN_00677f80((int)(short)((uint)local_170 >> 0x10),(int)(short)((uint)local_16c >> 0x10),1);
        *(undefined1 *)(connection + 0xd) = 1;
      }
      else if ((short)local_164 == 1) { // Ghost update position
        local_16c = FUN_00676010();
        local_16c = local_16c + param_8;
        iVar12 = (int)(short)local_140;
        iVar7 = FUN_00676010();
        local_170 = FUN_00676010();
        local_170 = local_170 + iVar7 + param_7;
        FUN_0067bd40(iVar12 << 0x10,&local_170,&local_16c);
        FUN_00677f80((int)(short)((uint)local_170 >> 0x10),(int)(short)((uint)local_16c >> 0x10),1);
        pbVar9 = local_160;
      }
      else if ((short)local_164 == 2) { // Ghost update with delta
        FUN_0067bd40((int)(short)local_140 << 0x10,&local_170,&local_16c);
        FUN_0067bd40((int)(short)local_13c << 0x10,&local_14c,&local_158);
        FUN_0067bd40((int)(short)local_138 << 0x10,&local_15c,&local_168);
        FUN_00677f80((int)(short)((uint)local_170 >> 0x10),(int)(short)((uint)local_16c >> 0x10),0);
        FUN_00677f80((int)(short)((uint)local_14c >> 0x10),(int)(short)((uint)local_158 >> 0x10),0);
        FUN_00677f80((int)(short)((uint)local_15c >> 0x10),(int)(short)(local_168 >> 0x10),1);
      }
    }
    *(undefined8 *)(connection + 0x38) = local_128; // Restore state
    *(undefined8 *)(connection + 0x3a) = local_120;
    *(undefined8 *)(connection + 0x3c) = local_118;
    if ((char)connection[0xd] != '\\0') {
      FUN_00677e80(); // Flush
      *(undefined1 *)(connection + 0xd) = 0;
    }
  }
  return;
switchD_0067b2ff_caseD_5:
  local_154 = pbVar9;
  if ((char)connection[0xd] != '\\0') {
    FUN_00677e80(); // Flush
  }
  FUN_0067bd40((int)sVar4 << 0x10,&local_170,&local_16c);
  sVar4 = (short)((uint)local_170 >> 0x10);
  FUN_00677f80((int)sVar4,(int)(short)((uint)local_16c >> 0x10),1); // Draw rect
  *(undefined1 *)(connection + 0xd) = 1;
  goto LAB_0067b2e1;
}