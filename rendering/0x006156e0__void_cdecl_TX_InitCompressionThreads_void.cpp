// Xbox PDB: void __cdecl TX_InitCompressionThreads(void)
// FUNC_NAME: TextureManager::initializeTextureWorkerSystem
void TextureManager::initializeTextureWorkerSystem(void)
{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 local_20; // thread creation flags
  undefined4 local_1c; // stack size = 0x2000
  undefined4 local_18; // creation flags = 0xffffff80 (CREATE_SUSPENDED | STACK_SIZE_PARAM_IS_A_RESERVATION)
  undefined4 local_14; // thread ID = 0xffffffff
  undefined1 local_10; // thread priority
  char *local_c; // thread name
  
  // Reset texture load count / completion flag
  DAT_01222528 = 0;
  
  // Clear texture loader state array (3000 bytes)
  _memset(&DAT_01222574, 0, 3000);
  
  // Initialize texture handle slots (every 6th DWORD is a texture handle)
  puVar3 = &DAT_0122257c;
  do {
    // Allocate texture data (0x10 bytes)
    iVar1 = FUN_009c8e50(0x10);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      // Get pointer to texture data
      uVar2 = FUN_00ab64e0(0, 1);
    }
    *puVar3 = uVar2;
    puVar3 = puVar3 + 6;
  } while ((int)puVar3 < 0x1223134);
  
  // Initialize threading system
  FUN_00ab5450();
  
  // Setup thread creation parameters
  local_20 = 0; // no specific thread attributes
  local_1c = 0x2000; // 8KB stack
  local_18 = 0xffffff80; // CREATE_SUSPENDED | STACK_SIZE_PARAM_IS_A_RESERVATION
  local_14 = 0xffffffff; // let system assign thread ID
  local_10 = 0; // default thread priority
  local_c = "TextureWorkerThread";
  
  // Get thread creation function
  uVar2 = FUN_00ab5470();
  
  // Create the texture worker thread
  FUN_00ab7410(FUN_006155e0, 0, &local_20, uVar2);
  
  return;
}