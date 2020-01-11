------------------------- MODULE BufferNotification -------------------------
EXTENDS Sequences, FiniteSets, Naturals, TLC
LOCAL Range(T) == { T[x] : x \in DOMAIN T }
CONSTANT numBuff
ASSUME numBuff > 0


(* --fair algorithm BufferNotification

variables 
    buffers = [buffer \in 1..numBuff |-> "lol hello"],
    note_objects = [note \in 1..numBuff |-> 0],
    
\* IPC calls
macro send(dest, msg) 
    begin
        \*print "sending to " \o dest;
        \*chan[dest] := Append(chan[dest], msg);
    end macro;

\*convert this to 'notify
\*it sets a notification object to '1'
\*have some other way that processes can register to listen to notification objects
macro receive(channel, msg) 
    begin
    (*
        \*print channel \o " received msg";
        await Len(chan[channel]) > 0;
        msg := Head(chan[channel]);
        chan[channel] := Tail(chan[channel]);
        *)
    end macro;

\* Signing process.
fair process consumer = "consumer"

variables   selectedBuffer;
begin
consume1:   while TRUE do
                \*select a single buffer in buffers that is not empty
                selectedBuffer := CHOOSE n \in 1..numBuff : TRUE;
                print selectedBuffer;
                print buffers[selectedBuffer];
                \*consume buffer
                buffers[selectedBuffer] := <<>>;
                \*signal notification object for said buffer
                
            end while;
end process
\*=========================================

\*Check validitity of the underlying protocol. In this case Modbus
fair process producer \in 1..numBuff

variables   msg = <<>>
            
begin
produce1:    while TRUE do
            \*get notification somehow
            \*fill buffer with some shit
            print self;
            buffers[self] := "lol I'm full xD";
            end while;
                
end process

end algorithm;*)
\* BEGIN TRANSLATION
CONSTANT defaultInitValue
VARIABLES buffers, note_objects, selectedBuffer, msg

vars == << buffers, note_objects, selectedBuffer, msg >>

ProcSet == {"consumer"} \cup (1..numBuff)

Init == (* Global variables *)
        /\ buffers = [buffer \in 1..numBuff |-> "lol hello"]
        /\ note_objects = [note \in 1..numBuff |-> 0]
        (* Process consumer *)
        /\ selectedBuffer = defaultInitValue
        (* Process producer *)
        /\ msg = [self \in 1..numBuff |-> <<>>]

consumer == /\ selectedBuffer' = (CHOOSE n \in 1..numBuff : TRUE)
            /\ PrintT(selectedBuffer')
            /\ PrintT(buffers[selectedBuffer'])
            /\ buffers' = [buffers EXCEPT ![selectedBuffer'] = <<>>]
            /\ UNCHANGED << note_objects, msg >>

producer(self) == /\ PrintT(self)
                  /\ buffers' = [buffers EXCEPT ![self] = "lol I'm full xD"]
                  /\ UNCHANGED << note_objects, selectedBuffer, msg >>

Next == consumer
           \/ (\E self \in 1..numBuff: producer(self))

Spec == /\ Init /\ [][Next]_vars
        /\ WF_vars(Next)
        /\ WF_vars(consumer)
        /\ \A self \in 1..numBuff : WF_vars(producer(self))

\* END TRANSLATION


(*
    \*modbus check module:
SAFE1 == \A m \in Range(chan["messagecheck"]) : Len(m.text) <= MAXMODBUSSIZE \*only messages with a valid length make it to the checking module
    \*messages going to untrusted network
SAFE2 == \A m \in validMessages : m.isValid = TRUE \*message parts waiting for their counterpart are valid
SAFE3 == \A m \in Range(chan["finished_untrustnet"]) : GetHMAC(m) = HMAC(m,m) \*only properly signed messages are sent to untrustnet
SAFE4 == \A m \in Range(chan["finished_untrustnet"]) : IsModbus(GetModbus(m)) \*only properly formed modbus is sent with signature to untrustnet
    \*messages going to trusted network:
SAFE5 == \A m \in validMessages_ : m.isValid = TRUE \*message parts waiting for their counterpart are valid
SAFE6 == \A m \in Range(chan["finished_trustnet"]) : IsModbus(m) \*only properly formed modbus is sent to trustnet
    
LIVENESS ==
   /\ <>(Len(incomingMessages_) = 0)
   /\ <>(Len(incomingMessages) = 0)
   /\ <>(Len(chan["finished_untrustnet"]) > 0)
   /\ <>(Len(chan["finished_trustnet"]) > 0)
   \* counterpart will eventually come
   \*/\ \A p \in validMessages_ : <>(msg_tr.id = p.id /\ msg_tr.source /= p.source ) 
   \*modbus check module:
   \*/\ \A p \in Range(chan["messagecheck"]), \E q \in Range(chan["untrustnet_out"]) : p.source = "trustnet_in" ~> : p.id = q.id
*)



=============================================================================
\* Modification History
\* Last modified Mon Nov 11 13:58:19 EST 2019 by msabraoui
\* Created Wed Oct 23 20:41:48 EDT 2019 by msabraoui