---- MODULE MC ----
EXTENDS Receive, TLC

\* SPECIFICATION definition @modelBehaviorSpec:0
spec_1525566028307393000 ==
Spec
----
\* INVARIANT definition @modelCorrectnessInvariants:0
inv_1525566028307394000 ==
OnlyModbus
----
\* INVARIANT definition @modelCorrectnessInvariants:1
inv_1525566028307395000 ==
NoAppOverflow
----
\* INVARIANT definition @modelCorrectnessInvariants:2
inv_1525566028307396000 ==
NoOverflow
----
\* INVARIANT definition @modelCorrectnessInvariants:3
inv_1525566028307397000 ==
NoMBNoFlag
----
\* PROPERTY definition @modelCorrectnessProperties:0
prop_1525566028307398000 ==
Termination
----
\* PROPERTY definition @modelCorrectnessProperties:1
prop_1525566028307399000 ==
ModbusGetsThrough
----
\* PROPERTY definition @modelCorrectnessProperties:2
prop_1525566028307400000 ==
ModbusGetsFlagged
----
=============================================================================
\* Modification History
\* Created Sat May 05 20:20:28 EDT 2018 by SabraouM
