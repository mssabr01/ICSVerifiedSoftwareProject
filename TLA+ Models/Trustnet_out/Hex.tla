-------------------------------- MODULE Hex --------------------------------
\* https://github.com/ahelwer/tla-experiments/blob/master/Hex.tla

LOCAL INSTANCE Naturals
LOCAL INSTANCE Sequences
LOCAL INSTANCE TLC

VARIABLES 
    hexValue,
    natValue

----------------------------------------------------------------------------

RECURSIVE HighestMultipleLEQ(_, _, _)
HighestMultipleLEQ(a, b, current) ==
    LET next == current + 1 IN
    IF next * b > a
    THEN current
    ELSE HighestMultipleLEQ(a, b, next)

a / b == HighestMultipleLEQ(a, b, 0)

HexDigit == 0 .. 15

Hex == Seq(HexDigit)

HexChar ==
    {"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"}

StringToHex(x) ==
    CASE x = "0" -> 0
      [] x = "1" -> 1
      [] x = "2" -> 2
      [] x = "3" -> 3
      [] x = "4" -> 4
      [] x = "5" -> 5
      [] x = "6" -> 6
      [] x = "7" -> 7
      [] x = "8" -> 8
      [] x = "9" -> 9
      [] x = "A" -> 10
      [] x = "B" -> 11
      [] x = "C" -> 12
      [] x = "D" -> 13
      [] x = "E" -> 14
      [] x = "F" -> 15


FormatByteString(hex) ==
    IF Len(hex) = 1
    THEN "0" \o hex
    ELSE hex

RECURSIVE ASCIIHexToDecimal(_)
ASCIIHexToDecimal(str) ==
    IF str = <<>>
    THEN <<>>
    ELSE <<StringToHex(str[1])*16 + StringToHex(str[2])>> \o ASCIIHexToDecimal(Tail(Tail(str)))

RECURSIVE HexToString(_)
HexToString(hex) ==
    IF hex = <<>>
    THEN ""
    ELSE HexChar[Head(hex) + 1] \o HexToString(Tail(hex))

RECURSIVE NatToHex(_)
NatToHex(val) ==
    LET
        prefix == val / 16
        remainder == val % 16
    IN
    IF prefix = 0
    THEN <<remainder>>
    ELSE Append(NatToHex(prefix), remainder)

TypeInvariant ==
    /\ hexValue \in Hex
    /\ natValue \in Nat

SafetyInvariant ==
    /\ hexValue = NatToHex(natValue)

LOCAL Init ==
    /\ hexValue = <<0>>
    /\ natValue = 0

RECURSIVE IncrementedHexValue(_)
IncrementedHexValue(hex) ==
    LET
        prefix == SubSeq(hex, 1, Len(hex) - 1)
        last == hex[Len(hex)]
    IN
    IF hex = <<>>
    THEN <<1>>
    ELSE
        IF last < 15
        THEN Append(prefix, last + 1)
        ELSE Append(IncrementedHexValue(prefix), 0)

IsHex(str) == str = SelectSeq(str, LAMBDA x: x \in HexChar)                                     \*this set is empty

Increment ==
    /\ Print(HexToString(hexValue), TRUE)
    /\ Print(HexToString(NatToHex(natValue)), TRUE)
    /\ hexValue' = IncrementedHexValue(hexValue)
    /\ natValue' = natValue + 1

LOCAL Next ==
    \/ Increment

=============================================================================
\* Modification History
\* Last modified Wed Jun 12 13:30:13 EDT 2019 by mehdi
\* Last modified Mon May 07 19:32:58 EDT 2018 by SabraouM
\* Created Wed May 02 15:28:50 EDT 2018 by SabraouM
