---- MODULE MC ----
EXTENDS Modbus, TLC

\* CONSTANT definitions @modelParameterConstants:0N
const_1525360203007113000 == 
2
----

\* INIT definition @modelBehaviorNoSpec:0
init_1525360203008114000 ==
FALSE/\hexValue = 0
----
\* NEXT definition @modelBehaviorNoSpec:0
next_1525360203008115000 ==
FALSE/\hexValue' = hexValue
----
=============================================================================
\* Modification History
\* Created Thu May 03 11:10:03 EDT 2018 by SabraouM
