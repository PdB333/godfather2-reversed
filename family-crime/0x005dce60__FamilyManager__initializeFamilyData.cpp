// FUNC_NAME: FamilyManager::initializeFamilyData
void FamilyManager::initializeFamilyData(void)
{
  // +0x00: this function is called after base class initialization (FUN_005dd030)
  // It initializes the array of 5 family data blocks (5 families in Godfather 2).
  // Magic numbers: 0xbadbadba, 0xbeefbeef, 0xeac15a55, 0x91100911 are debug fill.

  // Call base initialization (likely memset or base constructor)
  baseInitialize();

  // Global constants read at startup (likely debug default values)
  DWORD uVar2 = DAT_00e2b1a4; // +0x00?
  DWORD uVar1 = DAT_00e2b118; // +0x00?

  // Set field at offset +0x214 to -1 (invalid index)
  this->field_214 = 0xFFFFFFFF;

  // Pointer to beginning of family data array (starts at offset +0x18)
  DWORD* pFamilyData = (DWORD*)(this->dataStart);

  // Loop over 5 families
  int familyIndex = 5;
  do
  {
    // Write shared header fields that overlap across families
    pFamilyData[-6] = uVar2; // +0x00 (first family header)
    pFamilyData[-5] = uVar2; // +0x04
    pFamilyData[4] = uVar2;  // +0x10
    pFamilyData[5] = uVar2;  // +0x14

    // Set high water marks (96000 = 0x17700)
    pFamilyData[0xB] = 96000; // +0x2C
    pFamilyData[0xD] = 96000; // +0x34

    // Zero out some byte fields
    *(BYTE*)((int)pFamilyData + 9) = 0; // +0x09
    *(BYTE*)((int)pFamilyData + 10) = 0; // +0x0A

    // Zero more dwords
    pFamilyData[-4] = 0; // +0x08
    pFamilyData[3] = 0;  // +0x0C
    pFamilyData[6] = 0;  // +0x18
    pFamilyData[7] = 0;  // +0x1C
    pFamilyData[0xC] = 0; // +0x30
    *(BYTE*)((int)pFamilyData + 0xB) = 0; // +0x0B

    // Write debug sentinel values and pointers
    pFamilyData[-3] = 1;           // +0x0C (then overwritten later to -1)
    pFamilyData[-2] = 0xbadbadba; // +0x10
    pFamilyData[-1] = 0xbeefbeef; // +0x14
    *pFamilyData = 0xeac15a55;    // +0x18
    pFamilyData[1] = 0x91100911;  // +0x1C
    pFamilyData[8] = uVar1;       // +0x20
    pFamilyData[9] = uVar2;       // +0x24

    // Zero remaining fields
    pFamilyData[0xE] = 0;   // +0x38
    pFamilyData[0xF] = 0;   // +0x3C
    pFamilyData[0x10] = 0;  // +0x40
    pFamilyData[0x11] = 0;  // +0x44
    pFamilyData[0x12] = 0;  // +0x48
    pFamilyData[0x13] = 0;  // +0x4C

    // Override earlier value at +0x0C to -1 (index invalidator)
    pFamilyData[-3] = 0xFFFFFFFF;

    // Advance to next family block (0x68 bytes = 26 dwords)
    pFamilyData += 0x1A;
    familyIndex--;
  } while (familyIndex != 0);

  // Final assignments after all families processed
  this->field_27C = uVar1;   // +0x27C
  this->field_280 = uVar2;   // +0x280
  this->field_284 = uVar2;   // +0x284
  this->field_288 = uVar2;   // +0x288
  this->field_28C = uVar2;   // +0x28C
  this->field_290 = uVar2;   // +0x290
  this->field_29C = uVar2;   // +0x29C
  *(BYTE*)&this->field_298 = 0; // +0x298
  *(BYTE*)((int)&this->field_298 + 1) = 0; // +0x299
  this->field_2B8 = 0;       // +0x2B8
  this->field_2BC = 0xFFFFFFFF; // +0x2BC (offset 700 decimal)
}