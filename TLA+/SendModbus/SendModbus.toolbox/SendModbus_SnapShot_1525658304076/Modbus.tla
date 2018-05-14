--------------------------- MODULE Modbus ---------------------------

\*The set of all Modbus messages for a given network
LOCAL INSTANCE Integers 
LOCAL INSTANCE Hex 
    WITH natValue <- 0, hexValue <- <<0>> 
LOCAL INSTANCE Sequences
LOCAL INSTANCE LRC
LOCAL INSTANCE TLC

--------------------------------------------------------------------------

(*  Start:      ":"
    Address:    two hex chars
    Function:   two hex chars
    Data:       0 up to 504 hex chars
    LRC:        two hex char Longitudinal Redundancy Check (LRC)
    End:        "CRLF"
 *)

MAXMODBUSSIZE == 515 \*max modbus packet size
MINMODBUSSIZE == 9
\*Start ==================================================================
LOCAL IsStart(str) == str = ":"
ASSUME Print(IsStart(":"),TRUE)

\*Address fields =========================================================
LOCAL GetAddr(str) == SubSeq(str,2,3)

LOCAL IsAddr(str) == 
    /\ Len(str) = 2
    /\ Head(str) \in HexChar
    /\ Head(Tail(str)) \in HexChar
    
ASSUME Print(IsAddr(<<"E","0">>),TRUE)

\*Function fields ========================================================
LOCAL GetFunct(str) == SubSeq(str,4,5)

LOCAL IsFunctionCode(str) == 
    /\ Len(str) = 2
    /\ Head(str) \in HexChar
    /\ Head(Tail(str)) \in HexChar

ASSUME Print(IsFunctionCode(<<"E","0">>),TRUE)

\*Data ===================================================================
LOCAL GetData(str) == SubSeq(str,6,Len(str)-4)

LOCAL Range(T) == { T[x] : x \in DOMAIN T }

LOCAL IsData(str) == 
    /\ Len(str) \in 0..504
    /\ str = SelectSeq(str, LAMBDA x: x \in HexChar)
ASSUME Print(IsData(<<"1","1","0","3","0","0","6","B","0","0","0">>),TRUE)

\*End ====================================================================
LOCAL GetEnd(str) == SubSeq(str,Len(str)-3,Len(str))

LOCAL IsEnd(str) == str = <<"C","R","L","F">>

ASSUME Print(IsEnd(<<"C","R","L","F">>),TRUE)

\*LRC ====================================================================
LOCAL GetLRC(str) == SubSeq(str,Len(str)-5, Len(str)-4)

LOCAL IsLRC(str) == CheckLRC(str)
\*LRCInvariant == CheckLRC(start \o addr1 \o addr2 \o fc1 \o fc2 \o data \o end)

ASSUME Print(IsLRC(<<"F","4">>),TRUE)

\*The Whole Thing ========================================================

IsModbus(message) == 
    /\ Len(message) \in MINMODBUSSIZE..MAXMODBUSSIZE
    /\ IsStart(Head(message))
    /\ IsAddr(GetAddr(message))
    /\ IsFunctionCode(GetFunct(message))
    /\ IsData(GetData(message))
    /\ IsLRC(GetLRC(message))
    /\ IsEnd(GetEnd(message))

ModbusChar == {":", "C", "R", "L", "F", ""} \union HexChar
    
LOCAL notmod == <<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>
LOCAL ismod == <<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","F">>
ASSUME
  \*
  /\ Print(GetAddr(ismod),TRUE)
  /\ Print(GetFunct(ismod),TRUE)
  /\ Print(GetData(ismod),TRUE)
  /\ Print(GetLRC(ismod),TRUE)
  /\ Print(GetEnd(ismod),TRUE)
  /\ Print(IsModbus(notmod), TRUE)
  /\ Print(IsModbus(ismod), TRUE)
  \*/\ Print(IsModbus(<<"e","j","g","p","9","4","3","2","j","3","9","j","g","w","i","r","w">>), TRUE)
=============================================================================
\* Modification History
\* Last modified Sun May 06 11:52:43 EDT 2018 by SabraouM
\* Created Thu Jan 18 14:33:25 EST 2018 by SabraouM
