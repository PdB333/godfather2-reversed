// FUNC_NAME: LuaVM::executeInstruction
int* LuaVM::executeInstruction(int param_1)
{
  int *piVar1;
  uint uVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined4 *puVar5;
  int *piVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  undefined4 *puVar10;
  int *piVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  bool bVar15;
  float fVar16;
  uint *local_40;
  int *local_3c;
  int local_38;
  int *local_34;
  int local_30;
  int *local_2c;
  int *local_28;
  undefined4 local_24;
  int local_20;
  int aiStack_1c [3];
  undefined4 local_10;
  float local_c;
  
LAB_00634840:
  // Check if instruction pointer needs to be fetched from stack context
  if ((*(byte *)(param_1 + 0x30) & 1) != 0) {
    // +0x14: VM state, +0x10: top of stack pointer
    *(uint ***)(*(int *)(param_1 + 0x14) + 0x10) = &local_40;
    // Call stack frame pop
    FUN_00635d00(0xffffffff);
  }
LAB_0063485e:
  // Set up instruction decoding context
  *(uint ***)(*(int *)(param_1 + 0x14) + 0x10) = &local_40;
  // +0x08: VM state flags (set to 2 = RUNNING)
  *(undefined4 *)(*(int *)(param_1 + 0x14) + 8) = 2;
  // +0x0c: current instruction pointer in bytecode
  local_40 = *(uint **)(*(int *)(param_1 + 0x14) + 0xc);
  // +0x0c: prototype/function table offset
  local_30 = *(int *)(*(int *)(param_1 + 0xc) + -4);
  // +0x0c: global constants table
  local_38 = *(int *)(*(int *)(local_30 + 0xc) + 8);
  
LAB_00634890:
  do {
    // Fetch instruction word
    uVar8 = *local_40;
    local_40 = local_40 + 1;
    
    // Check for yield/interrupt flags
    if ((*(byte *)(param_1 + 0x30) & 0xc) != 0) {
      piVar11 = (int *)(param_1 + 0x38);
      *piVar11 = *piVar11 + -1;
      if (((*piVar11 == 0) || ((*(byte *)(param_1 + 0x30) & 4) != 0)) &&
         (FUN_00633a00(), (*(byte *)(*(int *)(param_1 + 0x14) + 8) & 0x10) != 0)) {
        *(uint **)(*(int *)(param_1 + 0x14) + 0xc) = local_40 + -1;
        *(undefined4 *)(*(int *)(param_1 + 0x14) + 8) = 0x18;
        return (int *)0x0;
      }
    }
    
    // Decode instruction: opcode in low 6 bits, operands in higher bits
    local_3c = *(int **)(param_1 + 0xc);
    piVar1 = (int *)((int)uVar8 >> 0x18);
    local_2c = (int *)((int)piVar1 * 8);
    piVar11 = (int *)((int)local_2c + (int)local_3c);
    uVar2 = uVar8 & 0x3f;
    local_34 = piVar11;
    local_28 = piVar1;
  } while (0x22 < uVar2); // Only execute for opcodes 0-0x22
  
  uVar13 = (int)uVar8 >> 0xf;
  uVar7 = (int)uVar8 >> 6;
  
  switch(uVar2) {
  case 0: // OP_LOADK - Load constant
    *piVar11 = local_3c[(uVar13 & 0x1ff) * 2];
    piVar11[1] = local_3c[(uVar13 & 0x1ff) * 2 + 1];
    goto LAB_00634890;
    
  case 1: // OP_LOADG - Load global
    *piVar11 = *(int *)(local_38 + (uVar7 & 0x3ffff) * 8);
    piVar11[1] = *(int *)(local_38 + (uVar7 & 0x3ffff) * 8 + 4);
    goto LAB_00634890;
    
  case 2: // OP_LOADBOOL - Load boolean
    *piVar11 = 1;
    piVar11[1] = uVar13 & 0x1ff;
    if ((uVar8 & 0x7fc0) != 0) {
      local_40 = local_40 + 1; // skip next instruction if condition
    }
    goto LAB_00634890;
    
  case 3: // OP_ZERO - Set to nil
    piVar1 = local_3c + (uVar13 & 0x1ff) * 2;
    do {
      *piVar1 = 0;
      piVar1 = piVar1 + -2;
    } while (piVar11 <= piVar1);
    goto LAB_00634890;
    
  case 4: // OP_LOADUPVAL - Load upvalue
    piVar1 = *(int **)(*(int *)(local_30 + 0x18 + (uVar13 & 0x1ff) * 4) + 8);
    *piVar11 = *piVar1;
    piVar11[1] = piVar1[1];
    goto LAB_00634890;
    
  case 5: // OP_GETTABLE - Get table value
    local_28 = (int *)(local_38 + (uVar7 & 0x3ffff) * 8);
    piVar1 = (int *)(*(int *)(*(int *)(local_30 + 0x14) + 0x10) +
                    ((1 << (*(byte *)(*(int *)(local_30 + 0x14) + 7) & 0x1f)) - 1U &
                    *(uint *)(local_28[1] + 8)) * 0x14);
    do {
      if ((*piVar1 == 4) && (piVar1[1] == local_28[1])) {
        if (piVar1[2] != 0) {
          *piVar11 = piVar1[2];
          piVar11[1] = piVar1[3];
          goto LAB_00634890;
        }
        break;
      }
      piVar1 = (int *)piVar1[4];
    } while (piVar1 != (int *)0x0);
    
    iVar12 = *(int *)(*(int *)(local_30 + 0x14) + 8);
    if ((*(byte *)(iVar12 + 6) & 1) == 0) {
      iVar14 = *(int *)(*(int *)(param_1 + 0x10) + 0x54);
      piVar11 = (int *)(*(int *)(iVar12 + 0x10) +
                       ((1 << (*(byte *)(iVar12 + 7) & 0x1f)) - 1U & *(uint *)(iVar14 + 8)) * 0x14);
      do {
        if ((*piVar11 == 4) && (piVar11[1] == iVar14)) {
          piVar11 = piVar11 + 2;
          if (*piVar11 != 0) goto LAB_00634a58;
          break;
        }
        piVar11 = (int *)piVar11[4];
      } while (piVar11 != (int *)0x0);
      *(byte *)(iVar12 + 6) = *(byte *)(iVar12 + 6) | 1;
    }
    piVar11 = (int *)0x0;
LAB_00634a58:
    if (piVar11 == (int *)0x0) {
      puVar5 = &DAT_00e2a93c;
    }
    else if (*piVar11 == 6) {
      FUN_00633ac0(param_1,piVar11,local_30 + 0x10,local_28);
      puVar5 = *(undefined4 **)(param_1 + 8);
    }
    else {
      puVar5 = (undefined4 *)FUN_00633cb0(param_1,piVar11,local_28,0);
    }
    goto LAB_00634a8b;
    
  case 6: // OP_SETTABLE - Set table value
    uVar7 = uVar7 & 0x1ff;
    local_28 = local_3c + (uVar13 & 0x1ff) * 2;
    if (uVar7 < 0xfa) {
      piVar11 = local_3c + uVar7 * 2;
    }
    else {
      piVar11 = (int *)(local_38 + -2000 + uVar7 * 8);
    }
    if (*local_28 == 5) {
      if (*piVar11 == 3) {
        if ((float)(int)(float)piVar11[1] != (float)piVar11[1]) goto LAB_00634b51;
        piVar1 = (int *)FUN_00637f10();
      }
      else if (*piVar11 == 4) {
        piVar1 = (int *)(*(int *)(local_28[1] + 0x10) +
                        ((1 << (*(byte *)(local_28[1] + 7) & 0x1f)) - 1U & *(uint *)(piVar11[1] + 8)) * 0x14);
        do {
          if ((*piVar1 == 4) && (piVar1[1] == piVar11[1])) {
            piVar1 = piVar1 + 2;
            goto LAB_00634b5c;
          }
          piVar1 = (int *)piVar1[4];
        } while (piVar1 != (int *)0x0);
        piVar1 = &DAT_00e2a93c;
      }
      else {
LAB_00634b51:
        piVar1 = (int *)FUN_00637ea0();
      }
LAB_00634b5c:
      if (*piVar1 == 0) {
        puVar5 = (undefined4 *)FUN_00633bc0(param_1,local_28,piVar11,0);
        goto LAB_00634a8b;
      }
      *local_34 = *piVar1;
      local_34[1] = piVar1[1];
      goto LAB_00634890;
    }
    puVar5 = (undefined4 *)FUN_00633c30(local_28,piVar11,0);
    goto LAB_00634a8b;
    
  case 7: // OP_ADD - Addition
    FUN_00633d60(local_30 + 0x10,local_38 + (uVar7 & 0x3ffff) * 8,piVar11);
    goto LAB_00634890;
    
  case 8: // OP_SETUPVAL - Set upvalue
    piVar1 = *(int **)(*(int *)(local_30 + 0x18 + (uVar13 & 0x1ff) * 4) + 8);
    *piVar1 = *piVar11;
    piVar1[1] = piVar11[1];
    goto LAB_00634890;
    
  case 9: // OP_ADD - Binary addition
    uVar7 = uVar7 & 0x1ff;
    if (uVar7 < 0xfa) {
      piVar1 = local_3c + uVar7 * 2;
    }
    else {
      piVar1 = (int *)(local_38 + -2000 + uVar7 * 8);
    }
    uVar13 = uVar13 & 0x1ff;
    if (uVar13 < 0xfa) {
      FUN_00633d60(piVar11,local_3c + uVar13 * 2,piVar1);
    }
    else {
      FUN_00633d60(piVar11,local_38 + -2000 + uVar13 * 8,piVar1);
    }
    goto LAB_00634890;
    
  case 10: // OP_LOADKX - Load constant extended
    *piVar11 = 5;
    iVar12 = FUN_00637c50((uVar13 & 7) << ((byte)((int)(uVar13 & 0x1ff) >> 3) & 0x1f),uVar7 & 0x1ff);
    piVar11[1] = iVar12;
    goto LAB_00634c7c;
    
  case 0xb: // OP_GETTABLE - Get table (alternate)
    uVar7 = uVar7 & 0x1ff;
    piVar1 = local_3c + (uVar13 & 0x1ff) * 2;
    if (uVar7 < 0xfa) {
      piVar6 = local_3c + uVar7 * 2;
    }
    else {
      piVar6 = (int *)(local_38 + -2000 + uVar7 * 8);
    }
    if (*piVar6 != 4) {
      return (int *)0x0;
    }
    piVar11[2] = *piVar1;
    piVar11[3] = piVar1[1];
    if (*piVar1 == 5) {
      piVar4 = (int *)(*(int *)(piVar1[1] + 0x10) +
                      ((1 << (*(byte *)(piVar1[1] + 7) & 0x1f)) - 1U & *(uint *)(piVar6[1] + 8)) * 0x14);
      do {
        if ((*piVar4 == 4) && (piVar4[1] == piVar6[1])) {
          if (piVar4[2] != 0) {
            *piVar11 = piVar4[2];
            piVar11[1] = piVar4[3];
            goto LAB_00634890;
          }
          break;
        }
        piVar4 = (int *)piVar4[4];
      } while (piVar4 != (int *)0x0);
      puVar5 = (undefined4 *)FUN_00633bc0(param_1,piVar1,piVar6,0);
    }
    else {
      puVar5 = (undefined4 *)FUN_00633c30(piVar1,piVar6,0);
    }
LAB_00634a8b:
    puVar10 = (undefined4 *)(*(int *)(param_1 + 0xc) + (int)local_2c);
    *puVar10 = *puVar5;
    puVar10[1] = puVar5[1];
    goto LAB_00634890;
    
  case 0xc: // OP_ADD - Numeric addition
    uVar13 = uVar13 & 0x1ff;
    if (uVar13 < 0xfa) {
      piVar1 = local_3c + uVar13 * 2;
    }
    else {
      piVar1 = (int *)(local_38 + -2000 + uVar13 * 8);
    }
    uVar7 = uVar7 & 0x1ff;
    if (uVar7 < 0xfa) {
      piVar6 = local_3c + uVar7 * 2;
    }
    else {
      piVar6 = (int *)(local_38 + -2000 + uVar7 * 8);
    }
    if ((*piVar1 == 3) && (*piVar6 == 3)) {
      *piVar11 = 3;
      piVar11[1] = (int)((float)piVar6[1] + (float)piVar1[1]);
    }
    else {
      FUN_00634660(param_1,piVar1,piVar6,5);
    }
    goto LAB_00634890;
    
  case 0xd: // OP_SUB - Subtraction
    uVar13 = uVar13 & 0x1ff;
    if (uVar13 < 0xfa) {
      piVar1 = local_3c + uVar13 * 2;
    }
    else {
      piVar1 = (int *)(local_38 + -2000 + uVar13 * 8);
    }
    uVar7 = uVar7 & 0x1ff;
    if (uVar7 < 0xfa) {
      piVar6 = local_3c + uVar7 * 2;
    }
    else {
      piVar6 = (int *)(local_38 + -2000 + uVar7 * 8);
    }
    if ((*piVar1 == 3) && (*piVar6 == 3)) {
      *piVar11 = 3;
      piVar11[1] = (int)((float)piVar1[1] - (float)piVar6[1]);
    }
    else {
      FUN_00634660(param_1,piVar1,piVar6,6);
    }
    goto LAB_00634890;
    
  case 0xe: // OP_MUL - Multiplication
    uVar13 = uVar13 & 0x1ff;
    if (uVar13 < 0xfa) {
      piVar1 = local_3c + uVar13 * 2;
    }
    else {
      piVar1 = (int *)(local_38 + -2000 + uVar13 * 8);
    }
    uVar7 = uVar7 & 0x1ff;
    if (uVar7 < 0xfa) {
      piVar6 = local_3c + uVar7 * 2;
    }
    else {
      piVar6 = (int *)(local_38 + -2000 + uVar7 * 8);
    }
    if ((*piVar1 == 3) && (*piVar6 == 3)) {
      *piVar11 = 3;
      piVar11[1] = (int)((float)piVar6[1] * (float)piVar1[1]);
    }
    else {
      FUN_00634660(param_1,piVar1,piVar6,7);
    }
    goto LAB_00634890;
    
  case 0xf: // OP_DIV - Division
    uVar13 = uVar13 & 0x1ff;
    if (uVar13 < 0xfa) {
      piVar1 = local_3c + uVar13 * 2;
    }
    else {
      piVar1 = (int *)(local_38 + -2000 + uVar13 * 8);
    }
    uVar7 = uVar7 & 0x1ff;
    if (uVar7 < 0xfa) {
      piVar6 = local_3c + uVar7 * 2;
    }
    else {
      piVar6 = (int *)(local_38 + -2000 + uVar7 * 8);
    }
    if ((*piVar1 == 3) && (*piVar6 == 3)) {
      *piVar11 = 3;
      piVar11[1] = (int)((float)piVar1[1] / (float)piVar6[1]);
    }
    else {
      FUN_00634660(param_1,piVar1,piVar6,8);
    }
    goto LAB_00634890;
    
  case 0x10: // OP_BINARY_OP - General binary operation
    uVar7 = uVar7 & 0x1ff;
    if (uVar7 < 0xfa) {
      piVar11 = local_3c + uVar7 * 2;
    }
    else {
      piVar11 = (int *)(local_38 + -2000 + uVar7 * 8);
    }
    uVar13 = uVar13 & 0x1ff;
    if (uVar13 < 0xfa) {
      FUN_00634660(param_1,local_3c + uVar13 * 2,piVar11,9);
    }
    else {
      FUN_00634660(param_1,local_38 + -2000 + uVar13 * 8,piVar11,9);
    }
    goto LAB_00634890;
    
  case 0x11: // OP_UNM - Unary minus
    piVar11 = local_3c + (uVar13 & 0x1ff) * 2;
    if (*piVar11 != 3) {
      if ((*piVar11 != 4) || (iVar12 = FUN_00636850(&local_24), iVar12 == 0)) {
        aiStack_1c[1] = 0;
        iVar12 = FUN_00633f00(param_1,piVar11,aiStack_1c + 1,local_34,10);
        if (iVar12 == 0) {
          local_28 = aiStack_1c + 1;
          if ((*piVar11 != 3) &&
             ((*piVar11 != 4 || (iVar12 = FUN_00636850(&local_2c), iVar12 == 0)))) {
            local_28 = piVar11;
          }
          FUN_006336f0("perform arithmetic on");
        }
        goto LAB_00634890;
      }
      aiStack_1c[1] = 3;
      aiStack_1c[2] = local_24;
      piVar11 = aiStack_1c + 1;
    }
    fVar16 = DAT_00e44564;
    *local_34 = 3;
    local_34[1] = (int)(fVar16 - (float)piVar11[1]);
    goto LAB_00634890;
    
  case 0x12: // OP_NOT - Logical not
    iVar12 = local_3c[(uVar13 & 0x1ff) * 2];
    if ((iVar12 == 0) || ((iVar12 == 1 && ((local_3c + (uVar13 & 0x1ff) * 2)[1] == 0)))) {
      *piVar11 = 1;
      piVar11[1] = 1;
    }
    else {
      *piVar11 = 1;
      piVar11[1] = 0;
    }
    goto LAB_00634890;
    
  case 0x13: // OP_JMP - Jump
    uVar13 = uVar13 & 0x1ff;
    FUN_006343b0(param_1,((uVar7 & 0x1ff) - uVar13) + 1,uVar7 & 0x1ff);
    iVar12 = *(int *)(param_1 + 0xc);
    *(undefined4 *)((int)local_2c + iVar12) = *(undefined4 *)(iVar12 + uVar13 * 8);
    *(undefined4 *)((int)local_2c + iVar12 + 4) = *(undefined4 *)(iVar12 + 4 + uVar13 * 8);
LAB_00634c7c:
    // Check for stack overflow and garbage collect
    if (*(uint *)(*(int *)(param_1 + 0x10) + 0x20) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x24)) {
      uVar3 = FUN_00627290();
      FUN_00626f80(param_1,0);
      FUN_00626fd0(0);
      FUN_00626f80(param_1,0);
      FUN_00627010(uVar3);
      FUN_006270e0();
    }
    goto LAB_00634890;
    
  case 0x14: // OP_JMP_LONG - Long jump
    local_40 = local_40 + ((uVar7 & 0x3ffff) - 0x1ffff);
    goto LAB_00634890;
    
  case 0x15: // OP_EQ - Equality test
    uVar13 = uVar13 & 0x1ff;
    if (uVar13 < 0xfa) {
      piVar11 = local_3c + uVar13 * 2;
    }
    else {
      piVar11 = (int *)(local_38 + -2000 + uVar13 * 8);
    }
    uVar7 = uVar7 & 0x1ff;
    if (uVar7 < 0xfa) {
      piVar1 = local_3c + uVar7 * 2;
    }
    else {
      piVar1 = (int *)(local_38 + -2000 + uVar7 * 8);
    }
    if (*piVar11 == *piVar1) {
      if (uVar7 < 0xfa) {
        piVar11 = local_3c + uVar7 * 2;
      }
      else {
        piVar11 = (int *)(local_38 + -2000 + uVar7 * 8);
      }
      iVar12 = FUN_006342e0(param_1,piVar11);
      if (iVar12 == 0) goto LAB_006351f0;
      piVar11 = (int *)0x1;
    }
    else {
LAB_006351f0:
      piVar11 = (int *)0x0;
    }
    if (piVar11 != local_28) {
      local_40 = local_40 + 1;
      goto LAB_00634890;
    }
    break;
    
  case 0x16: // OP_LT - Less than
    uVar7 = uVar7 & 0x1ff;
    if (uVar7 < 0xfa) {
      piVar11 = local_3c + uVar7 * 2;
    }
    else {
      piVar11 = (int *)(local_38 + -2000 + uVar7 * 8);
    }
    piVar11 = (int *)FUN_00634150(piVar11);
    if (piVar11 != local_28) {
      local_40 = local_40 + 1;
      goto LAB_00634890;
    }
    break;
    
  case 0x17: // OP_LE - Less than or equal
    uVar7 = uVar7 & 0x1ff;
    if (uVar7 < 0xfa) {
      piVar11 = local_3c + uVar7 * 2;
    }
    else {
      piVar11 = (int *)(local_38 + -2000 + uVar7 * 8);
    }
    uVar13 = uVar13 & 0x1ff;
    if (uVar13 < 0xfa) {
      piVar1 = local_3c + uVar13 * 2;
    }
    else {
      piVar1 = (int *)(local_38 + -2000 + uVar13 * 8);
    }
    piVar11 = (int *)FUN_00634200(piVar1,piVar11);
    if (piVar11 != local_28) {
      local_40 = local_40 + 1;
      goto LAB_00634890;
    }
    break;
    
  case 0x18: // OP_TEST - Test
    piVar1 = local_3c + (uVar13 & 0x1ff) * 2;
    iVar12 = *piVar1;
    if ((iVar12 == 0) || ((iVar12 == 1 && (piVar1[1] == 0)))) {
      uVar8 = 1;
    }
    else {
      uVar8 = 0;
    }
    if (uVar8 == (uVar7 & 0x1ff)) {
      local_40 = local_40 + 1;
      goto LAB_00634890;
    }
    *piVar11 = iVar12;
    piVar11[1] = piVar1[1];
    break;
    
  default:
    if ((uVar13 & 0x1ff) != 0) {
      *(int **)(param_1 + 8) = piVar11 + (uVar13 & 0x1ff) * 2;
    }
    local_28 = (int *)((uVar7 & 0x1ff) - 1);
    uVar2 = FUN_00636050(piVar11);
    piVar11 = local_28;
    if (uVar2 == 0) {
      if (((byte)uVar8 & 0x3f) == 0x19) {
        *(uint **)(*(int *)(param_1 + 0x14) + -0xc) = local_40;
        *(undefined4 *)(*(int *)(param_1 + 0x14) + -0x10) = 0xc;
      }
      else {
        iVar12 = *(int *)(*(int *)(param_1 + 0x14) + -0x18);
        local_34 = (int *)(iVar12 + (int)piVar1 * 8);
        if (*(int *)(param_1 + 0x48) != 0) {
          FUN_006382a0();
        }
        iVar14 = 0;
        if (local_34 < *(int **)(param_1 + 8)) {
          iVar9 = 0;
          piVar11 = local_34;
          do {
            *(int *)(iVar9 + -8 + iVar12) = *piVar11;
            *(int *)(iVar9 + -4 + iVar12) = piVar11[1];
            iVar14 = iVar14 + 1;
            iVar9 = iVar14 * 8;
            piVar11 = local_34 + iVar14 * 2;
          } while (piVar11 < *(int **)(param_1 + 8));
        }
        iVar12 = iVar12 + iVar14 * 8;
        *(int *)(param_1 + 8) = iVar12;
        *(int *)(*(int *)(param_1 + 0x14) + -0x14) = iVar12;
        *(undefined4 *)(*(int *)(param_1 + 0x14) + -0xc) =
             *(undefined4 *)(*(int *)(param_1 + 0x14) + 0xc);
        piVar11 = (int *)(*(int *)(param_1 + 0x14) + -4);
        *piVar11 = *piVar11 + 1;
        *(undefined4 *)(*(int *)(param_1 + 0x14) + -0x10) = 8;
        *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + -0x18;
        *(undefined4 *)(param_1 + 0xc) = **(undefined4 **)(param_1 + 0x14);
      }
      goto LAB_00634840;
    }
    if (*(uint *)(param_1 + 8) < uVar2) {
      *(uint **)(*(int *)(param_1 + 0x14) + -0xc) = local_40;
      *(undefined4 *)(*(int *)(param_1 + 0x14) + -0x10) = 8;
      return (int *)0x0;
    }
    FUN_00636260(param_1);
    if (-1 < (int)piVar11) {
      *(undefined4 *)(param_1 + 8) = *(undefined4 *)(*(int *)(param_1 + 0x14) + 4);
    }
    goto LAB_00634890;
    
  case 0x1b: // OP_LOOP - Loop
    goto switchD_006348ed_caseD_1b;
    
  case 0x1c: // OP_FORPREP - For loop preparation
    local_3c = piVar11 + 2;
    local_2c = piVar11 + 4;
    if (*piVar11 != 3) {
      FUN_00633920(param_1,"`for' initial value must be a number");
    }
    if (*local_3c != 3) {
      if ((*local_3c == 4) && (iVar12 = FUN_00636850(&local_20), piVar11 = local_34, iVar12 != 0)) {
        *local_3c = 3;
        local_3c[1] = local_20;
      }
      else {
        local_3c = (int *)0x0;
        FUN_00633920(param_1,"`for' limit must be a number");
      }
    }
    if (*local_2c != 3) {
      if ((*local_2c == 4) && (iVar12 = FUN_00636850(aiStack_1c), piVar11 = local_34, iVar12 != 0)) {
        *local_2c = 3;
        local_2c[1] = aiStack_1c[0];
      }
      else {
        local_2c = (int *)0x0;
        FUN_00633920(param_1,"`for' step must be a number");
      }
    }
    fVar16 = (float)local_2c[1] + (float)piVar11[1];
    if ((float)local_2c[1] <= DAT_00e2b05c) {
      bVar15 = fVar16 < (float)local_3c[1];
    }
    else {
      bVar15 = (float)local_3c[1] < fVar16;
    }
    if (!bVar15) {
      local_40 = local_40 + ((uVar7 & 0x3ffff) - 0x1ffff);
      piVar11[1] = (int)fVar16;
    }
    goto LAB_00634890;
    
  case 0x1d: // OP_FORLOOP - For loop iteration
    iVar14 = (uVar7 & 0x1ff) + 1;
    piVar11[iVar14 * 2 + 4] = *piVar11;
    piVar1 = piVar11 + iVar14 * 2 + 4;
    piVar1[1] = piVar11[1];
    piVar1[2] = piVar11[2];
    piVar1[3] = piVar11[3];
    piVar1[4] = piVar11[4];
    piVar1[5] = piVar11[5];
    *(int **)(param_1 + 8) = piVar1 + 6;
    FUN_006362d0(param_1,piVar1,iVar14);
    local_34 = (int *)(*(int *)(param_1 + 0xc) + 0x10 + (int)local_28 * 8);
    *(undefined4 *)(param_1 + 8) = *(undefined4 *)(*(int *)(param_1 + 0x14) + 4);
    piVar11 = local_34 + iVar14 * 2 + 1;
    iVar12 = iVar14;
    do {
      iVar9 = iVar12 * 2;
      iVar12 = iVar12 + -1;
      piVar1 = piVar11 + -2;
      piVar11[-3] = local_34[iVar14 * 2 + iVar9 + -2];
      *piVar1 = piVar1[iVar14 * 2];
      piVar11 = piVar1;
    } while (0 < iVar12);
    if (*local_34 == 0) {
      local_40 = local_40 + 1;
      goto LAB_00634890;
    }
    break;
    
  case 0x1e: // OP_CLOSURE - Closure
    if (*piVar11 == 5) {
      piVar11[2] = 5;
      piVar11[3] = piVar11[1];
      local_28 = (int *)FUN_00638920(param_1,&DAT_00e3ebc0,4);
      piVar1 = (int *)(*(int *)(*(int *)(param_1 + 0x44) + 0x10) +
                      ((1 << (*(byte *)(*(int *)(param_1 + 0x44) + 7) & 0x1f)) - 1U & local_28[2]) * 0x14);
      do {
        if ((*piVar1 == 4) && ((int *)piVar1[1] == local_28)) {
          piVar1 = piVar1 + 2;
          goto LAB_006355bd;
        }
        piVar1 = (int *)piVar1[4];
      } while (piVar1 != (int *)0x0);
      piVar1 = &DAT_00e2a93c;
LAB_006355bd:
      *piVar11 = *piVar1;
      piVar11[1] = piVar1[1];
    }
    local_40 = local_40 + ((uVar7 & 0x3ffff) - 0x1ffff);
    goto LAB_00634890;
    
  case 0x1f: // OP_CALL_VARARG - Call with varargs
  case 0x20: // OP_CALL_TAIL - Tail call
    if (*piVar11 != 5) {
      return (int *)0x0;
    }
    piVar1 = (int *)piVar11[1];
    if (uVar2 == 0x1f) {
      iVar12 = (uVar7 & 0x1f) + 1;
    }
    else {
      iVar12 = (*(int *)(param_1 + 8) - (int)piVar11 >> 3) + -1;
      *(undefined4 *)(param_1 + 8) = *(undefined4 *)(*(int *)(param_1 + 0x14) + 4);
    }
    local_2c = piVar1;
    if (0 < iVar12) {
      local_28 = (int *)(iVar12 + (uVar7 & 0x3ffe0));
      do {
        piVar11 = (int *)FUN_00637f10();
        if (piVar11 == &DAT_00e2a93c) {
          local_c = (float)(int)local_28;
          local_10 = 3;
          piVar11 = (int *)FUN_00637d60(param_1,piVar1,&local_10);
        }
        local_28 = (int *)((int)local_28 + -1);
        *piVar11 = local_34[iVar12 * 2];
        iVar14 = iVar12 * 2;
        iVar12 = iVar12 + -1;
        piVar11[1] = local_34[iVar14 + 1];
      } while (0 < iVar12);
    }
    goto LAB_00634890;
    
  case 0x21: // OP_CLEANUP - Cleanup
    FUN_006382a0();
    goto LAB_00634890;
    
  case 0x22: // OP_NEWTABLE - Create new table
    goto switchD_006348ed_caseD_22;
  }
  
  // Handle jump for conditional instructions
  local_40 = local_40 + (((int)*local_40 >> 6 & 0x3ffffU) - 0x1fffe);
  goto LAB_00634890;
  
switchD_006348ed_caseD_22:
  // Create new table
  local_28 = *(int **)(*(int *)(*(int *)(local_30 + 0xc) + 0x10) + (uVar7 & 0x3ffff) * 4);
  local_2c = (int *)(uint)*(byte *)(local_28 + 0x11);
  local_34 = (int *)FUN_00638190(local_2c,local_30 + 0x10);
  local_34[3] = (int)local_28;
  if (0 < (int)local_2c) {
    local_28 = local_34 + 6;
    do {
      uVar8 = (int)*local_40 >> 0xf & 0x1ff;
      if (((byte)*local_40 & 0x3f) == 4) {
        *local_28 = *(int *)(local_30 + 0x18 + uVar8 * 4);
      }
      else {
        iVar12 = FUN_00638220(local_3c + uVar8 * 2);
        *local_28 = iVar12;
      }
      local_28 = local_28 + 1;
      local_40 = local_40 + 1;
      local_2c = (int *)((int)local_2c + -1);
    } while (local_2c != (int *)0x0);
  }
  *piVar11 = 6;
  piVar11[1] = (int)local_34;
  
  // Check for stack overflow and garbage collect
  if (*(uint *)(*(int *)(param_1 + 0x10) + 0x20) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x24)) {
    local_28 = (int *)FUN_00627290();
    FUN_00626f80(param_1,0);
    iVar12 = 0;
    if (0 < *(int *)(*(int *)(param_1 + 0x10) + 8)) {
      do {
        iVar14 = *(int *)(param_1 + 0x10);
        iVar9 = FUN_00626f80(param_1,0);
        piVar11 = (int *)(iVar14 + 4);
        *piVar11 = *piVar11 - iVar9;
        iVar12 = iVar12 + 1;
      } while (iVar12 < *(int *)(*(int *)(param_1 + 0x10) + 8));
    }
    FUN_00626f80(param_1,0);
    FUN_00627010(local_28);
    FUN_006270e0();
  }
  goto LAB_00634890;
  
switchD_006348ed_caseD_1b:
  // Loop instruction
  local_28 = (int *)(*(int *)(param_1 + 0x14) + -0x18);
  if ((uVar13 & 0x1ff) != 0) {
    *(int **)(param_1 + 8) = piVar11 + (uVar13 & 0x1ff) * 2 + -2;
  }
  if (*(int *)(param_1 + 0x48) != 0) {
    FUN_006382a0();
  }
  *(undefined4 *)(*(int *)(param_1 + 0x14) + 8) = 8;
  *(uint **)(*(int *)(param_1 + 0x14) + 0xc) = local_40;
  if ((*(byte *)(local_28 + 2) & 4) == 0) {
    return piVar11;
  }
  iVar12 = *(int *)(local_28[3] + -4);
  FUN_00636260(param_1);
  if (-1 < (int)((iVar12 >> 6 & 0x1ffU) - 1)) {
    *(undefined4 *)(param_1 + 8) = *(undefined4 *)(*(int *)(param_1 + 0x14) + 4);
  }
  goto LAB_0063485e;
}