// FUNC_NAME: PlayerActionableInfo::constructor
void __thiscall PlayerActionableInfo::constructor(void *this, undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8, undefined1 param_9, undefined1 param_10, undefined4 param_11, undefined4 param_12, undefined4 param_13, undefined4 param_14, undefined4 param_15, undefined1 param_16, undefined1 param_17, undefined4 param_18, undefined4 param_19)
{
  undefined4 *in_EAX = (undefined4 *)this;
  
  // +0x230 (0x8c * 4) - likely some action/state data
  in_EAX[0x8c] = param_1;
  // +0x23C (0x8f * 4) - another action parameter
  in_EAX[0x8f] = param_5;
  // +0x234 (0x8d * 4) - action parameter
  in_EAX[0x8d] = param_2;
  // +0x244 (0x91 * 4) - action parameter
  in_EAX[0x91] = param_7;
  // +0x240 (0x90 * 4) - action parameter
  in_EAX[0x90] = param_6;
  // +0x251 - byte flag
  *(undefined1 *)((int)in_EAX + 0x251) = param_16;
  // +0x250 (0x94 * 4) - byte at offset 0x250
  *(undefined1 *)(in_EAX + 0x94) = param_9;
  // +0x1F0 (0x7c * 4) - some data
  in_EAX[0x7c] = param_11;
  // +0x120 (0x48 * 4) - some data
  in_EAX[0x48] = param_8;
  // +0x1F8 (0x7e * 4) - some data
  in_EAX[0x7e] = param_13;
  // +0x1F4 (0x7d * 4) - some data
  in_EAX[0x7d] = param_12;
  // +0x200 (0x80 * 4) - some data
  in_EAX[0x80] = param_15;
  // +0x1FC (0x7f * 4) - some data
  in_EAX[0x7f] = param_14;
  // +0x214 (0x85 * 4) - initialize to 0
  in_EAX[0x85] = 0;
  // +0x212 - byte flag initialized to 0
  *(undefined1 *)((int)in_EAX + 0x212) = 0;
  // +0x248 (0x92 * 4) - action parameter
  in_EAX[0x92] = param_7;
  // +0x210 (0x84 * 4) - byte at offset 0x210
  *(undefined1 *)(in_EAX + 0x84) = param_10;
  // +0x21C (0x87 * 4) - some data
  in_EAX[0x87] = param_18;
  // +0x24C (0x93 * 4) - action parameter
  in_EAX[0x93] = param_4;
  // +0x0 - vtable pointer
  *in_EAX = &PTR_LAB_00e38390;
  // +0x204 (0x81 * 4) - action parameter
  in_EAX[0x81] = param_3;
  // +0x211 - byte flag initialized to 1
  *(undefined1 *)((int)in_EAX + 0x211) = 1;
  // +0x220 (0x88 * 4) - some data
  in_EAX[0x88] = param_19;
  // +0x213 - byte flag
  *(undefined1 *)((int)in_EAX + 0x213) = param_17;
  return;
}