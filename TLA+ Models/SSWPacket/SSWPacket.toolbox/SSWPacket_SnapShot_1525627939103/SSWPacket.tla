----------------------------- MODULE SSWPacket -----------------------------

\*The definition of a SCADA Secure Wrap message
LOCAL INSTANCE Integers 
LOCAL INSTANCE Hex 
    WITH natValue <- 0, hexValue <- <<0>> 
LOCAL INSTANCE Sequences
LOCAL INSTANCE TLC

--------------------------------------------------------------------------

(*  Start:      "!"
    HMAC:       32 bytes of anything represented as 64 bytes of hex
    Message:    valid modbus (up to 515)
 *)

LOCAL PrintVal(id, exp)  ==  Print(<<id, exp>>, TRUE)
MINSSWSIZE == 74 \*1 start + 64 HMAC + 1 Message

\*Start ==================================================================
LOCAL IsStart(str) == str = "!" \*start with something that isn't hex so we can tell a new message from an HMAC
ASSUME PrintVal("Is this a start?", IsStart("!"))

\*Address fields =========================================================
LOCAL GetHMAC(str) == SubSeq(str,2,65)

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
GetMessage(str) == SubSeq(str,66,Len(str))

\*The Whole Thing ========================================================

IsSSW(message) == 
    /\ Len(message) >= MINSSWSIZE
    /\ IsStart(Head(message))
    /\ IsHMAC(GetHMAC(message))
    
LOCAL notSSW == <<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>
LOCAL notSSW2 == <<>>
LOCAL isSSW == <<"!","0","A","0","B","0","D","0","9","0","2","0","8","0","7","0","5","0","3","0","0","0","9","0","8","0",
                 "5","0","C","0","E","0","B","0","B","0","A","0","F","0","C","0","0","0","B","0","C","0","B","0","0","0",
                 "B","0","D","0","B","0","E","0","7","0","6","0","A",":","1","1","0","3","0","0","6","B","0","0","0","3",
                 "7","E","C","R","L","F">>
TYPEOK ==
  \*
  /\ PrintVal("The HMAC: ", GetHMAC(isSSW))
  /\ PrintVal("Is this SSW? ",IsSSW(notSSW))
  /\ PrintVal("Is this SSW? ",IsSSW(notSSW2))
  /\ PrintVal("Is this SSW? ",IsSSW(isSSW))


=============================================================================
\* Modification History
\* Last modified Sun May 06 13:32:00 EDT 2018 by SabraouM
\* Created Sun May 06 09:06:45 EDT 2018 by SabraouM
