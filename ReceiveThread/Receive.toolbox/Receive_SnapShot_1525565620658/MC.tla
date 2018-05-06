---- MODULE MC ----
EXTENDS Receive, TLC

\* SPECIFICATION definition @modelBehaviorSpec:0
spec_1525565607431353000 ==
Spec
----
\* INVARIANT definition @modelCorrectnessInvariants:0
inv_1525565607432354000 ==
OnlyModbus
----
\* INVARIANT definition @modelCorrectnessInvariants:1
inv_1525565607432355000 ==
NoAppOverflow
----
\* INVARIANT definition @modelCorrectnessInvariants:2
inv_1525565607432356000 ==
NoOverflow
----
\* INVARIANT definition @modelCorrectnessInvariants:3
inv_1525565607432357000 ==
NoMBNoFlag
----
\* PROPERTY definition @modelCorrectnessProperties:0
prop_1525565607432358000 ==
Termination
----
\* PROPERTY definition @modelCorrectnessProperties:1
prop_1525565607432359000 ==
ModbusGetsThrough
----
\* PROPERTY definition @modelCorrectnessProperties:2
prop_1525565607432360000 ==
ModbusGetsFlagged
----
=============================================================================
\* Modification History
\* Created Sat May 05 20:13:27 EDT 2018 by SabraouM
