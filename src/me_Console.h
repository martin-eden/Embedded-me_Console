// Serial console interface

/*
  Author: Martin Eden
  Status: sketched
  Last mod.: 2024-10-08
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
    when printed. I just want to call "Print("millis");
    Print(millis());" and see parseable result.

      Also I want inherent indentation. So when "foo()" does
      "Print("foo:"); Indent(); baz(); Unindent();" and
      "baz()" does "Print("baz!");", result is like

        foo:
          baz!

    Problem is strings. Should "Print()" for strings produce standalone
    line or print on current line?

    Current approach is that Print() for strings prints on standalone
    line and Write() prints on current line. For numbers Print()
    prints on current line. And there is no Write() for numbers.
    That's ugly and unintuitive.

    Float numbers are not supported, no need (yet?).

    Integer numbers are represented in decimal ASCII with leading
    zeroes. Signed integers always have "-" or "+" before value.
    Zero of signed type is represented with "+" sign.

    So Print(42) may produce "042", "00042", "0000000042", "+042", ...

    This allows us to parse integers back to original types.
    Also fixed-length numbers are neat when you need to estimate
    length of list of numbers.
  */

  class TConsole
  {
    public:
      // Initialize UART to given speed
      TBool Init(TUint_4 SerialSpeed);

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
      void Write(const TChar * String);

      // ) Write

      // ( Print data on standalone line

      // Data is memory segment
      void Print(me_MemorySegment::TMemorySegment Data);
      // Data is ASCIIZ pointer
      void Print(const TChar * Asciiz);

      // ) Print

      // Print newline
      void Newline();

      // Print space
      void Space();

      // Print separation line
      void Line();

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

        Flag to emit Print()-specific delimiter (newline or space)
      */
      TBool NeedDelimiter;

      // Flag that current line is empty
      TBool LineIsEmpty;

      // Indentation level
      TUint_1 IndentLev;

      // Print space before number if needed
      void ApplyNumberNeeds();

      // Print newline before string if needed
      void ApplyStringNeeds();
  };

  namespace Freetown
  {
    // Print indentation
    void PrintIndent(TUint_1 IndentLev);
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
  2024-10-03
  2024-10-06
  2024-10-08
*/
