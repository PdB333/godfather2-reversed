// FUNC_NAME: VersionNode::parseFromString
uint __thiscall VersionNode::parseFromString(char *node, char *inputStr)
{
  char c;
  char *src;
  char *dst;
  int charVal;
  uint result;
  char *child;
  int charIndex;

  charIndex = 0;
  if (inputStr != (char *)0x0) {
    c = *inputStr;
    charVal = (int)c;
    src = node;
    // Check if first character is alphanumeric (a-z, A-Z, or 0-9)
    if (((charVal - 0x61U < 0x1a) || (charVal - 0x41U < 0x1a)) || (charVal - 0x30U < 10)) {
      // Parse until null or underscore, but limit to 10 chars
      while ((c != '\0' && (c != '_'))) {
        if ((10 < charIndex) ||
           (((charVal = (int)c, 0x19 < charVal - 0x61U && (0x19 < charVal - 0x41U)) &&
            (9 < charVal - 0x30U)))) goto parseError;
        inputStr = inputStr + 1;
        *src = c;
        charIndex = charIndex + 1;
        src = src + 1;
        c = *inputStr;
      }
      if (*inputStr != '_') {
        // Expecting underscore after first segment
        goto checkSuccess;
      }
      *src = '_';
      char *p = inputStr;
      // Parse 8 hex digits after underscore
      while( true ) {
        char *next = p + 1;
        src = src + 1;
        if (next == inputStr + 8) break;
        c = *next;
        if ((c < '0') || ('9' < c)) {
          charVal = (int)c;
          int lower = charVal + 0x20;
          if (0x19 < charVal - 0x41U) {
            lower = charVal;
          }
          if (lower < 0x61) goto parseError;
          if (charVal - 0x41U < 0x1a) {
            charVal = charVal + 0x20;
          }
          if (0x66 < charVal) goto parseError;
        }
        *src = c;
        p = next;
      }
      char *afterSecondUnderscore = p + 2; // skip underscore after first 8-digit group
      if (*p != '_') goto checkSuccess;
      *src = '_';
      // Parse second 8-digit group
      for (; src = src + 1, afterSecondUnderscore != p + 9; afterSecondUnderscore = afterSecondUnderscore + 1) {
        c = *afterSecondUnderscore;
        if ((c < '0') || ('9' < c)) {
          charVal = (int)c;
          int lower = charVal + 0x20;
          if (0x19 < charVal - 0x41U) {
            lower = charVal;
          }
          if (lower < 0x61) {
parseError:
            result = handleParseError(); // FUN_004d8b80
            return result & 0xffffff00;
          }
          if (charVal - 0x41U < 0x1a) {
            charVal = charVal + 0x20;
          }
          if (0x66 < charVal) goto parseError;
        }
        *src = c;
      }
      if (*afterSecondUnderscore != '_') goto checkSuccess;
      *src = '_';
      // Expect "v3" suffix
      if (afterSecondUnderscore[1] != 'v') goto checkSuccess;
      src[2] = 'v';
      if (afterSecondUnderscore[2] != '3') goto checkSuccess;
      src[3] = '3';
      if (afterSecondUnderscore[3] == '\0') {
        src[4] = '\0';
        return (uint)(*node != '\x01'); // success if error flag not set
      }
      // If more characters after "v3", recursively parse child
      child = (char *)allocateNode(0x24); // FUN_009c8e50
      if (child == (char *)0x0) {
        child = (char *)0x0;
      }
      else {
        child[0x20] = '\0';
        child[0x21] = '\0';
        child[0x22] = '\0';
        child[0x23] = '\0';
        // Recursively parse the remainder after "v3"
        VersionNode::parseFromString(child, afterSecondUnderscore + 4);
      }
      *(char **)(node + 0x20) = child;
      if (*child == '\x01') goto checkSuccess;
      goto finish;
    }
  }
  // Cleanup on invalid input
  int childPtr = *(int *)(node + 0x20);
  *node = '\x01'; // set error flag
  if (childPtr != 0) {
    if (*(int *)(childPtr + 0x20) != 0) {
      freeChildren(1); // FUN_004d8bc0
    }
    deallocateNode(childPtr); // FUN_009c8eb0
  }
  node[0x20] = '\0';
  node[0x21] = '\0';
  node[0x22] = '\0';
  node[0x23] = '\0';
finish: // actually label is 0x004da51f
  return (uint)(*node != '\x01');
}