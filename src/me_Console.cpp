// Serial console interface

/*
  Author: Martin Eden
  Last mod.: 2024-12-18
*/

#include "me_Console.h"

#include <me_BaseTypes.h>
#include <me_MemorySegment.h> // TMemorySegment, iterator
#include <me_FlashMemory.h> // ReadByte()
#include <me_Uart.h> // SendByte()
#include <me_WorkMemory.h> // SetByte()

using namespace me_Console;

using
  me_MemorySegment::TMemorySegment,
  me_MemorySegment::TSegmentIterator;

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
  using
    me_Console::Freetown::PrintDelimiter,
    me_Console::Freetown::PrintIndent;

  // Print closing delimiter for previous item
  PrintDelimiter(LastItemType, CurItemType);
  // Print indentation for current item
  PrintIndent(IndentLev, LastItemType, CurItemType);
}

/*
  Write memory segment contents
*/
void TConsole::Write(
  TMemorySegment MemSeg
)
{
  using
    me_Console::Freetown::PrintMem;

  TItemType ItemType = TItemType::Chunk;

  PrintDelimiterBefore(ItemType);

  PrintMem(MemSeg);

  LastItemType = ItemType;
}

/*
  Raw print of program memory contents
*/
void TConsole::WriteFlash(
  TMemorySegment FlashSeg
)
{
  using
    me_Console::Freetown::PrintProgmem;

  TItemType ItemType = TItemType::Chunk;

  PrintDelimiterBefore(ItemType);

  PrintProgmem(FlashSeg);

  LastItemType = ItemType;
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
  using
    me_Console::Freetown::PrintByte;

  TItemType ItemType = TItemType::Chunk;

  PrintDelimiterBefore(ItemType);

  PrintByte(Unit);

  LastItemType = ItemType;
}

/*
  Print memory segment
*/
void TConsole::Print(
  TMemorySegment MemSeg
)
{
  using
    me_Console::Freetown::PrintMem,
    me_Console::Freetown::PrintByte;

  PrintDelimiterBefore(TItemType::Line);

  PrintMem(MemSeg);
  PrintByte('\n');

  LastItemType = TItemType::Nothing;
}

/*
  Print segment from program memory
*/
void TConsole::PrintFlash(
  TMemorySegment FlashSeg
)
{
  using
    me_Console::Freetown::PrintProgmem,
    me_Console::Freetown::PrintByte;

  PrintDelimiterBefore(TItemType::Line);

  PrintProgmem(FlashSeg);
  PrintByte('\n');

  LastItemType = TItemType::Nothing;
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
  Print newline if not on empty line
*/
void TConsole::EndLine()
{
  using
    me_Console::Freetown::PrintDelimiter;

  if (LastItemType != TItemType::Nothing)
  {
    PrintDelimiter(LastItemType, TItemType::Line);
    LastItemType = TItemType::Nothing;
  }
}

TUint_2 TConsole::ReadSegment(
  me_MemorySegment::TMemorySegment Data
)
{
  return Freetown::ReadSegment(Data);
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
  using
    me_Console::Freetown::PrintByte;

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
    PrintByte(' ');
  else if (WriteNewline)
    PrintByte('\n');
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
  using
    me_Console::Freetown::PrintByte;

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
      PrintByte(' ');
      PrintByte(' ');
    }
  }
}

/*
  Print byte

  Surprisingly useful function when you want to isolate your output.
*/
void me_Console::Freetown::PrintByte(
  TUint_1 Byte
)
{
  me_Uart::SendByte(Byte);
}

/*
  Read byte
*/
TBool me_Console::Freetown::ReadByte(
  TUint_1 * Byte
)
{
  return me_Uart::GetByte(Byte);
}

/*
  Print memory segment contents
*/
void me_Console::Freetown::PrintMem(
  TMemorySegment MemSeg
)
{
  using
    me_WorkMemory::GetByte,
    me_Console::Freetown::PrintByte;

  TSegmentIterator Rator;
  TAddress Addr;
  TUint_1 Byte;

  if (!Rator.Init(MemSeg))
    return;

  while (Rator.GetNext(&Addr))
  {
    if (!GetByte(&Byte, Addr))
      return;

    PrintByte(Byte);
  }
}

/*
  Print segment of program memory
*/
TBool me_Console::Freetown::PrintProgmem(
  TMemorySegment FlashSeg
)
{
  using
    me_FlashMemory::GetByte,
    me_Console::Freetown::PrintByte;

  TSegmentIterator Rator;
  TAddress Addr;
  TUint_1 Byte;

  if (!Rator.Init(FlashSeg))
    return false;

  while (Rator.GetNext(&Addr))
  {
    if (!GetByte(&Byte, Addr))
      return false;

    PrintByte(Byte);
  }

  return true;
}

/*
  Read data into memory segment

  Maximum data that can be read is segment capacity.

  Returns number of units (bytes) read.

  This function is the opposite of PrintMemory().
  So there is no special treatment for space characters in data.
*/
TUint_2 me_Console::Freetown::ReadSegment(
  TMemorySegment Data
)
{
  using
    me_Uart::GetByte,
    me_WorkMemory::SetByte;

  me_MemorySegment::TSegmentIterator Rator;
  TAddress Addr;
  TUint_1 Byte;
  TUint_2 NumBytesProcessed = 0;

  Rator.Init(Data);

  while (Rator.GetNext(&Addr))
  {
    if (!GetByte(&Byte))
      break;

    if (!SetByte(Byte, Addr))
      break;

    ++NumBytesProcessed;
  }

  return NumBytesProcessed;
}

// ) Freetown

/*
  Assign instance to shared "extern" global
*/
me_Console::TConsole Console;

/*
  2024-10 ######
  2024-12-12
  2024-12-15
  2024-12-18
*/
