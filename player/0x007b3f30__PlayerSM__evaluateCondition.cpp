// FUNC_NAME: PlayerSM::evaluateCondition
// Address: 0x007b3f30
// Role: Evaluates state machine transition conditions for the player state machine (PlayerSM).
// This function checks various conditions based on a switch on (param_4 - 0x13), which corresponds to condition IDs.
// It accesses the player object via param_1 and the underlying entity via *(int**)(param_1 + 0x58) (piVar8).
// Many conditions involve checking flags, calling other game systems, and comparing values.

char __thiscall PlayerSM::evaluateCondition(int thisPtr, float param_2, undefined4 param_3, float conditionId, float param_5)
{
  bool bVar1;
  float fVar2;
  char cVar3;
  undefined1 uVar4;
  char cVar5;
  uint uVar6;
  int *piVar7;
  int *entityPtr;
  int iVar9;
  undefined4 uVar10;
  bool bVar11;
  bool bVar12;
  bool bVar13;
  float10 fVar14;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float10 extraout_ST0_02;
  undefined4 uVar15;
  
  entityPtr = *(int **)(thisPtr + 0x58); // +0x58: pointer to entity/character object
  cVar5 = '\0';
  switch((int)conditionId + -0x13) {
  case 0: // condition 0x13
    if (entityPtr[0x3fc] == 0) { // +0xFF0: some state/ID
      return true;
    }
    if (entityPtr[0x3fc] != 0x48) { // +0xFF0: check if state is 0x48
      return false;
    }
    return true;
  default:
    cVar5 = FUN_007ab790(param_2,param_3,conditionId,param_5); // generic condition evaluation fallback
    break;
  case 2: // condition 0x15
    uVar4 = FUN_006252d0(); // get random float?
    param_5 = (float)CONCAT31(param_5._1_3_,uVar4);
    cVar3 = FUN_00690210(0x1d); // check if input action 0x1d is pressed
    if (cVar3 != '\0') {
      iVar9 = FUN_007ab1f0(); // get some game object (player?)
      if ((((entityPtr[0x3fc] != 0) && (entityPtr[0x3fc] != 0x48)) && (iVar9 != 0)) &&
         (*(char *)(iVar9 + 0x1aa) == param_5._0_1_)) { // +0x1AA: some ID
        uVar6 = (uint)param_5 & 0xff;
        cVar5 = '\x01';
        if (uVar6 != 0) {
          if (uVar6 == 1) {
            *(undefined4 *)(thisPtr + 0x74) = 0; // +0x74: state machine timer/action
            return true;
          }
          if (uVar6 == 2) {
            *(undefined4 *)(thisPtr + 0x74) = 1;
            return true;
          }
        }
      }
    }
    break;
  case 3: // condition 0x16
switchD_007b3f4b_caseD_3:
    uVar4 = FUN_007b1740(); // check some condition
    return uVar4;
  case 4: // condition 0x17
    uVar4 = FUN_007b1630(); // check another condition
    return uVar4;
  case 5: // condition 0x18
    iVar9 = FUN_007abe90(); // get some game state
    if ((iVar9 != 0) || (cVar3 = FUN_00690150(0x25), cVar3 != '\0')) { // check if action 0x25 is active
      if ((*(int *)(thisPtr + 0x1b0) == 1) && (cVar5 = FUN_00800c10(), cVar5 != '\0')) { // +0x1B0: some state flag
        return false;
      }
      if ((iVar9 != 0) && ((*(uint *)(iVar9 + 0x1d0) >> 3 & 1) != 0)) { // +0x1D0: bit 3
        return false;
      }
      *(ushort *)(thisPtr + 0x184) = *(ushort *)(thisPtr + 0x184) | 1; // +0x184: flags, set bit 0
      return true;
    }
    break;
  case 6: // condition 0x19
    if (((*(byte *)(thisPtr + 0x184) & 1) != 0) && (cVar3 = FUN_00690150(0x30), cVar3 == '\0')) { // check flag bit 0 and action 0x30 not active
      *(ushort *)(thisPtr + 0x184) = *(ushort *)(thisPtr + 0x184) & 0xfffe; // clear bit 0
      return true;
    }
    break;
  case 7: // condition 0x1A
    if (*(int *)(thisPtr + 0x1b0) == 0) { // +0x1B0: state flag
      return true;
    }
    break;
  case 8: // condition 0x1B
    if (*(int *)(thisPtr + 0x1b0) == 1) {
      return true;
    }
    break;
  case 9: // condition 0x1C
    uVar4 = FUN_007afd00(); // check some condition
    return uVar4;
  case 10: // condition 0x1D
    cVar3 = FUN_00800c10(); // check if something is active
    if (cVar3 != '\0') {
      return true;
    }
    break;
  case 0xb: // condition 0x1E
    uVar10 = FUN_00798f50(0xe); // get some game state
    cVar5 = FUN_0079e920(uVar10); // check if state is active
    if (cVar5 != '\0') {
      return false;
    }
    cVar5 = FUN_0079e920(0x6eae57f2); // check another state
    if (cVar5 == '\0') {
      cVar5 = FUN_00690150(0x32); // check action 0x32
      if (cVar5 == '\0') {
        return true;
      }
      return false;
    }
    return false;
  case 0xd: // condition 0x20
    goto switchD_007b3f4b_caseD_d;
  case 0xe: // condition 0x21
    iVar9 = *(int *)(thisPtr + 400); // +0x190: some state ID
    if (((iVar9 != 0xb) && (iVar9 != 0xc)) && ((iVar9 != 0xf && (iVar9 != 0x10)))) {
      return false;
    }
    iVar9 = *(int *)(thisPtr + 0x194); // +0x194: another state ID
    if ((((iVar9 != 9) && (iVar9 != 10)) && (iVar9 != 0xd)) && (iVar9 != 0xe)) {
      return false;
    }
    goto switchD_007b3f4b_caseD_d;
  case 0xf: // condition 0x22
    goto switchD_007b3f4b_caseD_f;
  case 0x10: // condition 0x23
    iVar9 = *(int *)(thisPtr + 400); // +0x190
    if ((((iVar9 != 9) && (iVar9 != 10)) && (iVar9 != 0xd)) && (iVar9 != 0xe)) {
      return false;
    }
    iVar9 = *(int *)(thisPtr + 0x194); // +0x194
    if (((iVar9 != 0xb) && (iVar9 != 0xc)) && ((iVar9 != 0xf && (iVar9 != 0x10)))) {
      return false;
    }
    goto switchD_007b3f4b_caseD_f;
  case 0x11: // condition 0x24
    cVar5 = FUN_007f95d0(); // check some condition
    if (cVar5 != '\x01') {
      return false;
    }
  case 0xc: // condition 0x1F (fall through from 0x11)
    uVar15 = 1;
    uVar10 = FUN_00798f50(0x10); // get state
    uVar4 = FUN_007b0fa0(uVar10,uVar15); // check condition with parameter
    cVar5 = FUN_00410eb0(); // check if in some mode
    if (cVar5 == '\0') {
      return uVar4;
    }
    bVar11 = DAT_00d6bfe0 < *(float *)(thisPtr + 0x1e0); // +0x1E0: some float value
    if (*(float *)(thisPtr + 0x1c4) < DAT_00d6bfe8) { // +0x1C4: another float
      return false;
    }
    if (DAT_00d6bfe4 < *(float *)(thisPtr + 0x1c4)) {
      return false;
    }
LAB_007b41cc:
    if (!bVar11) {
      return false;
    }
LAB_007b41d4:
    FUN_007af6c0(); // trigger some action
    return true;
  case 0x12: // condition 0x25
    cVar5 = FUN_007f95d0();
    if (cVar5 != '\x01') {
      return false;
    }
    uVar15 = 2;
    uVar10 = FUN_00798f50(0x11);
    uVar4 = FUN_007b0fa0(uVar10,uVar15);
    cVar5 = FUN_00410eb0();
    if (cVar5 == '\0') {
      return uVar4;
    }
    if (*(float *)(thisPtr + 0x1dc) <= DAT_00d6bfe0) goto LAB_007b41e6;
    bVar1 = true;
    goto LAB_007b41e8;
  case 0x13: // condition 0x26
    cVar5 = FUN_007f95d0();
    if (cVar5 != '\x01') {
      return false;
    }
    uVar15 = 4;
    uVar10 = FUN_00798f50(0x12);
    uVar4 = FUN_007b0fa0(uVar10,uVar15);
    cVar5 = FUN_00410eb0();
    if (cVar5 == '\0') {
      return uVar4;
    }
    if (*(float *)(thisPtr + 0x1dc) <= DAT_00d6bfe0) goto LAB_007b42b1;
    bVar1 = true;
    goto LAB_007b42b3;
  case 0x14: // condition 0x27
    cVar5 = FUN_00410eb0();
    if (cVar5 == '\0') {
      uVar10 = FUN_00798f50(0x13);
      cVar5 = FUN_0079e920(uVar10);
      if ((cVar5 == '\0') && (cVar5 = FUN_0079e920(0x8e6718b8), cVar5 == '\0')) {
        return false;
      }
      cVar5 = FUN_007afb20(); // check some condition
      if (cVar5 == '\0') {
        return false;
      }
      FUN_0079eab0(1,&param_5,&param_2,0,0,DAT_00d5ccf8,DAT_00d5ccf8,DAT_00d5ccf8); // some function call
      if (param_5 < _DAT_00d577a0) {
        return true;
      }
      return false;
    }
    cVar5 = FUN_00410eb0();
    if (cVar5 == '\0') {
      return false;
    }
    if (*(float *)(thisPtr + 0x1c8) < _DAT_00d5780c) { // +0x1C8: float
      return false;
    }
    if (0.0 < *(float *)(thisPtr + 0x1c4) || *(float *)(thisPtr + 0x1c4) == 0.0) {
      return false;
    }
    cVar5 = FUN_007afb20();
    if (cVar5 != '\0') {
      return true;
    }
    return false;
  case 0x15: // condition 0x28
  case 0x19: // condition 0x2C
    cVar5 = FUN_00410eb0();
    if (cVar5 == '\0') {
      uVar10 = FUN_00798f50(0x13);
      cVar5 = FUN_0079e920(uVar10);
      if (cVar5 != '\0') {
        return false;
      }
      cVar5 = FUN_0079e920(0x8e6718b8);
      if (cVar5 == '\0') {
        return true;
      }
      return false;
    }
    goto LAB_007b4560;
  case 0x16: // condition 0x29
  case 0x1a: // condition 0x2D
    cVar5 = FUN_00410eb0();
    if (cVar5 == '\0') {
      uVar10 = FUN_00798f50(0x14);
      cVar5 = FUN_0079e920(uVar10);
      if (cVar5 != '\0') {
        return false;
      }
      cVar5 = FUN_0079e920(0xb43ee40b);
      if (cVar5 == '\0') {
        return true;
      }
      return false;
    }
LAB_007b4560:
    uVar4 = FUN_007b0740(); // check some condition
    return uVar4;
  case 0x17: // condition 0x2A
  case 0x1b: // condition 0x2E
    cVar5 = FUN_00410eb0();
    if (cVar5 != '\0') {
      uVar4 = FUN_007b0770(); // check another condition
      return uVar4;
    }
    uVar10 = FUN_00798f50(0x15);
    cVar5 = FUN_0079e920(uVar10);
    if (cVar5 != '\0') {
      return true;
    }
    uVar10 = 0x1ffc4557;
    goto LAB_007b4620;
  case 0x18: // condition 0x2B
    cVar5 = FUN_00410eb0();
    if (cVar5 == '\0') {
      uVar10 = FUN_00798f50(0x13);
      cVar5 = FUN_0079e920(uVar10);
      if ((cVar5 == '\0') && (cVar5 = FUN_0079e920(0x8e6718b8), cVar5 == '\0')) {
        return false;
      }
      cVar5 = FUN_007afb20();
      if (cVar5 == '\0') {
        return false;
      }
      FUN_0079eab0(1,&param_5,&param_2,0,0,DAT_00d5ccf8,DAT_00d5ccf8,DAT_00d5ccf8);
      if (param_5 < 0.0) {
        return false;
      }
      return true;
    }
    cVar5 = FUN_00410eb0();
    if (cVar5 == '\0') {
      return false;
    }
    if (*(float *)(thisPtr + 0x1c8) < _DAT_00d5780c) {
      return false;
    }
    if (*(float *)(thisPtr + 0x1c4) < _DAT_00d577a0) {
      return false;
    }
    cVar5 = FUN_007afb20();
    if (cVar5 != '\0') {
      return true;
    }
    return false;
  case 0x1c: // condition 0x2F
    piVar7 = (int *)FUN_007ab710(); // get some game object
    if (piVar7 != (int *)0x0) {
      fVar14 = (float10)(**(code **)(*piVar7 + 0xc0))(); // call virtual function at vtable+0xC0
      param_5 = (float)fVar14;
      (**(code **)(*piVar7 + 0xc4))(); // call virtual function at vtable+0xC4
      if (extraout_ST0_00 * (float10)_DAT_00d5c458 < (float10)param_5) {
        return false;
      }
      if ((char)piVar7[0x6e3] == '\0') { // +0x1B8C: some flag
        if ((uint)entityPtr[0x83c] <= (uint)*(byte *)(thisPtr + 0x1ac)) { // +0x1AC: some byte
          return true;
        }
        return false;
      }
      return false;
    }
    break;
  case 0x1d: // condition 0x30
    cVar3 = FUN_007af890(); // check some condition
    if (cVar3 != '\0') {
      return true;
    }
    break;
  case 0x1e: // condition 0x31
    iVar9 = FUN_007ab710();
    if (iVar9 != 0) {
      param_5 = (float)CONCAT31(param_5._1_3_,*(undefined1 *)(iVar9 + 0x1b8c)); // +0x1B8C: flag
      uVar10 = FUN_00798f50(0x16);
      cVar3 = FUN_0079e920(uVar10);
      if (cVar3 == '\0') {
        uVar10 = FUN_00798f50(0x17);
        cVar3 = FUN_0079e920(uVar10);
        if (cVar3 == '\0') {
          uVar10 = FUN_00798f50(0x1e);
          cVar3 = FUN_0079e920(uVar10);
          if (cVar3 == '\0') {
            return false;
          }
          uVar10 = FUN_00798f50(0x1f);
          cVar3 = FUN_0079e920(uVar10);
          if (cVar3 == '\0') {
            return false;
          }
        }
      }
      if (param_5._0_1_ == '\x01') {
        return true;
      }
    }
    break;
  case 0x1f: // condition 0x32
    iVar9 = FUN_007ab710();
    if ((iVar9 != 0) && (*(char *)(iVar9 + 0x1b8c) == '\0')) { // +0x1B8C: flag
      uVar10 = FUN_00798f50(0x1b);
      cVar3 = FUN_0079e920(uVar10);
      if (((cVar3 != '\0') &&
          ((cVar3 = FUN_00690210(0x21), cVar3 == '\0' && // check input action 0x21
           (FUN_0079eab0(0,&param_5,&param_2,0,0,DAT_00d5ccf8,DAT_00d5ccf8,DAT_00d5ccf8),
           param_5 < 0.0)))) && (param_2 <= 0.0)) {
        return true;
      }
    }
    break;
  case 0x20: // condition 0x33
    uVar10 = FUN_00798f50(0x1b);
    cVar5 = FUN_0079e920(uVar10);
    return cVar5 == '\0';
  case 0x21: // condition 0x34
    iVar9 = FUN_007ab710();
    if ((iVar9 != 0) && (*(char *)(iVar9 + 0x1b8c) == '\0')) {
      uVar10 = FUN_00798f50(0x19);
      cVar3 = FUN_0079e920(uVar10);
      if ((cVar3 != '\0') &&
         (((cVar3 = FUN_00690210(0x21), cVar3 == '\0' &&
           (FUN_0079eab0(0,&param_5,&param_2,0,0,DAT_00d5ccf8,DAT_00d5ccf8,DAT_00d5ccf8),
           0.0 <= param_5)) && (0.0 < param_2)))) {
        return true;
      }
    }
    break;
  case 0x22: // condition 0x35
    uVar10 = FUN_00798f50(0x19);
    cVar5 = FUN_0079e920(uVar10);
    return cVar5 == '\0';
  case 0x23: // condition 0x36
    iVar9 = FUN_007ab710();
    if ((iVar9 != 0) && (*(char *)(iVar9 + 0x1b8c) == '\0')) {
      uVar10 = FUN_00798f50(0x1a);
      cVar3 = FUN_0079e920(uVar10);
      if (((cVar3 != '\0') &&
          ((cVar3 = FUN_00690210(0x21), cVar3 == '\0' &&
           (FUN_0079eab0(0,&param_5,&param_2,0,0,DAT_00d5ccf8,DAT_00d5ccf8,DAT_00d5ccf8),
           param_5 < 0.0)))) && (0.0 < param_2)) {
        return true;
      }
    }
    break;
  case 0x24: // condition 0x37
    uVar10 = FUN_00798f50(0x1a);
    cVar5 = FUN_0079e920(uVar10);
    return cVar5 == '\0';
  case 0x25: // condition 0x38
    iVar9 = FUN_007ab710();
    if ((iVar9 != 0) && (*(char *)(iVar9 + 0x1b8c) == '\0')) {
      uVar10 = FUN_00798f50(0x18);
      cVar3 = FUN_0079e920(uVar10);
      if ((cVar3 != '\0') &&
         (((cVar3 = FUN_00690210(0x21), cVar3 == '\0' &&
           (FUN_0079eab0(0,&param_5,&param_2,0,0,DAT_00d5ccf8,DAT_00d5ccf8,DAT_00d5ccf8),
           0.0 <= param_5)) && (param_2 <= 0.0)))) {
        return true;
      }
    }
    break;
  case 0x26: // condition 0x39
    uVar10 = FUN_00798f50(0x18);
    cVar5 = FUN_0079e920(uVar10);
    return cVar5 == '\0';
  case 0x27: // condition 0x3A
    uVar10 = FUN_00798f50(0x1c);
    cVar5 = FUN_0079e920(uVar10);
    if ((cVar5 == '\0') || (cVar5 = FUN_007b13a0(0), cVar5 == '\0')) {
      cVar5 = '\0';
    }
    else {
      cVar5 = '\x01';
    }
    cVar3 = FUN_00410eb0();
    if (cVar3 != '\0') {
      uVar4 = FUN_007b07f0(1);
      return uVar4;
    }
    break;
  case 0x28: // condition 0x3B
    uVar10 = FUN_00798f50(0x1d);
    cVar5 = FUN_0079e920(uVar10);
    if ((cVar5 == '\0') || (cVar5 = FUN_007b13a0(1), cVar5 == '\0')) {
      bVar11 = false;
    }
    else {
      bVar11 = true;
    }
    cVar5 = FUN_00410eb0();
    if (cVar5 == '\0') {
      return bVar11;
    }
    bVar11 = DAT_00d6bfe0 < *(float *)(thisPtr + 0x1dc); // +0x1DC: float
    if (*(float *)(thisPtr + 0x1c4) <= _DAT_00d577a0) {
      return false;
    }
    if (*(float *)(thisPtr + 0x1c8) <= DAT_00d5f79c) {
      return false;
    }
    goto LAB_007b41cc;
  case 0x29: // condition 0x3C
  case 0x2a: // condition 0x3D
    return false;
  case 0x2b: // condition 0x3E
    iVar9 = FUN_007ab710();
    if (iVar9 != 0) {
      uVar10 = FUN_00798f50(0x1e);
      cVar3 = FUN_0079e920(uVar10);
      if (cVar3 != '\0') {
        uVar10 = FUN_00798f50(0x1f);
        cVar3 = FUN_0079e920(uVar10);
        if ((cVar3 != '\0') && (*(char *)(iVar9 + 0x1b8c) == '\0')) {
          return true;
        }
      }
    }
    break;
  case 0x2c: // condition 0x3F
    iVar9 = FUN_007ab710();
    if (iVar9 == 0) {
      return false;
    }
    if (*(char *)(iVar9 + 0x1b8c) != '\x01') {
      return false;
    }
    uVar10 = FUN_00798f50(0x1e);
    cVar5 = FUN_0079e920(uVar10);
    if (cVar5 != '\0') {
      return true;
    }
    uVar10 = FUN_00798f50(0x1f);
LAB_007b4620:
    cVar5 = FUN_0079e920(uVar10);
    if (cVar5 == '\0') {
      return false;
    }
    return true;
  case 0x2d: // condition 0x40
    iVar9 = FUN_007ab710();
    if (iVar9 == 0) {
      return false;
    }
    uVar10 = FUN_00798f50(0x1e);
    cVar5 = FUN_0079e920(uVar10);
    if (cVar5 != '\0') {
      return false;
    }
    uVar10 = 0x1f;
    goto LAB_007b4cac;
  case 0x2e: // condition 0x41
    iVar9 = FUN_007ab710();
    if (iVar9 == 0) {
      return false;
    }
    uVar10 = FUN_00798f50(0x1e);
    cVar5 = FUN_0079e920(uVar10);
    if (cVar5 != '\0') {
      return false;
    }
    uVar10 = FUN_00798f50(0x1f);
    cVar5 = FUN_0079e920(uVar10);
    if (cVar5 != '\0') {
      return false;
    }
    cVar5 = FUN_0079e920(0x6eae57f2);
    if (cVar5 != '\0') {
      return false;
    }
    uVar10 = 0xe;
LAB_007b4cac:
    uVar10 = FUN_00798f50(uVar10);
    cVar5 = FUN_0079e920(uVar10);
LAB_007b4cbb:
    if (cVar5 == '\0') {
      return true;
    }
    return false;
  case 0x2f: // condition 0x42
    cVar5 = FUN_007af840(); // check some condition
    goto LAB_007b4d2e;
  case 0x30: // condition 0x43
    cVar5 = FUN_007af860(thisPtr + 0x188); // +0x188: some data
LAB_007b4d2e:
    if (cVar5 != '\0') {
      FUN_007ab730(); // trigger some action
      return cVar5;
    }
    break;
  case 0x31: // condition 0x44
    iVar9 = entityPtr[0x3fc]; // +0xFF0
    if (iVar9 == 0) {
      return true;
    }
    piVar7 = (int *)(iVar9 + -0x48);
    if (piVar7 == (int *)0x0) {
      return true;
    }
    fVar14 = (float10)(**(code **)(*entityPtr + 0x218))(); // call virtual function at vtable+0x218
    cVar5 = FUN_007f81c0(piVar7,(float)fVar14); // check some condition
    if (cVar5 == '\0') {
      return true;
    }
    (**(code **)(*piVar7 + 0xc0))(); // call virtual function at vtable+0xC0
    if ((float10)0 < extraout_ST0) {
      if (*(char *)(iVar9 + 0x1b44) == '\x03') { // +0x1B44: some state
        return true;
      }
      if (*(char *)(iVar9 + 0x1b44) != '\x02') {
        return false;
      }
      return true;
    }
    return true;
  case 0x32: // condition 0x45
    iVar9 = FUN_007ab710();
    if (iVar9 != 0) {
      fVar2 = (float)(int)param_2;
      if ((int)param_2 < 0) {
        fVar2 = fVar2 + DAT_00e44578;
      }
      param_2 = fVar2 * DAT_00d5efb8;
      param_5._0_1_ = *(float *)(thisPtr + 0x174) < param_2; // +0x174: float
      entityPtr = (int *)FUN_006bc8d0(iVar9,0x369ac561); // get component by hash
      if (entityPtr != (int *)0x0) {
        iVar9 = FUN_006ad770(entityPtr); // check some condition
        if ((((entityPtr[0x7e6] & 0x50cU) != 0) && (iVar9 != 0)) &&
           ((cVar5 = FUN_0078af40(), cVar5 != '\0' &&
            (param_5._0_1_ = '\x01', param_2 <= *(float *)(thisPtr + 0x174) + DAT_00d5d934)))) {
          param_5._0_1_ = '\0';
        }
        cVar5 = ((uint)entityPtr[0x7e6] >> 7 & 1) != 0; // +0x1F98: bit 7
        cVar3 = FUN_007aefe0(0x3c); // check some condition
        if (cVar3 == '\0') {
          if ((param_5._0_1_ == '\0') && (cVar3 = (**(code **)(*entityPtr + 0x294))(), cVar3 == '\0')) // call virtual function at vtable+0x294
          {
            return (bool)cVar5;
          }
          entityPtr[0x84b] = 0; // +0x212C: set to 0
          cVar5 = true;
        }
        if ((param_5._0_1_ != '\0') && (cVar3 = FUN_0072ac50(), cVar3 != '\0')) {
          *(ushort *)(thisPtr + 0x184) = *(ushort *)(thisPtr + 0x184) | 4; // set bit 2
          return (bool)cVar5;
        }
      }
    }
    break;
  case 0x33: // condition 0x46
    fVar2 = (float)(int)param_2;
    if ((int)param_2 < 0) {
      fVar2 = fVar2 + DAT_00e44578;
    }
    if (*(float *)(thisPtr + 0x178) < fVar2 * DAT_00d5efb8) { // +0x178: float
      return true;
    }
    return false;
  case 0x34: // condition 0x47
    param_5 = (float)entityPtr[0xc3e]; // +0x30F8: some value
    FUN_00799560(entityPtr[0xc3f]); // +0x30FC: another value
    if ((float10)conditionId <= extraout_ST0_02) {
      return true;
    }
    break;
  case 0x35: // condition 0x48
    iVar9 = FUN_007ab710();
    if (((iVar9 != 0) && (*(char *)(iVar9 + 0x1b8c) == '\0')) &&
       (cVar3 = FUN_00753da0(entityPtr,*(undefined4 *)(thisPtr + 0x30),entityPtr[0x404]), cVar3 != '\0')) // +0x30: some value, +0x1010: entity field
    {
      *(int *)(thisPtr + 0x18c) = entityPtr[0x404]; // +0x18C: store value
      return true;
    }
    break;
  case 0x36: // condition 0x49
    entityPtr = (int *)FUN_007ab710();
    if ((entityPtr != (int *)0x0) &&
       (((((**(code **)(*entityPtr + 0x20c))(*(undefined4 *)(thisPtr + 0x58)), // call virtual function at vtable+0x20C
          extraout_ST0_01 < (float10)DAT_00d5ef90 ||
          (cVar3 = (**(code **)(*entityPtr + 0x294))(), cVar3 != '\0')) &&
         ((char)entityPtr[0x6e3] == '\0')) && (((uint)entityPtr[0x208] >> 2 & 1) == 0)))) { // +0x820: bit 2
      return true;
    }
    break;
  case 0x37: // condition 0x4A
    iVar9 = FUN_007ab710();
    if (((iVar9 != 0) && (iVar9 = FUN_006bc8d0(iVar9,0x369ac561), iVar9 != 0)) &&
       ((*(byte *)(iVar9 + 0x1f54) & 1) != 0)) { // +0x1F54: bit 0
      return true;
    }
    break;
  case 0x38: // condition 0x4B
    if (*(float *)(thisPtr + 0x30) <= _DAT_00d5c458) { // +0x30: float
      return false;
    }
    cVar5 = FUN_0079ebe0(0);
    goto LAB_007b4cbb;
  case 0x39: // condition 0x4C
    iVar9 = FUN_007ab710();
    if ((iVar9 != 0) && (*(int *)(iVar9 + 0x1ed4) == *(int *)(*(int *)(thisPtr + 0x58) + 0x1ed4))) { // +0x1ED4: some ID
      return true;
    }
    break;
  case 0x3a: // condition 0x4D
    iVar9 = FUN_007ab710();
    if (((iVar9 != 0) && (*(char *)(iVar9 + 0x1b8c) == '\0')) &&
       (cVar3 = FUN_00690210(0x32), cVar3 != '\0')) { // check input action 0x32
      *(undefined4 *)(thisPtr + 0x74) = 0xe; // +0x74: set timer/action
      return true;
    }
    break;
  case 0x3b: // condition 0x4E
    iVar9 = FUN_007ab710();
    if (((iVar9 != 0) && (cVar3 = FUN_00800c10(), cVar3 != '\0')) &&
       ((*(char *)(iVar9 + 0x1b8c) == '\0' || (*(char *)(iVar9 + 0x1b8c) == '\x01')))) {
      uVar10 = FUN_00798f50(0x42);
      cVar3 = FUN_0079e920(uVar10);
      if (((cVar3 != '\0') && (cVar3 = FUN_00799b10(), cVar3 != '\0')) &&
         (cVar3 = FUN_007ab420(0x40), cVar3 != '\0')) {
        *(undefined4 *)(thisPtr + 0x74) = 0xd;
        return true;
      }
    }
    break;
  case 0x3d: // condition 0x50
    param_5 = (float)FUN_006252d0(); // get random float
    if (entityPtr[0x3fc] == 0) {
      iVar9 = 0;
    }
    else {
      iVar9 = entityPtr[0x3fc] + -0x48;
    }
    cVar3 = FUN_00690210(0x3e); // check input action 0x3E
    if (((cVar3 != '\0') && (iVar9 != 0)) && ((float)(int)(char)entityPtr[0x7b1] == param_5)) { // +0x1EC4: some byte
      FUN_007af760(param_5); // trigger action
      return true;
    }
    break;
  case 0x3e: // condition 0x51
switchD_007b3f4b_caseD_3e:
    uVar4 = FUN_007b0f00(); // check some condition
    return uVar4;
  case 0x3f: // condition 0x52
    cVar3 = FUN_007afe60(entityPtr); // check some condition
    if ((cVar3 != '\0') && ((entityPtr[0x9d2] & 0x8000U) != 0)) { // +0x2748: bit 15
      if (entityPtr[0x3fc] == 0) {
        iVar9 = 0;
      }
      else {
        iVar9 = entityPtr[0x3fc] + -0x48;
      }
      cVar5 = FUN_007b15c0(entityPtr,iVar9); // check another condition
      if (cVar5 != '\0') goto switchD_007b3f4b_caseD_3e;
    }
    break;
  case 0x40: // condition 0x53
    cVar3 = FUN_007afe60(entityPtr);
    if ((cVar3 != '\0') && ((entityPtr[0x9d2] & 0x4000U) != 0)) { // bit 14
      FUN_006901b0(0x1d); // set action 0x1D active
      cVar5 = FUN_007b1630(); // check condition
      if (cVar5 == '\0') {
        FUN_006901e0(0x1d); // clear action 0x1D
        return false;
      }
    }
    break;
  case 0x41: // condition 0x54
    cVar3 = FUN_007afe60(entityPtr);
    if ((cVar3 != '\0') && ((entityPtr[0x9d2] & 0x4000U) != 0)) {
      FUN_006901b0(0x1d);
      goto switchD_007b3f4b_caseD_3;
    }
    break;
  case 0x42: // condition 0x55
    uVar10 = FUN_00798f50(0xc);
    uVar4 = FUN_0079e920(uVar10);
    param_2 = (float)CONCAT31(param_2._1_3_,uVar4);
    uVar4 = FUN_00690210(0x41); // check input action 0x41
    param_4 = (float)CONCAT31(param_4._1_3_,uVar4);
    uVar4 = FUN_00690210(0x42); // check input action 0x42
    param_5 = (float)CONCAT31(param_5._1_3_,uVar4);
    if ((param_2._0_1_ != '\0') && (cVar3 = FUN_0045f120(), cVar3 != '\0')) {
      if ((param_4._0_1_ != '\0') || (param_5._0_1_ != '\0')) {
        cVar5 = '\x01';
        if (param_4._0_1_ != '\0') {
          FUN_006901e0(0x41); // clear action 0x41
          return true;
        }
        if (param_5._0_1_ != '\0') {
          FUN_006901e0(0x42); // clear action 0x42
          return true;
        }
      }
    }
    break;
  case 0x43: // condition 0x56
    cVar5 = FUN_00481660(); // check some condition
    if ((cVar5 == '\0') && (cVar5 = FUN_00481640(), cVar5 == '\0')) {
      return false;
    }
    if (*(char *)(*(int *)(thisPtr + 0x58) + 0x2470) != '\0') { // +0x2470: flag
      return false;
    }
    return true;
  case 0x44: // condition 0x57
    uVar10 = FUN_00798f50(0xc);
    uVar4 = FUN_0079e970(uVar10);
    return uVar4;
  }
  return cVar5;
switchD_007b3f4b_caseD_f:
  uVar15 = 4;
  uVar10 = FUN_00798f50(0x12);
  uVar4 = FUN_007b0fa0(uVar10,uVar15);
  cVar5 = FUN_00410eb0();
  if (cVar5 == '\0') {
    return uVar4;
  }
  if (*(float *)(thisPtr + 0x1dc) <= DAT_00d6bfe0) {
LAB_007b42b1:
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
LAB_007b42b3:
  if (*(float *)(thisPtr + 0x1e0) <= DAT_00d6bfe0) {
    bVar11 = false;
    bVar13 = *(float *)(thisPtr + 0x1c4) == DAT_00d6bfe4;
    bVar12 = *(float *)(thisPtr + 0x1c4) < DAT_00d6bfe4;
  }
  else {
    bVar13 = *(float *)(thisPtr + 0x1c4) == DAT_00d6bfe4;
    bVar12 = *(float *)(thisPtr + 0x1c4) < DAT_00d6bfe4;
    bVar11 = true;
  }
  goto LAB_007b420a;
switchD_007b3f4b_caseD_d:
  uVar15 = 2;
  uVar10 = FUN_00798f50(0x11);
  uVar4 = FUN_007b0fa0(uVar10,uVar15);
  cVar5 = FUN_00410eb0();
  if (cVar5 == '\0') {
    return uVar4;
  }
  if (*(float *)(thisPtr + 0x1dc) <= DAT_00d6bfe0) {
LAB_007b41e6:
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
LAB_007b41e8:
  bVar11 = DAT_00d6bfe0 < *(float *)(thisPtr + 0x1e0);
  bVar13 = DAT_00d6bfe8 == *(float *)(thisPtr + 0x1c4);
  bVar12 = DAT_00d6bfe8 < *(float *)(thisPtr + 0x1c4);
LAB_007b420a:
  if (bVar12 || bVar13) {
    return false;
  }
  if (DAT_00d5f79c < *(float *)(thisPtr + 0x1c8)) {
    return false;
  }
  if (bVar1) goto LAB_007b41d4;
  goto LAB_007b41cc;
}