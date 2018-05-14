---- MODULE MC ----
EXTENDS Modbus, TLC

\* CONSTANT definitions @modelParameterConstants:0N
const_1525360314999116000 == 
2
----

\* INIT definition @modelBehaviorNoSpec:0
init_1525360314999117000 ==
FALSE/\hexValue = 0
----
\* NEXT definition @modelBehaviorNoSpec:0
next_1525360314999118000 ==
FALSE/\hexValue' = hexValue
----
=============================================================================
\* Modification History
\* Created Thu May 03 11:11:54 EDT 2018 by SabraouM
