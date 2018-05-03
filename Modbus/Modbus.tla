--------------------------- MODULE Modbus ---------------------------

\*The set of all Modbus messages for a given network
EXTENDS 
    Integers, 
    Hex, 
    Sequences,
    LRC
    
CONSTANT N \* number of hosts on the line 

--------------------------------------------------------------------------

(*  Start:      ":"
    Address:    two hex chars
    Function:   two hex chars
    Data:       0 up to 504 hex chars
    LRC:        two hex char Longitudinal Redundancy Check (LRC)
    End:        "CRLF"
 *)
 
\*Start ==================================================================
IsStart(str) == str = ":"
 
\*Address fields =========================================================
GetAddr(str) == SubSeq(str,2,3)

IsAddr(str) == 
    /\ Len(str) = 2
    /\ Head(str) \in HexChar
    /\ Head(Tail(str)) \in HexChar

\*Function fields ========================================================
GetFunct(str) == SubSeq(str,4,5)

IsFunctionCode(str) == 
    /\ Len(str) = 2
    /\ Head(str) \in HexChar
    /\ Head(Tail(str)) \in HexChar

\*Data ===================================================================
GetData(str) == SubSeq(str,6,Len(str)-3)

IsData(str) == 
    /\ Len(str) \in 0..504
    /\ str = [x \in DOMAIN str |-> x \in HexChar]

\*End ====================================================================
GetEnd(str) == SubSeq(str,Len(str),Len(str))

IsEnd(str) == str = "CRLF"


\*LRC ====================================================================
GetLRC(str) == SubSeq(str,Len(str)-2, Len(str)-1)

IsLRC(str) == CheckLRC(str)
\*LRCInvariant == CheckLRC(start \o addr1 \o addr2 \o fc1 \o fc2 \o data \o end)

\*The Whole Thing ========================================================

IsModbus(message) == 
    /\ Len(message) \in 9..513
    /\ IsStart(Head(message))
    /\ IsAddr(GetAddr(message))
    /\ IsFunctionCode(GetFunct(message))
    /\ IsData(GetData(message))
    /\ IsLRC(GetLRC(message))
    /\ IsEnd(GetEnd(message))
=============================================================================
\* Modification History
\* Last modified Wed May 02 20:55:29 EDT 2018 by SabraouM
\* Created Thu Jan 18 14:33:25 EST 2018 by SabraouM
