---- MODULE MC ----
EXTENDS Modbus, TLC

\* CONSTANT definitions @modelParameterConstants:0N
const_1525357006636110000 == 
2
----

\* INIT definition @modelBehaviorNoSpec:0
init_1525357006636111000 ==
FALSE/\hexValue = 0
----
\* NEXT definition @modelBehaviorNoSpec:0
next_1525357006636112000 ==
FALSE/\hexValue' = hexValue
----
=============================================================================
\* Modification History
\* Created Thu May 03 10:16:46 EDT 2018 by SabraouM
