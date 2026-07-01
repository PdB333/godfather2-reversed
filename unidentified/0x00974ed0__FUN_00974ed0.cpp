// FUNC_NAME: unknown::compareMotolabConfig
uint compareMotolabConfig(void)

{
  float *pfVar1;
  uint3 uVar2;
  char cVar3;
  uint uVar4;
  undefined2 uVar5;
  
  // Read magic value at global offset +0x14 (likely config hash or version)
  uVar4 = *(uint *)(DAT_01129938 + 0x14);
  
  // Check if all 8 bit-fields at DAT_00e57568 match the extracted bits from the magic value
  // These are likely boolean/fixed-point fields in a config struct
  if ((((DAT_00e57568 == ((byte)(uVar4 >> 1) & 1)) && 
        (DAT_00e57569 == ((byte)(uVar4 >> 2) & 1))) &&
       (DAT_00e5756a == ((byte)(uVar4 >> 3) & 1))) &&
      ((DAT_00e5756b == ((byte)(uVar4 >> 4) & 1) &&
       (uVar4 = uVar4 >> 5 & 0xffffff01, DAT_00e5756c == (char)uVar4)))) {
    
    // Compare float field at +0x20 (first float in config)
    pfVar1 = (float *)(DAT_01129938 + 0x20);
    uVar5 = (undefined2)(uVar4 >> 0x10);
    
    // Build comparison flags: bit6=equal, bit2=NaN, bit1=always1, bit0=lessThan
    uVar4 = (uint)CONCAT21(uVar5,
            (DAT_00e57570 == *pfVar1) << 6 |
            (NAN(DAT_00e57570) || NAN(*pfVar1)) << 2 | 2U |
            DAT_00e57570 < *pfVar1) << 8;
    
    if (DAT_00e57570 == *pfVar1) {
      // Compare float at +0x24
      pfVar1 = (float *)(DAT_01129938 + 0x24);
      uVar2 = CONCAT21(uVar5,
              (DAT_00e57574 == *pfVar1) << 6 |
              (NAN(DAT_00e57574) || NAN(*pfVar1)) << 2 | 2U | DAT_00e57574 < *pfVar1);
      uVar4 = (uint)uVar2 << 8;
      
      if (DAT_00e57574 == *pfVar1) {
        // Compare byte at +0x14 (already extracted as char)
        uVar4 = CONCAT31(uVar2, *(undefined1 *)(DAT_01129938 + 0x14)) & 0xffffff01;
        cVar3 = (char)uVar4;
        
        if (DAT_00e57578 == cVar3) {
          // Compare float at +0x18
          pfVar1 = (float *)(DAT_01129938 + 0x18);
          uVar5 = (undefined2)(uVar4 >> 0x10);
          uVar4 = CONCAT22(uVar5,
                  CONCAT11((DAT_00e5757c == *pfVar1) << 6 |
                          (NAN(DAT_00e5757c) || NAN(*pfVar1)) << 2 | 2U | DAT_00e5757c < *pfVar1,
                          cVar3));
          
          if (DAT_00e5757c == *pfVar1) {
            // Compare float at +0x1c
            pfVar1 = (float *)(DAT_01129938 + 0x1c);
            uVar4 = CONCAT22(uVar5,
                    CONCAT11((DAT_00e57580 == *pfVar1) << 6 |
                            (NAN(DAT_00e57580) || NAN(*pfVar1)) << 2 | 2U | DAT_00e57580 < *pfVar1,
                            cVar3));
            
            if (DAT_00e57580 == *pfVar1) {
              // Compare float at +0x2c
              pfVar1 = (float *)(DAT_01129938 + 0x2c);
              uVar4 = CONCAT22(uVar5,
                      CONCAT11((DAT_00e57584 == *pfVar1) << 6 |
                              (NAN(DAT_00e57584) || NAN(*pfVar1)) << 2 | 2U | DAT_00e57584 < *pfVar1,
                              cVar3));
              
              if (DAT_00e57584 == *pfVar1) {
                // All comparisons succeeded - return success (low byte cleared)
                return uVar4 & 0xffffff00;
              }
            }
          }
        }
      }
    }
  }
  
  // Any comparison failed - return 1 (failure)
  return CONCAT31((int3)(uVar4 >> 8), 1);
}