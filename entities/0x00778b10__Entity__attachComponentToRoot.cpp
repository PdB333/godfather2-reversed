// FUNC_NAME: Entity::attachComponentToRoot
void Entity::attachComponentToRoot(int *pEntity, int *pComponent)
{
  char debugFlag;
  int *pManagerSingleton;
  int *localStackBuffer;
  int *pStackFrame;
  
  if ((pEntity != (int *)0x0) && (pComponent != (int *)0x0)) {
    // Initialize stack frame for vtable call arguments
    localStackBuffer = (int *)0x0;
    pStackFrame = &localStackBuffer;
    
    // Step 1: Call virtual function on the component (offset +0x1f8) - likely componentBeginSetup
    (**(code **)(*pComponent + 0x1f8))(pComponent);
    
    // Step 2: Call virtual function on the component (offset +0x1f0) - likely componentPreAttach
    (**(code **)(*pComponent + 0x1f0))(pComponent);
    
    // Check debug mode via a global function (likely editor/development check)
    debugFlag = isDebugMode(); // FUN_00543050
    if (debugFlag != '\0') {
      // If debug, call virtual function at +0x298 on the component (e.g., setDebugVisuals)
      (**(code **)(*pComponent + 0x298))(pComponent);
    }
    
    // Step 3: Attach the component to the entity by calling virtual function at +0x204 on pComponent
    // This passes the entity as argument (pComponent->attachToParent(pEntity))
    (**(code **)(*pComponent + 0x204))(pComponent, pEntity);
    
    // Step 4: Call virtual function on the entity (offset +0x1b4) - likely entityBeginAttachment
    (**(code **)(*pEntity + 0x1b4))(pEntity);
    
    // Step 5: Get the root child node named "m_root" from the entity (offset +0x94 - getChildByName)
    int *pRootChild = (int *)(**(code **)(*pEntity + 0x94))(pEntity, "m_root");
    
    // Step 6: Attach the component to the root child (offset +0x80 - attachChild)
    (**(code **)(*pEntity + 0x80))(pEntity, pComponent, &pStackFrame, (int *)0x0, 0);
    
    // Post-processing: check a global manager singleton (e.g., debug manager)
    pManagerSingleton = (int *)GetDebugManagerInstance(); // FUN_0043b870
    if ((pManagerSingleton != (int *)0x0) && 
        (debugFlag = (**(code **)(*pManagerSingleton + 0x38))(pManagerSingleton), debugFlag != '\0')) {
      // If manager is active, log the attachment event
      logDebugAttachment(); // FUN_009aef10
    }
  }
}