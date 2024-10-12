// Serial console interface

/*
  Author: Martin Eden
  Last mod.: 2024-10-12
*/

#include "me_Console.h"

#include <me_BaseTypes.h>

#include <me_MemorySegment.h> // TMemorySegment
#include <me_String.h> // formatting to TMemorySegment

#include <HardwareSerial.h> // "Serial" for Init()

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

  LastItemType = TItemType::Nothing;
  IndentLev = 0;

  return true;
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

  // Non-empty items on new lines are starting with indent
  if (
    (
      (LastItemType == TItemType::Line) ||
      (LastItemType == TItemType::Nothing)
    ) &&
    (CurItemType != TItemType::Nothing)
  )
    Freetown::PrintIndent(IndentLev);
}

/*
  Write memory segment contents
*/
void TConsole::Write(
  TMemorySegment MemSeg
)
{
  TItemType ItemType;

  if (MemSeg.Size == 0)
    ItemType = Nothing;
  else
    ItemType = Chunk;

  PrintDelimiterBefore(ItemType);

  Freetown::PrintMem(MemSeg);

  LastItemType = ItemType;
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

  Freetown::PrintMem(MemSeg);
  Freetown::PrintChar('\n');

  LastItemType = TItemType::Nothing;
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
void TConsole::EndLine()
{
  if (LastItemType != TItemType::Nothing)
    PrintDelimiterBefore(TItemType::Line);

  LastItemType = TItemType::Nothing;
}

/*
  Print TUint_1
*/
void TConsole::Print(
  TUint_1 Value
)
{
  TItemType ItemType = TItemType::Number;

  PrintDelimiterBefore(ItemType);

  me_String::TString Str;
  Str.Format(Value);
  Freetown::PrintMem(Str.GetData());

  LastItemType = ItemType;
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
  TItemType ItemType = TItemType::Number;

  PrintDelimiterBefore(ItemType);

  me_String::TString Str;
  Str.Format(Value);
  Freetown::PrintMem(Str.GetData());

  LastItemType = ItemType;
}

/*
  Print TUint_4
*/
void TConsole::Print(
  TUint_4 Value
)
{
  TItemType ItemType = TItemType::Number;

  PrintDelimiterBefore(ItemType);

  me_String::TString Str;
  Str.Format(Value);
  Freetown::PrintMem(Str.GetData());

  LastItemType = ItemType;
}

/*
  Print TSint_1
*/
void TConsole::Print(
  TSint_1 Value
)
{
  TItemType ItemType = TItemType::Number;

  PrintDelimiterBefore(ItemType);

  me_String::TString Str;
  Str.Format(Value);
  Freetown::PrintMem(Str.GetData());

  LastItemType = ItemType;
}

/*
  Print TSint_2
*/
void TConsole::Print(
  TSint_2 Value
)
{
  TItemType ItemType = TItemType::Number;

  PrintDelimiterBefore(ItemType);

  me_String::TString Str;
  Str.Format(Value);
  Freetown::PrintMem(Str.GetData());

  LastItemType = ItemType;
}

/*
  Print TSint_4
*/
void TConsole::Print(
  TSint_4 Value
)
{
  TItemType ItemType = TItemType::Number;

  PrintDelimiterBefore(ItemType);

  me_String::TString Str;
  Str.Format(Value);
  Freetown::PrintMem(Str.GetData());

  LastItemType = ItemType;
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
    Serial.write("  ");
}

/*
  Print delimiter

  Delimiter depends of previous and current item types.

   Next > | Chunk Line Number Nothing
  --Prev--+----------------------------
  Chunk   | ""    \n   " "    ""
  Line    | \n    \n   \n     \n
  Number  | " "   \n   " "    ""
  Nothing | ""    ""   ""     ""
*/
void me_Console::Freetown::PrintDelimiter(
  TItemType PrevItemType,
  TItemType CurItemType
)
{
  TBool WriteNothing = false;
  TBool WriteSpace = false;
  TBool WriteNewline = false;

  if (PrevItemType == Chunk)
  {
    if (CurItemType == Chunk)
      WriteNothing = true;
    else if (CurItemType == Line)
      WriteNewline = true;
    else if (CurItemType == Number)
      WriteSpace = true;
    else if (CurItemType == Nothing)
      WriteNothing = true;
  }
  else if (PrevItemType == Line)
  {
    if (CurItemType == Chunk)
      WriteNewline = true;
    else if (CurItemType == Line)
      WriteNewline = true;
    else if (CurItemType == Number)
      WriteNewline = true;
    else if (CurItemType == Nothing)
      WriteNewline = true;
  }
  else if (PrevItemType == Number)
  {
    if (CurItemType == Chunk)
      WriteSpace = true;
    else if (CurItemType == Line)
      WriteNewline = true;
    else if (CurItemType == Number)
      WriteSpace = true;
    else if (CurItemType == Nothing)
      WriteNothing = true;
  }
  else if (PrevItemType == Nothing)
  {
    if (CurItemType == Chunk)
      WriteNothing = true;
    else if (CurItemType == Line)
      WriteNothing = true;
    else if (CurItemType == Number)
      WriteNothing = true;
    else if (CurItemType == Nothing)
      WriteNothing = true;
  }

  if (WriteNothing)
    ;
  else if (WriteSpace)
    Freetown::PrintChar(' ');
  else if (WriteNewline)
    Freetown::PrintChar('\n');
}

/*
  Print memory segment contents
*/
void me_Console::Freetown::PrintMem(
  TMemorySegment MemSeg
)
{
  for (TUint_2 Offset = 0; Offset < MemSeg.Size; ++Offset)
    Freetown::PrintChar(MemSeg.Bytes[Offset]);
}

/*
  Print character

  Surprisingly useful function when you want to isolate your output.
*/
void me_Console::Freetown::PrintChar(TChar Char)
{
  Serial.write(Char);
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
  2024-10-10
*/
