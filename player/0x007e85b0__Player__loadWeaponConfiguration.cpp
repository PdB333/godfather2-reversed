// FUNC_NAME: Player::loadWeaponConfiguration
void __fastcall getBaseWeaponData(Player *this)
{
  int *pStaticId;
  int *pStruct;
  int scaledFloat;

  pStaticId = (int *)&kWeaponStaticIds; // 0x00d6fc18, array of 69 IDs
  pStruct = (int *)((char *)this + 0x1c); // points to second int of first struct
  do {
    void *pData = getWeaponData(*pStaticId); // FUN_006f5dd0 lookup
    if (pData != nullptr) {
      // pData+0xc is float (e.g. base damage), pData+0x10 int (e.g. clip size), pData+0x14 int (e.g. max ammo)
      scaledFloat = (int)(float)(*(float *)((char *)pData + 0xc) * kDamageMultiplier); // DAT_00d60d04
      pStruct[1] = scaledFloat;        // +4: scaled damage
      pStruct[-1] = *(int *)((char *)pData + 0x10); // -4: clip size
      *pStruct = *(int *)((char *)pData + 0x14);   //  0: max ammo
    }
    pStaticId++;
    pStruct += 3; // advance 12 bytes to next struct's middle int
  } while ((int)pStaticId < (int)&kWeaponStaticIds[69]); // 0xd6fd2c
}