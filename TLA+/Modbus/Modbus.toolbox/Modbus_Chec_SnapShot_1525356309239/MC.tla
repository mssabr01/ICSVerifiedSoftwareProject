---- MODULE MC ----
EXTENDS Modbus, TLC

\* CONSTANT definitions @modelParameterConstants:0N
const_1525356306119101000 == 
2
----

\* INIT definition @modelBehaviorNoSpec:0
init_1525356306119102000 ==
FALSE/\hexValue = 0
----
\* NEXT definition @modelBehaviorNoSpec:0
next_1525356306119103000 ==
FALSE/\hexValue' = hexValue
----
=============================================================================
\* Modification History
\* Created Thu May 03 10:05:06 EDT 2018 by SabraouM
