// Serial console interface

/*
  Author: Martin Eden
  Last mod.: 2025-08-27
*/

#include <me_Console.h>

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>

using namespace me_Console;

/*
  Setup

  Sets output stream.
*/
void TConsole::Init()
{
  RawConsole.Init();
}

/*
  Increase indent

  Indent is increased up to certain limit.
*/
void TConsole::Indent()
{
  const TUint_1 MaxIndent = 50;

  if (IndentLev == MaxIndent)
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
  PrintDelimiter(CurItemType);
  // Print indentation for current item
  PrintIndent(CurItemType);
}

/*
  Write memory segment contents
*/
void TConsole::Write(
  TAddressSegment MemSeg
)
{
  TItemType ItemType = TItemType::Chunk;

  PrintDelimiterBefore(ItemType);

  RawConsole.SendSegment(MemSeg);

  PrevItemType = ItemType;
}

/*
  Raw print of program memory contents
*/
void TConsole::WriteProgmem(
  TAddressSegment ProgmemSeg
)
{
  TItemType ItemType = TItemType::Chunk;

  PrintDelimiterBefore(ItemType);

  RawConsole.SendProgmemSegment(ProgmemSeg);

  PrevItemType = ItemType;
}

/*
  Write string binary contents
*/
void TConsole::Write(
  const TAsciiz Asciiz
)
{
  using
    me_MemorySegment::Freetown::FromAsciiz;

  Write(FromAsciiz(Asciiz));
}

/*
  Write one character (size is one byte)
*/
void TConsole::Write(
  TUnit Unit
)
{
  TItemType ItemType = TItemType::Chunk;

  PrintDelimiterBefore(ItemType);

  RawConsole.SendByte(Unit);

  PrevItemType = ItemType;
}

/*
  Print memory segment
*/
void TConsole::Print(
  TAddressSegment AddrSeg
)
{
  PrintDelimiterBefore(TItemType::Line);

  RawConsole.SendSegment(AddrSeg);
  RawConsole.SendByte('\n');

  PrevItemType = TItemType::Nothing;
}

/*
  Print segment from program memory
*/
void TConsole::PrintProgmem(
  TAddressSegment ProgmemSeg
)
{
  PrintDelimiterBefore(TItemType::Line);

  RawConsole.SendProgmemSegment(ProgmemSeg);
  RawConsole.SendByte('\n');

  PrevItemType = TItemType::Nothing;
}

/*
  Print string on new line and newline
*/
void TConsole::Print(
  const TAsciiz Asciiz
)
{
  using
    me_MemorySegment::Freetown::FromAsciiz;

  Print(FromAsciiz(Asciiz));
}

/*
  Print boolean value
*/
void TConsole::Print(
  TBool IsTrue
)
{
  using
    me_MemorySegment::Freetown::FromAsciiz;

  PrintDelimiterBefore(TItemType::Number);

  if (IsTrue)
    RawConsole.SendSegment(FromAsciiz("YES"));
  else
    RawConsole.SendSegment(FromAsciiz("NO"));

  PrevItemType = TItemType::Number;
}


// Printers for integers are in separate file

/*
  Print newline if not on empty line
*/
void TConsole::EndLine()
{
  PrintDelimiter(TItemType::Line);
  PrevItemType = TItemType::Nothing;
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
void TConsole::PrintDelimiter(
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
    RawConsole.SendByte(' ');
  else if (WriteNewline)
    RawConsole.SendByte('\n');
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
void TConsole::PrintIndent(
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
    // Print indentation
    for (TUint_1 CurIndent = 0; CurIndent < IndentLev; ++CurIndent)
    {
      // Indent is two spaces
      RawConsole.SendByte(' ');
      RawConsole.SendByte(' ');
    }
  }
}

/*
  Assign instance to shared "extern" global
*/
me_Console::TConsole Console;

/*
  2024-10 # # # # # #
  2024-12 # # #
  2025-08-14
  2025-08-21
*/
