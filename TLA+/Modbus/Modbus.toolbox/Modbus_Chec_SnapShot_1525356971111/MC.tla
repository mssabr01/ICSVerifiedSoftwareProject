---- MODULE MC ----
EXTENDS Modbus, TLC

\* CONSTANT definitions @modelParameterConstants:0N
const_1525356967998107000 == 
2
----

\* INIT definition @modelBehaviorNoSpec:0
init_1525356967998108000 ==
FALSE/\hexValue = 0
----
\* NEXT definition @modelBehaviorNoSpec:0
next_1525356967998109000 ==
FALSE/\hexValue' = hexValue
----
=============================================================================
\* Modification History
\* Created Thu May 03 10:16:07 EDT 2018 by SabraouM
