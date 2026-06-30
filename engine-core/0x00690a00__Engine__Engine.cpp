// FUNC_NAME: Engine::Engine

void __thiscall Engine::Engine(Engine *this)
{
  // Set vtable pointer (presumably for the Engine class)
  *(void **)this = &PTR_FUN_00d5c958;  // vtable

  // Initialize various global or subsystem objects
  initGlobal(&DAT_01130470);  // +0x? Unknown global
  initGlobal(&DAT_01130368);
  initGlobal(&DAT_01130370);
  initGlobal(&DAT_01130248);
  initGlobal(&DAT_01130378);
  initGlobal(&DAT_01130218);
  initGlobal(&DAT_011303c8);
  initGlobal(&DAT_011304c8);
  initGlobal(&DAT_01130360);
  initGlobal(&DAT_011301b0);
  initGlobal(&DAT_012069fc);
  initGlobal(&DAT_01206a10);

  // Final initialization step
  finalizeInit();
}

// Helper functions (likely defined elsewhere in the engine)
void __fastcall initGlobal(void *globalPtr);   // FUN_004086d0
void __fastcall finalizeInit(void);            // FUN_004083d0