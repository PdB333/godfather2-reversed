// FUNC_NAME: hashTableLookup
undefined * __fastcall hashTableLookup(undefined4 param_1,float *param_2)
{
  // This function appears to be a hash table lookup using two float values as keys.
  // It uses two global tables: DAT_010beed0 (byte table) and DAT_010c08f0 (data table).
  // The hash is computed by adding a global offset (DAT_00e445e0) to each float,
  // masking to 8 bits, adding 1, then using the result as indices into the byte table.
  // The final offset into the data table is computed as (byte1 + DAT_01205530 + byte2) * 8.

  return &DAT_010c08f0 +
         (uint)(byte)(&DAT_010beed0)
                     [(((int)(param_2[1] + DAT_00e445e0) & 0xffU) + 1 & 0xff) +
                      DAT_01205530 +
                      (uint)(byte)(&DAT_010beed0)
                                  [DAT_01205530 +
                                   (((int)(*param_2 + DAT_00e445e0) & 0xffU) + 1 & 0xff)]] * 8;
}