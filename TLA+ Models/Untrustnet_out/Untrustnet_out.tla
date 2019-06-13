-------------------------------- MODULE Untrustnet_out --------------------------------

EXTENDS Sequences,
        Naturals,
        EncapPacket,
        TLC,
        ASCII
        
LOCAL INSTANCE Hex
    WITH natValue <- 0, hexValue <- <<0>> 
MessagesToSerialPort == 
    {StrTupleToNumTuple(isSSW),
     StrTupleToNumTuple(<<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>),
     StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>),
     StrTupleToNumTuple(<<":","J","G","P","9","4","3","2","J","3","9","J","G","W",":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","F">>),
     <<>>,<<1>>,<<2>>,<<3>>,<<4>>,<<5>>,<<6>>,<<7>>,<<8>>,<<9>>,<<10>>,<<11>>,<<12>>,<<13>>, \* all possible values
      <<14>>,<<15>>,<<16>>,<<17>>,<<18>>,<<19>>,<<20>>,<<21>>,<<22>>,<<23>>,<<24>>,<<25>>,   \*that could come across the serial line
      <<26>>,<<27>>,<<28>>,<<29>>,<<30>>,<<31>>,<<32>>,<<33>>,<<34>>,<<35>>,<<36>>,<<37>>,<<38>>,<<39>>,<<40>>,<<41>>,
      <<42>>,<<43>>,<<44>>,<<45>>,<<46>>,<<47>>,<<48>>,<<49>>,<<50>>,<<51>>,<<52>>,<<53>>,<<54>>,<<55>>,<<56>>,<<57>>,
      <<58>>,<<59>>,<<60>>,<<61>>,<<62>>,<<63>>,<<64>>,<<65>>,<<66>>,<<67>>,<<68>>,<<69>>,<<70>>,<<71>>,<<72>>,<<73>>,
      <<74>>,<<75>>,<<76>>,<<77>>,<<78>>,<<79>>,<<80>>,<<81>>,<<82>>,<<83>>,<<84>>,<<85>>,<<86>>,<<87>>,<<88>>,<<89>>,
      <<90>>,<<91>>,<<92>>,<<93>>,<<94>>,<<95>>,<<96>>,<<97>>,<<98>>,<<99>>,<<100>>,<<101>>,<<102>>,<<103>>,<<104>>,<<105>>,
      <<106>>,<<107>>,<<108>>,<<109>>,<<110>>,<<111>>,<<112>>,<<113>>,<<114>>,<<115>>,<<116>>,<<117>>,<<118>>,<<119>>,<<120>>,<<121>>,
      <<122>>,<<123>>,<<124>>,<<125>>,<<126>>,<<127>>,<<128>>,<<129>>,<<130>>,<<131>>,<<132>>,<<133>>,<<134>>,<<135>>,<<136>>,<<137>>,
      <<138>>,<<139>>,<<140>>,<<141>>,<<142>>,<<143>>,<<144>>,<<145>>,<<146>>,<<147>>,<<148>>,<<149>>,<<150>>,<<151>>,<<152>>,<<153>>,
      <<154>>,<<155>>,<<156>>,<<157>>,<<158>>,<<159>>,<<160>>,<<161>>,<<162>>,<<163>>,<<164>>,<<165>>,<<166>>,<<167>>,<<168>>,<<169>>,
      <<170>>,<<171>>,<<172>>,<<173>>,<<174>>,<<175>>,<<176>>,<<177>>,<<178>>,<<179>>,<<180>>,<<181>>,<<182>>,<<183>>,<<184>>,<<185>>,
      <<186>>,<<187>>,<<188>>,<<189>>,<<190>>,<<191>>,<<192>>,<<193>>,<<194>>,<<195>>,<<196>>,<<197>>,<<198>>,<<199>>,<<200>>,<<201>>,
      <<202>>,<<203>>,<<204>>,<<205>>,<<206>>,<<207>>,<<208>>,<<209>>,<<210>>,<<211>>,<<212>>,<<213>>,<<214>>,<<215>>,<<216>>,<<217>>,
      <<218>>,<<219>>,<<220>>,<<221>>,<<222>>,<<223>>,<<224>>,<<225>>,<<226>>,<<227>>,<<228>>,<<229>>,<<230>>,<<231>>,<<232>>,<<233>>,
      <<234>>,<<235>>,<<236>>,<<237>>,<<238>>,<<239>>,<<240>>,<<241>>,<<242>>,<<243>>,<<244>>,<<245>>,<<246>>,<<247>>,<<248>>,<<249>>,
      <<250>>,<<251>>,<<252>>,<<253>>,<<254>>,<<255>>}
LOCAL Range(T) == { T[x] : x \in DOMAIN T }

(*--fair algorithm Transmit
variables   tx = FALSE,
            messageToSend \in MessagesToSerialPort,
            txBuf = <<>>,
            txReg = <<>>
begin

checkBuf:   txBuf := messageToSend;
            if IsSSW(NumTupleToStrTuple(txBuf))
            then tx := TRUE;
            end if;
idle: if tx = TRUE 
      then goto transmit;
      else goto finished;
      end if;
transmit:   if Len(txBuf) > 1
            then
                \*empty the buffer into the register
                a: txReg := <<Head(txBuf)>>;
                b: txBuf := Tail(txBuf);
                goto transmit;
            else
                txReg := <<txBuf[1]>>;
            end if;
            
            
finished: tx := FALSE;
          txReg:= <<>>;
          txBuf := <<>>;
end algorithm
*)
\* BEGIN TRANSLATION
VARIABLES tx, messageToSend, txBuf, txReg, pc

vars == << tx, messageToSend, txBuf, txReg, pc >>

Init == (* Global variables *)
        /\ tx = FALSE
        /\ messageToSend \in MessagesToSerialPort
        /\ txBuf = <<>>
        /\ txReg = <<>>
        /\ pc = "checkBuf"

checkBuf == /\ pc = "checkBuf"
            /\ txBuf' = messageToSend
            /\ IF IsSSW(NumTupleToStrTuple(txBuf'))
                  THEN /\ tx' = TRUE
                  ELSE /\ TRUE
                       /\ tx' = tx
            /\ pc' = "idle"
            /\ UNCHANGED << messageToSend, txReg >>

idle == /\ pc = "idle"
        /\ IF tx = TRUE
              THEN /\ pc' = "transmit"
              ELSE /\ pc' = "finished"
        /\ UNCHANGED << tx, messageToSend, txBuf, txReg >>

transmit == /\ pc = "transmit"
            /\ IF Len(txBuf) > 1
                  THEN /\ pc' = "a"
                       /\ txReg' = txReg
                  ELSE /\ txReg' = <<txBuf[1]>>
                       /\ pc' = "finished"
            /\ UNCHANGED << tx, messageToSend, txBuf >>

a == /\ pc = "a"
     /\ txReg' = <<Head(txBuf)>>
     /\ pc' = "b"
     /\ UNCHANGED << tx, messageToSend, txBuf >>

b == /\ pc = "b"
     /\ txBuf' = Tail(txBuf)
     /\ pc' = "transmit"
     /\ UNCHANGED << tx, messageToSend, txReg >>

finished == /\ pc = "finished"
            /\ tx' = FALSE
            /\ txReg' = <<>>
            /\ txBuf' = <<>>
            /\ pc' = "Done"
            /\ UNCHANGED messageToSend

Next == checkBuf \/ idle \/ transmit \/ a \/ b \/ finished
           \/ (* Disjunct to prevent deadlock on termination *)
              (pc = "Done" /\ UNCHANGED vars)

Spec == /\ Init /\ [][Next]_vars
        /\ WF_vars(Next)

Termination == <>(pc = "Done")

\* END TRANSLATION
LIVELINESS ==
\* check that if valid SSW is in the buffer it gets sent
    /\ tx = TRUE /\ IsSSW(NumTupleToStrTuple(txBuf)) ~> Len(txBuf) = 1
\*If there is something to send then it is alway sent
    /\ tx = TRUE /\ IsSSW(NumTupleToStrTuple(txBuf)) ~> (txReg /= <<>>)
\*If there is something to send, the flag is eventually reset
    /\ (tx = TRUE) ~> (tx = FALSE)

SAFETYCHECK ==
\*Only valid SSW triggers the sending
    /\ Len(txReg) > 0 => IsSSW(NumTupleToStrTuple(messageToSend))
\*only one thing in the transmission register
    /\ Len(txReg) <= 1
=============================================================================
\* Modification History
\* Last modified Thu Jun 13 18:17:32 EDT 2019 by mehdi
\* Last modified Mon May 14 12:54:26 EDT 2018 by SabraouM
\* Created Fri May 04 22:08:30 EDT 2018 by SabraouM
