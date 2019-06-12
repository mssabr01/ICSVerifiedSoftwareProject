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
    End:        "\r\n"
 *)
LOCAL PrintVal(id, exp)  ==  Print(<<id, exp>>, TRUE)
LOCAL notmod == <<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>
LOCAL ismod == <<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>

MAXMODBUSSIZE == 515 \*max modbus packet size
MINMODBUSSIZE == 9
\*Start ==================================================================
LOCAL IsStart(str) == str = ":"
\*ASSUME Print(IsStart(":"),TRUE)

\*Address fields =========================================================
LOCAL GetAddr(str) == SubSeq(str,2,3)

LOCAL IsAddr(str) == 
    /\ Len(str) = 2
    /\ Head(str) \in HexChar
    /\ Head(Tail(str)) \in HexChar
    
\*ASSUME Print(IsAddr(<<"E","0">>),TRUE)

\*Function fields ========================================================s
LOCAL GetFunct(str) == SubSeq(str,4,5)
LOCAL GetSubFunct(str) == SubSeq(str,6,7)
LOCAL IsSubFunct(code,subcode) == CASE code = <<"0","8">> ->    /\ StringToHex(Head(code)) \in 0..2
                                                                /\ StringToHex(Head(Tail(code))) \in 0..8
                                    [] OTHER -> /\ StringToHex(Head(code)) = 1
                                                /\ StringToHex(Head(Tail(code))) \in 3..4

LOCAL IsFunctionCode(str) ==    LET code == GetFunct(str)
                                IN  CASE code = <<"0","8">> -> IsSubFunct(code, GetSubFunct(str))
                                      [] code = <<"4","3">> -> IsSubFunct(code, GetSubFunct(str))
                                      [] OTHER ->   /\ Len(code) = 2
                                                    /\ Head(code) \in HexChar
                                                    /\ Head(Tail(code)) \in HexChar

ASSUME PrintVal(<<"function code:", IsFunctionCode(ismod)>>,TRUE)

\*Data ===================================================================
LOCAL GetData(str) == SubSeq(str,6,Len(str)-4)

LOCAL Range(T) == { T[x] : x \in DOMAIN T }

LOCAL IsData(str) == 
    /\ Len(str) \in 0..504
    /\ str = SelectSeq(str, LAMBDA x: x \in HexChar)
\*ASSUME Print(IsData(<<"1","1","0","3","0","0","6","B","0","0","0">>),TRUE)

\*End ====================================================================
LOCAL GetEnd(str) == SubSeq(str,Len(str)-1,Len(str))

LOCAL IsEnd(str) == str = <<"\r","\n">>

\*ASSUME Print(IsEnd(<<"\r","\n">>),TRUE)

\*LRC ====================================================================
LOCAL GetLRC(str) == SubSeq(str,Len(str)-5, Len(str)-4)

LOCAL IsLRC(str) == CheckLRC(str)
\*LRCInvariant == CheckLRC(start \o addr1 \o addr2 \o fc1 \o fc2 \o data \o end)

\*ASSUME Print(IsLRC(<<"F","4">>),TRUE)

\*The Whole Thing ========================================================

IsModbus(message) == 
    /\ Len(message) \in MINMODBUSSIZE..MAXMODBUSSIZE
    /\ IsStart(Head(message))
    /\ IsAddr(GetAddr(message))
    /\ IsFunctionCode(message)
    /\ IsData(GetData(message))
    /\ IsLRC(GetLRC(message))
    /\ IsEnd(GetEnd(message))

ModbusChar == {":", "\r", "\n", ""} \union HexChar

\*helper functions

IsWellformedModbus(message) ==
    /\ Len(message) \in MINMODBUSSIZE..MAXMODBUSSIZE
    /\ IsStart(Head(message))
    /\ IsEnd(GetEnd(message))

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
\* Last modified Tue Jun 11 20:35:57 EDT 2019 by mssabr01
\* Last modified Sun May 13 16:35:04 EDT 2018 by SabraouM
\* Created Thu Jan 18 14:33:25 EST 2018 by SabraouM
