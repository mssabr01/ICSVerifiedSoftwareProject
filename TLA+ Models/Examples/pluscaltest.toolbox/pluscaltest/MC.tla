---- MODULE MC ----
EXTENDS pluscaltest, TLC

\* CONSTANT definitions @modelParameterConstants:0N
const_15223464721967000 == 
3
----

\* SPECIFICATION definition @modelBehaviorSpec:0
spec_15223464721968000 ==
Spec
----
\* INVARIANT definition @modelCorrectnessInvariants:0
inv_15223464721969000 ==
\forall p,q \in 1..N : (p\=q) => ~((pc[p] = "cs") /\ (pc[q] = "cs"))
----
=============================================================================
\* Modification History
\* Created Thu Mar 29 14:01:12 EDT 2018 by SabraouM
