-------------------------------- MODULE Untrustnet_out --------------------------------

EXTENDS Sequences,
        Naturals,
        EncapPacket,
        TLC,
        ASCII
        
LOCAL INSTANCE Hex
    WITH natValue <- 0, hexValue <- <<0>>
LOCAL PrintVal(id, exp)  ==  Print(<<id, exp>>, TRUE)
\*HMAC == <<"I","K","o","W","L","9","v","G","U","h","S","1","q","t","Z","f","4","5","h","r","9","W","4","1","Z","i","B","G","P","j","d","o","w","6","S","Y","2","A","0","+","q","E","d","a","+","s","i","i","B","H","G","C","4","r","/","S","5","g","J","W","P","/","s","T">> \*not concerned with the inner workings of SHA2 
HMAC == <<"l","o","l">>
MessagesFromInnerCells == \*these are in ASCII but they are converted to decimal before being used below. See StrTupleToNumTuple in ASCII.tla
    << (* [text |-> StrTupleToNumTuple(<<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>), 
                        id |-> <<"u","t","i","0">>,
                        source |-> "sign",
                        hmac |-> HMAC,
                        isValid |-> TRUE ],
        [text |-> StrTupleToNumTuple(<<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>), 
                        id |-> <<"u","t","i","0">>,
                        source |-> "modchk", 
                        isValid |-> FALSE ],
        
        [text |-> StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>), 
                        id |-> <<"u","t","i","1">>,
                        source |-> "modchk",
                        isValid |-> TRUE ],              
        [text |-> StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>), 
                        id |-> <<"u","t","i","1">>,
                        source |-> "sign",
                        hmac |-> HMAC,
                        isValid |-> TRUE ],
                        
             (*           
        [text |-> StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","G","L","F">>), 
                        id |-> <<"u","t","i","2">>,
                        source |-> "sign", 
                        hmac |-> HMAC,
                        isValid |-> TRUE ],
        [text |-> StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","G","L","F">>), 
                        id |-> <<"u","t","i","2">>,
                        source |-> "modchk",  
                        isValid |-> TRUE ],
               *)         
        [text |-> StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0",":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>), \*this one starts a new modbus packet half way through the message 
                        id |-> <<"u","t","i","3">>,
                        source |-> "sign", 
                        hmac |-> HMAC,
                        isValid |-> TRUE ],
        [text |-> StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0",":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>), \*this one starts a new modbus packet half way through the message 
                        id |-> <<"u","t","i","3">>,
                        source |-> "modchk",  
                        isValid |-> TRUE ]
      *)>>

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
                    
                    if msg.source = "sign" then
                        txBuf := StrTupleToNumTuple(<<"!">>) \o StrTupleToNumTuple(msg.hmac) \o msg.text;
                    else
                        txBuf := StrTupleToNumTuple(<<"!">>) \o StrTupleToNumTuple(tmpMsg.hmac) \o msg.text;
                    end if;
                    
                    serialport := Append(serialport, txBuf);
                    metaserialport := Append(metaserialport,msg);
                    
                    \*transmit: send("finished_untrustnet", NumTupleToStrTuple(txBuf)); \*converting back to characters for easier troubleshooting
                    to2: validMessages := validMessages \ {tmpMsg}; \*remove sent message from set
                    
                    (*txBuf := msg.text;
                    serialport := Append(serialport, txBuf);
                    metaserialport := Append(metaserialport,msg);
                    \*transmit: send("finished_trustnet", NumTupleToStrTuple(txBuf)); \*converting back to characters for easier troubleshooting
                    to2: validMessages := validMessages \ {tmpMsg}; \*remove sent message from set
                    *)
                else
                    validMessages := validMessages \ {tmpMsg}; \*remove sent message from set
                end if;
            else
                validMessages := validMessages \union {msg}; \*if a message with the same id is not found then add this message to that set
            end if;
        finished: txReg := <<>>;
        txBuf := <<>>;
    end while;
    print "hmac: ";
    print StrTupleToNumTuple(<<"I","K","o","W","L","9","v","G","U","h","S","1","q","t","Z","f","4","5","h","r","9","W","4","1","Z","i","B","G","P","j","d","o","w","6","S","Y","2","A","0","+","q","E","d","a","+","s","i","i","B","H","G","C","4","r","/","S","5","g","J","W","P","/","s","T">>);
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
                                   THEN /\ IF msg'.source = "sign"
                                              THEN /\ txBuf' = StrTupleToNumTuple(<<"!">>) \o StrTupleToNumTuple(msg'.hmac) \o msg'.text
                                              ELSE /\ txBuf' = StrTupleToNumTuple(<<"!">>) \o StrTupleToNumTuple(tmpMsg'.hmac) \o msg'.text
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
             ELSE /\ PrintT("hmac: ")
                  /\ PrintT(StrTupleToNumTuple(<<"I","K","o","W","L","9","v","G","U","h","S","1","q","t","Z","f","4","5","h","r","9","W","4","1","Z","i","B","G","P","j","d","o","w","6","S","Y","2","A","0","+","q","E","d","a","+","s","i","i","B","H","G","C","4","r","/","S","5","g","J","W","P","/","s","T">>))
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

=============================================================================
\* Modification History
\* Last modified Tue Jun 25 16:04:18 EDT 2019 by mssabr01
\* Last modified Thu Jun 13 18:17:32 EDT 2019 by mehdi
\* Last modified Mon May 14 12:54:26 EDT 2018 by SabraouM
\* Created Fri May 04 22:08:30 EDT 2018 by SabraouM
