------------------------------ MODULE ReceiveModbus ------------------------------

EXTENDS Sequences,
        Naturals,
        Modbus,
        TLC
        
LOCAL INSTANCE Hex
    WITH natValue <- 0, hexValue <- <<0>> 
MessagesToSerialPort == 
    { <<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>,
      <<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","F">>,
      <<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","G","L","F">>,
      <<":","1","1","0","3","0","0","6","B","0","0","0",":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","F">>, \*this one starts a new modbus packet half way through the message
      <<>>}

  \*}


(*
(*--fair algorithm Transmit
variables   rx = FALSE,
            rxBuf = "",
            rxReg = "",
            incMessage \in MessagesToSerialPort,
            applicationBuffer = "" \*this is what is passed to the application. Only valid modbus here plz
begin

\* wait for something to appear in the buffer
idle:   if incMessage = <<>>
            then goto alldone;
            else
                rxReg := Head(incMessage);
                incMessage := Tail(incMessage);
        end if;

start:  if rxReg /= "" /\ Len(rxBuf)
        then goto receive;
        else goto alldone;
        end if;
        
receive:    \* a ":" character indicates the start of a new message
            if rxReg = ":"
                then rxBuf := "";
            end if;
            r1: rxBuf := rxBuf \o rxReg; \* put the contents of the register into the buffer
            \*empty the register
            r2: rxReg := "";

check:      \*if we have a full modbus packet then signal
            if IsModbus(rxBuf)
            then 
                rx := TRUE; 
                applicationBuffer := rxBuf;
                goto alldone;
            else goto idle;
            end if;
            
alldone:    rxBuf := "";
            rxReg := "";

end algorithm
*)*)

\* BEGIN TRANSLATION
VARIABLES rx, rxBuf, rxReg, incMessage, applicationBuffer, pc

vars == << rx, rxBuf, rxReg, incMessage, applicationBuffer, pc >>

Init == (* Global variables *)
        /\ rx = FALSE
        /\ rxBuf = <<>>
        /\ rxReg = <<>>
        /\ incMessage \in MessagesToSerialPort
        /\ applicationBuffer = <<>>
        /\ pc = "idle"

idle == /\ pc = "idle"
        /\ IF Len(incMessage) = 0 
              THEN /\ pc' = "start"
                   /\ rxReg' = <<>>
                   /\ UNCHANGED << incMessage >>
              ELSE /\ rxReg' = <<Head(incMessage)>>
                   /\ incMessage' = Tail(incMessage)
                   /\ pc' = "start"
        /\ UNCHANGED << rx, rxBuf, applicationBuffer >>

start == /\ pc = "start"
         /\ IF rxReg /= <<>> /\ Len(rxBuf) < MAXMODBUSSIZE
               THEN /\ pc' = "receive"
               ELSE /\ pc' = "alldone"
         /\ UNCHANGED << rx, rxBuf, rxReg, incMessage, applicationBuffer >>

receive == /\ pc = "receive"
           /\ IF Head(rxReg) = ":"
                 THEN /\ rxBuf' = <<>>
                 ELSE /\ TRUE
                      /\ rxBuf' = rxBuf
           /\ pc' = "r1"
           /\ UNCHANGED << rx, rxReg, incMessage, applicationBuffer >>

r1 == /\ pc = "r1"
      /\ rxBuf' = rxBuf \o rxReg
      /\ pc' = "r2"
      /\ UNCHANGED << rx, rxReg, incMessage, applicationBuffer >>

r2 == /\ pc = "r2"
      /\ rxReg' = <<>>
      /\ pc' = "check"
      /\ UNCHANGED << rx, rxBuf, incMessage, applicationBuffer >>

check == /\ pc = "check"
         /\ IF IsModbus(rxBuf)
               THEN /\ rx' = TRUE
                    /\ applicationBuffer' = rxBuf
                    /\ pc' = "alldone"
               ELSE /\ pc' = "idle"
                    /\ UNCHANGED << rx, applicationBuffer >>
         /\ UNCHANGED << rxBuf, rxReg, incMessage >>

alldone == /\ pc = "alldone"
           /\ rxBuf' = <<>>
           /\ rxReg' = <<>>
           /\ pc' = "Done"
           /\ UNCHANGED << rx, incMessage, applicationBuffer >>

Next == idle \/ start \/ receive \/ r1 \/ r2 \/ check \/ alldone
           \/ (* Disjunct to prevent deadlock on termination *)
              (pc = "Done" /\ UNCHANGED vars)

Spec == /\ Init /\ [][Next]_vars
        /\ WF_vars(Next)

Termination == <>(pc = "Done")

\* END TRANSLATION

SAFETYCHECK ==
    /\ Len(rxBuf) <= MAXMODBUSSIZE \*receive buffer never overflows
    /\ Len(applicationBuffer) <= MAXMODBUSSIZE \*application buffer never overflows
    /\ IsModbus(applicationBuffer) \/ applicationBuffer = <<>> \*only valid modbus makes it to the app buffer
    /\ rx = TRUE <=> IsModbus(applicationBuffer) \*flag is raised if and only if there is valid modbus in app buffer

LIVELINESS ==
    /\ IsModbus(incMessage) ~> IsModbus(applicationBuffer) \* if the message is modbus then it gets to the app buffer
    /\ IsModbus(incMessage) ~> rx = TRUE \* if valid modbus comes through then it gets flagged for the application to consume


=============================================================================
\* Modification History
\* Last modified Sun May 06 18:05:32 EDT 2018 by SabraouM
\* Created Sat May 05 11:36:54 EDT 2018 by SabraouM
