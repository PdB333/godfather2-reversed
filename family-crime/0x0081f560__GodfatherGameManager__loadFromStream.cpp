// FUNC_NAME: GodfatherGameManager::loadFromStream
void __thiscall GodfatherGameManager::loadFromStream(int this, undefined4 stream)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  uint *puVar7;
  uint local_7c [30];
  
  FUN_00833510(stream);  // stream::beginRead
  FUN_0043aff0(stream,0x679dc961);  // stream::readMagic
  cVar1 = FUN_0043b120();  // stream::hasMoreData
  while (cVar1 == '\0') {
    FUN_0043b210();  // stream::readChunkHeader
    uVar2 = FUN_0043ab70();  // stream::getChunkType
    switch(uVar2) {
    case 0:  // kChunkAmbientColor
      puVar7 = local_7c;
      FUN_0043b210(puVar7);  // stream::readData
      FUN_0043ad80(puVar7);  // stream::endianSwap
      *(float *)(this + 0x50) = (float)(local_7c[0] & 0xff);  // ambientColor.r
      *(float *)(this + 0x54) = (float)(local_7c[0] >> 8 & 0xff);  // ambientColor.g
      *(float *)(this + 0x58) = (float)(local_7c[0] >> 0x10 & 0xff);  // ambientColor.b
      *(float *)(this + 0x5c) = (float)(local_7c[0] >> 0x18);  // ambientColor.a
      fVar4 = DAT_00e44640 * *(float *)(this + 0x54);  // normalize factor
      fVar5 = DAT_00e44640 * *(float *)(this + 0x58);
      fVar6 = DAT_00e44640 * *(float *)(this + 0x5c);
      *(float *)(this + 0x50) = DAT_00e44640 * *(float *)(this + 0x50);
      *(float *)(this + 0x54) = fVar4;
      *(float *)(this + 0x58) = fVar5;
      *(float *)(this + 0x5c) = fVar6;
      break;
    case 1:  // kChunkDiffuseColor
      puVar7 = local_7c;
      FUN_0043b210(puVar7);
      FUN_0043ad80(puVar7);
      *(float *)(this + 0x60) = (float)(local_7c[0] & 0xff);  // diffuseColor.r
      *(float *)(this + 100) = (float)(local_7c[0] >> 8 & 0xff);  // diffuseColor.g
      *(float *)(this + 0x68) = (float)(local_7c[0] >> 0x10 & 0xff);  // diffuseColor.b
      *(float *)(this + 0x6c) = (float)(local_7c[0] >> 0x18);  // diffuseColor.a
      fVar4 = DAT_00e44640 * *(float *)(this + 100);
      fVar5 = DAT_00e44640 * *(float *)(this + 0x68);
      fVar6 = DAT_00e44640 * *(float *)(this + 0x6c);
      *(float *)(this + 0x60) = DAT_00e44640 * *(float *)(this + 0x60);
      *(float *)(this + 100) = fVar4;
      *(float *)(this + 0x68) = fVar5;
      *(float *)(this + 0x6c) = fVar6;
      break;
    case 2:  // kChunkSomeString1
      iVar3 = FUN_0043b210();  // stream::readString
      *(undefined4 *)(this + 0x90) = *(undefined4 *)(iVar3 + 8);  // someString1
      break;
    case 3:  // kChunkSpecularColor
      puVar7 = local_7c;
      FUN_0043b210(puVar7);
      FUN_0043ad80(puVar7);
      *(float *)(this + 0x70) = (float)(local_7c[0] & 0xff);  // specularColor.r
      *(float *)(this + 0x74) = (float)(local_7c[0] >> 8 & 0xff);  // specularColor.g
      *(float *)(this + 0x78) = (float)(local_7c[0] >> 0x10 & 0xff);  // specularColor.b
      *(float *)(this + 0x7c) = (float)(local_7c[0] >> 0x18);  // specularColor.a
      fVar4 = DAT_00e44640 * *(float *)(this + 0x74);
      fVar5 = DAT_00e44640 * *(float *)(this + 0x78);
      fVar6 = DAT_00e44640 * *(float *)(this + 0x7c);
      *(float *)(this + 0x70) = DAT_00e44640 * *(float *)(this + 0x70);
      *(float *)(this + 0x74) = fVar4;
      *(float *)(this + 0x78) = fVar5;
      *(float *)(this + 0x7c) = fVar6;
      break;
    case 4:  // kChunkEmissiveColor
      puVar7 = local_7c;
      FUN_0043b210(puVar7);
      FUN_0043ad80(puVar7);
      *(float *)(this + 0x80) = (float)(local_7c[0] & 0xff);  // emissiveColor.r
      *(float *)(this + 0x84) = (float)(local_7c[0] >> 8 & 0xff);  // emissiveColor.g
      *(float *)(this + 0x88) = (float)(local_7c[0] >> 0x10 & 0xff);  // emissiveColor.b
      *(float *)(this + 0x8c) = (float)(local_7c[0] >> 0x18);  // emissiveColor.a
      fVar4 = DAT_00e44640 * *(float *)(this + 0x84);
      fVar5 = DAT_00e44640 * *(float *)(this + 0x88);
      fVar6 = DAT_00e44640 * *(float *)(this + 0x8c);
      *(float *)(this + 0x80) = DAT_00e44640 * *(float *)(this + 0x80);
      *(float *)(this + 0x84) = fVar4;
      *(float *)(this + 0x88) = fVar5;
      *(float *)(this + 0x8c) = fVar6;
      break;
    case 5:  // kChunkSomeString2
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x94) = *(undefined4 *)(iVar3 + 8);  // someString2
      break;
    case 6:  // kChunkSomeString3
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x98) = *(undefined4 *)(iVar3 + 8);  // someString3
      break;
    case 7:  // kChunkSomeString4
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x9c) = *(undefined4 *)(iVar3 + 8);  // someString4
      break;
    case 8:  // kChunkSomeString5
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0xa0) = *(undefined4 *)(iVar3 + 8);  // someString5
      break;
    case 9:  // kChunkSomeString6
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0xa4) = *(undefined4 *)(iVar3 + 8);  // someString6
    }
    FUN_0043b1a0();  // stream::endChunk
    cVar1 = FUN_0043b120();  // stream::hasMoreData
  }
  return;
}