// FUNC_NAME: HandleConnection::initialize
undefined4 * __thiscall HandleConnection::initialize(HandleConnection *this, void *owner, void *handleTable)
{
  uint hash;
  code *funcPtr;
  undefined4 *connectionPtr;
  int eaxValue;
  int objIndex;
  int *components;
  int componentCount;
  int field_c;
  int local_buffer[3];
  
  connectionPtr = this;
  connectionPtr[0] = &PTR_FUN_00e39c38; // vtable
  connectionPtr[1] = eaxValue;          // owner's refcount? (from EAX)
  connectionPtr[2] = owner;
  connectionPtr[3] = handleTable;
  
  if (*(short *)(eaxValue + 4) != 0) {
    *(short *)(eaxValue + 6) = *(short *)(eaxValue + 6) + 1;
  }
  
  components = (int *)connectionPtr[2]; // owner
  if (((components != 0) && (handleTable != 0)) && (0 < *(int *)(handleTable + 4))) {
    if (0 < *(int *)(components + 0xc)) {
      for (objIndex = 0; objIndex < *(int *)(components + 0xc); objIndex++) {
        int object = *(int *)(*(int *)(components + 8) + objIndex * 4);
        *(undefined4 *)(object + 0xc) = 0;
        
        if (0 < *(int *)(object + 0x78)) {
          int *componentList = *(int **)(object + 0x74);
          for (componentCount = 0; componentCount < *(int *)(object + 0x78); componentCount++) {
            if (componentList[componentCount] == 0x2f8d528a) { // component GUID
              int *lookupResult = Fun_004af8c0(local_buffer, 0x2f8d528a);
              int resultValue = *lookupResult;
              
              if (resultValue < 1) {
                if ((resultValue == -1) && (field_c = Fun_0054a2b0(), field_c != 0)) {
                  funcPtr = *(code **)(*(int *)(field_c + 0x10) + 8);
                  *(undefined4 *)(field_c + 8) = 0;
                  
                  for (int iter = (*funcPtr)(); iter != -1;
                       iter = (**(code **)(*(int *)(field_c + 0x10) + 0xc))(iter)) {
                    int handleIndex = (**(code **)(*(int *)(field_c + 0x10) + 0x10))(iter);
                    if (0 < handleIndex) {
                      uint handleValue = *(uint *)(*(int *)connectionPtr[3] + -4 + handleIndex * 4);
                      Fun_00a68d30(iter, handleValue >> 2 | 0x80000000);
                    }
                  }
                }
              }
              else {
                uint uVar1 = *(uint *)(*(int *)connectionPtr[3] + -4 + resultValue * 4);
                *(uint *)(field_c + 0x2c) = uVar1 >> 2 | 0x80000000;
                *(uint *)(field_c + 0xc) = uVar1;
              }
              break;
            }
          }
        }
      }
    }
  }
  return connectionPtr;
}