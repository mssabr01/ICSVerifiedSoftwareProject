----------------------------- MODULE deployment -----------------------------

EXTENDS TLC, Integers
(* --algorithm deploy
variables
  servers = {"s1", "s2", "s3"},
  updated = [s \in servers |-> FALSE];

define
  SameVersion ==
    \A x, y \in servers:
      updated[x] = updated[y]
end define

fair process update_server \in servers
begin Update:
  updated[self] := TRUE;
end process;

end algorithm; *)

=============================================================================
\* Modification History
\* Last modified Tue Mar 13 15:25:04 EDT 2018 by SabraouM
\* Created Tue Mar 13 15:25:00 EDT 2018 by SabraouM
