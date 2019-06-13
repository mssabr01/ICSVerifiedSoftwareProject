------------------------------- MODULE ASCII -------------------------------
\* https://github.com/ahelwer/tla-experiments/blob/master/Hex.tla

LOCAL INSTANCE Naturals
LOCAL INSTANCE Sequences
LOCAL INSTANCE TLC


LOCAL PrintVal(id, exp)  ==  Print(<<id, exp>>, TRUE)

LOCAL ismod == <<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>

\*LOCAL usableASCII == " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^__abcdefghijklmnopqrstuvwxyz{|}~"
usableASCII == <<" ","!","\"","#","$","%","&","'","(",")",
                     "*","+",",","-",".","/","0","1","2","3",
                     "4","5","6","7","8","9",":",";","<","=",
                     ">","?","@","A","B","C","D","E","F","G",
                     "H","I","J","K","L","M","N","O","P","Q",
                     "R","S","T","U","V","W","X","Y","Z","[",
                     "\\","]","^","_","_","a","b","c","d","e",
                     "f","g","h","i","j","k","l","m","n","o",
                     "p","q","r","s","t","u","v","w","x","y",
                     "z","{","|","}","~">>

LOCAL specialChars == {"\t","\r","\n","\f"}

LOCAL Range(T) == { T[x] : x \in DOMAIN T }

SetOfASCII == Range(usableASCII) \union specialChars

CharToNum(char) == IF char \in Range(usableASCII)
                   THEN 31 + CHOOSE i \in 1 .. 95 : usableASCII[i] = char
                   ELSE CASE char = "\t" -> 9 \*tab
                        []   char = "\r" -> 13
                        []   char = "\n" -> 10
                        []   char = "\f" -> 12 \*form feed
                        []   OTHER -> 0

NumToChar(num) == IF num \in 32..126 
                    THEN usableASCII[num-31]
                  ELSE CASE num = 9 -> "\t" \*tab
                        []   num = 13 -> "\r" \*carrage return
                        []   num = 10 -> "\n" \*line feed
                        []   num = 12 -> "\f" \*form feed
                        []   OTHER -> ""


NumTupleToStrTuple(numTuple) == [x \in DOMAIN numTuple |-> NumToChar(numTuple[x])]
    
RECURSIVE SeqToString(_)
SeqToString(ascii) ==
    IF ascii = <<>>
    THEN ""
    ELSE Head(ascii) \o SeqToString(Tail(ascii))

\*RECURSIVE StrTupleToNumTuple(_)
StrTupleToNumTuple(str) == [x \in DOMAIN str |-> CharToNum(str[x])]

IsUsableASCII(str) == str = SelectSeq(str, LAMBDA x: x \in SetOfASCII)

SanityCheck == usableASCII = NumTupleToStrTuple(StrTupleToNumTuple(usableASCII))

\*Tests

(*ASSUME PrintVal("ASCIIToString", SeqToString(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>) 
                                         = ":1103006B00037E\r\n")
ASSUME PrintVal("Range", Range(usableASCII))
ASSUME PrintVal("StrArrayToNumArray", StrTupleToNumTuple(ismod) = <<58, 49, 49, 48, 51, 48, 48, 54, 66, 48, 48, 48, 51, 55, 69, 13, 10>>)

ASSUME PrintVal("Sanity Check", SanityCheck)
*)

=============================================================================
\* Modification History
\* Last modified Wed Jun 12 13:21:22 EDT 2019 by mehdi
\* Last modified Mon May 14 12:45:14 EDT 2018 by SabraouM
\* Created Thu May 10 13:34:02 EDT 2018 by SabraouM
