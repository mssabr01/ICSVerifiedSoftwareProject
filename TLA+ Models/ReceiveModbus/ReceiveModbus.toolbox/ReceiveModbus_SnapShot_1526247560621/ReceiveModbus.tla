------------------------------ MODULE ReceiveModbus ------------------------------

EXTENDS Sequences,
        Naturals,
        Modbus,
        TLC,
        ASCII
        
LOCAL INSTANCE Hex
    WITH natValue <- 0, hexValue <- <<0>> 

LOCAL Range(T) == { T[x] : x \in DOMAIN T }

MessagesToSerialPort == \*these are in ASCII but they are converted to decimal before being used below. See StrTupleToNumTuple in ASCII.tla
    { StrTupleToNumTuple(<<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>),
      StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>),
      \*StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","G","L","F">>),
      StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0",":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>), \*this one starts a new modbus packet half way through the message
      <<>>,<<1>>,<<2>>,<<3>>,<<4>>,<<5>>,<<6>>,<<7>>,<<8>>,<<9>>,<<10>>,<<11>>,<<12>>,<<13>>,
      <<14>>,<<15>>,<<16>>,<<17>>,<<18>>,<<19>>,<<20>>,<<21>>,<<22>>,<<23>>,<<24>>,<<25>>,
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
      <<250>>,<<251>>,<<252>>,<<253>>,<<254>>,<<255>>
      }

(*--fair algorithm ReceiveModbus
variables   rxBuf = <<>>,
            rx = FALSE,
            rxReg = <<>>,
            incMessage \in MessagesToSerialPort,
            incByte = <<>>,
            applicationBuffer = <<>> \*this is what is passed to the application. Only valid modbus here plz
begin

\* wait for something to appear in the buffer
idle:   if incMessage = <<>>
            then incByte := <<>>;
            else
                incByte :=  <<Head(incMessage)>>;
                incMessage := Tail(incMessage);
        end if;

inc:    if incByte = <<>>
        then goto alldone;
        else
                rxReg := incByte;    
        end if;

start:  if Len(rxBuf) < MAXMODBUSSIZE
        then goto receive;
        else goto alldone;
        end if;
    
receive:    \* a ":" character indicates the start of a new message
            if rxReg = StrTupleToNumTuple(<<":">>)
                then rxBuf := <<>>;
            end if;
            r1: rxBuf := rxBuf \o rxReg; \* put the contents of the register into the buffer
            \*empty the register
            r2: rxReg := <<>>;

check:     \*if we have a full modbus packet then signal
            if IsModbus(NumTupleToStrTuple(rxBuf)) \*convert back to ASCII before checking for modbus
            then 
                rx := TRUE; 
                applicationBuffer := rxBuf;
                goto alldone;
            else goto idle;
            end if;
            
alldone:    rxBuf := <<>>;
            rxReg := <<>>;
            incByte := <<>>;
            incMessage := <<>>;

end algorithm
*)

\* BEGIN TRANSLATION
VARIABLES rxBuf, rx, rxReg, incMessage, incByte, applicationBuffer, pc

vars == << rxBuf, rx, rxReg, incMessage, incByte, applicationBuffer, pc >>

Init == (* Global variables *)
        /\ rxBuf = <<>>
        /\ rx = FALSE
        /\ rxReg = <<>>
        /\ incMessage \in MessagesToSerialPort
        /\ incByte = <<>>
        /\ applicationBuffer = <<>>
        /\ pc = "idle"

idle == /\ pc = "idle"
        /\ IF incMessage = <<>>
              THEN /\ incByte' = <<>>
                   /\ UNCHANGED incMessage
              ELSE /\ incByte' = <<Head(incMessage)>>
                   /\ incMessage' = Tail(incMessage)
        /\ pc' = "inc"
        /\ UNCHANGED << rxBuf, rx, rxReg, applicationBuffer >>

inc == /\ pc = "inc"
       /\ IF incByte = <<>>
             THEN /\ pc' = "alldone"
                  /\ rxReg' = rxReg
             ELSE /\ rxReg' = incByte
                  /\ pc' = "start"
       /\ UNCHANGED << rxBuf, rx, incMessage, incByte, applicationBuffer >>

start == /\ pc = "start"
         /\ IF Len(rxBuf) < MAXMODBUSSIZE
               THEN /\ pc' = "receive"
               ELSE /\ pc' = "alldone"
         /\ UNCHANGED << rxBuf, rx, rxReg, incMessage, incByte, 
                         applicationBuffer >>

receive == /\ pc = "receive"
           /\ IF rxReg = StrTupleToNumTuple(<<":">>)
                 THEN /\ rxBuf' = <<>>
                 ELSE /\ TRUE
                      /\ rxBuf' = rxBuf
           /\ pc' = "r1"
           /\ UNCHANGED << rx, rxReg, incMessage, incByte, applicationBuffer >>

r1 == /\ pc = "r1"
      /\ rxBuf' = rxBuf \o rxReg
      /\ pc' = "r2"
      /\ UNCHANGED << rx, rxReg, incMessage, incByte, applicationBuffer >>

r2 == /\ pc = "r2"
      /\ rxReg' = <<>>
      /\ pc' = "check"
      /\ UNCHANGED << rxBuf, rx, incMessage, incByte, applicationBuffer >>

check == /\ pc = "check"
         /\ IF IsModbus(NumTupleToStrTuple(rxBuf))
               THEN /\ rx' = TRUE
                    /\ applicationBuffer' = rxBuf
                    /\ pc' = "alldone"
               ELSE /\ pc' = "idle"
                    /\ UNCHANGED << rx, applicationBuffer >>
         /\ UNCHANGED << rxBuf, rxReg, incMessage, incByte >>

alldone == /\ pc = "alldone"
           /\ rxBuf' = <<>>
           /\ rxReg' = <<>>
           /\ incByte' = <<>>
           /\ incMessage' = <<>>
           /\ pc' = "Done"
           /\ UNCHANGED << rx, applicationBuffer >>

Next == idle \/ inc \/ start \/ receive \/ r1 \/ r2 \/ check \/ alldone
           \/ (* Disjunct to prevent deadlock on termination *)
              (pc = "Done" /\ UNCHANGED vars)

Spec == /\ Init /\ [][Next]_vars
        /\ WF_vars(Next)

Termination == <>(pc = "Done")

\* END TRANSLATION

SAFETYCHECK ==
    \*receive buffer never overflows
    /\ Len(rxBuf) <= MAXMODBUSSIZE 
    \*application buffer never overflows
    /\ Len(applicationBuffer) <= MAXMODBUSSIZE 
    \*only valid modbus makes it to the app buffer
    /\ IsModbus(NumTupleToStrTuple(applicationBuffer)) \/ applicationBuffer = <<>> 
    \*flag is raised if and only if there is valid modbus in app buffer
    /\ rx = TRUE <=> IsModbus(NumTupleToStrTuple(applicationBuffer))

LIVELINESS ==
    \* if the message is modbus then it gets to the app buffer
    /\ IsModbus(NumTupleToStrTuple(incMessage)) ~> IsModbus(NumTupleToStrTuple(applicationBuffer)) 
    \* if valid modbus comes through then it gets flagged for the application to consume
    \*/\ IsModbus(NumTupleToStrTuple(incMessage)) ~> rx = TRUE 


=============================================================================
\* Modification History
\* Last modified Sun May 13 17:38:35 EDT 2018 by SabraouM
\* Created Sat May 05 11:36:54 EDT 2018 by SabraouM