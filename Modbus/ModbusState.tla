--------------------------- MODULE ModbusState ---------------------------
EXTENDS Integers
VARIABLES i, pc, addr1, addr2, func1, func2, data, delimiter

TypeOK == addr1 \in 0..16 /\ addr2 \in 0..16

Init == (pc = "start") /\ addr1 = 0 /\ addr2 = 0 /\ func1 = 0 /\ func2 = 0 /\ data = "" /\ delimiter = ""
         
Addr1 == /\ pc = "addr1"
            /\ i' = i + 1
            /\ pc' = "addr2"

Addr2 == /\ pc = "addr1"
            /\ i' = i + 1
            /\ pc' = "func1"
    
Func1 == /\ pc = "func1"
            /\ i' = i + 1
            /\ pc' = "func2"

Func2 == /\ pc = "func2"
            /\ i' = i + 1
            /\ pc' = "data"     
            
Data == /\ pc = "data"
        /\ pc' = "data" \/ "end"
        
End == /\ pc = "end"

Next == Init

Valid == End


=============================================================================
\* Modification History
\* Last modified Tue Mar 06 12:25:54 EST 2018 by SabraouM
\* Created Thu Jan 18 14:33:25 EST 2018 by SabraouM
