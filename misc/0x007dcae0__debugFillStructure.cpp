// FUNC_NAME: debugFillStructure
// Function address: 0x007dcae0
// Initializes a 68-byte structure with debug sentinel values.
// Pattern: 4 repetitions of [0xbadbadba, 0xbeefbeef, 0xeac15a55, 0x91100911] followed by 0.
void __fastcall debugFillStructure(uint32_t* param_1)
{
  param_1[1] = 0xbeefbeef;
  param_1[5] = 0xbeefbeef;
  param_1[9] = 0xbeefbeef;
  param_1[0xd] = 0xbeefbeef;
  *param_1 = 0xbadbadba;
  param_1[2] = 0xeac15a55;
  param_1[3] = 0x91100911;
  param_1[4] = 0xbadbadba;
  param_1[6] = 0xeac15a55;
  param_1[7] = 0x91100911;
  param_1[8] = 0xbadbadba;
  param_1[10] = 0xeac15a55;
  param_1[0xb] = 0x91100911;
  param_1[0xc] = 0xbadbadba;
  param_1[0xe] = 0xeac15a55;
  param_1[0xf] = 0x91100911;
  param_1[0x10] = 0;
  return;
}