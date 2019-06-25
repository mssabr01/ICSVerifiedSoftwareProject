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

MessagesFromInnerCells == \*these are in ASCII but they are converted to decimal before being used below. See StrTupleToNumTuple in ASCII.tla
    <<  [text |-> StrTupleToNumTuple(<<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>), 
                        id |-> <<"u","t","i","0">>,
                        source |-> "verify",
                        isValid |-> TRUE ],
        [text |-> StrTupleToNumTuple(<<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>), 
                        id |-> <<"u","t","i","0">>,
                        source |-> "modchk", 
                        isValid |-> FALSE ],
                        
        [text |-> StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>), 
                        id |-> <<"u","t","i","1">>,
                        source |-> "verify",
                        isValid |-> TRUE ],
        [text |-> StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>), 
                        id |-> <<"u","t","i","1">>,
                        source |-> "modchk",
                        isValid |-> TRUE ],
             (*           
        [text |-> StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","G","L","F">>), 
                        id |-> <<"u","t","i","2">>,
                        source |-> "verify", 
                        isValid |-> TRUE ],
        [text |-> StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","G","L","F">>), 
                        id |-> <<"u","t","i","2">>,
                        source |-> "modchk",  
                        isValid |-> TRUE ],
               *)         
        [text |-> StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0",":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>), \*this one starts a new modbus packet half way through the message 
                        id |-> <<"u","t","i","3">>,
                        source |-> "verify", 
                        isValid |-> TRUE ],
        [text |-> StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0",":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>), \*this one starts a new modbus packet half way through the message 
                        id |-> <<"u","t","i","3">>,
                        source |-> "modchk",  
                        isValid |-> TRUE ]
      >>

LOCAL Range(T) == { T[x] : x \in DOMAIN T }

(*--fair algorithm trustnet_out
\*process to send modbus out the trusted serial port

variables   msg = <<>>,
            incomingMessages = MessagesFromInnerCells,
            txBuf = <<>>,
            txReg = <<>>,
            tmpMsg = <<>>,
            adder = 0,
            serialport = <<>>,
            metaserialport = <<>>, \*to have ID numbers for property checks. This should be the same as serial port but the whole object rather than raw modbus
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
                    metaserialport := Append(metaserialport,msg);
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
          metaserialport, validMessages, pc

vars == << msg, incomingMessages, txBuf, txReg, tmpMsg, adder, serialport, 
           metaserialport, validMessages, pc >>

Init == (* Global variables *)
        /\ msg = <<>>
        /\ incomingMessages = MessagesFromInnerCells
        /\ txBuf = <<>>
        /\ txReg = <<>>
        /\ tmpMsg = <<>>
        /\ adder = 0
        /\ serialport = <<>>
        /\ metaserialport = <<>>
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
                                        /\ metaserialport' = Append(metaserialport,msg')
                                        /\ pc' = "to2"
                                        /\ UNCHANGED validMessages
                                   ELSE /\ validMessages' = validMessages \ {tmpMsg'}
                                        /\ pc' = "finished"
                                        /\ UNCHANGED << txBuf, serialport, 
                                                        metaserialport >>
                        ELSE /\ validMessages' = (validMessages \union {msg'})
                             /\ pc' = "finished"
                             /\ UNCHANGED << txBuf, tmpMsg, serialport, 
                                             metaserialport >>
             ELSE /\ PrintT(serialport)
                  /\ pc' = "Done"
                  /\ UNCHANGED << msg, incomingMessages, txBuf, tmpMsg, 
                                  serialport, metaserialport, validMessages >>
       /\ UNCHANGED << txReg, adder >>

finished == /\ pc = "finished"
            /\ txReg' = <<>>
            /\ txBuf' = <<>>
            /\ pc' = "to1"
            /\ UNCHANGED << msg, incomingMessages, tmpMsg, adder, serialport, 
                            metaserialport, validMessages >>

to2 == /\ pc = "to2"
       /\ validMessages' = validMessages \ {tmpMsg}
       /\ pc' = "finished"
       /\ UNCHANGED << msg, incomingMessages, txBuf, txReg, tmpMsg, adder, 
                       serialport, metaserialport >>

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
*)

\*stuff on the serial port and the metaserialport are the same (weakly, this checks for the existance of a message but its not 1-1 mapping)
SAFE1 == /\ \A x \in Range(serialport) : \E y \in Range(metaserialport) : y.text = x
         /\ \A y \in Range(metaserialport) : \E x \in Range(serialport) : x = y.text
\*Only prints if both inner components say its valid
SAFE2 == \A x \in Range(metaserialport) : /\ (\E y \in Range(MessagesFromInnerCells) : x.id = y.id /\ y.isValid /\ y.source = "modchk")
                                   /\ (\E y \in Range(MessagesFromInnerCells) : x.id = y.id /\ y.isValid /\ y.source = "verify")
\*sending buffer never overflows
\*SAFE3 == ~(txBuf = <<>>) => IsWellformedModbus(NumTupleToStrTuple(txBuf))
SAFE3 == Len(txBuf) < MAXMODBUSSIZE 
\*only valid Modbus gets printed (this module assumes valid Modbus is received from both inner components
SAFE4 == \A x \in Range(serialport): \E y \in Range(MessagesFromInnerCells) : x = y.text

\* each message received is eventually sent or discarded is NOT a property of this module
\*Each message that gets its companion message is sent or discarded
LIVE1 == \A x \in Range(MessagesFromInnerCells) : x \in validMessages /\ x.id = msg.id ~> x \notin validMessages
        
\*valid messages are eventually sent
LIVE2 == \A x \in Range(MessagesFromInnerCells) : msg = x /\ x.isValid /\ (\E y \in validMessages : y.id = x.id /\ y.isValid /\ y.source /= x.source)
            ~> \E z \in Range(metaserialport) : z.id = x.id
\*all messages are eventually processed
LIVE3 == \A x \in Range(MessagesFromInnerCells) : TRUE => <>(\E y \in validMessages : y.id = x.id)

=============================================================================
\* Modification History
\* Last modified Tue Jun 25 14:56:16 EDT 2019 by mssabr01
\* Last modified Fri Jun 14 09:43:37 EDT 2019 by mehdi
\* Last modified Mon May 14 13:43:42 EDT 2018 by SabraouM
\* Created Fri May 04 22:08:30 EDT 2018 by SabraouM
