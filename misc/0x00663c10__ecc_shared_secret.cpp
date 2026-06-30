// Xbox PDB: ecc_shared_secret
// FUNC_NAME: ecc_sign_hash
int ecc_sign_hash(int *private_key, int *public_key, int *out, uint *outlen)
{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  undefined1 local_14 [20];

  // Validate NULL pointers
  if (private_key == (int *)0x0) {
    pcVar4 = "_ARGCHK '%s' failure on line %d of file %s\n";
    iVar1 = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n","private_key != NULL",
                         0x391,"..\\src\\libtomcrypt\\ecc.c");
    _fprintf((FILE *)(iVar1 + 0x40),pcVar4);
  }
  if (public_key == 0) {
    pcVar4 = "_ARGCHK '%s' failure on line %d of file %s\n";
    iVar1 = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n","public_key != NULL",0x392
                         ,"..\\src\\libtomcrypt\\ecc.c");
    _fprintf((FILE *)(iVar1 + 0x40),pcVar4);
  }
  if (out == 0) {
    pcVar4 = "_ARGCHK '%s' failure on line %d of file %s\n";
    iVar1 = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n","out != NULL",0x393,
                         "..\\src\\libtomcrypt\\ecc.c");
    _fprintf((FILE *)(iVar1 + 0x40),pcVar4);
  }
  if (outlen == (uint *)0x0) {
    pcVar4 = "_ARGCHK '%s' failure on line %d of file %s\n";
    iVar1 = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n","outlen != NULL",0x394,
                         "..\\src\\libtomcrypt\\ecc.c");
    _fprintf((FILE *)(iVar1 + 0x40),pcVar4);
  }

  // Check private key type
  if (*private_key != 0) {
    return 0xf;
  }
  // Check curve match between keys
  if (private_key[1] != *(int *)(public_key + 4)) {
    return 0xe;
  }

  // Start cryptographic operations
  iVar1 = FUN_00662440();  // Initialize PRNG state
  if (iVar1 == 0) {
    return 0xd;
  }
  
  iVar2 = FUN_006677b0();  // Initialize hash state
  if (iVar2 != 0) {
    FUN_00662480();  // Cleanup PRNG
    return 0xd;
  }

  // Load base point G for the curve
  iVar2 = FUN_00669f00((&PTR_s_G00000000000000000000000007_00e279c8)[private_key[1] * 7], 0x40);
  if (iVar2 == 0) {
    // ECDSA signing: compute k*G, then hash and compute signature
    iVar2 = FUN_00662a30(private_key + 10, public_key + 8, iVar1, local_14);
    if (iVar2 != 0) goto LAB_00663db3;
    
    iVar2 = FUN_0066b910();  // Get signature size (r)
    iVar3 = FUN_0066b910();  // Get signature size (s) 
    if (*outlen < (uint)(iVar3 + iVar2)) {
      iVar2 = 6;  // Buffer too small
      goto LAB_00663db3;
    }
    *outlen = iVar3 + iVar2;  // Set output length
    
    iVar2 = FUN_0066a970(iVar1);   // Serialize r
    if ((iVar2 == 0) && (iVar1 = FUN_0066a970(iVar1 + 0x10), iVar1 == 0)) {  // Serialize s
      iVar2 = 0;  // Success
      goto LAB_00663db3;
    }
  }
  iVar2 = 0xd;  // Error

LAB_00663db3:
  FUN_00665b40();  // Cleanup hash
  FUN_00662480();  // Cleanup PRNG
  return iVar2;
}