# Caesar Cipher (C++)

## Usage:
```caesar```<br>
```caesar <-h/-help/h/help>```<br>
```caesar <-f/-file/f/file> <filename> <conversion> <key/all>```<br>

If no argument is given, the program will prompt the user for text.
If the flag `-f` and a file name is given, the program will read the text from the file.

The conversion argument can be:<br>
for Caesar encryption: `-c` `-caesar` `c` `caesar`<br>
for Vigenere encryption: `-v` `-vigenere` `v` `vigenere`<br>
for Caesar decryption: `-d` `-decrypt` `d` `decrypt`<br>

For Caesar encryption, the key must be an integer.
For Vigenere encryption, the key must be a string of alphabetic characters.

For Caesar decryption, to show all results provide either `-a`, `-all`, `a` or `all` as a flag. 
Otherwise, to not show all results, do not provide any flags.

The program will then carry out the conversion and output the result.
