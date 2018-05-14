-------------------------------- MODULE SendModbus --------------------------------

EXTENDS Sequences,
        Naturals,
        Modbus,
        TLC
        
LOCAL INSTANCE Hex
    WITH natValue <- 0, hexValue <- <<0>> 
MessagesFromCryptoCell == 
    {<<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>,
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
VARIABLES tx, txBuf, txBufIndex, pc, txReg, message

vars == << tx, txBuf, txBufIndex, pc, txReg, message >>

Init == (* Global variables *)
        /\ tx \in BOOLEAN
        /\ message \in MessagesFromCryptoCell
        /\ txBuf = <<>>
        /\ txReg = ""
        /\ txBufIndex = 1
        /\ pc = "idle"

idle == /\ pc = "idle"
        /\ txBuf' = message
        /\ IF tx = TRUE
              THEN /\ pc' = "transmit"
              ELSE /\ pc' = "Done"
        /\ UNCHANGED << tx, txBufIndex, txReg, message >>

transmit == /\ pc = "transmit"
            /\ IF IsModbus(txBuf)
                  THEN /\ pc' = "send"
                  ELSE /\ pc' = "t1"
            /\ UNCHANGED << tx, txBuf, txReg, txBufIndex, message >>

send == /\ pc = "send"
        /\ IF Len(txBuf) > 1
              THEN /\ pc' = "a"
                   /\ txReg' = txReg
              ELSE /\ pc' = "t1"
                   /\ txReg' = Head(txBuf)
        /\ UNCHANGED << tx, txBuf, txBufIndex, message >>

a == /\ pc = "a"
     /\ txReg' = Head(txBuf)
     /\ txBuf' = Tail(txBuf)
     /\ pc' = "b"
     /\ UNCHANGED << tx, txBufIndex, message >>

b == /\ pc = "b"
     /\ txBufIndex' = txBufIndex + 1
     /\ pc' = "send"
     /\ UNCHANGED << tx, txBuf, txReg, message >>

t1 == /\ pc = "t1"
      /\ txReg' = ""
      /\ tx' = FALSE
      /\ pc' = "Done"
      /\ UNCHANGED << txBuf, txBufIndex, message >>

Next == idle \/ transmit \/ send \/ a \/ b \/ t1
           \/ (* Disjunct to prevent deadlock on termination *)
              ( pc = "Done" /\ UNCHANGED vars)

Spec == Init /\ [][Next]_vars /\ WF_vars(Next)

Termination == <>(pc = "Done")

LIVELINESS ==
\* check that if valid modbus is in the buffer it gets sent
    /\ (tx = TRUE /\ IsModbus(txBuf)) ~> Len(txBuf) = 0
\*If there is something to send then it is alway sent
    /\ (tx = TRUE /\ IsModbus(txBuf)) ~> (txReg /= "")
\*If there is something to send, the flag is eventually reset
    /\(tx = TRUE) ~> (tx = FALSE)

SAFETYCHECK ==
\*Only valid modbus triggers the sending
    /\ txReg /= "" => IsModbus(message)
\*Only valid modbus characters are sent
    /\ (txReg \in ModbusChar)

\* END TRANSLATION

=============================================================================
\* Modification History
\* Last modified Sun May 06 22:04:55 EDT 2018 by SabraouM
\* Created Fri May 04 22:08:30 EDT 2018 by SabraouM
