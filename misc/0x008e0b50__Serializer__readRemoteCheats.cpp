// FUNC_NAME: Serializer::readRemoteCheats
void __thiscall SER_008e0b50(int this, undefined4 param_2)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  // Initialize remote cheat state
  FUN_0046c710(param_2);
  FUN_0043aff0(param_2,0xbd5437d3);
  cVar1 = FUN_0043b120();
  do {
    if (cVar1 != '\0') {
      return;
    }
    FUN_0043b210();
    uVar2 = FUN_0043ab70();
    switch(uVar2) {
    case 0:
      // Unknown field at +0x50 - read integer
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      iVar3 = this + 0x50;
      goto LAB_008e0f70;
    case 1:
      // Boolean field at +0x58 - read bool
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0x58,uVar2);
      break;
    case 2:
      // Unknown field at +0x68 - read integer
      iVar3 = this + 0x68;
      goto LAB_008e0be0;
    case 3:
      // Unknown field at +0x60 - read integer
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      iVar3 = this + 0x60;
      goto LAB_008e0f70;
    case 4:
      // Unknown field at +0x78 - read compound
      iVar3 = this + 0x78;
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 5:
      // Unknown field at +0x88 - read integer
      iVar3 = this + 0x88;
      goto LAB_008e0be0;
    case 6:
      // Unknown field at +0x98 - read compound
      iVar3 = this + 0x98;
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 7:
      // Unknown field at +0xa8 - read compound
      iVar3 = this + 0xa8;
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 8:
      // Unknown field at +0xb8 - read integer
      iVar3 = this + 0xb8;
      goto LAB_008e0be0;
    case 9:
      // Unknown field at +0xc8 - read compound
      iVar3 = this + 200;
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 10:
      // Unknown field at +0xd8 - read compound
      iVar3 = this + 0xd8;
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 0xb:
      // Unknown field at +0xe8 - read integer
      iVar3 = this + 0xe8;
      goto LAB_008e0be0;
    case 0xc:
      // Unknown field at +0xf8 - read compound
      iVar3 = this + 0xf8;
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 0xd:
      // Unknown field at +0x108 - read compound
      iVar3 = this + 0x108;
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 0xe:
      // Unknown field at +0x118 - read integer
      iVar3 = this + 0x118;
      goto LAB_008e0be0;
    case 0xf:
      // Unknown field at +0x128 - read compound
      iVar3 = this + 0x128;
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 0x10:
      // Unknown field at +0x138 - read compound
      iVar3 = this + 0x138;
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 0x11:
      // Unknown field at +0x148 - read integer
      iVar3 = this + 0x148;
LAB_008e0be0:
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 0x12:
      // Unknown field at +0x158 - read compound
      iVar3 = this + 0x158;
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 0x13:
      // Unknown field at +0x168 - read compound
      iVar3 = this + 0x168;
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 0x14:
      // Boolean field at +0x17c - read bool
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0x17c,uVar2);
      break;
    case 0x15:
      // Unknown field at +0x184 - read integer
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      iVar3 = this + 0x184;
      goto LAB_008e0f70;
    case 0x16:
      // Boolean field at +0x18c - read bool
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0x18c,uVar2);
      break;
    case 0x17:
      // Unknown field at +0x194 - read integer
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      iVar3 = this + 0x194;
      goto LAB_008e0f70;
    case 0x18:
      // Boolean field at +0x19c - read bool
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0x19c,uVar2);
      break;
    case 0x19:
      // Unknown field at +0x1a4 - read integer
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      iVar3 = this + 0x1a4;
      goto LAB_008e0f70;
    case 0x1a:
      // Boolean field at +0x1ac - read bool
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0x1ac,uVar2);
      break;
    case 0x1b:
      // Unknown field at +0x1b4 - read integer
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      iVar3 = this + 0x1b4;
      goto LAB_008e0f70;
    case 0x1c:
      // Boolean field at +0x1bc - read bool
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0x1bc,uVar2);
      break;
    case 0x1d:
      // Unknown field at +0x1c4 - read integer
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      iVar3 = this + 0x1c4;
      goto LAB_008e0f70;
    case 0x1e:
      // Boolean field at +0x1cc - read bool
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0x1cc,uVar2);
      break;
    case 0x1f:
      // Unknown field at +0x1d4 - read integer
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      iVar3 = this + 0x1d4;
      goto LAB_008e0f70;
    case 0x20:
      // Boolean field at +0x1dc - read bool
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0x1dc,uVar2);
      break;
    case 0x21:
      // Unknown field at +0x1e4 - read integer
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      iVar3 = this + 0x1e4;
      goto LAB_008e0f70;
    case 0x22:
      // Boolean field at +0x1ec - read bool
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0x1ec,uVar2);
      break;
    case 0x23:
      // Unknown field at +0x1f4 - read integer
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      iVar3 = this + 500;
LAB_008e0f70:
      FUN_004089b0(iVar3,uVar2);
    }
    FUN_0043b1a0();
    cVar1 = FUN_0043b120();
  } while( true );
}