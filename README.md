# arduino-pio-vscode-bootstrap
Bootstrap code for arduino project with Platform.IO, done in vscode IDE.

## Note
This project is Win based, some tasks might not work. Another thing to note is that GDB path in tasks.json is hardcoded :)
## Goals
I just needed simple bootstrap for free and light IDE like vscode for Arduino. To make developing and debuging painless, by debugging I mean locally debugging same (almost) code with watchers and stepping through the code.
Another thing is JS-alike EventManager too keep actual project code maximally un-spagethized.

## Features
- Easy way to debug your code inside VSCode with GDB over code compiled with local MinGW.
- Code splited (in clumsy way) with Arduino only file (main.platform.h) and Debug only (main.debug.h) which provide for example easy way to emulate arduino.h package (which is actually done).
- JS Alike EventManager that can register multiple events packing any number of listeners both as static function and member function with passed context (this). This was made possible thanks to: ...
- Delegate Implementation included (http://www.codeproject.com/Articles/136799/Lightweight-Generic-C-Callbacks-or-Yet-Another-Del)
- Intervals implementation
- Make main() in debug run setup() loop() properly


### TO BE DONE:
- Sending signals of called arduino function to some tool visualizing it would be cool :)
