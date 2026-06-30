// FUNC_NAME: ECCKey::eccDecrypt
void ECCKey::eccDecrypt(void)
{
  int key;
  int iVar1;
  char *_Format;
  
  if (key == 0) {
    _Format = "_ARGCHK '%s' failure on line %d of file %s\n";
    iVar1 = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n","key != NULL",0x291,
                         "..\\src\\libtomcrypt\\ecc.c");
    _fprintf((FILE *)(iVar1 + 0x40),_Format);
  }
  // +0x08: public key, +0x18: private key, +0x28: curve parameters
  FUN_00665b80(key + 8,key + 0x18,key + 0x28,0);
  return;
}