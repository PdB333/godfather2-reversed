// FUNC_NAME: EARSObject::loadPropertiesFromStream
undefined4* __thiscall EARSObject::loadPropertiesFromStream(undefined4* this, int stream, undefined4 param_3)
{
  int* piVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  // Call base class initializer (likely EARSObject::baseInit)
  FUN_00414f30(stream, param_3);
  
  uVar3 = DAT_00e2b1a4; // Some global constant or default value
  
  // Set vtable pointers
  this[0xd] = &PTR_LAB_00e2f7a8; // First vtable assignment
  *this = &PTR_FUN_00e2f7b8; // Main vtable
  this[0xd] = &PTR_LAB_00e2f840; // Override secondary vtable
  
  // Zero out fields at +0x70 through +0xA0 (offsets 0x70 = 0x1c*4, 0x7c, 0x80, etc.)
  this[0x1c] = 0; // +0x70
  this[0x1d] = 0; // +0x74
  this[0x1e] = 0; // +0x78
  this[0x1f] = 0; // +0x7c
  this[0x20] = 0; // +0x80
  
  // Set color/default values (RGBA?)
  this[0x22] = uVar3; // +0x88
  this[0x23] = uVar3; // +0x8c
  this[0x24] = uVar3; // +0x90
  this[0x25] = uVar3; // +0x94
  this[0x26] = DAT_00e2eff4; // +0x98, another global constant
  
  this[0x21] = 0; // +0x84 (flags?)
  this[0x27] = 0; // +0x9c
  this[0x28] = 0; // +0xa0
  this[0x29] = 1; // +0xa4 (default scale = 1)
  this[0x2a] = 0; // +0xa8
  this[0x2b] = 0; // +0xac
  
  uVar5 = 0; // Property index counter
  if (*(short*)(stream + 0x20) != 0) {
    do {
      // Get property descriptor pointer from stream's property array
      piVar1 = *(int**)(*(int*)(stream + 0x1c) + uVar5 * 4);
      uVar2 = piVar1[4]; // Hash ID of property name
      
      // Match against known property hashes (likely from EARS engine)
      if (uVar2 < 0x7c875d3d) {
        if (uVar2 == 0x7c875d3c) {
          // Property: ??? (likely a bounding box or transform)
          iVar4 = *piVar1; // Pointer to property data
          this[0x1c] = *(undefined4*)(iVar4 + 0xc); // +0x70
          this[0x1d] = *(undefined4*)(iVar4 + 0x10); // +0x74
          this[0x1e] = *(undefined4*)(iVar4 + 0x14); // +0x78
          this[0x1f] = *(undefined4*)(iVar4 + 0x18); // +0x7c
        }
        else if (uVar2 < 0x60b56c5f) {
          if (uVar2 == 0x60b56c5e) {
            // Property: flags/mask?
            this[0x21] = *piVar1; // +0x84
          }
          else if (uVar2 == 0x3ce7f57a) {
            // Property: color/alpha component?
            this[0x24] = *piVar1; // +0x90
          }
          else if (uVar2 == 0x5cc9abae) {
            // Property: scale?
            this[0x29] = *piVar1; // +0xa4
          }
        }
        else if (uVar2 == 0x787f84f3) {
          // Property: another color component?
          this[0x23] = *piVar1; // +0x8c
        }
        else if (uVar2 == 0x7a15cb34) {
          // Property: constant/alpha?
          this[0x26] = *piVar1; // +0x98
        }
      }
      else if (uVar2 < 0xf77d06c2) {
        if (uVar2 == 0xf77d06c1) {
          // Property: some value?
          this[0x28] = *piVar1; // +0xa0
        }
        else if (uVar2 == 0xb9df2092) {
          // Property: color component?
          this[0x25] = *piVar1; // +0x94
        }
        else if (uVar2 == 0xcab10700) {
          // Property: unknown
          this[0x27] = *piVar1; // +0x9c
        }
      }
      else if (uVar2 == 0xfd265132) {
        // Property: color component (R?)?
        this[0x22] = *piVar1; // +0x88
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(ushort*)(stream + 0x20));
  }
  
  // Compute final length/magnitude based on flags
  if ((this[0x21] & 0x400) == 0) {
    // If flag 0x400 not set, use single value
    this[0x2c] = this[0x22]; // +0xb0 = first color component
  }
  else {
    // Else compute magnitude from three components (R,G,B?)
    this[0x2c] = SQRT((float)this[0x23] * (float)this[0x23] +
                     (float)this[0x24] * (float)this[0x24] +
                     (float)this[0x25] * (float)this[0x25]); // +0xb0 = sqrt(R^2+G^2+B^2)
  }
  
  // Debug/editor preview: if global DAT_012233c4 (debug flag?) is set, call a render preview function
  if (DAT_012233c4 != 0) {
    // Call a virtual function on a child/component object at this[3] (offset +0x0c)
    iVar4 = (**(code**)(*(int*)this[3] + 0x60))();
    local_20 = *(undefined4*)(iVar4 + 0x30);
    local_1c = *(undefined4*)(iVar4 + 0x34);
    local_18 = *(undefined4*)(iVar4 + 0x38);
    local_14 = *(undefined4*)(iVar4 + 0x3c);
    FUN_00416070(this + 0xd, &local_20, this[0x2c]); // Store preview transform
  }
  return this;
}