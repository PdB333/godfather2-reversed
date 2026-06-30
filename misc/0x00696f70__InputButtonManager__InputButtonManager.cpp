// FUNC_NAME: InputButtonManager::InputButtonManager
int __fastcall InputButtonManager::InputButtonManager(InputButtonManager* this)
{
  ButtonNode* listHead;
  int local_10[3];
  DestructorCallback local_4;

  // Allocate list head node (size 0x28 = 40 bytes)
  listHead = (ButtonNode*)FUN_009c8e50(0x28);
  if (listHead != (ButtonNode*)0x0) {
    listHead->next = 0;
  }
  if (listHead + 1 != (ButtonNode*)0x0) {
    listHead->prev = 0;
  }
  if (listHead + 2 != (ButtonNode*)0x0) {
    listHead->actionType = 0;
  }
  listHead->byte9 = 1;
  listHead->byte37 = 0; // offset 0x25
  this->listHead = listHead;
  listHead->byte37 = 1; // mark as initialized

  // Initialize circular doubly linked list (sentinel node)
  this->listHead->prev = this->listHead;
  this->listHead->next = this->listHead;
  this->listHead->actionType = this->listHead;
  this->actionCount = 0;

  // Register 16 buttons (Button.1 to Button.16)
  debugPrint("Button.1");
  listHead = createButtonNode(local_10);
  listHead->next = 0;
  listHead->prev = 1; // button index 0
  if (local_10[0] != 0) {
    local_4(local_10[0]); // cleanup if needed
  }

  debugPrint("Button.2");
  listHead = createButtonNode(local_10);
  listHead->next = 0;
  listHead->prev = 1; // button index 1
  if (local_10[0] != 0) {
    local_4(local_10[0]);
  }

  debugPrint("Button.3");
  listHead = createButtonNode(local_10);
  listHead->next = 0;
  listHead->prev = 2; // button index 2
  if (local_10[0] != 0) {
    local_4(local_10[0]);
  }

  // ... repeat for Button.4 through Button.16 with indices 3..15 ...
  // (omitted for brevity, pattern is identical)
  
  // Button.16 (index 0xF)
  debugPrint("Button.16");
  listHead = createButtonNode(local_10);
  listHead->next = 0;
  listHead->prev = 0xF;
  if (local_10[0] != 0) {
    local_4(local_10[0]);
  }

  return this;
}