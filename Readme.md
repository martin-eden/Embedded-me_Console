## What

(2024, 2025)

Serial text input/output.


## Details

For me it started as experimental library and became base for all
text output.

You ask us to write values. You provide _what_.
_How_ do we write and separate values is not your business.

We'll cure your code of "\n" and side spaces infestation.

Also we have indents.


## Sample output

```
--
[me_Console] demo

(
  --
  Prints demo

  We'll show how values are represented for base types.
  We'll use indentation too.

  (
    TUint_1 ( 000 127 128 255 )
    TSint_1 ( +000 +127 -128 -001 )
    TUint_2 ( 00000 32767 32768 65535 )
    TSint_2 ( +00000 +32767 -32768 -00001 )
    TUint_4 ( 0000000000 2147483647 2147483648 4294967295 )
    TSint_4 ( +0000000000 +2147483647 -2147483648 -0000000001 )
    Program memory ( These characters are located in program memory )
    Program memory (via macro) ( These are in program memory too )
  )
  --
  Reading demo

  We'll read from input stream and try to parse to fixed type.

  (
    Enter integer [0, 255]
jh
    Reading TUint_1 failed
    Got 000
    Enter integer [0, 65535]
4589
    Got 04589
  )
) Done
```

## Code

* [Example][Example]
* [Interface][Interface]
* [Implementation][Implementation]


## Install/remove

Easy way is to clone [GetLibs][GetLibs] repo and run it's code.


## See also

* [My other embedded C++ libraries][Embedded]
* [My other repositories][Repos]


[me_CodecDecInt]: https://github.com/martin-eden/Embedded-me_CodecDecInt

[Example]: examples/me_Console/me_Console.ino
[Interface]: src/me_Console.h
[Implementation]: src/me_Console.cpp

[GetLibs]: https://github.com/martin-eden/Embedded-Framework-GetLibs

[Embedded]: https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts
[Repos]: https://github.com/martin-eden/contents
