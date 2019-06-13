--------------------------- MODULE Modbus ---------------------------

\*The set of all Modbus messages for a given network
LOCAL INSTANCE Integers 
LOCAL INSTANCE Hex 
    WITH natValue <- 0, hexValue <- <<0>> 
LOCAL INSTANCE Sequences
LOCAL INSTANCE LRC
LOCAL INSTANCE ASCII
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

\*Modbus testing
LOCAL notmod == <<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>
LOCAL ismod  == <<":","1","1","0","8","1","6","0","0","6","B","0","0","0","3","7","E","\r","\n">>
LOCAL ismod1 == <<":","1","1","0","8","1","9","6","B","0","0","0","3","7","E","\r","\n">>
LOCAL ismod2 == <<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>

LOCAL ValidFunctionCodes == 0..8 \union {11,12,15,16,17,20,21,22,23,24,43}

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
\*TODO Update GetFunct to return sub function code if applicable
LOCAL GetFunct(str) == SubSeq(str,4,5)
LOCAL GetSubFunct(str) == SubSeq(str,6,7)
LOCAL IsSubFunct(code,subcode) == CASE code = <<"0","8">> -> StringToHex(Head(subcode)) * 16 + StringToHex(Head(Tail(subcode))) \in 0..18 \union {20}
                                    [] OTHER -> /\ StringToHex(Head(subcode)) = 1
                                                /\ StringToHex(Head(Tail(subcode))) \in 3..4

\*check if function code (and possibly subcode) is congruent with Modbus standard
LOCAL IsFunctionCode(str) ==    LET code == GetFunct(str)
                                IN  CASE code = <<"0","8">> -> IsSubFunct(code, GetSubFunct(str))
                                      [] code = <<"4","3">> -> IsSubFunct(code, GetSubFunct(str))
                                      [] OTHER ->   IF Head(code) \in HexChar /\ Head(Tail(code)) \in HexChar
                                                    THEN StringToHex(Head(code)) * 16 + StringToHex(Head(Tail(code))) \in ValidFunctionCodes
                                                    ELSE FALSE
                                                    
(*
ASSUME PrintVal(<<"function code:", IsFunctionCode(ismod1)>>,TRUE)
ASSUME PrintVal(<<"subfunction code:", GetSubFunct(ismod)>>,TRUE)
ASSUME PrintVal(<<"Is subfunction correct?", IsSubFunct(<<"4","3">>,<<"1","3">>)>>,TRUE)
*)
\*Data ===================================================================
\*Todo update getdata to work with subfunction codes
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
LOCAL GetLRC(str) == LET ascii == SubSeq(str,Len(str)-3, Len(str)-2)
                     IN StringToHex(ascii[1]) * 16 + StringToHex(ascii[2]) 

LOCAL IsLRC(str) == LET checkableMsg == ASCIIHexToDecimal(GetAddr(str) \o GetFunct(str) \o GetData(str))
                    IN CalculateLRC(checkableMsg) = GetLRC(str)

(*
ASSUME Print("Is lrc? should be tru",TRUE)
ASSUME Print(GetLRC(ismod2),TRUE)
ASSUME Print(CalculateLRC(
                    ASCIIHexToDecimal(GetAddr(ismod2) \o GetFunct(ismod2) \o GetData(ismod2))
             )
        ,TRUE)
ASSUME Print(IsLRC(ismod2),TRUE)
*)

\*The Whole Thing ========================================================

IsModbus(message) == 
    /\ Len(message) \in MINMODBUSSIZE..MAXMODBUSSIZE
    /\ IsStart(Head(message))
    /\ IsAddr(GetAddr(message))
    /\ IsFunctionCode(message)
    /\ IsData(GetData(message))
    /\ IsLRC(message)
    /\ IsEnd(GetEnd(message))

ModbusChar == {":", "\r", "\n", ""} \union HexChar

\*helper functions

IsWellformedModbus(message) ==
    /\ Len(message) \in MINMODBUSSIZE..MAXMODBUSSIZE
    /\ IsStart(Head(message))
    /\ IsEnd(GetEnd(message))

(*
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
*)
=============================================================================
\* Modification History
\* Last modified Thu Jun 13 12:27:59 EDT 2019 by mehdi
\* Last modified Tue Jun 11 20:35:57 EDT 2019 by mssabr01
\* Last modified Sun May 13 16:35:04 EDT 2018 by SabraouM
\* Created Thu Jan 18 14:33:25 EST 2018 by SabraouM
