------------------------------- MODULE ModChk -------------------------------
EXTENDS Sequences, FiniteSets, Naturals, TLC, Modbus, ASCII

LOCAL Range(T) == { T[x] : x \in DOMAIN T }

ModbusMessages == \*these are in ASCII but they are converted to decimal before being used below. See StrTupleToNumTuple in ASCII.tla
    {   [text |-> StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>), 
            id |-> <<"t","i","0">>,
            source |-> "trustnet_in" ](*, \*good from trustnet
        [text |-> StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>), 
            id |-> <<"u","t","i","0">>,
            source |-> "untrustnet_in" ], \*good from untrustnet
        [text |-> StrTupleToNumTuple(<<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>), 
            id |-> <<"u","t","i","1">>,
            source |-> "untrustnet_in" ],\*bad from untrustnet
        [text |-> StrTupleToNumTuple(<<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>),
            id |-> <<"t","i","2">>,
            source |-> "trustnet_in" ] \*bad from trustnet*)
      }


(*--fair algorithm ModChk
\* IPC calls
\*macro send(dest, msg) begin
\*        sentBuffer := sentBuffer \o msg;
\*end macro;

variables   rxBuf = <<>>,
            rxReg = <<>>,
            incomingMessages \in ModbusMessages,
            msg = <<>>,
            receivedMessages = <<>>, \*to keep track of IDs that have been received so far. See invariant SAFE1 below
            untrustBuf = <<>>, \*this is what is passed to untrustnet_out
            trustBuf = <<>>  \*this is what is passed to trustnet_out

    
begin
     
modbus1:    msg := incomingMessages;
            m2: incomingMessages := <<>>;
            receivedMessages := Append(receivedMessages, msg);
                \*receive("messagecheck", msg);
            if IsModbus(NumTupleToStrTuple(msg.text)) then
                if msg.source = "trustnet_in" then 
                    mod1: untrustBuf := Append(untrustBuf, [id|->msg.id, isValid|->TRUE,source|->"msgchk", text|->msg.text]);
                    \*mod1: send("untrustnet_out", [id|->msg.id, isValid|->TRUE,source|->"msgchk", text|->msg.text]);
                elsif (msg.source = "untrustnet_in") then
                    mod2: trustBuf := Append(trustBuf, [id|->msg.id, isValid|->TRUE, source|->"msgchk", text|->msg.text]); 
                    \*mod2: send("trustnet_out", [id|->msg.id, isValid|->TRUE, source|->"msgchk", text|->msg.text]);
                end if;
            else
                if msg.source = "trustnet_in" then
                    mod3: untrustBuf := Append(trustBuf, [id|->msg.id, isValid|->FALSE, source|->"msgchk", text|->msg.text]);
                    \*mod3: send("untrustnet_out", [id|->msg.id, isValid|->FALSE, source|->"msgchk", text|->msg.text]);
                elsif msg.source = "untrustnet_in" then
                    mod4: trustBuf := Append(trustBuf, [id|->msg.id, isValid|->FALSE, source|->"msgchk", text|->msg.text]);
                    \*mod4: send("trustnet_out", [id|->msg.id, isValid|->FALSE, source|->"msgchk", text|->msg.text]);
                end if;
            end if;
           pr: print("untrusted buffer");
               print(untrustBuf);
               print("trusted buffer");
               print(trustBuf);
end algorithm;
*)
\* BEGIN TRANSLATION
VARIABLES rxBuf, rxReg, incomingMessages, msg, receivedMessages, untrustBuf, 
          trustBuf, pc

vars == << rxBuf, rxReg, incomingMessages, msg, receivedMessages, untrustBuf, 
           trustBuf, pc >>

Init == (* Global variables *)
        /\ rxBuf = <<>>
        /\ rxReg = <<>>
        /\ incomingMessages \in ModbusMessages
        /\ msg = <<>>
        /\ receivedMessages = <<>>
        /\ untrustBuf = <<>>
        /\ trustBuf = <<>>
        /\ pc = "modbus1"

modbus1 == /\ pc = "modbus1"
           /\ msg' = incomingMessages
           /\ pc' = "m2"
           /\ UNCHANGED << rxBuf, rxReg, incomingMessages, receivedMessages, 
                           untrustBuf, trustBuf >>

m2 == /\ pc = "m2"
      /\ incomingMessages' = <<>>
      /\ receivedMessages' = Append(receivedMessages, msg)
      /\ IF IsModbus(NumTupleToStrTuple(msg.text))
            THEN /\ IF msg.source = "trustnet_in"
                       THEN /\ pc' = "mod1"
                       ELSE /\ IF (msg.source = "untrustnet_in")
                                  THEN /\ pc' = "mod2"
                                  ELSE /\ pc' = "pr"
            ELSE /\ IF msg.source = "trustnet_in"
                       THEN /\ pc' = "mod3"
                       ELSE /\ IF msg.source = "untrustnet_in"
                                  THEN /\ pc' = "mod4"
                                  ELSE /\ pc' = "pr"
      /\ UNCHANGED << rxBuf, rxReg, msg, untrustBuf, trustBuf >>

mod1 == /\ pc = "mod1"
        /\ untrustBuf' = Append(untrustBuf, [id|->msg.id, isValid|->TRUE,source|->"msgchk", text|->msg.text])
        /\ pc' = "pr"
        /\ UNCHANGED << rxBuf, rxReg, incomingMessages, msg, receivedMessages, 
                        trustBuf >>

mod2 == /\ pc = "mod2"
        /\ trustBuf' = Append(trustBuf, [id|->msg.id, isValid|->TRUE, source|->"msgchk", text|->msg.text])
        /\ pc' = "pr"
        /\ UNCHANGED << rxBuf, rxReg, incomingMessages, msg, receivedMessages, 
                        untrustBuf >>

mod3 == /\ pc = "mod3"
        /\ untrustBuf' = Append(trustBuf, [id|->msg.id, isValid|->FALSE, source|->"msgchk", text|->msg.text])
        /\ pc' = "pr"
        /\ UNCHANGED << rxBuf, rxReg, incomingMessages, msg, receivedMessages, 
                        trustBuf >>

mod4 == /\ pc = "mod4"
        /\ trustBuf' = Append(trustBuf, [id|->msg.id, isValid|->FALSE, source|->"msgchk", text|->msg.text])
        /\ pc' = "pr"
        /\ UNCHANGED << rxBuf, rxReg, incomingMessages, msg, receivedMessages, 
                        untrustBuf >>

pr == /\ pc = "pr"
      /\ PrintT(("untrusted buffer"))
      /\ PrintT((untrustBuf))
      /\ PrintT(("trusted buffer"))
      /\ PrintT((trustBuf))
      /\ pc' = "Done"
      /\ UNCHANGED << rxBuf, rxReg, incomingMessages, msg, receivedMessages, 
                      untrustBuf, trustBuf >>

Next == modbus1 \/ m2 \/ mod1 \/ mod2 \/ mod3 \/ mod4 \/ pr
           \/ (* Disjunct to prevent deadlock on termination *)
              (pc = "Done" /\ UNCHANGED vars)

Spec == /\ Init /\ [][Next]_vars
        /\ WF_vars(Next)

Termination == <>(pc = "Done")

\* END TRANSLATION

\* Messages from untrustnet are forwarded to trustnet. This is two parts, first an invariant
\* that says no messages from untrustnet will ever make it into the set of messages sent to untrustnet
SAFE1 == \A x \in ModbusMessages : x.source = "trustnet_in" => (\E y \in Range(trustBuf) : y.id = x.id) = FALSE
\* The second part is that if a message is from untrustnet, it eventually will be sent to trustnet exactly once
LIVE1 == IF Len(receivedMessages) > 0
         THEN \A x \in Range(receivedMessages) : x.source = "untrustnet_in" ~> \E y \in Range(trustBuf) : y.id = x.id
         ELSE TRUE
\*Same deal as above but in reverse
SAFE2 == \A x \in ModbusMessages : x.source = "untrustnet_in" => (\E y \in Range(untrustBuf) : y.id = x.id) = FALSE
LIVE2 == \A x \in ModbusMessages : x.source = "untrustnet_in" ~> Cardinality({y \in Range(untrustBuf) : y.id = x.id}) = 1
\*Malformed Modbus is marked Invalid when it leaves
\*Good Modbus is marked valid when it leaves
SAFE3 == /\ \A x \in Range(untrustBuf) : x.isValid <=> IsModbus(NumTupleToStrTuple(x.text))
         /\ \A x \in Range(trustBuf) : x.isValid <=> IsModbus(NumTupleToStrTuple(x.text))
\*if a message is received it is eventually processed
LIVE3 == <>[](incomingMessages = <<>>)
\*sending buffers never overflow


=============================================================================
\* Modification History
\* Last modified Thu Jun 13 16:53:42 EDT 2019 by mehdi
\* Created Wed Jun 12 11:10:03 EDT 2019 by mehdi
