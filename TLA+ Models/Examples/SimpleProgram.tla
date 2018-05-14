--------------------------- MODULE ModbusState ---------------------------
EXTENDS Integers
VARIABLES i, pc, buff

Init == (pc = "start") /\ (i = 0) /\ (buff = 0)

Start == /\ pc = "start"  
         /\ i' = 1
         /\ pc' = "addr1"
         /\ buff' = ":"
         
Addr1 == /\ pc = "addr1"
            /\ buff = ":" 
            /\ i' = i + 1
            /\ pc' = "addr2"
            /\ buff' \in 0 .. 16

Addr2 == /\ pc = "addr1"
            /\ buff = ":" 
            /\ i' = i + 1
            /\ pc' = "func1"
            /\ buff' \in 0 .. 16
    
Func1 == /\ pc = "func1"
            /\ buff = ":" 
            /\ i' = i + 1
            /\ pc' = "func2"
            /\ buff' \in 0 .. 16

Func2 == /\ pc = "func2"
            /\ buff = ":" 
            /\ i' = i + 1
            /\ pc' = "data"
            /\ buff' \in 0 .. 16      
            
Data == /\ pc = "data"
        /\ (buff \in 0 .. 255 \/ (buff = 15 /\ buff' = 10))
        /\ pc' = "data" \/ "end"
        
End == /\ pc = "end"
       /\ buff = 10

Next == Init \/ Start

Valid == End


=============================================================================
\* Modification History
\* Last modified Mon Jan 22 12:01:47 EST 2018 by SabraouM
\* Created Thu Jan 18 14:33:25 EST 2018 by SabraouM
