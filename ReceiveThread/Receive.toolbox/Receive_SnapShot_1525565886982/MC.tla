---- MODULE MC ----
EXTENDS Receive, TLC

\* SPECIFICATION definition @modelBehaviorSpec:0
spec_1525565874549377000 ==
Spec
----
\* INVARIANT definition @modelCorrectnessInvariants:0
inv_1525565874549378000 ==
OnlyModbus
----
\* INVARIANT definition @modelCorrectnessInvariants:1
inv_1525565874549379000 ==
NoAppOverflow
----
\* INVARIANT definition @modelCorrectnessInvariants:2
inv_1525565874549380000 ==
NoOverflow
----
\* INVARIANT definition @modelCorrectnessInvariants:3
inv_1525565874549381000 ==
NoMBNoFlag
----
\* PROPERTY definition @modelCorrectnessProperties:0
prop_1525565874549382000 ==
Termination
----
\* PROPERTY definition @modelCorrectnessProperties:1
prop_1525565874549383000 ==
ModbusGetsThrough
----
\* PROPERTY definition @modelCorrectnessProperties:2
prop_1525565874549384000 ==
ModbusGetsFlagged
----
=============================================================================
\* Modification History
\* Created Sat May 05 20:17:54 EDT 2018 by SabraouM
