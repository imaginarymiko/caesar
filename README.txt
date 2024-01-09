Caesar Cipher (C++)

Usage:
    ./caesar
    ./caesar <-h/-help/h/help>
    ./caesar <-f/-file/f/file> <filename> <conversion> <key/all>

    If no argument is given, the program will prompt the user for text.
    If the flag -f and a file name is given, the program will read the text from the file.

    The conversion argument can be:
        for Caesar encryption: '-c' '-caesar' 'c' 'caesar'
        for Vigenere encryption: '-v' '-vigenere' 'v' 'vigenere'
        for Caesar decryption: '-d' '-decrypt' 'd' 'decrypt'
    
    For Caesar encryption, the key must be an integer.
    For Vigenere encryption, the key must be a string of alphabetic characters.
    
    For Caesar decryption, to show all results provide either '-a', '-all', 'a' or 'all' as a flag. 
    Otherwise, to not show all results, do not provide any flags.

    The program will then carry out the conversion and output the result.
