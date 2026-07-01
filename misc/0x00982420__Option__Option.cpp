// FUNC_NAME: Option::Option
void __fastcall Option::Option(void)
{
  // Call base class constructor (likely OptionBase)
  OptionBase::OptionBase();

  // Initialize option data at offsets 0x74 and 0x70
  // DAT_00d9069c is probably a string constant for the option name/key
  registerOptionEntry(&DAT_00d9069c, this + 0x74, 0, 0, 0, 0);
  registerOptionEntry("option", this + 0x70, 0, 0, 0, 0);

  // Check global option manager pointer
  if (g_pOptionManager != 0 && *(int *)(g_pOptionManager + 0xc) != 0) {
    // Option is already managed – set flag to disabled
    *(char *)(this + 0x88) = 0;
    return;
  }
  // Otherwise this option becomes the manager? Set flag to enabled
  *(char *)(this + 0x88) = 1;
  return;
}