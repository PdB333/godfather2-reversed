// FUNC_NAME: LicenseManager::validateLicense
void __thiscall LicenseManager::validateLicense(int thisPtr, int licenseData)
{
  int *piVar1;
  undefined4 *puVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  char cVar7;
  int iVar8;
  undefined4 uVar9;
  int *piVar10;
  int *piVar11;
  undefined1 *puVar12;
  int local_74;
  int local_5c;
  int local_44;
  undefined1 local_40 [16];
  undefined1 local_30 [16];
  undefined1 local_20 [16];
  undefined1 local_10 [16];
  
  iVar8 = FUN_009c8e50(0x44); // allocate 0x44 bytes
  if (iVar8 == 0) {
    uVar9 = 0;
  }
  else {
    uVar9 = FUN_008afc20(licenseData); // copy license data
  }
  iVar8 = *(int *)(thisPtr + 0x30); // capacity
  piVar11 = (int *)(thisPtr + 0x28); // pointer to array
  if (*(int *)(thisPtr + 0x2c) == iVar8) { // if size == capacity
    if (iVar8 == 0) {
      iVar8 = 1;
    }
    else {
      iVar8 = iVar8 * 2;
    }
    FUN_008b0020(iVar8); // resize array
  }
  puVar2 = (undefined4 *)(*piVar11 + *(int *)(thisPtr + 0x2c) * 4);
  *(int *)(thisPtr + 0x2c) = *(int *)(thisPtr + 0x2c) + 1; // increment size
  if (puVar2 != (undefined4 *)0x0) {
    *puVar2 = uVar9; // store license
  }
  piVar1 = (int *)(licenseData + 0x10); // license key data
  if ((((*(int *)(licenseData + 0x10) == -0x45245246) && (*(int *)(licenseData + 0x14) == -0x41104111)) &&
      (*(int *)(licenseData + 0x18) == -0x153ea5ab)) && (*(int *)(licenseData + 0x1c) == -0x6eeff6ef)) {
    return; // invalid license
  }
  bVar5 = false;
  bVar4 = false;
  bVar3 = false;
  FUN_004da550("XSZAKAL202_C820D3E_E3B541F_v3"); // hash function init
  piVar10 = (int *)FUN_004da7e0(local_20); // compute hash
  if (((*piVar1 == *piVar10) && (*(int *)(licenseData + 0x14) == piVar10[1])) &&
     ((*(int *)(licenseData + 0x18) == piVar10[2] && (*(int *)(licenseData + 0x1c) == piVar10[3])))) {
LAB_008b10b6:
    bVar6 = true; // license valid
  }
  else {
    bVar5 = true;
    bVar4 = false;
    bVar3 = false;
    local_74 = 0;
    FUN_004da550("XSZAKAL202_C81BF85_031D92E_v3"); // hash function init
    piVar10 = (int *)FUN_004da7e0(local_10); // compute hash
    if (((*piVar1 == *piVar10) && (*(int *)(licenseData + 0x14) == piVar10[1])) &&
       ((*(int *)(licenseData + 0x18) == piVar10[2] && (*(int *)(licenseData + 0x1c) == piVar10[3]))))
    goto LAB_008b10b6;
    bVar5 = true;
    bVar4 = true;
    bVar3 = false;
    local_5c = 0;
    FUN_004da550("XATZ0273XX_C80F4DE_B706157_v3"); // hash function init
    uVar9 = FUN_004da7e0(local_40); // compute hash
    cVar7 = FUN_00420950(uVar9); // compare hash
    if (cVar7 != '\0') goto LAB_008b10b6;
    bVar5 = true;
    bVar4 = true;
    bVar3 = true;
    local_44 = 0;
    FUN_004da550("XATZ0273XX_C7B4343_275E758_v3"); // hash function init
    uVar9 = FUN_004da7e0(local_30); // compute hash
    cVar7 = FUN_00420950(uVar9); // compare hash
    bVar6 = false;
    if (cVar7 != '\0') goto LAB_008b10b6;
  }
  if ((bVar3) && (local_44 != 0)) {
    FUN_004d8be0(); // cleanup
    FUN_009c8eb0(local_44); // free memory
  }
  if ((bVar4) && (local_5c != 0)) {
    FUN_004d8be0(); // cleanup
    FUN_009c8eb0(local_5c); // free memory
  }
  if ((bVar5) && (local_74 != 0)) {
    FUN_004d8be0(); // cleanup
    FUN_009c8eb0(local_74); // free memory
  }
  bVar3 = false;
  if (bVar6) {
    *(undefined4 *)(*(int *)(*piVar11 + -4 + *(int *)(thisPtr + 0x2c) * 4) + 0x20) = 0x14; // set license type to 0x14
    return;
  }
  FUN_004da550("XATZ0273XX_C7B44DB_3651001_v3"); // hash function init
  piVar10 = (int *)FUN_004da7e0(local_30); // compute hash
  if ((((*piVar1 == *piVar10) && (*(int *)(licenseData + 0x14) == piVar10[1])) &&
      (*(int *)(licenseData + 0x18) == piVar10[2])) && (*(int *)(licenseData + 0x1c) == piVar10[3])) {
LAB_008b1244:
    bVar4 = true; // license valid
  }
  else {
    bVar3 = true;
    local_74 = 0;
    FUN_004da550("XATZ0273XX_C7B44DB_70485CC_v3"); // hash function init
    uVar9 = FUN_004da7e0(local_40); // compute hash
    cVar7 = FUN_00420950(uVar9); // compare hash
    if (cVar7 != '\0') goto LAB_008b1244;
    bVar3 = true;
    FUN_004da550("XSZAKAL202_C820DB6_D9DB509_v3"); // hash function init
    uVar9 = FUN_004da7e0(local_10); // compute hash
    cVar7 = FUN_00420950(uVar9); // compare hash
    if (cVar7 != '\0') goto LAB_008b1244;
    puVar12 = local_20;
    bVar3 = true;
    FUN_004d8c00("XKATZ6792X_C8E2F04_FE1715D_v3"); // hash function init
    uVar9 = FUN_004da7e0(puVar12); // compute hash
    cVar7 = FUN_00420950(uVar9); // compare hash
    bVar4 = false;
    if (cVar7 != '\0') goto LAB_008b1244;
  }
  if ((bVar3) && (local_74 != 0)) {
    FUN_004d8be0(); // cleanup
    FUN_009c8eb0(local_74); // free memory
  }
  if (bVar4) {
    *(undefined4 *)(*(int *)(*piVar11 + -4 + *(int *)(thisPtr + 0x2c) * 4) + 0x20) = 0x15; // set license type to 0x15
    return;
  }
  bVar3 = false;
  FUN_004da550("XATZ0273XX_C7B44DB_A5A1275_v3"); // hash function init
  uVar9 = FUN_004da7e0(local_30); // compute hash
  cVar7 = FUN_00420950(uVar9); // compare hash
  if (cVar7 == '\0') {
    bVar3 = false;
    FUN_004da550("XSZAKAL202_C81BF6A_B07822C_v3"); // hash function init
    uVar9 = FUN_004da7e0(local_40); // compute hash
    cVar7 = FUN_00420950(uVar9); // compare hash
    if (cVar7 != '\0') goto LAB_008b13c5;
    puVar12 = local_10;
    bVar3 = true;
    FUN_004d8c00("XATZ0273XX_C80F501_702F228_v3"); // hash function init
    uVar9 = FUN_004da7e0(puVar12); // compute hash
    cVar7 = FUN_00420950(uVar9); // compare hash
    if (cVar7 != '\0') goto LAB_008b13c5;
    puVar12 = local_20;
    bVar3 = true;
    FUN_004d8c00("XATZ0273XX_C80F4FC_4C169AA_v3"); // hash function init
    uVar9 = FUN_004da7e0(puVar12); // compute hash
    cVar7 = FUN_00420950(uVar9); // compare hash
    bVar4 = false;
    if (cVar7 != '\0') goto LAB_008b13c5;
  }
  else {
LAB_008b13c5:
    bVar4 = true; // license valid
  }
  if ((bVar3) && (local_44 != 0)) {
    FUN_004d8be0(); // cleanup
    FUN_009c8eb0(local_44); // free memory
  }
  if (bVar4) {
    *(undefined4 *)(*(int *)(*piVar11 + -4 + *(int *)(thisPtr + 0x2c) * 4) + 0x20) = 0x16; // set license type to 0x16
    return;
  }
  bVar5 = false;
  bVar4 = false;
  bVar3 = false;
  FUN_004da550("XATZ0273XX_C7B44DB_8DC98F5_v3"); // hash function init
  uVar9 = FUN_004da7e0(local_30); // compute hash
  cVar7 = FUN_00420950(uVar9); // compare hash
  if (cVar7 == '\0') {
    puVar12 = local_40;
    bVar5 = true;
    bVar4 = false;
    bVar3 = false;
    FUN_004d8c00("XATZ0273XX_C80F4EA_14D4522_v3"); // hash function init
    uVar9 = FUN_004da7e0(puVar12); // compute hash
    cVar7 = FUN_00420950(uVar9); // compare hash
    if (cVar7 != '\0') goto LAB_008b1556;
    puVar12 = local_10;
    bVar5 = true;
    bVar4 = true;
    bVar3 = false;
    FUN_004d8c00("XATZ0273XX_C80F4DE_D735FCF_v3"); // hash function init
    uVar9 = FUN_004da7e0(puVar12); // compute hash
    cVar7 = FUN_00420950(uVar9); // compare hash
    if (cVar7 != '\0') goto LAB_008b1556;
    puVar12 = local_20;
    bVar5 = true;
    bVar4 = true;
    bVar3 = true;
    FUN_004d8c00("XKATZ6792X_C8E2F0C_06BC271_v3"); // hash function init
    uVar9 = FUN_004da7e0(puVar12); // compute hash
    cVar7 = FUN_00420950(uVar9); // compare hash
    bVar6 = false;
    if (cVar7 != '\0') goto LAB_008b1556;
  }
  else {
LAB_008b1556:
    bVar6 = true; // license valid
  }
  if (bVar3) {
    FUN_004d8be0(); // cleanup
  }
  if (bVar4) {
    FUN_004d8be0(); // cleanup
  }
  if (bVar5) {
    FUN_004d8be0(); // cleanup
  }
  FUN_004d8be0(); // cleanup
  if (bVar6) {
    *(undefined4 *)(*(int *)(*piVar11 + -4 + *(int *)(thisPtr + 0x2c) * 4) + 0x20) = 0x17; // set license type to 0x17
    return;
  }
  puVar12 = local_30;
  bVar5 = false;
  bVar4 = false;
  bVar3 = false;
  FUN_004d8c00("XATZ0273XX_C80F4EA_2CF83FC_v3"); // hash function init
  uVar9 = FUN_004da7e0(puVar12); // compute hash
  cVar7 = FUN_00420950(uVar9); // compare hash
  if (cVar7 == '\0') {
    puVar12 = local_40;
    bVar5 = true;
    bVar4 = false;
    bVar3 = false;
    FUN_004d8c00("XATZ0273XX_C80F50B_2F484F0_v3"); // hash function init
    uVar9 = FUN_004da7e0(puVar12); // compute hash
    cVar7 = FUN_00420950(uVar9); // compare hash
    if (cVar7 == '\0') {
      puVar12 = local_10;
      bVar5 = true;
      bVar4 = true;
      bVar3 = false;
      FUN_004d8c00("XATZ0273XX_C80F50B_50833F3_v3"); // hash function init
      uVar9 = FUN_004da7e0(puVar12); // compute hash
      cVar7 = FUN_00420950(uVar9); // compare hash
      if (cVar7 == '\0') {
        puVar12 = local_20;
        bVar5 = true;
        bVar4 = true;
        bVar3 = true;
        FUN_004d8c00("XKATZ6792X_C8E2F09_0079C07_v3"); // hash function init
        uVar9 = FUN_004da7e0(puVar12); // compute hash
        cVar7 = FUN_00420950(uVar9); // compare hash
        bVar6 = false;
        if (cVar7 == '\0') goto LAB_008b16aa;
      }
    }
  }
  bVar6 = true;
LAB_008b16aa:
  if (bVar3) {
    FUN_004d8be0(); // cleanup
  }
  if (bVar4) {
    FUN_004d8be0(); // cleanup
  }
  if (bVar5) {
    FUN_004d8be0(); // cleanup
  }
  FUN_004d8be0(); // cleanup
  if (bVar6) {
    *(undefined4 *)(*(int *)(*piVar11 + -4 + *(int *)(thisPtr + 0x2c) * 4) + 0x20) = 0x18; // set license type to 0x18
  }
  return;
}