// Printing integer types in decimal ASCII

/*
  Author: Martin Eden
  Last mod.: 2024-12-18
*/

/*
  Very boring code.

  We support six integer types:

    TUint_1  TSint_1
    TUint_2  TSint_2
    TUint_4  TSint_4

  We promised to provide overridden Print() for each of them.
*/

#include <me_Console.h>

#include <me_MemorySegment.h> // TMemorySegment
#include <me_String.h> // FormatUint_4(), FormatSint_4()

using namespace me_Console;

using
  me_MemorySegment::TMemorySegment,
  me_MemorySegment::Freetown::FromAddrSize,
  me_String::Freetown::FormatUint_4,
  me_String::Freetown::FormatSint_4;

/*
  4-bytes signed integer when represented as decimal can take
  11 bytes.

  So we need additional memory.

  We can't use heap allocations because heap allocators want to
  call us for printing. So we're asking compiler to allocate it
  on stack:

    {
      TUint_1 Buffer[11];
    }

  Then we're describing <Buffer> as memory segment and pass it
  to integers representer and then to printer.

  Code is mostly copy-pasted (what I hate to do).
*/

/*
  Print TUint_4
*/
void TConsole::Print(
  TUint_4 Value
)
{
  TItemType ItemType = TItemType::Number;

  PrintDelimiterBefore(ItemType);

  // Allocate fixed buffer and represent <Value> there. Print it
  {
    TUint_1 BuffSize = 10;
    TUint_1 Buff[BuffSize];
    TMemorySegment BuffSeg = FromAddrSize((TUint_2) &Buff, BuffSize);

    FormatUint_4(BuffSeg, Value);

    PutSegment(BuffSeg);
  }

  PrevItemType = ItemType;
}

/*
  Print TUint_2

  Same code as for TUint_4, but we're using smaller buffer.
*/
void TConsole::Print(
  TUint_2 Value
)
{
  TItemType ItemType = TItemType::Number;

  PrintDelimiterBefore(ItemType);

  {
    TUint_1 BuffSize = 5;
    TUint_1 Buff[BuffSize];
    TMemorySegment BuffSeg = FromAddrSize((TUint_2) &Buff, BuffSize);

    FormatUint_4(BuffSeg, (TUint_4) Value);

    PutSegment(BuffSeg);
  }

  PrevItemType = ItemType;
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

  {
    TUint_1 BuffSize = 3;
    TUint_1 Buff[BuffSize];
    TMemorySegment BuffSeg = FromAddrSize((TUint_2) &Buff, BuffSize);

    FormatUint_4(BuffSeg, (TUint_4) Value);

    PutSegment(BuffSeg);
  }

  PrevItemType = ItemType;
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

  {
    TUint_1 BuffSize = 11;
    TUint_1 Buff[BuffSize];
    TMemorySegment BuffSeg = FromAddrSize((TUint_2) &Buff, BuffSize);

    FormatSint_4(BuffSeg, Value);

    PutSegment(BuffSeg);
  }

  PrevItemType = ItemType;
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

  {
    TUint_1 BuffSize = 6;
    TUint_1 Buff[BuffSize];
    TMemorySegment BuffSeg = FromAddrSize((TUint_2) &Buff, BuffSize);

    FormatSint_4(BuffSeg, (TSint_4) Value);

    PutSegment(BuffSeg);
  }

  PrevItemType = ItemType;
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

  {
    TUint_1 BuffSize = 4;
    TUint_1 Buff[BuffSize];
    TMemorySegment BuffSeg = FromAddrSize((TUint_2) &Buff, BuffSize);

    FormatSint_4(BuffSeg, (TSint_4) Value);

    PutSegment(BuffSeg);
  }

  PrevItemType = ItemType;
}

/*
  2024-10-17
  2024-12-18
*/
