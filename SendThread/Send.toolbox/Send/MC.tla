---- MODULE MC ----
EXTENDS Send, TLC

\* SPECIFICATION definition @modelBehaviorSpec:0
spec_15254864151479000 ==
Spec
----
\* INVARIANT definition @modelCorrectnessInvariants:0
inv_152548641514710000 ==
BUFFOVERFLOW
----
\* INVARIANT definition @modelCorrectnessInvariants:1
inv_152548641514711000 ==
ONLYHEXSENT
----
\* PROPERTY definition @modelCorrectnessProperties:0
prop_152548641514712000 ==
Termination
----
\* PROPERTY definition @modelCorrectnessProperties:1
prop_152548641514713000 ==
ALLSENT
----
\* PROPERTY definition @modelCorrectnessProperties:2
prop_152548641514714000 ==
NOTHANG
----
\* PROPERTY definition @modelCorrectnessProperties:3
prop_152548641514715000 ==
SENDSOMETHING
----
=============================================================================
\* Modification History
\* Created Fri May 04 22:13:35 EDT 2018 by SabraouM
