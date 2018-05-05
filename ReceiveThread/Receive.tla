--------------------------- MODULE Receive ---------------------------

EXTENDS Sequences,
        Naturals,
        Modbus
        
LOCAL INSTANCE Hex
    WITH natValue <- 0, hexValue <- <<0>> 
MessagesFromSerialPort == 
    {<<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>,
     <<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","F">>,
     <<>>}

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
        /\ tx = TRUE
        /\ txBuf \in MessagesFromSerialPort
        /\ txReg = ""
        /\ txBufIndex = 0
        /\ pc = "idle"

idle == /\ pc = "idle"
        /\ IF tx = TRUE
              THEN /\ pc' = "transmit"
              ELSE /\ pc' = "Done"
        /\ UNCHANGED << tx, txBuf, txBufIndex, txReg >>

transmit == /\ pc = "transmit"
            /\ IF IsModbus(txBuf)
                  THEN /\ txBufIndex' = Len(txBuf)
                       /\ pc' = "send"
                  ELSE /\ pc' = "t1"
                       /\ UNCHANGED txBufIndex
            /\ UNCHANGED << tx, txBuf, txReg >>

send == /\ pc = "send"
        /\ IF txBufIndex  < Len(txBuf)
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
      /\ txReg = ""
      /\ tx' = FALSE
      /\ pc' = "Done"
      /\ UNCHANGED << txBuf, txBufIndex, txReg >>

Next == idle \/ transmit \/ send \/ a \/ b \/ t1
           \/ (* Disjunct to prevent deadlock on termination *)
              ( pc = "Done"
                /\ tx = FALSE 
                /\ UNCHANGED << txBuf, txReg, txBufIndex, tx, pc >>)

Spec == Init /\ [][Next]_vars /\ WF_vars(Next)

Termination == <>(pc = "Done")

\* check that if valid modbus is in the buffer it gets sent
ALLSENT == tx = TRUE ~> txBufIndex = 0

NOTHANG == tx = TRUE ~> tx = FALSE

BUFFOVERFLOW == [](txBufIndex <= Len(txBuf))

SENDSOMETHING == <>(txReg /= "")

ONLYHEXSENT == [](txReg \in HexChar \/ txReg = ":")

\* END TRANSLATION

=============================================================================
\* Modification History
\* Last modified Fri May 04 20:12:08 EDT 2018 by SabraouM
\* Created Thu May 03 13:28:54 EDT 2018 by SabraouM
