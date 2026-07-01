// FUNC_NAME: HelpContextManager::enableContext
void __thiscall HelpContextManager::enableContext(int this, int contextIndex, char forceRefresh)
{
  uint bitMask;
  
  bitMask = 1 << ((byte)contextIndex & 0x1f);
  // Only fire the context enable function if the context is not already enabled,
  // or if forceRefresh is set (non-zero).
  if ((forceRefresh == '\0') || ((*(uint *)(this + 8) & bitMask) == 0)) {
    // Call the context-specific enable function pointer stored in a table.
    FUN_00922cd0((&PTR_s__dv_context_help_guards_concept_00e54d64)[contextIndex * 2]);
    // Set the bit for this context in the active context mask. (+0x8 is the active context bitmask)
    *(uint *)(this + 8) = *(uint *)(this + 8) | bitMask;
  }
  return;
}