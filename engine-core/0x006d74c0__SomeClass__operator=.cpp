// FUNC_NAME: SomeClass::operator=
void __thiscall SomeClass::operator=(SomeClass *this, SomeClass *other)
{
  int *pNode;
  int *pNode2;
  
  // Copy entire structure (first 40 bytes: five qwords)
  *(long long *)this = *(long long *)other;       // +0x00
  *(long long *)(this + 1) = *(long long *)(other + 1); // +0x08
  *(long long *)(this + 2) = *(long long *)(other + 2); // +0x10
  *(long long *)(this + 3) = *(long long *)(other + 3); // +0x18
  *(long long *)(this + 4) = *(long long *)(other + 4); // +0x20
  
  // First linked list node at offset +0x28 (pNode points to some node)
  pNode = *(int **)(other + 5);                         // +0x28
  *(int **)(this + 5) = pNode;                          // +0x28
  *(int *)((char *)this + 0x2c) = 0;                    // +0x2c (prev)
  if (pNode != (int *)0x0) {
    *(int *)((char *)this + 0x2c) = *(int *)((char *)pNode + 4); // +0x2c = pNode[1] (old prev)
    *(int ***)((char *)pNode + 4) = (int **)(this + 5);           // pNode->next = &this->+0x28
  }
  
  // Second linked list node at offset +0x30 (pNode2 points to another node)
  pNode2 = *(int **)(other + 6);                         // +0x30
  *(int **)(this + 6) = pNode2;                          // +0x30
  *(int *)((char *)this + 0x34) = 0;                    // +0x34 (prev)
  if (pNode2 != (int *)0x0) {
    *(int *)((char *)this + 0x34) = *(int *)((char *)pNode2 + 4); // +0x34 = pNode2[1] (old prev)
    *(int ***)((char *)pNode2 + 4) = (int **)(this + 6);           // pNode2->next = &this->+0x30
  }
  
  // Copy remaining fields
  *(int *)(this + 7) = *(int *)(other + 7);               // +0x38
  *(int *)((char *)this + 0x3c) = *(int *)((char *)other + 0x3c); // +0x3c
  *(int *)(this + 8) = *(int *)(other + 8);               // +0x40
  *(int *)((char *)this + 0x44) = *(int *)((char *)other + 0x44); // +0x44
  *(int *)(this + 9) = *(int *)(other + 9);               // +0x48
  *(int *)((char *)this + 0x4c) = *(int *)((char *)other + 0x4c); // +0x4c
  *(int *)(this + 10) = *(int *)(other + 10);             // +0x50
  *(int *)((char *)this + 0x54) = *(int *)((char *)other + 0x54); // +0x54
  *(int *)(this + 11) = *(int *)(other + 11);             // +0x58
  *(int *)((char *)this + 0x5c) = *(int *)((char *)other + 0x5c); // +0x5c
  *(int *)(this + 12) = *(int *)(other + 12);             // +0x60
  *(int *)((char *)this + 0x64) = *(int *)((char *)other + 0x64); // +0x64
  *(int *)(this + 13) = *(int *)(other + 13);             // +0x68
  *(int *)((char *)this + 0x6c) = *(int *)((char *)other + 0x6c); // +0x6c
  *(int *)(this + 14) = *(int *)(other + 14);             // +0x70
  *(int *)((char *)this + 0x74) = *(int *)((char *)other + 0x74); // +0x74
  *(int *)(this + 15) = *(int *)(other + 15);             // +0x78
  *(long long *)((char *)this + 0x7c) = *(long long *)((char *)other + 0x7c); // +0x7c (8 bytes)
  *(int *)((char *)this + 0x84) = *(int *)((char *)other + 0x84); // +0x84
  *(int *)(this + 17) = *(int *)(other + 17);             // +0x88
}