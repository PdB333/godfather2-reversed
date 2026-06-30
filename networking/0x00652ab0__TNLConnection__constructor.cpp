// FUNC_NAME: TNLConnection::constructor
void TNLConnection::constructor(void *this)
{
  unsigned long uVar1;
  int iVar2;
  bool bVar3;
  
  _DAT_01205a30 = _DAT_01205a30 + 1; // Increment connection counter
  *(int *)this = &PTR_LAB_00e43088;  // vtable pointer
  *(int *)((int)this + 4) = 0;      // connection state
  *(int *)((int)this + 8) = 0;      // connection flags
  *(int *)((int)this + 0xb8) = 0;   // +0xB8
  *(short *)((int)this + 0x100) = 0; // +0x100
  *(short *)((int)this + 0x102) = 0; // +0x102
  *(int *)((int)this + 0x110) = 0;   // +0x110
  *(int *)((int)this + 0x10c) = 0;   // +0x10C
  *(int *)((int)this + 0x108) = 0;   // +0x108
  uVar1 = htonl(0);                  // +0x104 - network order null
  *(int *)((int)this + 0x104) = uVar1;
  *(int *)((int)this + 0x124) = 0;   // +0x124
  *(int *)((int)this + 0x150) = 0;   // +0x150
  *(int *)((int)this + 0x154) = 0;   // +0x154
  *(int *)((int)this + 0x158) = 0;   // +0x158
  *(int *)((int)this + 0x15c) = 0;   // +0x15c
  *(int *)((int)this + 0x18c) = 0;   // +0x18C
  *(int *)((int)this + 0x184) = 0;   // +0x184
  *(int *)((int)this + 0x188) = 0;   // +0x188
  *(int *)((int)this + 0x194) = 0;   // +0x194
  *(char *)((int)this + 0x190) = 0;  // +0x190
  *(char *)((int)this + 0x132) = 0;  // +0x132
  *(char *)((int)this + 0x131) = 0;  // +0x131
  *(char *)((int)this + 0x130) = 0;  // +0x130
  *(char *)((int)this + 0x198) = 0;  // +0x198
  *(char *)((int)this + 0x191) = 0;  // +0x191
  *(int *)((int)this + 0x1a4) = 0;   // +0x1A4
  *(int *)((int)this + 0x1b0) = 0;   // +0x1B0
  iVar2 = FUN_0065bf40();            // Get some timer/sequence value
  bVar3 = DAT_0120588f == '\0';      // Check if initialized
  *(int *)((int)this + 0xa4) = iVar2; // +0xA4
  if (bVar3) {
    DAT_0120588f = '\x01';
    FUN_00662100(&DAT_01203740);     // Initialize global mutex
    FUN_006622a0(&DAT_01203740);     // Additional init
  }
  FUN_00662350((int)this + 0x133, 8, &DAT_01203740); // Initialize buffer/lock
  *(int *)((int)this + 0xe0) = 0x9c4;  // +0xE0 - max packet size
  *(int *)((int)this + 0xdc) = 0x9c4;  // +0xDC - current packet size
  *(int *)((int)this + 0xcc) = 0;      // +0xCC
  *(int *)((int)this + 0xc0) = 0;      // +0xC0
  *(int *)((int)this + 0xd8) = 0x60;   // +0xD8 - send rate
  *(int *)((int)this + 0xd4) = 0x60;   // +0xD4 - receive rate
  *(long long *)((int)this + 0xe4) = *(long long *)((int)this + 0xd4); // Copy rate
  *(int *)((int)this + 0xc8) = 0;      // +0xC8
  *(int *)((int)this + 0xd0) = 0;      // +0xD0
  *(int *)((int)this + 12) = 0;        // +0x0C
  *(int *)((int)this + 0xbc) = 0;      // +0xBC
  *(int *)((int)this + 0xc4) = 0;      // +0xC4
  *(int *)((int)this + 0x1b4) = 0;     // +0x1B4
  *(int *)((int)this + 0x11c) = 0;     // +0x11C
  *(int *)((int)this + 0x120) = 0;     // +0x120
  *(long long *)((int)this + 0xec) = *(long long *)((int)this + 0xdc); // Copy size
  *(char *)((int)this + 0xf4) = 1;     // +0xF4 - active flag
  FUN_006538d0();                      // Init something else
  *(int *)((int)this + 0x1b8) = DAT_00e2b04c; // +0x1B8
  int localVar1 = DAT_00e2afb8;
  *(int *)((int)this + 0x114) = 0;     // +0x114
  *(int *)((int)this + 0x118) = 0;     // +0x118
  *(int *)((int)this + 0x90) = 0;      // +0x90
  *(int *)((int)this + 0x94) = *(int *)((int)this + 0xa4); // +0x94
  *(int *)((int)this + 0x98) = *(int *)((int)this + 0xa4); // +0x98
  *(int *)((int)this + 0x9c) = 0;      // +0x9C
  *(int *)((int)this + 0xa0) = 0;      // +0xA0
  *(int *)((int)this + 0x1c0) = 0;     // +0x1C0
  *(int *)((int)this + 0x1c8) = 0;     // +0x1C8
  *(int *)((int)this + 0x1bc) = localVar1; // +0x1BC
  *(int *)((int)this + 0xb0) = 5000;    // +0xB0 - timeout value (ms)
  *(int *)((int)this + 0xb4) = 10;      // +0xB4 - retry count
  return;
}