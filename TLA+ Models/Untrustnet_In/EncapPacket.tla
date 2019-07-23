----------------------------- MODULE EncapPacket -----------------------------

\*The definition of an enapsulated message
LOCAL INSTANCE Integers 
LOCAL INSTANCE Hex 
    WITH natValue <- 0, hexValue <- <<0>> 
LOCAL INSTANCE Sequences
LOCAL INSTANCE TLC
LOCAL INSTANCE Modbus

STARTCHAR == "!"
--------------------------------------------------------------------------

(*  Start:      "!"
    HMAC:       32 bytes of anything represented as 64 bytes of hex
    Message:    valid modbus (up to 515)
 *)

LOCAL PrintVal(id, exp)  ==  Print(<<id, exp>>, TRUE)
MINENCAPSIZE == 65+MINMODBUSSIZE \*1 start + 64 HMAC + min modbus
MAXENCAPSIZE == 65+MAXMODBUSSIZE

\*Start ==================================================================
LOCAL IsStart(str) == Head(str) = STARTCHAR \*start with something that isn't hex so we can tell a new message from an HMAC
\*ASSUME PrintVal("Is this a start?", IsStart("!"))

\*HMAC fields =========================================================
GetHMAC(str) == SubSeq(str,2,65)

LOCAL IsHMAC(str) == 
    /\ Len(str) = 64 \*these bytes can be anything so we are just checking length?
    /\ IsHex(str)    \*no - bytes are only hex: 00-0F
    

ASSUME PrintVal("Is this HMAC?", IsHMAC(<<"D","9","2","8","D","9","2","8",
                                          "7","5","3","0","7","5","3","0",
                                          "9","8","5","C","9","8","5","C",
                                          "E","B","B","A","E","B","B","A",
                                          "D","9","2","8","D","9","2","8",
                                          "7","5","3","0","7","5","3","0",
                                          "9","8","5","C","9","8","5","C",
                                          "E","B","B","A","E","B","B","A">>))
                                          
\*Data ===================================================================
GetModbus(str) == SubSeq(str, 66, Len(str))

\*The Whole Thing ========================================================

IsWellformedEncap(message) ==
    /\ Len(message) >= MINENCAPSIZE
    /\ Len(message) <= MAXENCAPSIZE
    /\ IsStart(message)
    /\ IsWellformedModbus(GetModbus(message))

notEncap == <<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>

isEncap == <<"!","0","A","0","B","0","D","0","9","0","2","0","8","0","7","0","5","0","3","0","0","0","9","0","8","0",
                 "5","0","C","0","E","0","B","0","B","0","A","0","F","0","C","0","0","0","B","0","C","0","B","0","0","0",
                 "B","0","D","0","B","0","E","0","7","0","6","0","A",":","1","1","0","3","0","0","6","B","0","0","0","3",
                 "7","E","\r","\n">>

(*
TYPEOK ==
  \*
  /\ PrintVal("The HMAC: ", GetHMAC(isEncap))
  /\ PrintVal("Is this SSW? ",IsWellformedEncap(isEncap))
  /\ PrintVal("Is this SSW? ",IsWellformedEncap(notEncap))
*)

=============================================================================
\* Modification History
\* Last modified Mon Jul 08 16:09:42 EDT 2019 by mehdi
\* Last modified Wed Jun 05 15:29:59 EDT 2019 by mssabr01
\* Last modified Mon May 14 11:23:11 EDT 2018 by SabraouM
\* Created Sun May 06 09:06:45 EDT 2018 by SabraouM
