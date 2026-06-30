// FUNC_NAME: Debug::storeControllerSnapshot
void __fastcall Debug::storeControllerSnapshot(uint32_t *param_1)
{
  uint32_t *in_EAX; // pointer to source data

  // Copy 16 dwords (64 bytes) from param_1 to global buffer at 0x011f69f0
  _DAT_011f69f0 = *param_1;
  uRam011f69f4 = param_1[1];
  _DAT_011f69f8 = param_1[2];
  uRam011f69fc = param_1[3];
  _DAT_011f6a00 = param_1[4];
  uRam011f6a04 = param_1[5];
  _DAT_011f6a08 = param_1[6];
  uRam011f6a0c = param_1[7];
  _DAT_011f6a10 = param_1[8];
  uRam011f6a14 = param_1[9];
  _DAT_011f6a18 = param_1[10];
  uRam011f6a1c = param_1[0xb];
  _DAT_011f6a20 = param_1[0xc];
  uRam011f6a24 = param_1[0xd];
  _DAT_011f6a28 = param_1[0xe];
  uRam011f6a2c = param_1[0xf];

  // Copy 16 dwords from in_EAX to global buffer at 0x011f6b30
  _DAT_011f6b30 = *in_EAX;
  uRam011f6b34 = in_EAX[1];
  uRam011f6b38 = in_EAX[2];
  uRam011f6b3c = in_EAX[3];
  _DAT_011f6b40 = in_EAX[4];
  uRam011f6b44 = in_EAX[5];
  uRam011f6b48 = in_EAX[6];
  uRam011f6b4c = in_EAX[7];
  _DAT_011f6b50 = in_EAX[8];
  uRam011f6b54 = in_EAX[9];
  uRam011f6b58 = in_EAX[10];
  uRam011f6b5c = in_EAX[0xb];
  _DAT_011f6b60 = in_EAX[0xc];
  uRam011f6b64 = in_EAX[0xd];
  uRam011f6b68 = in_EAX[0xe];
  uRam011f6b6c = in_EAX[0xf];

  // If debug flag is set, call additional processing
  if ((DAT_011f7430 & 1) != 0) {
    FUN_00614ab0(); // likely debug display/logging
    return;
  }
  return;
}