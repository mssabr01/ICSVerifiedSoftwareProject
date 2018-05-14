---- MODULE MC ----
EXTENDS TCommit, TLC

\* CONSTANT definitions @modelParameterConstants:0RM
const_15173264336706000 == 
{"r1","r2","r3"}
----

\* INIT definition @modelBehaviorInit:0
init_15173264336707000 ==
TCInit
----
\* NEXT definition @modelBehaviorNext:0
next_15173264336718000 ==
TCNext
----
\* INVARIANT definition @modelCorrectnessInvariants:0
inv_15173264336719000 ==
TCTypeOK
----
=============================================================================
\* Modification History
\* Created Tue Jan 30 10:33:53 EST 2018 by SabraouM
