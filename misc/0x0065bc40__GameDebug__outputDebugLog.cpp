// FUNC_NAME: GameDebug::outputDebugLog
void GameDebug::outputDebugLog(char *format, ...)
{
  char buffer [4092]; // Local buffer for formatted output
  char *currentPos;   // Current position in buffer
  char *prefix;       // Optional prefix from global data
  int *logCallback;   // Iterator for registered log callbacks
  
  // Initialize position and prefix
  currentPos = buffer;
  prefix = (char *)0x0;
  
  // If we have a global debug context (DAT_01205a5c), prepend it as prefix
  if (DAT_01205a5c != 0) {
    prefix = *(char **)(DAT_01205a5c + 8); // +0x8: debug context prefix string
    
    // Copy prefix into buffer with careful pointer arithmetic
    int offset = -(int)prefix;
    do {
      char c = *prefix;
      prefix[offset + (int)(buffer)] = c; // Write character into buffer at adjusted position
      prefix = prefix + 1;
    } while (*prefix != '\0'); // Continue until null terminator
    
    // Now prefix is null, move past the copied prefix in buffer
    prefix = buffer + 1;
    do {
      currentPos++;
    } while (*currentPos != '\0'); // Find end of prefix string
    currentPos[-(int)(prefix) + (int)(buffer)] = ':'; // Append colon
    currentPos[(1 - (int)(prefix)) + (int)(buffer)] = ' '; // Append space
    prefix = currentPos + (2 - (int)(prefix)); // Update prefix pointer
  }
  
  // Format the message using vsnprintf with variable arguments
  __vsnprintf(buffer + (int)prefix, 0x1000 - (int)prefix, format, &stack0x00000008);
  
  // Call all registered log callbacks (DAT_01205a54 is a linked list head)
  for (logCallback = DAT_01205a54; logCallback != (int *)0x0; logCallback = (int *)logCallback[1]) {
    (**(code **)(*logCallback + 4))(buffer); // Callback at offset 4, executes on buffer
  }
  
  // Output to debug console
  OutputDebugStringA(buffer);
  OutputDebugStringA("\n");
}