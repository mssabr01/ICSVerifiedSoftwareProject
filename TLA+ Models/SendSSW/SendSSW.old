-------------------------------- MODULE SendSSW --------------------------------

EXTENDS Sequences,
        Naturals,
        SSWPacket,
        TLC,
        ASCII
        
LOCAL INSTANCE Hex
    WITH natValue <- 0, hexValue <- <<0>> 
MessagesToSerialPort == 
    {StrTupleToNumTuple(isSSW),
     StrTupleToNumTuple(<<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>),
     StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>),
     \*StrTupleToNumTuple(<<":","J","G","P","9","4","3","2","J","3","9","J","G","W",":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","F">>),
     <<>>}
LOCAL Range(T) == { T[x] : x \in DOMAIN T }

(*--fair algorithm Transmit
variables   tx = FALSE,
            messageToSend \in MessagesToSerialPort,
            txBuf = <<>>,
            txReg = <<>>
begin

checkBuf:   txBuf := messageToSend;
            if IsSSW(NumTupleToStrTuple(txBuf))
            then tx := TRUE;
            end if;
idle: if tx = TRUE 
      then goto transmit;
      else goto finished;
      end if;
transmit:   if Len(txBuf) > 1
            then
                \*empty the buffer into the register
                a: txReg := <<Head(txBuf)>>;
                b: txBuf := Tail(txBuf);
                goto transmit;
            else
                txReg := <<txBuf[1]>>;
            end if;
            
            
finished: tx := FALSE;
          txReg:= <<>>;
          txBuf := <<>>;
end algorithm
*)
\* BEGIN TRANSLATION
VARIABLES tx, messageToSend, txBuf, txReg, pc

vars == << tx, messageToSend, txBuf, txReg, pc >>

Init == (* Global variables *)
        /\ tx = FALSE
        /\ messageToSend \in MessagesToSerialPort
        /\ txBuf = <<>>
        /\ txReg = <<>>
        /\ pc = "checkBuf"

checkBuf == /\ pc = "checkBuf"
            /\ txBuf' = messageToSend
            /\ IF IsSSW(NumTupleToStrTuple(txBuf'))
                  THEN /\ tx' = TRUE
                  ELSE /\ TRUE
                       /\ tx' = tx
            /\ pc' = "idle"
            /\ UNCHANGED << messageToSend, txReg >>

idle == /\ pc = "idle"
        /\ IF tx = TRUE
              THEN /\ pc' = "transmit"
              ELSE /\ pc' = "finished"
        /\ UNCHANGED << tx, messageToSend, txBuf, txReg >>

transmit == /\ pc = "transmit"
            /\ IF Len(txBuf) > 1
                  THEN /\ pc' = "a"
                       /\ txReg' = txReg
                  ELSE /\ txReg' = txBuf[1]
                       /\ pc' = "finished"
            /\ UNCHANGED << tx, messageToSend, txBuf >>

a == /\ pc = "a"
     /\ txReg' = <<Head(txBuf)>>
     /\ pc' = "b"
     /\ UNCHANGED << tx, messageToSend, txBuf >>

b == /\ pc = "b"
     /\ txBuf' = Tail(txBuf)
     /\ pc' = "transmit"
     /\ UNCHANGED << tx, messageToSend, txReg >>

finished == /\ pc = "finished"
            /\ tx' = FALSE
            /\ txReg' = <<>>
            /\ txBuf' = <<>>
            /\ pc' = "Done"
            /\ UNCHANGED messageToSend

Next == checkBuf \/ idle \/ transmit \/ a \/ b \/ finished
           \/ (* Disjunct to prevent deadlock on termination *)
              (pc = "Done" /\ UNCHANGED vars)

Spec == /\ Init /\ [][Next]_vars
        /\ WF_vars(Next)

Termination == <>(pc = "Done")

\* END TRANSLATION
LIVELINESS ==
\* check that if valid SSW is in the buffer it gets sent
    /\ tx = TRUE /\ IsSSW(NumTupleToStrTuple(txBuf)) ~> Len(txBuf) = 1
\*If there is something to send then it is alway sent
    /\ tx = TRUE /\ IsSSW(NumTupleToStrTuple(txBuf)) ~> (txReg /= <<>>)
\*If there is something to send, the flag is eventually reset
    /\ (tx = TRUE) ~> (tx = FALSE)

SAFETYCHECK ==
\*Only valid SSW triggers the sending
    /\ Len(txReg) > 0 => IsSSW(NumTupleToStrTuple(messageToSend))
\*only one thing in the transmission register
    /\ Len(txReg) <= 1
=============================================================================
\* Modification History
\* Last modified Mon May 14 12:47:48 EDT 2018 by SabraouM
\* Created Fri May 04 22:08:30 EDT 2018 by SabraouM
