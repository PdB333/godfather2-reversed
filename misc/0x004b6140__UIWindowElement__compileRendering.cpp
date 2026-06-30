// FUNC_NAME: UIWindowElement::compileRendering
void __fastcall UIWindowElement::compileRendering(int this) // __thiscall equivalent: first param = this
{
  ushort compCount;
  int inputMgr;       // param_1 + 0x4
  int renderDevice;   // param_1 + 0x8
  char *componentPtr;
  int iVar2;
  int iVar3;
  char cVar6;
  ushort uVar7;
  int *piVar8;
  uint uVar9;
  undefined4 uVar10;
  undefined4 *puVar11;
  int iVar12;
  undefined4 uStack_c;

  // Get input manager and render device from this window
  inputMgr = *(int *)(this + 0x4);    // +0x4: pointer to input manager (e.g., InputManager)
  renderDevice = *(int *)(this + 0x8); // +0x8: pointer to render device (e.g., RenderDevice)

  // Get some singleton from render device's vtable (offset 0x20)
  piVar8 = (int *)(**(code **)(**(int **)(renderDevice + 8) + 0x20))(); // calls vtable[0x20]
  cVar6 = (**(code **)(*piVar8 + 0x48))(); // calls method at vtable[0x48] on returned object

  // If singleton's method returns false, set the "interactive" flag
  if (cVar6 == '\0') {
    *(byte *)(this + 0x28) = *(byte *)(this + 0x28) | 2; // +0x28: flags; bit 1 = interactive
  }

  // Search for a text component (ID 0x8A9AFFDB) to set "hasText" flag
  uVar9 = 0;
  compCount = *(ushort *)(inputMgr + 0x20); // +0x20: number of components
  if (compCount != 0) {
    puVar11 = *(undefined4 **)(inputMgr + 0x1c); // +0x1c: pointer to component array
    do {
      componentPtr = (char *)*puVar11;
      // Check component type by hash at offset +0x10
      if (*(int *)(componentPtr + 0x10) == 0x8A9AFFDB) { // hash for "TextComponent"
        if ((componentPtr != (char *)0x0) && (*componentPtr != '\0')) {
          // Set bit 4 (0x10) = hasText
          *(byte *)(this + 0x28) = *(byte *)(this + 0x28) | 0x10;
        }
        break;
      }
      uVar9 = uVar9 + 1;
      puVar11 = puVar11 + 1;
    } while (uVar9 < compCount);
  }

  // Search for an image component (ID 0x22898A7F) to get texture handle
  uVar1 = compCount;
  uVar9 = 0;
  uStack_c = 8; // default? maybe sentinel
  if (uVar1 != 0) {
    piVar8 = *(int **)(inputMgr + 0x1c);
    do {
      puVar11 = (undefined4 *)*piVar8;
      if (puVar11[4] == 0x22898A7F) { // hash for "ImageComponent"
        if (puVar11 != (undefined4 *)0x0) {
          uStack_c = *puVar11; // first dword = texture handle/ID
        }
        break;
      }
      uVar9 = uVar9 + 1;
      piVar8 = piVar8 + 1;
    } while (uVar9 < uVar1);
  }

  // Search for a transform component (type 0x10 at offset +0x14) to get a resource
  iVar12 = 0;
  uVar7 = 0;
  if (uVar1 != 0) {
    do {
      piVar8 = *(int **)(*(int *)(inputMgr + 0x1c) + (uint)uVar7 * 4);
      if (piVar8[5] == 0x10) { // offset +0x14 == 0x10 (TransformComponent type?)
        iVar12 = *piVar8; // component pointer
        break;
      }
      uVar7 = uVar7 + 1;
    } while (uVar7 < uVar1);
  }

  // Get a shader/material handle from the transform component
  // iVar12->+0x1c -> +0x14 -> +0x8
  uVar5 = *(undefined4 *)(*(int *)(*(int *)(iVar12 + 0x1c) + 0x14) + 8); // resource handle

  // Acquire a render context from renderDevice vtable (offset 0x1c)
  uVar10 = (**(code **)(**(int **)(renderDevice + 8) + 0x1c))(); // e.g., RenderContext*

  // Call the core drawing function with texture, context, and material
  FUN_004b5df0(this, uStack_c, uVar10, uVar5); // likely draws the element batch
  FUN_004b5fc0(uVar10); // release render context

  return;
}