// FUNC_NAME: Entity::createComponent
void __fastcall Entity::createComponent(Entity *thisPtr)
{
   if ((*(int *)(thisPtr + 0x10) != 0) && (*(int *)(thisPtr + 0x88) < 3))
   {
      byte randomByte;
      int randomInt;
      // Get a random integer + byte pair (FUN_008aee10)
      getRandomPair(0, &randomInt, &randomByte);

      void *component = alloc(0x50); // FUN_009c8e50(0x50) - allocate component memory
      if (component != NULL)
      {
         component = constructComponent(thisPtr - 0x50); // FUN_008aebf0 - placement new with parent offset
      }

      if (component != NULL)
      {
         *(int *)(component + 0x38) = 0;          // +0x38: some int field set to 0
         *(byte *)(component + 0x3c) = randomByte; // +0x3c: store random byte
         hashTransform(&randomInt);               // FUN_004d8a60 - likely a hash/transform
         addComponentToList(component);           // FUN_0064ef60 - register component
         broadcastEvent();                        // FUN_00407430 - notify listeners
      }
   }
}