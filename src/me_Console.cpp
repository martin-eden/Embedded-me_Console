// Serial console interface

/*
  Author: Martin Eden
  Status: sketching
  Last mod.: 2024-10-08
*/

#include "me_Console.h"

#include <me_BaseTypes.h>
#include <me_InstallStandardStreams.h> // make printf() work
#include <me_MemorySegment.h> // TMemorySegment
#include <me_String.h> // formatting to TMemorySegment

#include <HardwareSerial.h> // "Serial" for Init()
#include <stdio.h> // printf()

using namespace me_Console;

using
  me_MemorySegment::TMemorySegment;

/*
  Setup console with serial speed
*/
TBool TConsole::Init(
  TUint_4 SerialSpeed
)
{
  Serial.begin(SerialSpeed);
  InstallStandardStreams();

  LastItemType = TItemType::Chunk;
  IndentLev = 0;

  return true;
}

/*
  Flushing destructor
*/
TConsole::~TConsole()
{
  Flush();

  Serial.end();
}

/*
  Write pending delimiter for last item
*/
void TConsole::Flush()
{
  PrintDelimiterBefore(TItemType::Chunk);
}

// Max byte value. I need to move such lame constants somewhere
const TUint_1 Max_Uint_1 = 0xFF;

/*
  Increase indent

  Indent is increased up to certain hardcoded limit.
*/
void TConsole::Indent()
{
  if (IndentLev == Max_Uint_1)
    return;

  ++IndentLev;
}

/*
  Decrease indent

  Zero indent is not decreasing.
*/
void TConsole::Unindent()
{
  if (IndentLev == 0)
    return;

  --IndentLev;
}

/*
  [Internal] Print delimiter and maybe indent
*/
void TConsole::PrintDelimiterBefore(
  TItemType CurItemType
)
{
  // Print closing delimiter for previous item
  Freetown::PrintDelimiter(LastItemType, CurItemType);

  // New lines are starting with indent
  if (
    (LastItemType == TItemType::Line) ||
    (CurItemType == TItemType::Line)
  )
  {
    Freetown::PrintIndent(IndentLev);
  }

  // Set last item type to this one
  LastItemType = CurItemType;
}

/*
  Write memory segment contents
*/
void TConsole::Write(
  TMemorySegment MemSeg
)
{
  PrintDelimiterBefore(TItemType::Chunk);

  me_MemorySegment::Freetown::Print(MemSeg);
}

/*
  Write string binary contents
*/
void TConsole::Write(
  const TChar * Asciiz
)
{
  Write(me_MemorySegment::Freetown::FromAsciiz(Asciiz));
}

/*
  Print memory segment
*/
void TConsole::Print(
  TMemorySegment MemSeg
)
{
  PrintDelimiterBefore(TItemType::Line);

  me_MemorySegment::Freetown::Print(MemSeg);
}

/*
  Print string on new line and newline
*/
void TConsole::Print(
  const TChar * Asciiz
)
{
  Print(me_MemorySegment::Freetown::FromAsciiz(Asciiz));
}

/*
  Print newline next time
*/
void TConsole::Newline()
{
  LastItemType = TItemType::Line;
}

/*
  Print separation line

  Current implementation prints "--".
*/
void TConsole::Line()
{
  Print("--");
}

/*
  Print TUint_1
*/
void TConsole::Print(
  TUint_1 Value
)
{
  PrintDelimiterBefore(TItemType::Number);

  me_String::TString Str;
  Str.Format(Value);
  me_MemorySegment::Freetown::Print(Str.GetData());
}

/*
  Print TUint_2
*/
void TConsole::Print(
  TUint_2 Value
)
{
  /*
    Same code, but Format() is overridden and so different
    function is called.
  */
  PrintDelimiterBefore(TItemType::Number);

  me_String::TString Str;
  Str.Format(Value);
  me_MemorySegment::Freetown::Print(Str.GetData());
}

/*
  Print TUint_4
*/
void TConsole::Print(
  TUint_4 Value
)
{
  PrintDelimiterBefore(TItemType::Number);

  me_String::TString Str;
  Str.Format(Value);
  me_MemorySegment::Freetown::Print(Str.GetData());
}

/*
  Print TSint_1
*/
void TConsole::Print(
  TSint_1 Value
)
{
  PrintDelimiterBefore(TItemType::Number);

  me_String::TString Str;
  Str.Format(Value);
  me_MemorySegment::Freetown::Print(Str.GetData());
}

/*
  Print TSint_2
*/
void TConsole::Print(
  TSint_2 Value
)
{
  PrintDelimiterBefore(TItemType::Number);

  me_String::TString Str;
  Str.Format(Value);
  me_MemorySegment::Freetown::Print(Str.GetData());
}

/*
  Print TSint_4
*/
void TConsole::Print(
  TSint_4 Value
)
{
  PrintDelimiterBefore(TItemType::Number);

  me_String::TString Str;
  Str.Format(Value);
  me_MemorySegment::Freetown::Print(Str.GetData());
}

// ( Freetown

/*
  Print indentation
*/
void me_Console::Freetown::PrintIndent(
  TUint_1 IndentLev
)
{
  for (TUint_1 CurIndent = 0; CurIndent < IndentLev; ++CurIndent)
    printf("  ");
}

/*
  Print delimiter

  Delimiter depends of previous and current item types.

   2nd > Chunk Line Number
  1st
  Chunk  ""    \n    ""
  Line   \n    \n    \n
  Number ""    \n    " "
*/
void me_Console::Freetown::PrintDelimiter(
  TItemType PrevItemType,
  TItemType CurItemType
)
{
  if (PrevItemType == Chunk)
  {
    // No delimiters between chunks
    if (CurItemType == Chunk)
      ;
    // Heading newline
    else if (CurItemType == Line)
      printf("\n");
    // No delimiter between chunk and number
    else if (CurItemType == Number)
    {
      ;
    }
  }
  else if (PrevItemType == Line)
  {
    // Tail newline
    if (CurItemType == Chunk)
      printf("\n");
    // Lines are separated by newlines
    else if (CurItemType == Line)
      printf("\n");
    // Tail newline
    else if (CurItemType == Number)
      printf("\n");
  }
  else if (PrevItemType == Number)
  {
    // No delimiter between number and chunk
    if (CurItemType == Chunk)
      ;
    // Heading newline
    else if (CurItemType == Line)
      printf("\n");
    // Numbers are separated by spaces
    else if (CurItemType == Number)
      printf(" ");
  }
}

// ) Freetown

/*
  Assign instance to shared "extern" global
*/
me_Console::TConsole Console;

/*
  2024-10-03
  2024-10-06
  2024-10-08
*/
