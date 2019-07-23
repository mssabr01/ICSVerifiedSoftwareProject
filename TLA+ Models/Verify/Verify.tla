------------------------------ MODULE Verify ------------------------------

EXTENDS Sequences, Naturals, EncapPacket, Modbus

LOCAL HMACSIZE == 64
LOCAL START == "!" 
LOCAL MINMESSAGESIZE == 65
LOCAL PASSWORD == "lolpassword"
LOCAL Range(T) == { T[x] : x \in DOMAIN T }
HMAC == <<"0","5","b","7","1","b","9","3",
          "0","3","a","d","6","c","7","4",
          "E","6","2","3","7","a","2","7",
          "5","6","c","9","5","f","8","3",
          "e","c","8","8","7","e","d","9",
          "c","c","9","a","2","f","7","1",
          "d","6","d","6","6","d","6","0",
          "d","3","9","2","e","c","4","2">> \*not concerned with the inner workings of SHA2

signedMessages == \*these are in ASCII but they are converted to decimal before being used below. See StrTupleToNumTuple in ASCII.tla
    <<  [text |-> <<"!">> \o HMAC \o <<"1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>, 
                        id |-> <<"u","t","i","1">> ],              
        [text |-> <<":">> \o HMAC \o <<"1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>, 
                        id |-> <<"u","t","i","1">> ],
        [text |-> <<":">> \o HMAC \o <<"1","1","0","3","0","0","6","B","0","0","0",":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>, \*this one starts a new modbus packet half way through the message 
                        id |-> <<"u","t","i","3">>],
        [text |-> <<":">> \o HMAC \o <<"1","1","0","3","0","0","6","B","0","0","0",":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>, \*this one starts a new modbus packet half way through the message 
                        id |-> <<"u","t","i","3">>]
      >>
                       
genHMAC(str, pass) == <<"l","o","l","h","m","a","c">> \*not concerned with the inner workings of SHA2

SendMessage(str) == TRUE \*sending message to another cell. Assuming this works

(*--fair algorithm Verify

variables   msg = <<>>,
            retreivedHMAC = <<>>,
            incomingMessages = signedMessages,
            generatedHMAC = <<>>,
            CompareHMAC \in BOOLEAN, \*since we dont model SHA2 this is random
            trustnet_out = <<>>,
            hmacsMatch = FALSE
begin
to1: while Len(incomingMessages) > 0 do
        if Len(incomingMessages) = 1 then
            msg := incomingMessages[1];
            incomingMessages := <<>>;
        else
            msg := Head(incomingMessages);
            incomingMessages := Tail(incomingMessages);
        end if;
        
        \*receive("verify", msg);
        verify2: retreivedHMAC := GetHMAC(msg.text);
        verify3: generatedHMAC := genHMAC(msg.text, PASSWORD);
        verify4: hmacsMatch := CompareHMAC;
        if hmacsMatch then
            \*verify5: send("trustnet_out", [id|->msg.id, isValid|->TRUE, source|->"verify", text|->msg.text]);
            trustnet_out := Append(trustnet_out, [id|->msg.id, isValid|->TRUE, source|->"verify", text|->msg.text]);
        else
            \*verify6: send("trustnet_out", [id|->msg.id, isValid|->FALSE, source|->"verify", text|->msg.text]);
            trustnet_out := Append(trustnet_out, [id|->msg.id, isValid|->FALSE, source|->"verify", text|->msg.text]);
        end if;
    end while;

end algorithm

*)
\* BEGIN TRANSLATION
VARIABLES msg, retreivedHMAC, incomingMessages, generatedHMAC, CompareHMAC, 
          trustnet_out, hmacsMatch, pc

vars == << msg, retreivedHMAC, incomingMessages, generatedHMAC, CompareHMAC, 
           trustnet_out, hmacsMatch, pc >>

Init == (* Global variables *)
        /\ msg = <<>>
        /\ retreivedHMAC = <<>>
        /\ incomingMessages = signedMessages
        /\ generatedHMAC = <<>>
        /\ CompareHMAC \in BOOLEAN
        /\ trustnet_out = <<>>
        /\ hmacsMatch = FALSE
        /\ pc = "to1"

to1 == /\ pc = "to1"
       /\ IF Len(incomingMessages) > 0
             THEN /\ IF Len(incomingMessages) = 1
                        THEN /\ msg' = incomingMessages[1]
                             /\ incomingMessages' = <<>>
                        ELSE /\ msg' = Head(incomingMessages)
                             /\ incomingMessages' = Tail(incomingMessages)
                  /\ pc' = "verify2"
             ELSE /\ pc' = "Done"
                  /\ UNCHANGED << msg, incomingMessages >>
       /\ UNCHANGED << retreivedHMAC, generatedHMAC, CompareHMAC, trustnet_out, 
                       hmacsMatch >>

verify2 == /\ pc = "verify2"
           /\ retreivedHMAC' = GetHMAC(msg.text)
           /\ pc' = "verify3"
           /\ UNCHANGED << msg, incomingMessages, generatedHMAC, CompareHMAC, 
                           trustnet_out, hmacsMatch >>

verify3 == /\ pc = "verify3"
           /\ generatedHMAC' = genHMAC(msg.text, PASSWORD)
           /\ pc' = "verify4"
           /\ UNCHANGED << msg, retreivedHMAC, incomingMessages, CompareHMAC, 
                           trustnet_out, hmacsMatch >>

verify4 == /\ pc = "verify4"
           /\ hmacsMatch' = CompareHMAC
           /\ IF hmacsMatch'
                 THEN /\ trustnet_out' = Append(trustnet_out, [id|->msg.id, isValid|->TRUE, source|->"verify", text|->msg.text])
                 ELSE /\ trustnet_out' = Append(trustnet_out, [id|->msg.id, isValid|->FALSE, source|->"verify", text|->msg.text])
           /\ pc' = "to1"
           /\ UNCHANGED << msg, retreivedHMAC, incomingMessages, generatedHMAC, 
                           CompareHMAC >>

Next == to1 \/ verify2 \/ verify3 \/ verify4
           \/ (* Disjunct to prevent deadlock on termination *)
              (pc = "Done" /\ UNCHANGED vars)

Spec == /\ Init /\ [][Next]_vars
        /\ WF_vars(Next)

Termination == <>(pc = "Done")

\* END TRANSLATION

\*SAFETYCHECK ==
        \* The password is never changed
 \*      /\ PASSWORD = "lolpassword"
SAFE1 == PASSWORD = "lolpassword"
        \* if we send something then it was valid SSW
   \*     /\ flag = TRUE => IsSSW(signedMessage)
SAFE2 == \A x \in Range(trustnet_out) : \E y \in Range(signedMessages) : y.text = x.text 
    \*buffers don't overflow
SAFE3 == /\ IF msg /= <<>>
            THEN Len(msg.text) <= MAXMODBUSSIZE
            ELSE TRUE
         /\ \A x \in Range(trustnet_out) : Len(x.text) <= MAXMODBUSSIZE
         /\ \/ Len(retreivedHMAC) = 64
            \/ Len(retreivedHMAC) = 0

\*LIVELINESS ==
    \* if we get a message then something is eventually sent sent
LIVE1 == <>[](Len(incomingMessages) = 0)
    \*/\ Len(bareMessage) >= MINMESSAGESIZE ~> result = TRUE
LIVE2 == <>[](Len(trustnet_out) = Len(signedMessages))
    \* if we get a message it is eventually processed
LIVE3 == \A x \in Range(signedMessages) : <>(\E y \in Range(trustnet_out) : y.text = x.text /\ y.id=x.id)
    \*/\ Len(bareMessage) >= MINMESSAGESIZE ~> IsSSW(macMessage)
=============================================================================
\* Modification History
\* Last modified Mon Jul 08 18:01:10 EDT 2019 by mehdi
\* Last modified Tue May 08 03:43:33 EDT 2018 by SabraouM
\* Created Sun May 06 09:03:31 EDT 2018 by SabraouM
