// FUNC_NAME: GodfatherGameManager::readFromBitStream
void __thiscall GodfatherGameManager::readFromBitStream(int this, uint bitStream)
{
  float fVar1;
  uint uVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  bool bVar6;
  undefined4 *puVar7;
  
  uVar2 = bitStream;
  FUN_0043b540(bitStream); // bitStream->readClassId
  FUN_0043aff0(uVar2,0x3c0d84c8); // bitStream->read(0x3c0d84c8) - some class identifier
  cVar3 = FUN_0043b120(); // bitStream->isEndOfStream?
  do {
    if (cVar3 != '\0') {
      return;
    }
    FUN_0043b210(); // bitStream->readInt
    uVar4 = FUN_0043ab70(); // bitStream->readTag
    switch(uVar4) {
    case 0: // tag 0: read uint16
      iVar5 = FUN_0043b210(); // bitStream->readInt
      *(undefined2 *)(this + 0x54) = *(undefined2 *)(iVar5 + 8); // this->field_0x54 = read value
      break;
    case 1: // tag 1: read uint32
      iVar5 = FUN_0043b210(); // bitStream->readInt
      *(undefined4 *)(this + 0x50) = *(undefined4 *)(iVar5 + 8); // this->field_0x50 = read value
      break;
    case 2: // tag 2: read color (RGBA)
      puVar7 = &bitStream;
      FUN_0043b210(puVar7); // bitStream->readInt
      FUN_0043ad80(puVar7); // bitStream->readColor?
      fVar1 = DAT_00e44640; // 1.0f/255.0f
      *(float *)(this + 0x58) = (float)(bitStream & 0xff) * DAT_00e44640; // this->colorR = (R/255)
      *(float *)(this + 0x5c) = (float)(bitStream >> 8 & 0xff) * fVar1; // this->colorG
      *(float *)(this + 0x60) = (float)(bitStream >> 0x10 & 0xff) * fVar1; // this->colorB
      *(float *)(this + 100) = (float)(bitStream >> 0x18) * fVar1; // this->colorA
      break;
    case 3: // tag 3: read uint32
      iVar5 = FUN_0043b210();
      *(undefined4 *)(this + 0x68) = *(undefined4 *)(iVar5 + 8); // this->field_0x68
      break;
    case 4: // tag 4: read uint32
      iVar5 = FUN_0043b210();
      *(undefined4 *)(this + 0x6c) = *(undefined4 *)(iVar5 + 8); // this->field_0x6c
      break;
    case 5: // tag 5: read uint32
      iVar5 = FUN_0043b210();
      *(undefined4 *)(this + 0x70) = *(undefined4 *)(iVar5 + 8); // this->field_0x70
      break;
    case 7: // tag 7: read uint32
      iVar5 = FUN_0043b210();
      *(undefined4 *)(this + 0x74) = *(undefined4 *)(iVar5 + 8); // this->field_0x74
      break;
    case 8: // tag 8: read uint32
      iVar5 = FUN_0043b210();
      *(undefined4 *)(this + 0x78) = *(undefined4 *)(iVar5 + 8); // this->field_0x78
      break;
    case 9: // tag 9: read uint32
      iVar5 = FUN_0043b210();
      *(undefined4 *)(this + 0x7c) = *(undefined4 *)(iVar5 + 8); // this->field_0x7c
      break;
    case 10: // tag 10: read uint32
      iVar5 = FUN_0043b210();
      *(undefined4 *)(this + 0x80) = *(undefined4 *)(iVar5 + 8); // this->field_0x80
      break;
    case 0xb: // tag 11: read uint32
      iVar5 = FUN_0043b210();
      *(undefined4 *)(this + 0x84) = *(undefined4 *)(iVar5 + 8); // this->field_0x84
      break;
    case 0xc: // tag 12: read uint32
      iVar5 = FUN_0043b210();
      *(undefined4 *)(this + 0x88) = *(undefined4 *)(iVar5 + 8); // this->field_0x88
      break;
    case 0xd: // tag 13: read bool
      iVar5 = FUN_0043b210();
      bVar6 = *(int *)(iVar5 + 8) != 0;
      *(bool *)(this + 0x9c) = bVar6; // this->field_0x9c = bool
      if ((bVar6) && (DAT_0120e93c != 0)) {
        FUN_00408900(this + 0x3c,&DAT_0120e93c,0x8000); // some string copy or assignment
      }
      break;
    case 0xe: // tag 14: read string
      FUN_0043b210();
      uVar4 = FUN_0043ab90(); // bitStream->readString
      iVar5 = this + 0x8c; // this->field_0x8c (string)
      goto LAB_0094d65c;
    case 0xf: // tag 15: read string
      FUN_0043b210();
      uVar4 = FUN_0043ab90(); // bitStream->readString
      iVar5 = this + 0x94; // this->field_0x94 (string)
LAB_0094d65c:
      FUN_004089b0(iVar5,uVar4); // string copy
    }
    FUN_0043b1a0(); // bitStream->endReadTag?
    cVar3 = FUN_0043b120(); // bitStream->isEndOfStream?
  } while( true );
}