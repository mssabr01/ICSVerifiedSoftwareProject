---- MODULE MC ----
EXTENDS Modbus, TLC

\* CONSTANT definitions @modelParameterConstants:0N
const_1525356397223104000 == 
2
----

\* INIT definition @modelBehaviorNoSpec:0
init_1525356397223105000 ==
FALSE/\hexValue = 0
----
\* NEXT definition @modelBehaviorNoSpec:0
next_1525356397223106000 ==
FALSE/\hexValue' = hexValue
----
=============================================================================
\* Modification History
\* Created Thu May 03 10:06:37 EDT 2018 by SabraouM
