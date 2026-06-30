// FUNC_NAME: aes_keysize
int aes_keysize(int *desiredKeysize)
{
  int keysize;
  char *format;
  
  if (desiredKeysize == (int *)0x0) {
    format = "_ARGCHK '%s' failure on line %d of file %s\n";
    keysize = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n","desired_keysize != NULL",
                         0x242,"..\\src\\libtomcrypt\\aes.c");
    _fprintf((FILE *)(keysize + 0x40),format);
  }
  keysize = *desiredKeysize;
  if (keysize < 0x10) {
    return 3; // CRYPT_INVALID_KEYSIZE
  }
  if (keysize < 0x18) {
    *desiredKeysize = 0x10; // 16 bytes = AES-128
    return 0; // CRYPT_OK
  }
  if (keysize < 0x20) {
    *desiredKeysize = 0x18; // 24 bytes = AES-192
    return 0; // CRYPT_OK
  }
  *desiredKeysize = 0x20; // 32 bytes = AES-256
  return 0; // CRYPT_OK
}