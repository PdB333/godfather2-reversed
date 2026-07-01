// FUN_NAME: ScoringManager::addScoringRow
void __thiscall ScoringManager::addScoringRow(undefined4 param_1, undefined4 *param_2)
{
  int *ptr; // points to global singleton
  CoreString local_10; // string buffer
  CoreString local_20;
  CoreString local_30;
  CoreString local_40;

  ptr = g_pScoringManager; // DAT_0112ebb4, global pointer to ScoringManager instance

  // Initialize local strings to zero
  memset(&local_10, 0, sizeof(CoreString));
  memset(&local_20, 0, sizeof(CoreString));
  memset(&local_30, 0, sizeof(CoreString));
  memset(&local_40, 0, sizeof(CoreString));

  // Store first parameter at offset +0x144 (likely a row ID or type)
  *(undefined4 *)(ptr + 0x144) = param_1;
  // Store param_2[5] at offset +0x164 (likely a score value or flag)
  *(undefined4 *)(ptr + 0x164) = param_2[5];

  // Convert/allocate string for param_2[6] into local_10
  CoreString::fromSomeSource(param_2[6], &local_10);
  // Same for [7] and [8]
  CoreString::fromSomeSource(param_2[7], &local_20);
  CoreString::fromSomeSource(param_2[8], &local_30);
  // Combined: [7]+[8] into local_40 (maybe concatenation?)
  CoreString::fromSomeSource(param_2[7] + param_2[8], &local_40);

  // Fallback to empty string if any are null
  char *s5 = local_40.data ? local_40.data : &EMPTY_STRING; // DAT_0120546e
  char *s4 = local_30.data ? local_30.data : &EMPTY_STRING;
  char *s3 = local_20.data ? local_20.data : &EMPTY_STRING;
  char *s2 = local_10.data ? local_10.data : &EMPTY_STRING;
  char *s1 = param_2[0] ? (char*)param_2[0] : &EMPTY_STRING;

  // Log the row with format string at DAT_00d88e88 (e.g., "%s %s %s %s %s")
  Debug::printf("AddScoringRow", 0, g_formatString, 5, s1, s2, s3, s4, s5);

  // Cleanup local strings (calling their destructor function pointer)
  if (local_40.data) {
    local_40.destructor(local_40.data);
  }
  if (local_30.data) {
    local_30.destructor(local_30.data);
  }
  if (local_20.data) {
    local_20.destructor(local_20.data);
  }
  if (local_10.data) {
    local_10.destructor(local_10.data);
  }
}