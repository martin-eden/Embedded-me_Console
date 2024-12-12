// Serial console interface

/*
  Author: Martin Eden
  Last mod.: 2024-12-12
*/

#include "me_Console.h"

#include <me_BaseTypes.h>
#include <me_MemorySegment.h> // TMemorySegment
#include <me_Uart.h>

using namespace me_Console;

using
  me_MemorySegment::TMemorySegment;

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
  // Print indentation for current item
  Freetown::PrintIndent(IndentLev, LastItemType, CurItemType);
}

/*
  Write memory segment contents
*/
void TConsole::Write(
  TMemorySegment MemSeg
)
{
  TItemType ItemType = TItemType::Chunk;

  PrintDelimiterBefore(ItemType);

  Freetown::PrintMem(MemSeg);

  LastItemType = ItemType;
}

/*
  Write string binary contents
*/
void TConsole::Write(
  const TAsciiz Asciiz
)
{
  Write(me_MemorySegment::Freetown::FromAsciiz(Asciiz));
}

/*
  Write one character (size is one byte)
*/
void TConsole::Write(
  TUint_1 Byte
)
{
  TItemType ItemType = TItemType::Chunk;

  PrintDelimiterBefore(ItemType);

  Freetown::PrintUnit(Byte);

  LastItemType = ItemType;
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
  Freetown::PrintUnit('\n');

  LastItemType = TItemType::Nothing;
}

/*
  Print string on new line and newline
*/
void TConsole::Print(
  const TAsciiz Asciiz
)
{
  Print(me_MemorySegment::Freetown::FromAsciiz(Asciiz));
}

/*
  Print newline if not on empty line
*/
void TConsole::EndLine()
{
  if (LastItemType != TItemType::Nothing)
  {
    Freetown::PrintDelimiter(LastItemType, TItemType::Line);
    LastItemType = TItemType::Nothing;
  }
}


/*
  Print()'s for TUint_1, ..., TSint_4 are in "NumberPrinting.cpp".
*/

// ( Freetown

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
    Freetown::PrintUnit(' ');
  else if (WriteNewline)
    Freetown::PrintUnit('\n');
}

/*
  Print indentation

  Same as for PrintDelimiter(), whether or not print indentation
  depends of types of adjacent items:

   Next > | Chunk Line Number Nothing
  --Prev--+----------------------------
  Chunk   |   -     +     -      -
  Line    |   +     +     +      -
  Number  |   -     +     -      -
  Nothing |   +     +     +      -

*/
void me_Console::Freetown::PrintIndent(
  TUint_1 IndentLev,
  TItemType PrevItemType,
  TItemType CurItemType
)
{
  TBool DoIt = false;

  {
    if (PrevItemType == Chunk)
    {
      if (CurItemType == Chunk)
        DoIt = false;
      else if (CurItemType == Line)
        DoIt = true;
      else if (CurItemType == Number)
        DoIt = false;
      else if (CurItemType == Nothing)
        DoIt = false;
    }
    else if (PrevItemType == Line)
    {
      if (CurItemType == Chunk)
        DoIt = true;
      else if (CurItemType == Line)
        DoIt = true;
      else if (CurItemType == Number)
        DoIt = true;
      else if (CurItemType == Nothing)
        DoIt = false;
    }
    else if (PrevItemType == Number)
    {
      if (CurItemType == Chunk)
        DoIt = false;
      else if (CurItemType == Line)
        DoIt = true;
      else if (CurItemType == Number)
        DoIt = false;
      else if (CurItemType == Nothing)
        DoIt = false;
    }
    else if (PrevItemType == Nothing)
    {
      if (CurItemType == Chunk)
        DoIt = true;
      else if (CurItemType == Line)
        DoIt = true;
      else if (CurItemType == Number)
        DoIt = true;
      else if (CurItemType == Nothing)
        DoIt = false;
    }
  }

  if (DoIt)
  {
    for (TUint_1 CurIndent = 0; CurIndent < IndentLev; ++CurIndent)
    {
      Freetown::PrintUnit(' ');
      Freetown::PrintUnit(' ');
    }
  }
}

/*
  Print memory segment contents
*/
void me_Console::Freetown::PrintMem(
  TMemorySegment MemSeg
)
{
  for (TUint_2 Offset = 0; Offset < MemSeg.Size; ++Offset)
    Freetown::PrintUnit(MemSeg.Bytes[Offset]);
}

/*
  Print character

  Surprisingly useful function when you want to isolate your output.
*/
void me_Console::Freetown::PrintUnit(
  TUnit Unit
)
{
  me_Uart::SendByte(Unit);
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
  2024-10-17
  2024-10-18
  2024-12-12
*/
