---- MODULE MC ----
EXTENDS TCommit, TLC

\* CONSTANT definitions @modelParameterConstants:0RM
const_151732879443215000 == 
{"r1","r2","r3"}
----

\* INIT definition @modelBehaviorInit:0
init_151732879443216000 ==
TCInit
----
\* NEXT definition @modelBehaviorNext:0
next_151732879443217000 ==
TCNext
----
\* INVARIANT definition @modelCorrectnessInvariants:0
inv_151732879443218000 ==
TCTypeOK
----
\* INVARIANT definition @modelCorrectnessInvariants:1
inv_151732879443219000 ==
TCConsistent
----
=============================================================================
\* Modification History
\* Created Tue Jan 30 11:13:14 EST 2018 by SabraouM
