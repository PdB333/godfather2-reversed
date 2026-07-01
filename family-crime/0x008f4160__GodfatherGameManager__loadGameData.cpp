// FUNC_NAME: GodfatherGameManager::loadGameData
void __fastcall GodfatherGameManager::loadGameData(int this)
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  int local_284;
  undefined1 *local_280;
  undefined4 local_27c;
  int local_278;
  int local_274;
  undefined4 local_270;
  code *local_26c;
  undefined2 *local_268;
  code *local_25c;
  undefined2 *local_258;
  undefined4 local_254;
  undefined4 local_250;
  code *local_24c;
  undefined1 local_248 [584];
  
  // Check if game data is already loaded (+0x2098 = m_bGameDataLoaded)
  if (*(int *)(this + 0x2098) == 0) {
    local_284 = 0;
    local_280 = (undefined1 *)0x0;
    local_27c = 0;
    
    // Allocate memory for game data
    local_284 = FUN_009c89c0();  // likely malloc or memory allocator
    if (local_284 == 0) {
      local_284 = 0;
    }
    else {
      local_284 = local_284 + 4;
    }
    
    // Setup callback function pointer
    local_280 = &LAB_008f39c0;  // likely a callback or event handler
    local_27c = 0;
    local_278 = 0;
    local_274 = 0;
    local_270 = 0;
    local_26c = (code *)0x0;
    local_258 = (undefined2 *)0x0;
    local_250 = 0;
    local_254 = 0;
    
    // Load game data from save file
    FUN_00603330(0x9e30c21d, &local_278);  // likely file open/read with hash ID
    if (local_274 != 0) {
      FUN_004dd9e0(&local_278, &local_258);  // likely decompress or parse data
    }
    
    // Initialize audio system
    uVar1 = FUN_00697cb0();  // get audio manager
    uVar2 = FUN_004dbef0(uVar1);  // get audio state
    FUN_004dba00(uVar1, uVar2);  // set audio state
    
    // Reset audio data
    uVar1 = FUN_004dbef0(&DAT_00e36ef4);  // get global audio data
    FUN_004dbd90(&DAT_00e36ef4, 0, uVar1);  // clear audio data
    
    // Reset streaming audio (+0x2260 = m_pStreamManager, +0x2264 = m_streamCount)
    FUN_004dbd90(*(undefined4 *)(this + 0x2260), 0, *(undefined4 *)(this + 0x2264));
    
    // Reset audio data again
    uVar1 = FUN_004dbef0(&DAT_00e36ef4);
    FUN_004dbd90(&DAT_00e36ef4, 0, uVar1);
    
    // Compare and merge data
    puVar4 = local_268;
    if (local_268 == (undefined2 *)0x0) {
      puVar4 = &DAT_00e2df14;  // default empty data
    }
    puVar3 = local_258;
    if (local_258 == (undefined2 *)0x0) {
      puVar3 = &DAT_00e2df14;  // default empty data
    }
    FUN_00accbe0(puVar3, puVar4, &DAT_00d81088);  // likely data merge/copy
    
    // Finalize game data loading
    uVar1 = FUN_00acdec0(&local_284, this + 0x2090, local_248);  // process loaded data
    *(undefined4 *)(this + 0x2098) = uVar1;  // set loaded flag
    
    // Cleanup allocated resources
    if (local_268 != (undefined2 *)0x0) {
      (*local_25c)(local_268);  // free memory
    }
    if (local_258 != (undefined2 *)0x0) {
      (*local_24c)(local_258);  // free memory
    }
    if (local_278 != 0) {
      (*local_26c)(local_278);  // free memory
    }
  }
  return;
}