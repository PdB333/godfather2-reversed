// Xbox PDB: void __cdecl luaV_settable(struct lua_State *,struct lua_TObject const *,struct lua_TObject *,struct lua_TObject *)
// FUNC_NAME: LuaScriptEngine::executeNode
void LuaScriptEngine::executeNode(int *node, undefined4 param_2, int *result)
{
  int type;
  int *childNode;
  int *currentNode;
  int *nextNode;
  int *foundNode;
  int *dataNode;
  
  currentNode = node;
  node = (int *)0x0;
  
LAB_00633d72:
  type = *currentNode;
  if (type != 5) {
    // Get the script context's hash table from the engine (+0x10 -> +0x58)
    int *hashTable = *(int **)(*(int *)(in_EAX + 0x10) + 0x58);
    
    if (type == 5) {
      // Hash lookup for node type 5
      int *hashBucket = (int *)(*(int *)(*(int *)(currentNode[1] + 8) + 0x10) +
                      ((1 << (*(byte *)(*(int *)(currentNode[1] + 8) + 7) & 0x1f)) - 1U &
                      *(uint *)(hashTable + 8)) * 0x14);
      do {
        if ((*hashBucket == 4) && (hashBucket[1] == (int)hashTable)) goto LAB_00633ed3;
        hashBucket = (int *)hashBucket[4];
      } while (hashBucket != (int *)0x0);
LAB_00633e55:
      hashBucket = &DAT_00e2a93c;
      goto LAB_00633e5a;
    }
    
    if (type == 7) {
      // Hash lookup for node type 7
      int *hashBucket2 = (int *)(*(int *)(*(int *)(currentNode[1] + 8) + 0x10) +
                      ((1 << (*(byte *)(*(int *)(currentNode[1] + 8) + 7) & 0x1f)) - 1U &
                      *(uint *)(hashTable + 8)) * 0x14);
      do {
        if ((*hashBucket2 == 4) && (hashBucket2[1] == (int)hashTable)) goto LAB_00633ed3;
        hashBucket2 = (int *)hashBucket2[4];
      } while (hashBucket2 != (int *)0x0);
      goto LAB_00633e55;
    }
    
    hashBucket = &DAT_00e2a93c;
    goto LAB_00633e60;
  }
  
  // Node type 5 handling
  int nodeData = currentNode[1];
  int *engineData = (int *)FUN_00638020();  // Get engine data
  if (*engineData != 0) {
LAB_00633df1:
    *engineData = *result;
    engineData[1] = result[1];
    return;
  }
  
  int nodeInfo = *(int *)(nodeData + 8);
  if ((*(byte *)(nodeInfo + 6) & 2) == 0) {
    int *hashTable2 = *(int **)(*(int *)(in_EAX + 0x10) + 0x58);
    int *hashBucket3 = (int *)(*(int *)(nodeInfo + 0x10) +
                    ((1 << (*(byte *)(nodeInfo + 7) & 0x1f)) - 1U & *(uint *)(hashTable2 + 8)) * 0x14);
    do {
      if ((*hashBucket3 == 4) && (hashBucket3[1] == (int)hashTable2)) {
        dataNode = hashBucket3 + 2;
        if (hashBucket3[2] == 0) {
          *(byte *)(nodeInfo + 6) = *(byte *)(nodeInfo + 6) | 2;
          dataNode = (int *)0x0;
        }
        goto LAB_00633ded;
      }
      hashBucket3 = (int *)hashBucket3[4];
    } while (hashBucket3 != (int *)0x0);
    *(byte *)(nodeInfo + 6) = *(byte *)(nodeInfo + 6) | 2;
    dataNode = (int *)0x0;
  }
  else {
    dataNode = (int *)0x0;
  }
  
LAB_00633ded:
  if (dataNode == (int *)0x0) goto LAB_00633df1;
  goto LAB_00633e6f;
  
LAB_00633ed3:
  dataNode = hashBucket + 2;
  
LAB_00633e5a:
  if (*dataNode == 0) {
LAB_00633e60:
    FUN_006336f0("index");  // Error: index not found
  }
  
LAB_00633e6f:
  if (*dataNode == 6) {
    FUN_00633b40(dataNode, currentNode);  // Execute child node
    return;
  }
  
  node = (int *)((int)node + 1);
  currentNode = dataNode;
  if (100 < (int)node) {
    FUN_00633920();  // Stack overflow protection
    return;
  }
  goto LAB_00633d72;
}