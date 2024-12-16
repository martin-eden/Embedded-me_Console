// Serial console interface

/*
  Author: Martin Eden
  Last mod.: 2024-12-15
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>

namespace me_Console
{
  /*
    Currently "console" is values printer to Serial.

    There are several design ideas.

    First idea is to keep granularity between values.
    So result from "Print(1); Print(2);" should not be the same
    as from "Print(12);".

    Second idea is raising level of abstraction for caller.
    As a user, I don't want to care how exactly number is formatted
    when printed. I just want to call "Print("millis()");
    Print(millis());" and see parseable result.

      Also I want inherent indentation. So when "foo()" does
      "Print("foo:"); Indent(); baz(); Unindent();" and
      "baz()" does "Print("baz!");", result is like

        foo:
          baz!

    Print() and Write()

    Print() is fire-and-forget. For argument it supports ints,
    memory segments and asciiz. They all be printed somehow,
    with indents and delimiters.

    Write() is a core data printer without delimiters between items.
    For argument it supports memory segment and asciiz.

    Useful when you printing several items on one line:

      // Produce "Time spent: 0000000029"
      Write("Time spent:");
      Print(millis());

    Float numbers are not supported, no need (yet?).

    Integer numbers are represented in decimal ASCII with leading
    zeroes. Signed integers always have "-" or "+" before value.
    Zero of signed type is represented with "+" sign.

    So "Print((TUint_2) 42)" will produce "00042".

    This allows us to parse integers back to original types.
    Also fixed-length numbers are neat when you need to estimate
    length of list of numbers.
  */

  /*
    Item type

    Used in detection what delimiter we should emit between two
    items.

    Can be "chunk", "line", "number" or "nothing".
  */
  enum TItemType
  {
    Chunk,
    Line,
    Number,
    Nothing
  };

  class TConsole
  {
    public:
      // ( Indents!

      // Increase indent
      void Indent();
      // Decrease indent
      void Unindent();

      // ) Indents!

      // ( Write data

      // Data is memory segment
      void Write(me_MemorySegment::TMemorySegment Data);
      // Data is ASCIIZ pointer
      void Write(const TAsciiz String);
      // Data is character
      void Write(TUnit Unit);
      // Data is segment in program memory
      void WriteFlash(me_MemorySegment::TMemorySegment Data);

      // ) Write

      // ( Print data on standalone line

      // Data is memory segment
      void Print(me_MemorySegment::TMemorySegment Data);
      // Data is ASCIIZ pointer
      void Print(const TAsciiz Asciiz);
      // Data is segment in program memory
      void PrintFlash(me_MemorySegment::TMemorySegment Data);

      // ) Print

      // Print newline if not on empty line
      void EndLine();

      // ( Custom printers for base types

      // Print TUint_1
      void Print(TUint_1 Uint_1);
      // Print TUint_2
      void Print(TUint_2 Uint_2);
      // Print TUint_4
      void Print(TUint_4 Uint_4);
      // Print TSint_1
      void Print(TSint_1 Sint_1);
      // Print TSint_2
      void Print(TSint_2 Sint_2);
      // Print TSint_4
      void Print(TSint_4 Sint_4);

      // ) Custom printers

    private:
      /*
        Internal mechanics to avoid double spaces and heading/trailing
        spaces in output.
      */
      // Last item type
      TItemType LastItemType = TItemType::Nothing;

      // Indentation level
      TUint_1 IndentLev = 0;

      // Print delimiter and maybe indent before item
      void PrintDelimiterBefore(TItemType CurItemType);
  };

  namespace Freetown
  {
    // Print indentation
    void PrintIndent(
      TUint_1 IndentLev,
      TItemType PrevItemType,
      TItemType CurItemType
    );

    // Print delimiter
    void PrintDelimiter(
      TItemType PrevItemType,
      TItemType CurItemType
    );

    // Print memory contents
    void PrintMem(me_MemorySegment::TMemorySegment);

    // Print program memory contents
    TBool PrintProgmem(me_MemorySegment::TMemorySegment);

    // Print unit
    void PrintUnit(TUnit Unit);
  }
}

/*
  Exported class instance for shared use

  Because you want to keep indentation in call chain of functions
  that are using this module.

  Assigned in "me_Console.cpp".
*/
extern me_Console::TConsole Console;

/*
  2024-10 ######
  2024-12-12
  2024-12-15
*/
