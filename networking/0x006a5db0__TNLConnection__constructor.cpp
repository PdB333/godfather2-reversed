// FUNC_NAME: TNLConnection::constructor
undefined4 * __fastcall TNLConnection::constructor(undefined4 *this)
{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  
  uVar1 = DAT_00d5d7b8; // vtable or global
  this[1] = 1; // +0x04: connection state (e.g., CONNECTED)
  this[2] = 0; // +0x08: some flag
  this[3] = &PTR_LAB_00d5d7a0; // +0x0C: vtable pointer
  DAT_011299b0 = this; // global singleton pointer
  *this = &PTR_FUN_00d5d7a8; // +0x00: vtable
  this[3] = &PTR_LAB_00d5d7a4; // +0x0C: another vtable
  this[4] = uVar1; // +0x10: some value from global
  
  // Initialize 32 packet slots (0x1F = 31, loop 32 times)
  puVar2 = this + 8; // +0x20: start of packet slot array
  iVar4 = 0x1f;
  do {
    *puVar2 = 0xfe16702f; // +0x00: packet sequence number (invalid marker)
    puVar2[1] = 0; // +0x04: packet data pointer
    puVar2[2] = 0; // +0x08: packet size
    puVar2 = puVar2 + 10; // each slot is 0x28 bytes (10 * 4)
    iVar4 = iVar4 + -1;
  } while (-1 < iVar4);
  
  // More initialization of specific fields
  this[0x149] = 0; // +0x524: some counter
  this[0x14a] = 0; // +0x528: some counter
  this[0x14d] = 0xfe16702f; // +0x534: last received sequence
  this[0x14e] = 0xfe16702f; // +0x538: last sent sequence
  this[0x14f] = 0; // +0x53C: some flag
  this[0x150] = 0; // +0x540: some flag
  this[0x158] = 0xfe16702f; // +0x560: another sequence
  this[0x159] = 0; // +0x564: data
  this[0x15a] = 0; // +0x568: data
  this[0x162] = 0xfe16702f; // +0x588: sequence
  this[0x163] = 0; // +0x58C: data
  this[0x164] = 0; // +0x590: data
  this[0x16c] = 0xfe16702f; // +0x5B0: sequence
  this[0x16d] = 0; // +0x5B4: data
  this[0x16e] = 0; // +0x5B8: data
  this[0x176] = 0xfe16702f; // +0x5D8: sequence
  this[0x177] = 0; // +0x5DC: data
  this[0x178] = 0; // +0x5E0: data
  this[0x180] = 0xfe16702f; // +0x600: sequence
  this[0x181] = 0; // +0x604: data
  this[0x182] = 0; // +0x608: data
  this[0x18a] = 0xfe16702f; // +0x628: sequence
  this[0x18b] = 0; // +0x62C: data
  this[0x18c] = 0; // +0x630: data
  this[0x194] = 0xfe16702f; // +0x650: sequence
  this[0x195] = 0; // +0x654: data
  this[0x196] = 0; // +0x658: data
  
  // Magic numbers for validation
  this[0x19e] = 0xffffffff; // +0x678: magic
  this[0x19f] = 0xbadbadba; // +0x67C: magic
  this[0x1a0] = 0xbeefbeef; // +0x680: magic
  this[0x1a1] = 0xeac15a55; // +0x684: magic
  this[0x1a2] = 0x91100911; // +0x688: magic
  this[0x1a3] = 0; // +0x68C: some field
  this[0x1a4] = 0; // +0x690: some field
  this[0x1a5] = 0; // +0x694: some field
  this[0x1a6] = 0; // +0x698: some field
  this[0x1a7] = 6; // +0x69C: some count
  this[0x1a8] = 0; // +0x6A0: some field
  this[0x1a9] = 0xfe16702f; // +0x6A4: sequence
  this[0x1ae] = 0; // +0x6B8: some field
  
  // Initialize 32 more slots (0x1F = 31, loop 32 times)
  puVar2 = this + 0x1af; // +0x6BC: start of another array
  iVar4 = 0x1f;
  do {
    *puVar2 = 0xfe16702f; // sequence marker
    puVar2 = puVar2 + 6; // each slot is 0x18 bytes (6 * 4)
    iVar4 = iVar4 + -1;
  } while (-1 < iVar4);
  
  this[5] = 0; // +0x14: some field
  this[6] = 0; // +0x18: some field
  this[7] = 0; // +0x1C: some field
  
  // Clear 8 more slots (loop 8 times)
  piVar5 = this + 0x14f; // +0x53C
  iVar4 = 8;
  do {
    iVar3 = iVar4;
    piVar5[-1] = 0; // clear previous slot
    if (*piVar5 != 0) {
      FUN_004daf90(piVar5); // free memory
      *piVar5 = 0;
    }
    piVar5[7] = 0; // +0x1C offset
    piVar5[8] = 0; // +0x20 offset
    piVar5 = piVar5 + 10; // each slot 0x28 bytes
    iVar4 = iVar3 + -1;
  } while (iVar4 != 0);
  
  FUN_006a5740(); // some initialization function
  
  // Initialize more slots (0x1F = 31, loop 32 times)
  iVar3 = iVar3 + 0x1f;
  puVar2 = this + 0x1b0; // +0x6C0
  do {
    puVar2[-1] = 0; // clear previous
    *(undefined1 *)(puVar2 + 4) = 0; // byte at +0x10
    *puVar2 = 0; // clear current
    puVar2[1] = 0;
    puVar2[2] = 0;
    puVar2[3] = 0;
    puVar2 = puVar2 + 6; // each slot 0x18 bytes
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  
  this[0x1aa] = 0; // +0x6A8
  this[0x1ab] = 0; // +0x6AC
  this[0x1ac] = 0; // +0x6B0
  uVar1 = _DAT_00d5780c; // global
  this[0x1a9] = 0; // +0x6A4
  *(undefined1 *)(this + 0x26f) = 1; // +0x9BC: byte flag
  this[0x1ad] = uVar1; // +0x6B4
  this[0x1a2] = 0; // +0x688
  this[0x1a1] = 0; // +0x684
  this[0x1a0] = 0; // +0x680
  this[0x19f] = 0; // +0x67C
  
  return this;
}