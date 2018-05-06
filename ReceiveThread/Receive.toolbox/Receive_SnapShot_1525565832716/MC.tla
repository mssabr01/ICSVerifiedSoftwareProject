---- MODULE MC ----
EXTENDS Receive, TLC

\* SPECIFICATION definition @modelBehaviorSpec:0
spec_1525565818359369000 ==
Spec
----
\* INVARIANT definition @modelCorrectnessInvariants:0
inv_1525565818359370000 ==
OnlyModbus
----
\* INVARIANT definition @modelCorrectnessInvariants:1
inv_1525565818359371000 ==
NoAppOverflow
----
\* INVARIANT definition @modelCorrectnessInvariants:2
inv_1525565818359372000 ==
NoOverflow
----
\* INVARIANT definition @modelCorrectnessInvariants:3
inv_1525565818359373000 ==
NoMBNoFlag
----
\* PROPERTY definition @modelCorrectnessProperties:0
prop_1525565818359374000 ==
Termination
----
\* PROPERTY definition @modelCorrectnessProperties:1
prop_1525565818359375000 ==
ModbusGetsThrough
----
\* PROPERTY definition @modelCorrectnessProperties:2
prop_1525565818359376000 ==
ModbusGetsFlagged
----
=============================================================================
\* Modification History
\* Created Sat May 05 20:16:58 EDT 2018 by SabraouM
