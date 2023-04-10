# termDisplay
Basic ascii terminal display library, similar to ncurses

It is linux only as it defines its getch function using termios.h, a more universal version of the library is in the works, (though it probably wont have the getch function)

## Installation
It is highly recommended to compile the library yourself as the static library provided was compiled on arch linux, which is bleeding edge and so it has a high chance of not being compatible with your system.

After that, just link the library into your binary and include the header file found in src/termDisplay
