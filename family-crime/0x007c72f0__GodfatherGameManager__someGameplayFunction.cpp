// FUNC_NAME: GodfatherGameManager::someGameplayFunction
void __fastcall GodfatherGameManager::someGameplayFunction(int *param_1)
{
  int playerPtr;
  
  playerPtr = FUN_007ab1f0(); // likely getPlayer or getActivePlayer
  if (playerPtr != 0) {
    // Call a virtual function at vtable offset 0x2c (likely some setState or applyEffect)
    // The first argument is a complex conditional expression based on a byte at player+0x1aa
    // When byte != 2: result = -(uint)(byte != 2) & 0x1fc6e941 + 0xf60ba72a = 0x1fc6e941 + 0xf60ba72a = 0x15D0906B (sign extended negative)
    // When byte == 2: result = 0x00000000 + 0xf60ba72a = 0xf60ba72a (large unsigned)
    // Additional params: param3=1, param4=0, param5=1, param6=0x3f800000 (1.0f), param7=0x3f800000 (1.0f)
    (**(code **)(*param_1 + 0x2c))
              ((-(uint)(*(char *)(playerPtr + 0x1aa) != '\x02') & 0x1fc6e941) + 0xf60ba72a, 1, 0, 1,
               0x3f800000, 0x3f800000);
  }
  return;
}