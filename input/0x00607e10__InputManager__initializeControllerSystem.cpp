// FUNC_NAME: InputManager::initializeControllerSystem
void InputManager::initializeControllerSystem(void)
{
  int iVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  int **ppiVar7;
  int *piStack_24;
  int *piStack_20;
  int *piStack_1c;
  undefined4 uStack_18;
  
  if (DAT_01205765 == '\0') { // Check if already initialized
    DAT_01205765 = '\x01'; // Set initialized flag
    piVar3 = (int *)0x0;
    do {
      iVar5 = (&DAT_011f38f0)[(int)piVar3 * 2]; // Previous controller state
      iVar1 = (&DAT_011f38f4)[(int)piVar3 * 2]; // Current controller state
      (&DAT_011f38f0)[(int)piVar3 * 2] = 0; // Clear previous state
      (&DAT_011f38f4)[(int)piVar3 * 2] = 0; // Clear current state
      piVar2 = DAT_01205750; // InputManager instance
      if ((iVar5 != 0) || (iVar1 != 0)) {
        if (piVar3 == (int *)&DAT_00000004) { // Controller slot 4 (special case)
          uStack_18 = 0;
          piStack_1c = DAT_01205750;
          piStack_20 = (int *)0x607e6a;
          (**(code **)(*DAT_01205750 + 0x9c))(); // Call vtable method at offset 0x9c (resetController?)
        }
        else if (piVar3 == (int *)0x0) { // Controller slot 0
          iVar5 = *DAT_01205750;
          uStack_18 = 0x607e7d;
          uStack_18 = FUN_00609260(); // Initialize controller
          piStack_1c = (int *)0x0;
          piStack_20 = piVar2;
          piStack_24 = (int *)0x607e88;
          (**(code **)(iVar5 + 0x94))(); // Call vtable method at offset 0x94 (setupController?)
          DAT_01223538 = 1; // Set controller active flag
        }
        else {
          uStack_18 = 0;
          piStack_20 = DAT_01205750;
          piStack_24 = (int *)0x607ea3;
          piStack_1c = piVar3;
          (**(code **)(*DAT_01205750 + 0x94))(); // Call vtable method at offset 0x94 (setupController?)
        }
      }
      piVar3 = (int *)((int)piVar3 + 1);
    } while ((int)piVar3 < 5); // Loop through 5 controller slots
    
    uVar4 = 0;
    do {
      uStack_18 = 0x607ec7;
      FUN_00618d40(); // Clear controller state
      (&DAT_011d912c)[uVar4] = 0; // Reset controller data
      uVar4 = uVar4 + 1;
    } while (uVar4 < 0x14); // Loop through 20 controller data slots
    
    iVar5 = 0;
    do {
      uStack_18 = 0;
      piStack_20 = DAT_01205750;
      piStack_24 = (int *)0x607ef2;
      piStack_1c = (int *)iVar5;
      (**(code **)(*DAT_01205750 + 0x104))(); // Call vtable method at offset 0x104 (setControllerMapping?)
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x10); // Loop through 16 controller mappings
    
    uStack_18 = 0;
    piStack_1c = DAT_01205750;
    piStack_20 = (int *)0x607f0b;
    (**(code **)(*DAT_01205750 + 0x1a0))(); // Call vtable method at offset 0x1a0 (finalizeSetup?)
    
    iVar5 = 0;
    do {
      piStack_20 = (int *)0x0;
      piStack_24 = (int *)0x0;
      (**(code **)(*DAT_01205750 + 400))(DAT_01205750,iVar5,0); // Call vtable method at offset 0x190 (setControllerVibration?)
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x10); // Loop through 16 controllers
    
    piStack_20 = (int *)0x0;
    piStack_24 = DAT_01205750;
    (**(code **)(*DAT_01205750 + 0x1ac))(); // Call vtable method at offset 0x1ac (resetAllControllers?)
    (**(code **)(*DAT_01205750 + 0x170))(DAT_01205750,0); // Call vtable method at offset 0x170 (setActiveController?)
    (**(code **)(*DAT_01205750 + 0x9c))(DAT_01205750,0); // Call vtable method at offset 0x9c (resetController?)
    
    if ((char)piStack_1c != '\0') {
      ppiVar7 = &piStack_24;
      piVar3 = (int *)0x0;
      (**(code **)(*DAT_01205750 + 0x48))(DAT_01205750,0,0,0,ppiVar7); // Call vtable method at offset 0x48 (shutdownController?)
      (**(code **)(*DAT_01205750 + 0x94))(DAT_01205750,0,ppiVar7); // Call vtable method at offset 0x94 (setupController?)
      (**(code **)(*piVar3 + 8))(piVar3); // Call destructor
      if (DAT_012058a8 != 0) {
        FUN_006065a0(DAT_012058a8,0); // Release resource
      }
      DAT_012058a8 = 0;
      if (DAT_012058a4 != 0) {
        FUN_006065a0(DAT_012058a4,0); // Release resource
      }
      DAT_012058a4 = 0;
    }
    
    if ((DAT_012224a8 != 0) && (iVar5 = DAT_012224a8 + -1, -1 < iVar5)) {
      puVar6 = &DAT_01222328 + iVar5 * 3;
      do {
        if ((code *)*puVar6 != (code *)0x0) {
          (*(code *)*puVar6)(piStack_1c); // Call cleanup callbacks
        }
        iVar5 = iVar5 + -1;
        puVar6 = puVar6 + -3;
      } while (-1 < iVar5);
    }
    
    iVar5 = 0;
    if (0 < DAT_00f15a6c) {
      puVar6 = &DAT_0120577c;
      do {
        (**(code **)(*(int *)*puVar6 + 8))((int *)*puVar6); // Call destructor on controller objects
        *puVar6 = 0;
        iVar5 = iVar5 + 1;
        puVar6 = puVar6 + 6;
      } while (iVar5 < DAT_00f15a6c);
    }
    
    if (DAT_01205754 != (int *)0x0) {
      (**(code **)(*DAT_01205754 + 8))(DAT_01205754); // Call destructor
      DAT_01205754 = (int *)0x0;
    }
    
    DAT_01205830 = 0; // Reset controller state flags
    DAT_01205834 = 0;
    DAT_01205838 = 0;
    DAT_0120583c = 0;
    
    _memset(&DAT_011da7f0,-1,0x100); // Clear controller data buffers
    _memset(&DAT_011d97f0,-1,0x1000);
    _memset(&DAT_011ea8f0,-1,0x1000);
  }
  return;
}