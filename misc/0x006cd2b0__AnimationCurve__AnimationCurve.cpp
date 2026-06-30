// FUNC_NAME: AnimationCurve::AnimationCurve
// Function address: 0x006cd2b0
// Constructor for an animation curve/path class. Initializes base, sets vtable, zeros 14 3D vectors
// (control points?) and sets two scalar fields. Also seeds random number generator on first call.

// Class definition assumed:
// class AnimationCurve : public SomeBase {
// public:
//     AnimationCurve(SomeBase* owner);
//     // vtable at +0x00, base at +? actually vtable is first, but base call sets it?
//     // Fields from offset 0x30 (0xC0 bytes into this):
//     // +0x30-0x35: 2 vectors (6 floats)
//     // +0x36: float someScalar1 (global value)
//     // +0x37: float someScalar2 (0x21 = 33.0f)
//     // +0x38-0x58: 11 vectors (33 floats) [all zero]
//     // +0x59-0x5b: 1 vector (3 floats) [zero]
// };

// Undefined4* is used for pointer arithmetic; treat as this pointer.
undefined4 * __thiscall AnimationCurve::AnimationCurve(undefined4 *this, undefined4 owner)
{
  undefined4 local_c;      // seed for random init
  undefined4 local_8;      // zero
  undefined1 local_4;      // padding
  undefined4 uVar1;
  int iVar2;
  bool bFirstInit;

  // Call base class constructor: SomeBase::SomeBase(owner, someGlobalVtable)
  FUN_006c9760(owner, _DAT_00d5cf70);

  // Set vtable pointers (possible multiple inheritance)
  *this = &PTR_FUN_00d5f174;          // main vtable
  this[2] = &PTR_LAB_00d5f16c;        // secondary vtable

  // Fetch global value for field at +0xD8 (offset 0x36*4)
  uVar1 = DAT_00d5d740;

  // Initialize first two vectors (offsets 0x30-0x35) to zero
  this[0x30] = 0; // x0
  this[0x31] = 0; // y0
  this[0x32] = 0; // z0
  this[0x33] = 0; // x1
  this[0x34] = 0; // y1
  this[0x35] = 0; // z1

  // Set two scalar fields (offsets 0x36, 0x37)
  this[0x36] = uVar1;          // some global value (e.g., angle, scale)
  this[0x37] = 0x21;           // likely 33.0f as integer bit pattern (0x42000000? no, 0x21 is 33 decimal as int, but might be float)

  // Zero the final vector at offsets 0x59-0x5b
  this[0x59] = 0;
  this[0x5a] = 0;
  this[0x5b] = 0;

  // Zero the remaining 11 vectors (offsets 0x38-0x58) in groups of three
  this[0x3a] = 0; this[0x39] = 0; this[0x38] = 0; // group 0x38-0x3a
  this[0x3d] = 0; this[0x3c] = 0; this[0x3b] = 0; // 0x3b-0x3d
  this[0x40] = 0; this[0x3f] = 0; this[0x3e] = 0; // 0x3e-0x40
  this[0x43] = 0; this[0x42] = 0; this[0x41] = 0; // 0x41-0x43
  this[0x46] = 0; this[0x45] = 0; this[0x44] = 0; // 0x44-0x46
  this[0x49] = 0; this[0x48] = 0; this[0x47] = 0; // 0x47-0x49
  this[0x4c] = 0; this[0x4b] = 0; this[0x4a] = 0; // 0x4a-0x4c
  this[0x4f] = 0; this[0x4e] = 0; this[0x4d] = 0; // 0x4d-0x4f
  this[0x52] = 0; this[0x51] = 0; this[0x50] = 0; // 0x50-0x52
  this[0x55] = 0; this[0x54] = 0; this[0x53] = 0; // 0x53-0x55
  this[0x58] = 0; this[0x57] = 0; this[0x56] = 0; // 0x56-0x58

  // Increment static counter and seed random number generator on first call
  iVar2 = DAT_0112a804 + 1;
  bFirstInit = DAT_0112a804 == 0;
  DAT_0112a804 = iVar2;
  if (bFirstInit) {
    local_c = DAT_0112a814;   // some initial seed value
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c, 0); // likely srand(seed)
  }

  return this;
}