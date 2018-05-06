---- MODULE MC ----
EXTENDS Receive, TLC

\* SPECIFICATION definition @modelBehaviorSpec:0
spec_1525566084827409000 ==
Spec
----
\* INVARIANT definition @modelCorrectnessInvariants:0
inv_1525566084827410000 ==
OnlyModbus
----
\* INVARIANT definition @modelCorrectnessInvariants:1
inv_1525566084827411000 ==
NoAppOverflow
----
\* INVARIANT definition @modelCorrectnessInvariants:2
inv_1525566084827412000 ==
NoOverflow
----
\* INVARIANT definition @modelCorrectnessInvariants:3
inv_1525566084827413000 ==
NoMBNoFlag
----
\* PROPERTY definition @modelCorrectnessProperties:0
prop_1525566084827414000 ==
Termination
----
\* PROPERTY definition @modelCorrectnessProperties:1
prop_1525566084827415000 ==
ModbusGetsThrough
----
\* PROPERTY definition @modelCorrectnessProperties:2
prop_1525566084827416000 ==
ModbusGetsFlagged
----
=============================================================================
\* Modification History
\* Created Sat May 05 20:21:24 EDT 2018 by SabraouM
