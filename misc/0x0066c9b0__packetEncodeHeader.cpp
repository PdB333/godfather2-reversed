// FUNC_NAME: packetEncodeHeader
void packetEncodeHeader(byte param_1)

{
  int iVar1;
  byte *unaff_ESI;
  char *_Format;
  
  if (unaff_ESI == (byte *)0x0) {
    _Format = "_ARGCHK '%s' failure on line %d of file %s\n";
    iVar1 = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n","dst != NULL",7,
                         "..\\src\\libtomcrypt\\packet.c");
    _fprintf((FILE *)(iVar1 + 0x40),_Format);
  }
  *unaff_ESI = 0x92;           // Packet header magic byte
  unaff_ESI[1] = 0;            // Packet type (0 = data)
  unaff_ESI[2] = 2;            // Packet version/flag
  unaff_ESI[3] = param_1;      // Sequence number or sub-type
  return;
}