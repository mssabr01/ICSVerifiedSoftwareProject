------------------------------ MODULE Sign ------------------------------
LOCAL INSTANCE Sequences
LOCAL INSTANCE Naturals
LOCAL INSTANCE Modbus

LOCAL HMACSIZE == 64
LOCAL MINMESSAGESIZE == 1
LOCAL MINMACMESSAGESIZE == 65
LOCAL PASSWORD == "lolpassword"
LOCAL Range(T) == { T[x] : x \in DOMAIN T }
LOCAL testmessages ==  <<  [text |-> <<"w","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>, 
                        id |-> <<"t","i","0">>],
        [text |-> <<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>, 
                        id |-> <<"t","i","0">> ],
        [text |-> <<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>, 
                        id |-> <<"t","i","1">> ],              
        [text |-> <<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>, 
                        id |-> <<"t","i","1">>],
        [text |-> <<":","1","1","0","3","0","0","6","B","0","0","0",":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>, \*this one starts a new modbus packet half way through the message 
                        id |-> <<"t","i","3">> ],
        [text |-> <<":","1","1","0","3","0","0","6","B","0","0","0",":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>, \*this one starts a new modbus packet half way through the message 
                        id |-> <<"t","i","3">>]
      >>
                       
HMAC(str, pass) == <<"l","o","l","h","m","a","c">> \*not concerned with the inner workings of SHA2

SendMessage(str) == TRUE \*sending message to another cell. Assuming this works

(*--fair algorithm Sign

variables   msg = <<>>,
            generated_hmac = <<>>,
            incomingMessages = testmessages,
            output = <<>>
begin
to1: while Len(incomingMessages) > 0 do
        if Len(incomingMessages) = 1 then
            msg := incomingMessages[1];
            incomingMessages := <<>>;
        else
            msg := Head(incomingMessages);
            incomingMessages := Tail(incomingMessages);
        end if;
         \*receive("sign", msg);
         sign2: generated_hmac := HMAC(msg.text, PASSWORD); \*hash it and the password
         \*sign3: send("untrustnet_out", [id|->msg.id, hmac|->generated_hmac, source|->"sign", isValid|->TRUE, text|->msg.text]);
         output := Append(output, [id|->msg.id, hmac|->generated_hmac, source|->"sign", isValid|->TRUE, text|->msg.text]);
         end while;

end algorithm
*)
\* BEGIN TRANSLATION
VARIABLES msg, generated_hmac, incomingMessages, output, pc

vars == << msg, generated_hmac, incomingMessages, output, pc >>

Init == (* Global variables *)
        /\ msg = <<>>
        /\ generated_hmac = <<>>
        /\ incomingMessages = testmessages
        /\ output = <<>>
        /\ pc = "to1"

to1 == /\ pc = "to1"
       /\ IF Len(incomingMessages) > 0
             THEN /\ IF Len(incomingMessages) = 1
                        THEN /\ msg' = incomingMessages[1]
                             /\ incomingMessages' = <<>>
                        ELSE /\ msg' = Head(incomingMessages)
                             /\ incomingMessages' = Tail(incomingMessages)
                  /\ pc' = "sign2"
             ELSE /\ pc' = "Done"
                  /\ UNCHANGED << msg, incomingMessages >>
       /\ UNCHANGED << generated_hmac, output >>

sign2 == /\ pc = "sign2"
         /\ generated_hmac' = HMAC(msg.text, PASSWORD)
         /\ output' = Append(output, [id|->msg.id, hmac|->generated_hmac', source|->"sign", isValid|->TRUE, text|->msg.text])
         /\ pc' = "to1"
         /\ UNCHANGED << msg, incomingMessages >>

Next == to1 \/ sign2
           \/ (* Disjunct to prevent deadlock on termination *)
              (pc = "Done" /\ UNCHANGED vars)

Spec == /\ Init /\ [][Next]_vars
        /\ WF_vars(Next)

Termination == <>(pc = "Done")

\* END TRANSLATION

\*SAFETYCHECK ==
    \*message sent is exactly what was received
SAFE1 == \A x \in Range(output) : \E y \in Range(testmessages) : y.text = x.text 
    \* output has good hash
SAFE2 == \A x \in Range(output) : x.hmac = HMAC(msg.text, PASSWORD)
    \*buffers don't overflow
SAFE3 == /\ IF msg /= <<>>
            THEN Len(msg.text) <= MAXMODBUSSIZE
            ELSE TRUE
         /\ \A x \in Range(output) : Len(x.text) <= MAXMODBUSSIZE
         /\ \/ Len(generated_hmac) = Len(HMAC("anything","here")) 
            \/ Len(generated_hmac) = 0
    \* the password is never changed
SAFE4 == PASSWORD = "lolpassword"
    
\*LIVELINESS ==
    \* if we get a message then something is eventually sent sent
LIVE1 == <>[](Len(incomingMessages) = 0)
    \*/\ Len(bareMessage) >= MINMESSAGESIZE ~> result = TRUE
LIVE2 == <>[](Len(output) = Len(testmessages))
    \* if we get a message it is eventually processed
LIVE3 == \A x \in Range(testmessages) : <>(\E y \in Range(output) : y.text = x.text /\ y.id=x.id)
    \*/\ Len(bareMessage) >= MINMESSAGESIZE ~> IsSSW(macMessage)


=============================================================================
\* Modification History
\* Last modified Mon Jul 08 17:38:01 EDT 2019 by mehdi
\* Last modified Tue May 08 03:38:23 EDT 2018 by SabraouM
\* Created Sun May 06 15:34:11 EDT 2018 by SabraouM
