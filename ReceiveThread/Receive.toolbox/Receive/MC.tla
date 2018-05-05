---- MODULE MC ----
EXTENDS Receive, TLC

\* SPECIFICATION definition @modelBehaviorSpec:0
spec_1525484575300423000 ==
Spec
----
\* INVARIANT definition @modelCorrectnessInvariants:0
inv_1525484575300424000 ==
ONLYHEXSENT
----
\* INVARIANT definition @modelCorrectnessInvariants:1
inv_1525484575300425000 ==
BUFFOVERFLOW
----
\* PROPERTY definition @modelCorrectnessProperties:0
prop_1525484575300426000 ==
Termination
----
\* PROPERTY definition @modelCorrectnessProperties:1
prop_1525484575300427000 ==
ALLSENT
----
\* PROPERTY definition @modelCorrectnessProperties:2
prop_1525484575300428000 ==
NOTHANG
----
\* PROPERTY definition @modelCorrectnessProperties:3
prop_1525484575300429000 ==
SENDSOMETHING
----
=============================================================================
\* Modification History
\* Created Fri May 04 21:42:55 EDT 2018 by SabraouM
