---- MODULE MC ----
EXTENDS auth_device, TLC

\* SPECIFICATION definition @modelBehaviorSpec:0
spec_154034544323774000 ==
Spec
----
\* INVARIANT definition @modelCorrectnessInvariants:0
inv_154034544323775000 ==
\forall message \in validMessages : message.isValid = TRUE
----
=============================================================================
\* Modification History
\* Created Tue Oct 23 21:44:03 EDT 2018 by userMehdi
