## What

(2024-10..)

Experimental library for serial console output.


## Details

Well, it's not too bad.

I love conception that Print() prints something standalone.
Integer surrounded by spaces, string occupies whole line.
Plus obligatory sign for signed integers. +000, yeah.

This class is not usable if you want to embed number like in "(000)".
We'll see soon how much places do really need printf() flexibility.

And it ignores floats. Floats are pain in the ass on AVR. Even printf()
does not support them. Only Serial.print() accepts them. But there's
no design and code is cursed.


## Sample output

```
[me_Console] Okay, we are here.
TUint_1( 000 127 255 )
TSint_1( -128 +000 +127 )
TUint_2( 00000 32767 65535 )
TSint_2( -32768 +00000 +32767 )
TUint_4( 0000000000 2147483647 4294967295 )
TSint_4( -2147483648 +0000000000 +2147483647 )
millis(): 0000000029 ms.
[me_Console] Done.
```

## Code

* [Example][Example]
* [Interface][Interface]
* [Implementation][Implementation]


## See also

* [My other embedded C++ libraries][Embedded]
* [My other repositories][Repos]

[Example]: examples/me_Console/me_Console.ino
[Interface]: src/me_Console.h
[Implementation]: src/me_Console.cpp
[Embedded]: https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts
[Repos]: https://github.com/martin-eden/contents
