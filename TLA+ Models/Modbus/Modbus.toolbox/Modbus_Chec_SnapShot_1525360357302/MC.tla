---- MODULE MC ----
EXTENDS Modbus, TLC

\* CONSTANT definitions @modelParameterConstants:0N
const_1525360354186119000 == 
2
----

\* INIT definition @modelBehaviorNoSpec:0
init_1525360354186120000 ==
FALSE/\hexValue = 0
----
\* NEXT definition @modelBehaviorNoSpec:0
next_1525360354186121000 ==
FALSE/\hexValue' = hexValue
----
=============================================================================
\* Modification History
\* Created Thu May 03 11:12:34 EDT 2018 by SabraouM
