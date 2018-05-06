---- MODULE MC ----
EXTENDS Receive, TLC

\* SPECIFICATION definition @modelBehaviorSpec:0
spec_1525614650284425000 ==
Spec
----
\* INVARIANT definition @modelCorrectnessInvariants:0
inv_1525614650284426000 ==
OnlyModbus
----
\* INVARIANT definition @modelCorrectnessInvariants:1
inv_1525614650284427000 ==
NoAppOverflow
----
\* INVARIANT definition @modelCorrectnessInvariants:2
inv_1525614650284428000 ==
NoOverflow
----
\* INVARIANT definition @modelCorrectnessInvariants:3
inv_1525614650284429000 ==
NoMBNoFlag
----
\* PROPERTY definition @modelCorrectnessProperties:0
prop_1525614650284430000 ==
Termination
----
\* PROPERTY definition @modelCorrectnessProperties:1
prop_1525614650284431000 ==
ModbusGetsThrough
----
\* PROPERTY definition @modelCorrectnessProperties:2
prop_1525614650284432000 ==
ModbusGetsFlagged
----
=============================================================================
\* Modification History
\* Created Sun May 06 09:50:50 EDT 2018 by SabraouM
