------------------------------ MODULE diehard ------------------------------
\* from the 1995 movie Die Hard 3. Bruce Willis 
EXTENDS Integers

VARIABLES smol, big

TypeOK == /\ smol \in 0..3
          /\ big  \in 0..5

Init == /\ big  = 0
        /\ smol = 0

FillSmol == /\ smol' = 3
            /\ big'  = big

FillBig  == /\ smol' = smol
            /\ big'  = 5

EmptySmol == /\ smol' = 0
             /\ big'  = big

EmptyBig  == /\ big'  = 0
             /\ smol' = smol

SmolToBig == IF big + smol <= 5
                THEN /\ smol' = 0
                     /\ big'  = big + smol
                ELSE
                     /\ big' = 5
                     /\ smol' = 5 - big
                    
BigToSmol == IF big + smol <= 3
                THEN
                     /\ smol' = big + smol
                     /\ big'  = 0
                ELSE
                     /\ smol' = 3
                     /\ big'  = 3 - smol

Next == \/ FillSmol      \*fill a jug
        \/ FillBig
        \/ EmptySmol
        \/ EmptyBig
        \/ SmolToBig
        \/ BigToSmol
=============================================================================
\* Modification History
\* Last modified Fri Jan 26 21:48:06 EST 2018 by SabraouM
\* Created Fri Jan 26 21:25:13 EST 2018 by SabraouM
