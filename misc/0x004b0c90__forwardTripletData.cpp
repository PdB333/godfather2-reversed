// FUNC_NAME: forwardTripletData
void __fastcall forwardTripletData(undefined4 *param_1)

{
  // in_EAX is the 'this' pointer (passed in ECX via __fastcall).
  // This function reads three consecutive dwords from the object (this[0..2])
  // and three from the input parameter pointer (param_1[0..2]),
  // then calls another function with all six values.
  // This is a thin wrapper that extracts two triplets and forwards them.

  FUN_004b0d40(*in_EAX,                // +0x00: first member of calling object
               in_EAX[1],              // +0x04: second member
               in_EAX[2],              // +0x08: third member
               *param_1,               // +0x00: first member of supplied data
               param_1[1],             // +0x04: second member
               param_1[2]);            // +0x08: third member
  return;
}