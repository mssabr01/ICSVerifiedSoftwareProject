------------------------------- MODULE ASCII -------------------------------
\* https://github.com/ahelwer/tla-experiments/blob/master/Hex.tla

LOCAL INSTANCE Naturals
LOCAL INSTANCE Sequences
LOCAL INSTANCE TLC


LOCAL PrintVal(id, exp)  ==  Print(<<id, exp>>, TRUE)

LOCAL ismod == <<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>

\*LOCAL usableASCII == " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^__abcdefghijklmnopqrstuvwxyz{|}~"
LOCAL usableASCII == <<" ","!","\"","#","$","%","&","'","(",")",
                     "*","+",",","-",".","/","0","1","2","3",
                     "4","5","6","7","8","9",":",";","<","=",
                     ">","?","@","A","B","C","D","E","F","G",
                     "H","I","J","K","L","M","N","O","P","Q",
                     "R","S","T","U","V","W","X","Y","Z","[",
                     "\\","]","^","_","_","a","b","c","d","e",
                     "f","g","h","i","j","k","l","m","n","o",
                     "p","q","r","s","t","u","v","w","x","y",
                     "z","{","|","}","~">>

CharToNum(char) == IF SelectSeq( usableASCII, LAMBDA y: y = char) /= <<>>
                   THEN 31 + CHOOSE i \in 1 .. 95 : usableASCII[i] = char
                   ELSE CASE char = "\t" -> 9 \*tab
                        []   char = "\r" -> 13
                        []   char = "\n" -> 10
                        []   char = "\f" -> 12 \*form feed
                        [] OTHER -> 0

RECURSIVE SeqToString(_)
SeqToString(ascii) ==
    IF ascii = <<>>
    THEN ""
    ELSE Head(ascii) \o SeqToString(Tail(ascii))

RECURSIVE StrToNumArray(_)
StrToNumArray(str) ==
    IF Len(str) = 0
    THEN <<>>
    ELSE <<CharToNum(Head(str))>> \o StrToNumArray(Tail(str))

IsUsableASCII(str) == str = SelectSeq(str, LAMBDA x: x \in usableASCII)

\*Tests
ASSUME PrintVal("ASCIIToString", SeqToString(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>) 
                                         = ":1103006B00037E\r\n")

ASSUME PrintVal("StrArrayToNumArray", StrToNumArray(ismod) = <<58, 49, 49, 48, 51, 48, 48, 54, 66, 48, 48, 48, 51, 55, 69, 13, 10>>)
                                    


=============================================================================
\* Modification History
\* Last modified Sat May 12 02:15:15 EDT 2018 by SabraouM
\* Created Thu May 10 13:34:02 EDT 2018 by SabraouM
