---- MODULE MC ----
EXTENDS TCommit, TLC

\* CONSTANT definitions @modelParameterConstants:0RM
const_15377635098562000 == 
{"r1","r2","r3"}
----

\* INIT definition @modelBehaviorInit:0
init_15377635098563000 ==
TCInit
----
\* NEXT definition @modelBehaviorNext:0
next_15377635098564000 ==
TCNext
----
\* INVARIANT definition @modelCorrectnessInvariants:0
inv_15377635098575000 ==
TCTypeOK
----
\* INVARIANT definition @modelCorrectnessInvariants:1
inv_15377635098576000 ==
TCConsistent
----
=============================================================================
\* Modification History
\* Created Mon Sep 24 00:31:49 EDT 2018 by mssabr01
