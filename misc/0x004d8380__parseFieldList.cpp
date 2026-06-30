// FUNC_NAME: parseFieldList
// Parses a delimited list of tokens with parentheses grouping and quoted strings.
// param_1: pointer to the current position in the input string (advances past parsed portion)
// param_2: unused (maybe legacy parameter)
// param_3: if non-zero, trims whitespace inside tokens
// Returns 1 if a closing parenthesis at depth 1 was encountered, otherwise 0.

char parseFieldList(char** inputPtr, int unused, char trimWhitespace)
{
  char* cursor = *inputPtr;
  char currentChar = *cursor;
  int parenDepth = 0;
  char closedInnerGroup = '\0';
  bool inGroup = false;
  bool inQuotes = false;
  
  // The following fields manage a list of token buffers
  int tokenCount = 0;      // number of tokens collected so far
  int tokenCapacity = 0;   // current capacity of token array
  char* tokenArray = NULL; // pointer to array of token strings (each 16 bytes?)
  int local_10[3];         // temporary buffer for constructing a token in place
  code* callback;          // function pointer to process each token? (unused in decomp)
  
  // Initialize local buffer (unclear purpose)
  local_4 = 0; // actually local_4 is a code* not used later except in callback call
  
  if (currentChar == '\0')
    goto cleanup;
  
  char* prevChar = cursor - 1;
  char* tokenStart = cursor; // start of current token (after potential whitespace)
  
  while (true)
  {
    if (!inGroup && !inQuotes)
    {
      char* commaPos = NULL;
      char* tokenEnd = tokenStart;
      
      if (currentChar == '\"')
      {
        inQuotes = true;
        goto continueLoop;
      }
      
      if (currentChar == ',')
      {
        commaPos = prevChar;
        if (parenDepth == 1)
        {
          // Found a comma at depth 1: start a new token context
          if (commaPos != NULL)
          {
            tokenEnd = commaPos + 2;
            // Notify that we start a new token (maybe push to global buffer)
            FUN_004d3bc0(&DAT_00e2f044); // global stream or buffer
          }
          
          // Trim leading whitespace if requested
          if (tokenStart <= commaPos)
          {
            if (trimWhitespace == '\0')
            {
              if (tokenStart != commaPos)
              {
                do {
                  currentChar = *tokenStart;
                  if (((currentChar != ' ') && (currentChar != '\t')) && 
                      ((currentChar != '\n') && (currentChar != '\r')))
                  {
                    if (tokenStart == commaPos)
                      goto checkEnd;
                    else
                      goto findEndTrim;
                  }
                  tokenStart++;
                } while (tokenStart != commaPos);
                goto emptyToken;
              }
              goto checkEnd;
            }
            goto copyToken;
          }
          goto copyToken;
        }
        goto continueLoop;
      }
      
      if (currentChar == '(')
      {
        if (parenDepth == 0)
          tokenStart = prevChar + 2; // start token after the parenthesis
        parenDepth++;
        goto continueLoop;
      }
      
      if (currentChar == ')')
      {
        if (parenDepth == 0)
        {
          // Closing at top level: mark that we are inside a group
          inGroup = true;
        }
        else if (parenDepth == 1)
        {
          closedInnerGroup = '\x01';
          commaPos = prevChar;
          inGroup = true;
        }
        parenDepth--;
        goto checkComma;
      }
    }
    
    // If we get here, either inGroup or inQuotes or other character
    if (inGroup)
      goto endLoop;
    
  continueLoop:
    currentChar = cursor[1];
    cursor++;
    prevChar++;
    tokenStart = tokenEnd; // not actually, but tokenStart stays same unless changed above
    if (currentChar == '\0')
      break;
    continue;
    
  checkComma:
    // Handle comma at inner level after closing parenthesis
    if (commaPos != NULL)
    {
      tokenEnd = commaPos + 2;
      // Trim and copy token
      if (tokenStart <= commaPos)
      {
        // Similar trimming logic as above
        if (trimWhitespace == '\0')
        {
          // ... (same trimming)
        }
      }
    }
    goto copyToken;
    
  copyToken:
    // Copy token from tokenStart to tokenEnd into tokenArray
    // First, find end of token with whitespace trimming from end
    while (prevChar > tokenStart)
    {
      char c = *prevChar;
      if (((c != ' ') && (c != '\t')) && (c != '\n') && (c != '\r'))
        break;
      prevChar--;
    }
    
    if (tokenStart <= prevChar)
    {
      // Copy string with length (prevChar - tokenStart + 1)
      FUN_004d3f10(tokenStart, 0, prevChar + 1 - tokenStart);
    }
    
    // Resize token array if needed
    if (tokenCount == tokenCapacity)
    {
      int newCap = (tokenCapacity == 0) ? 1 : tokenCapacity * 2;
      FUN_00407880(newCap); // reallocate tokenArray
    }
    
    // Add new token entry (each entry is 16 bytes? So offset = tokenCount * 16)
    int entryOffset = tokenCount * 16;
    tokenCount++;
    
    if (entryOffset != 0) // always true after first token? but condition checks !=0
    {
      // Construct a temporary object in local_10
      FUN_004d3b50(local_10);
    }
    
    if (local_10[0] != 0)
    {
      // Call callback with the constructed object (unused in this decompilation)
      (*callback)(local_10[0]);
    }
    
    parenDepth = local_28; // restore depth from saved copy? Not clear
    // Actually local_28 holds the depth before increment/decrement
    // Continue processing rest of input
    goto continueLoop;
    
  emptyToken:
  checkEnd:
    // Handle empty token after trimming
    FUN_004d3f10(tokenStart, 0, (prevChar+1)-tokenStart);
    goto addEntry;
    
  endLoop:
    // If we saw a closing parenthesis at depth 1, finalize
    if (closedInnerGroup != '\0')
    {
      if ((tokenCount == 1) && (*(int*)(tokenArray + 4) == 0)) // check if single empty? 
      {
        FUN_004d8a00();
      }
      else
      {
        FUN_004d8a60(&tokenArray);
      }
      *inputPtr = cursor;
    }
    break;
  }
  
cleanup:
  FUN_00407430(); // cleanup function
  return closedInnerGroup;
}