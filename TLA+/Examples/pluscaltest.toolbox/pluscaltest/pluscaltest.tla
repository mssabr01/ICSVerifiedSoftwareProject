---------------------------- MODULE pluscaltest ----------------------------

EXTENDS Naturals, TLC
CONSTANT N

(*
--algorithm FastMutex
{ variables x = 0, y = 0, b = [i \in 1 .. N |-> FALSE] ;
process (Proc \in  1 .. N )
variable j ;
{ ncs: skip ; (* The Noncritical Section *)
start: b[self ] := TRUE;
lab1: x := self;
lab2: if (y /= 0) { lab3: b[self ] := FALSE;
lab4: await y = 0;
goto start };
lab5: y := self;
lab6: if (x /= self ) { lab7: b[self ] := FALSE;
j := 1;
lab8: while (j <= N ) { await ~b[j];
j := j + 1 };
lab9: if (y /= self ) { lab10: await y = 0;
goto start }};
cs: skip; (* The Critical Section *)
lab11: y := 0;
lab12: b[self ] := FALSE;
goto ncs }}

*)
\* BEGIN TRANSLATION
CONSTANT defaultInitValue
VARIABLES x, y, b, pc, j

vars == << x, y, b, pc, j >>

ProcSet == (1 .. N)

Init == (* Global variables *)
        /\ x = 0
        /\ y = 0
        /\ b = [i \in 1 .. N |-> FALSE]
        (* Process Proc *)
        /\ j = [self \in 1 .. N |-> defaultInitValue]
        /\ pc = [self \in ProcSet |-> "ncs"]

ncs(self) == /\ pc[self] = "ncs"
             /\ TRUE
             /\ pc' = [pc EXCEPT ![self] = "start"]
             /\ UNCHANGED << x, y, b, j >>

start(self) == /\ pc[self] = "start"
               /\ b' = [b EXCEPT ![self ] = TRUE]
               /\ pc' = [pc EXCEPT ![self] = "lab1"]
               /\ UNCHANGED << x, y, j >>

lab1(self) == /\ pc[self] = "lab1"
              /\ x' = self
              /\ pc' = [pc EXCEPT ![self] = "lab2"]
              /\ UNCHANGED << y, b, j >>

lab2(self) == /\ pc[self] = "lab2"
              /\ IF y /= 0
                    THEN /\ pc' = [pc EXCEPT ![self] = "lab3"]
                    ELSE /\ pc' = [pc EXCEPT ![self] = "lab5"]
              /\ UNCHANGED << x, y, b, j >>

lab3(self) == /\ pc[self] = "lab3"
              /\ b' = [b EXCEPT ![self ] = FALSE]
              /\ pc' = [pc EXCEPT ![self] = "lab4"]
              /\ UNCHANGED << x, y, j >>

lab4(self) == /\ pc[self] = "lab4"
              /\ y = 0
              /\ pc' = [pc EXCEPT ![self] = "start"]
              /\ UNCHANGED << x, y, b, j >>

lab5(self) == /\ pc[self] = "lab5"
              /\ y' = self
              /\ pc' = [pc EXCEPT ![self] = "lab6"]
              /\ UNCHANGED << x, b, j >>

lab6(self) == /\ pc[self] = "lab6"
              /\ IF x /= self
                    THEN /\ pc' = [pc EXCEPT ![self] = "lab7"]
                    ELSE /\ pc' = [pc EXCEPT ![self] = "cs"]
              /\ UNCHANGED << x, y, b, j >>

lab7(self) == /\ pc[self] = "lab7"
              /\ b' = [b EXCEPT ![self ] = FALSE]
              /\ j' = [j EXCEPT ![self] = 1]
              /\ pc' = [pc EXCEPT ![self] = "lab8"]
              /\ UNCHANGED << x, y >>

lab8(self) == /\ pc[self] = "lab8"
              /\ IF j[self] <= N
                    THEN /\ ~b[j[self]]
                         /\ j' = [j EXCEPT ![self] = j[self] + 1]
                         /\ pc' = [pc EXCEPT ![self] = "lab8"]
                    ELSE /\ pc' = [pc EXCEPT ![self] = "lab9"]
                         /\ j' = j
              /\ UNCHANGED << x, y, b >>

lab9(self) == /\ pc[self] = "lab9"
              /\ IF y /= self
                    THEN /\ pc' = [pc EXCEPT ![self] = "lab10"]
                    ELSE /\ pc' = [pc EXCEPT ![self] = "cs"]
              /\ UNCHANGED << x, y, b, j >>

lab10(self) == /\ pc[self] = "lab10"
               /\ y = 0
               /\ pc' = [pc EXCEPT ![self] = "start"]
               /\ UNCHANGED << x, y, b, j >>

cs(self) == /\ pc[self] = "cs"
            /\ TRUE
            /\ pc' = [pc EXCEPT ![self] = "lab11"]
            /\ UNCHANGED << x, y, b, j >>

lab11(self) == /\ pc[self] = "lab11"
               /\ y' = 0
               /\ pc' = [pc EXCEPT ![self] = "lab12"]
               /\ UNCHANGED << x, b, j >>

lab12(self) == /\ pc[self] = "lab12"
               /\ b' = [b EXCEPT ![self ] = FALSE]
               /\ pc' = [pc EXCEPT ![self] = "ncs"]
               /\ UNCHANGED << x, y, j >>

Proc(self) == ncs(self) \/ start(self) \/ lab1(self) \/ lab2(self)
                 \/ lab3(self) \/ lab4(self) \/ lab5(self) \/ lab6(self)
                 \/ lab7(self) \/ lab8(self) \/ lab9(self) \/ lab10(self)
                 \/ cs(self) \/ lab11(self) \/ lab12(self)

Next == (\E self \in 1 .. N: Proc(self))
           \/ (* Disjunct to prevent deadlock on termination *)
              ((\A self \in ProcSet: pc[self] = "Done") /\ UNCHANGED vars)

Spec == Init /\ [][Next]_vars

Termination == <>(\A self \in ProcSet: pc[self] = "Done")

\* END TRANSLATION


=============================================================================
\* Modification History
\* Last modified Thu Mar 29 13:59:57 EDT 2018 by SabraouM
\* Created Mon Mar 26 15:54:05 EDT 2018 by SabraouM
