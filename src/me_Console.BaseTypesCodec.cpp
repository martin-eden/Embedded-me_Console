// Reading/writing subset of base types

/*
  Author: Martin Eden
  Last mod.: 2025-09-23
*/

#include <me_Console.h>

#include <me_BaseTypes.h>
#include <me_ReadInteger.h>
#include <me_WriteInteger.h>
#include <me_WorkmemTools.h>
#include <me_StreamTokenizer.h>

using namespace me_Console;

// Read TUint_1
TBool TConsole::Read(
  TUint_1 * Uint_1
)
{
  return me_ReadInteger::Read_TUint_1(Uint_1, InputStream);
}

// Print TUint_1
void TConsole::Print(
  TUint_1 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_WriteInteger::Write_U1(Value, OutputStream);
  PrevItemType = ItemType;
}

// Read TUint_2
TBool TConsole::Read(
  TUint_2 * Uint_2
)
{
  return me_ReadInteger::Read_TUint_2(Uint_2, InputStream);
}

// Print TUint_2
void TConsole::Print(
  TUint_2 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_WriteInteger::Write_U2(Value, OutputStream);
  PrevItemType = ItemType;
}

// Print TUint_4
void TConsole::Print(
  TUint_4 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_WriteInteger::Write_U4(Value, OutputStream);
  PrevItemType = ItemType;
}

// Print TSint_1
void TConsole::Print(
  TSint_1 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_WriteInteger::Write_S1(Value, OutputStream);
  PrevItemType = ItemType;
}

// Print TSint_2
void TConsole::Print(
  TSint_2 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_WriteInteger::Write_S2(Value, OutputStream);
  PrevItemType = ItemType;
}

// Print TSint_4
void TConsole::Print(
  TSint_4 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_WriteInteger::Write_S4(Value, OutputStream);
  PrevItemType = ItemType;
}

// Print TBool
void TConsole::Print(
  TBool IsTrue
)
{
  PrintDelimiterBefore(TItemType::Number);

  if (IsTrue)
    SendSegment(me_WorkmemTools::FromAsciiz("YES"));
  else
    SendSegment(me_WorkmemTools::FromAsciiz(" NO"));

  PrevItemType = TItemType::Number;
}

// Read TBool
TBool TConsole::Read(
  TBool * Bool
)
{
  const TAddressSegment
    TrueValue = me_WorkmemTools::FromAsciiz("YES"),
    FalseValue = me_WorkmemTools::FromAsciiz("NO");

  const TUint_1 BufferSize = 4;
  TUint_1 Buffer[BufferSize];
  TAddressSegment BuffSeg;
  me_StreamsCollection::TWorkmemOutputStream BuffStream;
  TAddressSegment DataSeg;

  BuffSeg = { .Addr = (TAddress) &Buffer, .Size = BufferSize };

  BuffStream.Init(BuffSeg);

  if (!me_StreamTokenizer::GetEntity(&BuffStream, InputStream))
    return false;

  DataSeg = BuffStream.GetProcessedSegment();

  if (me_WorkmemTools::AreEqual(DataSeg, TrueValue))
    *Bool = true;
  else if (me_WorkmemTools::AreEqual(DataSeg, FalseValue))
    *Bool = false;
  else
    return false;

  return true;
}

/*
  2024 # # #
  2025 # #
  2025-09-01
  2025-09-12
  2025-09-23
*/
