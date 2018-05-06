-------------------------------- MODULE SendSSW --------------------------------

EXTENDS Sequences,
        Naturals,
        SSWPacket,
        TLC
        
LOCAL INSTANCE Hex
    WITH natValue <- 0, hexValue <- <<0>> 
MessagesFromSerialPort == 
    {isSSW,
     <<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>,
     <<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","F">>,
     <<":","J","G","P","9","4","3","2","J","3","9","J","G","W",":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","F">>,
     <<>>}

\*This algorithm didn't translate correctly. If I have time I'll break it down and post a bug report
(* (*--algorithm Transmit
variables   tx = FALSE,
            txBuf \in STRINGS,
            txReg = "", 
            txBufIndex = ""
begin
idle: if tx = TRUE
      then goto transmit;
      end if;
transmit:   if IsModbus(txBuf)
            then
            txBufIndex := Len(txBuf);
            \*empty the buffer into the register
            send: while txBufIndex > 0 do
                    a: txReg := txBuf[txBufIndex];
                    b: txBufIndex := txBufIndex - 1;
                end while;
            end if;
    t1:     tx := FALSE;
            goto idle;
                
end algorithm
*)*)
\* BEGIN TRANSLATION
VARIABLES tx, txBuf, txBufIndex, pc, txReg

vars == << tx, txBuf, txBufIndex, pc, txReg >>

Init == (* Global variables *)
        /\ tx \in BOOLEAN
        /\ txBuf \in MessagesFromSerialPort
        /\ txReg = ""
        /\ txBufIndex = 1
        /\ pc = "idle"

idle == /\ pc = "idle"
        /\ IF tx = TRUE
              THEN /\ pc' = "transmit"
              ELSE /\ pc' = "Done"
        /\ UNCHANGED << tx, txBuf, txBufIndex, txReg >>

transmit == /\ pc = "transmit"
            /\ IF IsSSW(txBuf)
                  THEN /\ pc' = "send"
                  ELSE /\ pc' = "t1"
            /\ UNCHANGED << tx, txBuf, txReg, txBufIndex >>

send == /\ pc = "send"
        /\ IF txBufIndex <= Len(txBuf)
              THEN /\ pc' = "a"
              ELSE /\ pc' = "t1"
        /\ UNCHANGED << tx, txBuf, txBufIndex, txReg >>

a == /\ pc = "a"
     /\ txReg' = txBuf[txBufIndex]
     /\ pc' = "b"
     /\ UNCHANGED << tx, txBuf, txBufIndex >>

b == /\ pc = "b"
     /\ txReg = txBuf[txBufIndex]
     /\ txBufIndex' = txBufIndex + 1
     /\ pc' = "send"
     /\ UNCHANGED << tx, txBuf, txReg >>

t1 == /\ pc = "t1"
      /\ txReg' = ""
      /\ tx' = FALSE
      /\ pc' = "Done"
      /\ UNCHANGED << txBuf, txBufIndex >>

Next == idle \/ transmit \/ send \/ a \/ b \/ t1
           \/ (* Disjunct to prevent deadlock on termination *)
              ( pc = "Done" /\ UNCHANGED vars)

Spec == Init /\ [][Next]_vars /\ WF_vars(Next)

Termination == <>(pc = "Done")

LIVELINESS ==
\* check that if valid modbus is in the buffer it gets sent
    /\ (tx = TRUE /\ IsSSW(txBuf)) ~> txBufIndex = Len(txBuf)+1
\*If there is something to send then it is alway sent
    /\ (tx = TRUE /\ IsSSW(txBuf)) ~> (txReg /= "")
\*If there is something to send, the flag is eventually reset
    /\(tx = TRUE) ~> (tx = FALSE)

SAFETYCHECK ==
\* The counter never goes above the buffer length+1
    /\ (txBufIndex <= Len(txBuf)+1)
\*Only valid modbus triggers the sending
    /\ txReg /= "" => IsSSW(txBuf)
\*Only valid SSW characters are sent
    \*/\ txReg \in HexChar \union {"!", ""} This doesn't work. SSW could contain anything in the message. Found in the 200th state

\* END TRANSLATION

=============================================================================
\* Modification History
\* Last modified Sun May 06 18:17:16 EDT 2018 by SabraouM
\* Created Fri May 04 22:08:30 EDT 2018 by SabraouM
