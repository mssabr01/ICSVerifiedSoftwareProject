---------------------------- MODULE auth_device ----------------------------
EXTENDS Sequences, FiniteSets, Naturals, TLC, Modbus, ASCII, EncapPacket

LOCAL HMACSIZE == 64
LOCAL MINMESSAGESIZE == 1
LOCAL MINMACMESSAGESIZE == 65
LOCAL PASSWORD == "lolpassword"
LOCAL INSTANCE Hex
    WITH natValue <- 0, hexValue <- <<0>> 
LOCAL Range(T) == { T[x] : x \in DOMAIN T }
MessagesToSerialPort == \*these are in ASCII but they are converted to decimal before being used below. See StrTupleToNumTuple in ASCII.tla
    << StrTupleToNumTuple(<<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>),
      StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>),
      StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>),
      StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0",":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>), \*this one starts a new modbus packet half way through the message
      StrTupleToNumTuple(<<"!","m","Q","I","N","B","F","u","O","v","x","M","B","E","A","D","g","D","B","Q","v","c","R","P","z","T","e","G","w","v","V","2","J","C","r","t","m","x","U","j","v","Y","S","Z","7","P","j","W","p","H","l","5","2","4","g","I","g","J","h","b","t","d","I","T","U",":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>)(*,
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
      <<250>>,<<251>>,<<252>>,<<253>>,<<254>>,<<255>>*)
     >>
MessagesToUntrustNet == <<StrTupleToNumTuple(<<"!","m","Q","I","N","B","F","u","O","v","x","M","B","E","A","D","g","D","B","Q","v","c","R","P","z","T","e","G","w","v","V","2","J","C","r","t","m","x","U","j","v","Y","S","Z","7","P","j","W","p","H","l","5","2","4","g","I","g","J","h","b","t","d","I","T","U",":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>),
                        StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>)
                        >>
HMAC(str, pass) == <<"I","K","o","W","L","9","v","G","U","h","S","1","q","t","Z","f","4","5","h","r","9","W","4","1","Z","i","B","G","P","j","d","o","w","6","S","Y","2","A","0","+","q","E","d","a","+","s","i","i","B","H","G","C","4","r","/","S","5","g","J","W","P","/","s","T">> \*not concerned with the inner workings of SHA2
FindPartnerMessage(msg, messages) == CHOOSE x \in messages : x.id = msg.id

(* --fair algorithm auth_device

variables 
    
    chan = [sign |-> <<>>]
    
    
\* IPC calls
macro send(dest, msg) 
    begin
        \*print "sending to " \o dest;
        chan[dest] := Append(chan[dest], msg);
    end macro;

macro receive(channel, msg) 
    begin
        \*print channel \o " received msg";
        await Len(chan[channel]) > 0;
        msg := Head(chan[channel]);
        chan[channel] := Tail(chan[channel]);
    end macro;

\* Signing process.
fair process sign = "sign"

variables   msg = <<>>,
            generated_hmac = <<>>;
begin
sign1:   while TRUE do
         
             receive("sign", msg);
             sign2: generated_hmac := HMAC(msg.text, PASSWORD); \*hash it and the password
             sign3: send("untrustnet_out", [id|->msg.id, hmac|->generated_hmac, source|->"sign", isValid|->TRUE, text|->msg.text]);
         end while;
end process
\*=========================================

\*Receive plaintext modbus from the trusted serial port
fair process trustnet_in = "trustnet_in"

variables   rxBuf = <<>>,
            incomingMessages = MessagesToSerialPort,
            guid = <<0>>,
            msg = <<>>,
            msgid = <<>>,
            rx = FALSE,
            rxReg = <<>>,
            last2 = <<3,3>>, \*dummy numbers
            incByte = <<>>,

begin
\* wait for something to appear in the buffer
trustnet_in1:   while Len(incomingMessages) > 0 do
                    if Len(incomingMessages) > 1 then
                        uti1: msg := Head(incomingMessages);
                        uti2: incomingMessages := Tail(incomingMessages);
                    else
                        uti3: msg := incomingMessages[1];
                        uti4: incomingMessages := <<>>;
                    end if;
                start:  while Len(msg) > 0 do
                        if Len(rxBuf) = MAXMODBUSSIZE then
                            rxBuf := <<>>;
                            rxReg := <<>>;
                            incByte := <<>>;
                            incMessage := <<>>;
                            goto start;
                        end if;
                inc:    incByte :=  <<Head(msg)>>;
                        msg := Tail(msg);
                        if incByte = <<>> then 
                        else
                            rxReg := incByte;    
                        end if;

    
                receive:    \* a ":" character indicates the start of a new message
                            if rxReg = StrTupleToNumTuple(<<":">>)
                                then rxBuf := <<>>;
                            end if;
                            r0: last2 := Tail(last2 \o rxReg);
                            r1: rxBuf := rxBuf \o rxReg; \* put the contents of the register into the buffer
                            \*empty the register
                            r2: rxReg := <<>>;
                check:     \*if we get the end of the modbus "/r/n" then ship it
                            if NumTupleToStrTuple(last2) = <<"\r","\n">> then \*convert back to ASCII before checking for end of packet
                                check0: msgid := <<guid[1]>> \o <<"t","n","i">>;
                                check1: guid[1] := guid[1] + 1;
                                check2: send("messagecheck", [id|->msgid, text|->rxBuf, source|->"trustnet_in"]);
                                check3: send("sign", [id|->msgid, text|->rxBuf]);
                                check4: rxBuf := <<>>;
                                rxReg := <<>>;
                                incByte := <<>>;
                                incMessage := <<>>;
            end if;
        end while;
    end while;
            
end process;
\*=========================================

end algorithm;*)
\* BEGIN TRANSLATION

\* END TRANSLATION


    \*modbus check module:
SAFE1 == \A m \in Range(chan["messagecheck"]) : Len(m.text) <= MAXMODBUSSIZE \*only messages with a valid length make it to the checking module
    \*messages going to untrusted network
SAFE2 == \A m \in validMessages : m.isValid = TRUE \*message parts waiting for their counterpart are valid
SAFE3 == \A m \in Range(chan["finished_untrustnet"]) : GetHMAC(m) = HMAC(m,m) \*only properly signed messages are sent to untrustnet
SAFE4 == \A m \in Range(chan["finished_untrustnet"]) : IsModbus(GetModbus(m)) \*only properly formed modbus is sent with signature to untrustnet
    \*messages going to trusted network:
SAFE5 == \A m \in validMessages_ : m.isValid = TRUE \*message parts waiting for their counterpart are valid
SAFE6 == \A m \in Range(chan["finished_trustnet"]) : IsModbus(m) \*only properly formed modbus is sent to trustnet
    (*
LIVENESS ==
   /\ <>(Len(incomingMessages_) = 0)
   /\ <>(Len(incomingMessages) = 0)
   /\ <>(Len(chan["finished_untrustnet"]) > 0)
   /\ <>(Len(chan["finished_trustnet"]) > 0)
   \* counterpart will eventually come
   \*/\ \A p \in validMessages_ : <>(msg_tr.id = p.id /\ msg_tr.source /= p.source ) 
   \*modbus check module:
   \*/\ \A p \in Range(chan["messagecheck"]), \E q \in Range(chan["untrustnet_out"]) : p.source = "trustnet_in" ~> : p.id = q.id
*)
=============================================================================
\* Modification History
\* Last modified Thu Jul 18 10:24:59 EDT 2019 by mssabr01
\* Last modified Wed Oct 17 11:32:47 EDT 2018 by userMehdi
\* Created Tue Oct 02 17:14:28 EDT 2018 by mssabr01
