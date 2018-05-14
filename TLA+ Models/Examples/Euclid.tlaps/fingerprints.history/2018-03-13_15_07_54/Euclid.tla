------------------------------- MODULE Euclid -------------------------------
EXTENDS Integers

p | q == \E d \in 1..q : q = p * d

Divisors(q) == {d \in 1..q : d | q}

Maximum(S) == CHOOSE x \in S : \A y \in S : x>= y

GCD(p,q) == Maximum(Divisors(p) \cap Divisors(q))

Number == Nat \ {0}

CONSTANT M, N
VARIABLE x, y

Init == (x = M) /\ (y = N)

Next == \/  /\ x > y
            /\ y' = y
            /\ x' = x - y
        \/  /\ y > x
            /\ x' = x
            /\ y' = y-x

Spec == Init /\ [][Next]_<<x,y>>

ResultCorrect == (x = y) => x = GCD(M,N)

THEOREM Correctness == Spec => []ResultCorrect

InductiveInvariant ==  /\ x \in Number
                       /\ y \in Number
                       /\ GCD(x,y) = GCD(M,N)
                       
ASSUME NumberASsumptions == M \in Number /\ N \in Number

THEOREM InitProperty == Init => InductiveInvariant
    BY DEF Init, InductiveInvariant 

=============================================================================
\* Modification History
\* Last modified Tue Mar 13 15:07:52 EDT 2018 by SabraouM
\* Created Mon Mar 12 18:44:22 EDT 2018 by SabraouM
