// FUNC_NAME: ScenarioManager::initializeScenarioDefs

void __thiscall ScenarioManager::initializeScenarioDefs(uchar param_2)
{
  int *defListPtr;
  int count;
  char *namePtr;
  uint i;
  int id;
  char flag;
  ScenarioDefEntry *newEntry;
  
  ScenarioDefEntry* entry = (ScenarioDefEntry*)allocScenarioEntry(0x60);
  if (entry != nullptr) {
    initScenarioEntry(entry);
    entry->field_0x50 = 0;
    entry->field_0x54 = 0;
    entry->field_0x58 = 0;
    entry->field_0x59 = 0;
    entry->field_0x5c = 0;
  }
  finalizeScenarioEntry(entry);
  entry->type = (param_2 == 0) ? 4 : 2; // single-player = 4, multiplayer = 2
  
  defListPtr = (int*)getScenarioDefList(0);
  *defListPtr = entry;
  
  if (g_scenarioManager->defCount == 0) {
    count = 0;
  } else {
    count = g_scenarioManager->defCount; // virtual call to get count
  }
  
  for (i = 0; i < count; i++) {
    ScenarioDefSource* source = (ScenarioDefSource*)getScenarioSource(i);
    id = source->getId(); // vtable +0xc
    if (id != entry->field_0x5c) {
      newEntry = (ScenarioDefEntry*)allocScenarioEntry(0x60);
      if (newEntry != nullptr) {
        initScenarioEntry(newEntry);
        newEntry->field_0x50 = 0;
        newEntry->field_0x54 = 0;
        newEntry->field_0x58 = 0;
        newEntry->field_0x59 = 0;
        newEntry->field_0x5c = 0;
      }
      namePtr = source->getName(); // vtable +4
      strncpy(newEntry->name, namePtr, 0x30);
      newEntry->name[0x2f] = '\0'; // null terminate
      newEntry->field_0x58 = 0;
      newEntry->field_0x5c = source->getId(); // stored ID
      flag = source->getSomeFlag(); // vtable +0x18
      newEntry->type = 4 - (flag != 0); // 3 if flag set, else 4
      
      // Add to internal list via vtable call
      (this->listHandler->addEntry)(newEntry);
    }
  }
}