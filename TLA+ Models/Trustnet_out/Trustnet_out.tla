-------------------------------- MODULE Trustnet_out --------------------------------

EXTENDS Sequences,
        Naturals,
        Modbus,
        TLC,
        FiniteSets,
        ASCII
        
LOCAL INSTANCE Hex
    WITH natValue <- 0, hexValue <- <<0>> 
LOCAL PrintVal(id, exp)  ==  Print(<<id, exp>>, TRUE)

MessagesFromCryptoCell == \*these are in ASCII but they are converted to decimal before being used below. See StrTupleToNumTuple in ASCII.tla
    <<  [text |-> StrTupleToNumTuple(<<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>), 
                        id |-> <<"u","t","i","0">>, 
                        isValid |-> TRUE ],
        [text |-> StrTupleToNumTuple(<<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>), 
                        id |-> <<"u","t","i","0">>, 
                        isValid |-> TRUE ],
                        
        [text |-> StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>), 
                        id |-> <<"u","t","i","1">>, 
                        isValid |-> TRUE ],
        [text |-> StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>), 
                        id |-> <<"u","t","i","1">>, 
                        isValid |-> TRUE ],
                        
        [text |-> StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","G","L","F">>), 
                        id |-> <<"u","t","i","2">>, 
                        isValid |-> TRUE ],
        [text |-> StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","G","L","F">>), 
                        id |-> <<"u","t","i","2">>, 
                        isValid |-> TRUE ],
                        
        [text |-> StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0",":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>), \*this one starts a new modbus packet half way through the message 
                        id |-> <<"u","t","i","3">>, 
                        isValid |-> TRUE ],
        [text |-> StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0",":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>), \*this one starts a new modbus packet half way through the message 
                        id |-> <<"u","t","i","3">>, 
                        isValid |-> TRUE ]
      >>

LOCAL Range(T) == { T[x] : x \in DOMAIN T }

(*--fair algorithm trustnet_out
\*process to send modbus out the trusted serial port

variables   msg = <<>>,
            incomingMessages = MessagesFromCryptoCell,
            txBuf = <<>>,
            txReg = <<>>,
            tmpMsg = <<>>,
            adder = 0,
            serialport = <<>>,
            validMessages = {}
            
begin
    to1: while Len(incomingMessages) > 0 do
        if Len(incomingMessages) = 1 then
            msg := incomingMessages[1];
            incomingMessages := <<>>;
        else
            msg := Head(incomingMessages);
            incomingMessages := Tail(incomingMessages);
        end if;
        \*receive("trustnet_out", msg);
            if \E x \in validMessages : x.id = msg.id then
                tmpMsg := CHOOSE x \in validMessages : x.id = msg.id;
                \*if one exists then both portions of the message were verified and the message can be sent
                if msg.isValid /\ tmpMsg.isValid then \*if the message is valid then look for another message in the validMessages set with the same id.
                    txBuf := msg.text;
                    serialport := Append(serialport, txBuf);
                    \*transmit: send("finished_trustnet", NumTupleToStrTuple(txBuf)); \*converting back to characters for easier troubleshooting
                    to2: validMessages := validMessages \ {tmpMsg}; \*remove sent message from set
                else
                    validMessages := validMessages \ {tmpMsg}; \*remove sent message from set
                end if;
            else
                validMessages := validMessages \union {msg}; \*if a message with the same id is not found then add this message to that set
            end if;
        finished: txReg := <<>>;
        txBuf := <<>>;
    end while;
    print serialport;
end algorithm
*)
\* BEGIN TRANSLATION
VARIABLES msg, incomingMessages, txBuf, txReg, tmpMsg, adder, serialport, 
          validMessages, pc

vars == << msg, incomingMessages, txBuf, txReg, tmpMsg, adder, serialport, 
           validMessages, pc >>

Init == (* Global variables *)
        /\ msg = <<>>
        /\ incomingMessages = MessagesFromCryptoCell
        /\ txBuf = <<>>
        /\ txReg = <<>>
        /\ tmpMsg = <<>>
        /\ adder = 0
        /\ serialport = <<>>
        /\ validMessages = {}
        /\ pc = "to1"

to1 == /\ pc = "to1"
       /\ IF Len(incomingMessages) > 0
             THEN /\ IF Len(incomingMessages) = 1
                        THEN /\ msg' = incomingMessages[1]
                             /\ incomingMessages' = <<>>
                        ELSE /\ msg' = Head(incomingMessages)
                             /\ incomingMessages' = Tail(incomingMessages)
                  /\ IF \E x \in validMessages : x.id = msg'.id
                        THEN /\ tmpMsg' = (CHOOSE x \in validMessages : x.id = msg'.id)
                             /\ IF msg'.isValid /\ tmpMsg'.isValid
                                   THEN /\ txBuf' = msg'.text
                                        /\ serialport' = Append(serialport, txBuf')
                                        /\ pc' = "to2"
                                        /\ UNCHANGED validMessages
                                   ELSE /\ validMessages' = validMessages \ {tmpMsg'}
                                        /\ pc' = "finished"
                                        /\ UNCHANGED << txBuf, serialport >>
                        ELSE /\ validMessages' = (validMessages \union {msg'})
                             /\ pc' = "finished"
                             /\ UNCHANGED << txBuf, tmpMsg, serialport >>
             ELSE /\ PrintT(serialport)
                  /\ pc' = "Done"
                  /\ UNCHANGED << msg, incomingMessages, txBuf, tmpMsg, 
                                  serialport, validMessages >>
       /\ UNCHANGED << txReg, adder >>

finished == /\ pc = "finished"
            /\ txReg' = <<>>
            /\ txBuf' = <<>>
            /\ pc' = "to1"
            /\ UNCHANGED << msg, incomingMessages, tmpMsg, adder, serialport, 
                            validMessages >>

to2 == /\ pc = "to2"
       /\ validMessages' = validMessages \ {tmpMsg}
       /\ pc' = "finished"
       /\ UNCHANGED << msg, incomingMessages, txBuf, txReg, tmpMsg, adder, 
                       serialport >>

Next == to1 \/ finished \/ to2
           \/ (* Disjunct to prevent deadlock on termination *)
              (pc = "Done" /\ UNCHANGED vars)

Spec == /\ Init /\ [][Next]_vars
        /\ WF_vars(Next)

Termination == <>(pc = "Done")

\* END TRANSLATION

(*
LIVELINESS ==
\* check that if valid SSW is in the buffer it gets sent
    /\ tx = TRUE /\ IsModbus(NumTupleToStrTuple(txBuf)) ~> Len(txBuf) = 1
\*If there is something to send then it is alway sent
    /\ tx = TRUE /\ IsModbus(NumTupleToStrTuple(txBuf)) ~> (txReg /= <<>>)
\*If there is something to send, the flag is eventually reset
    /\ (tx = TRUE) ~> (tx = FALSE)

SAFETYCHECK ==
\*Only valid SSW triggers the sending
    /\ Len(txReg) > 0 => IsModbus(NumTupleToStrTuple(messageToSend))
\*only one thing in the transmission register
    /\ Len(txReg) <= 1
\* only valid modbus characters get into register
    /\ txReg = <<>> \/ NumToChar(txReg[1]) \in ModbusChar
    *)
=============================================================================
\* Modification History
\* Last modified Tue Jun 11 14:46:47 EDT 2019 by mehdi
\* Last modified Sat Jun 01 14:40:15 EDT 2019 by mssabr01
\* Last modified Mon May 14 13:43:42 EDT 2018 by SabraouM
\* Created Fri May 04 22:08:30 EDT 2018 by SabraouM
