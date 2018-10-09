---------------------------- MODULE auth_device ----------------------------
EXTENDS Sequences, FiniteSets, Naturals, TLC, Modbus, ASCII

LOCAL HMACSIZE == 64
LOCAL MINMESSAGESIZE == 1
LOCAL MINMACMESSAGESIZE == 65
LOCAL PASSWORD == "lolpassword"
LOCAL INSTANCE Hex
    WITH natValue <- 0, hexValue <- <<0>> 
LOCAL Range(T) == { T[x] : x \in DOMAIN T }
MessagesToSerialPort == \*these are in ASCII but they are converted to decimal before being used below. See StrTupleToNumTuple in ASCII.tla
    { StrTupleToNumTuple(<<":","J","G","P","9","4","3","2","J","3","9","J","G","W","I","R","W">>),
      StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>),
      StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","1","0","3","0","0","6","B","0","0","0","3","7","E","C","G","L","F">>),
      StrTupleToNumTuple(<<":","1","1","0","3","0","0","6","B","0","0","0",":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","\r","\n">>), \*this one starts a new modbus packet half way through the message
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
      <<250>>,<<251>>,<<252>>,<<253>>,<<254>>,<<255>>
     }
                       
HMAC(str, pass) == <<"l","o","l","h","m","a","c">> \*not concerned with the inner workings of SHA2
GetHMAC(str) == SubSeq(str,2,65)

(* --algorithm auth_device

variables 
    trustnet_in = <<>>,
    trustnet_out = <<>>,
    sign = <<>>,
    verify = <<>>,
    messagecheck,
    untrustnet_in = <<>>,
    untrustnet_out = <<>>,
    finished_trustnet = <<>>, \*all the messages that get sent out the trustnet
    finished_untrustnet = <<>>, \*all the messages that get sent out the untrustnet
    chan = <<trustnet_in, trustnet_out, sign, verify, messagecheck, untrustnet_in, untrustnet_out,finished_untrustnet,finished_trustnet>>;

\* IPC calls
macro send(dest, msg) 
    begin
        chan[dest] := Append(chan[dest], msg);
    end macro;

macro receive(channel, msg) 
    begin
        await Len(chan[channel]) > 0;
        msg := Head(chan[channel]);
        chan[channel] := Tail(chan[channel]);
    end macro;

\* Signing process.
process sign = "sign"

variables   msg = <<>>,
            generated_hmac = <<>>;
begin
sign1:   while TRUE do
         
             receive(sign, msg);
             sign2: generated_hmac := HMAC(msg.text, PASSWORD); \*hash it and the password
             sign3: send(untrustnet_out, [id|->msg.id, hmac|->generated_hmac, isValid|->TRUE]);
         end while;
end process
\*=========================================

\*Check validitity of the underlying protocol. In this case Modbus
process messagecheck = "messagecheck"

variables   msg = <<>>
            
begin
modbus1:    while TRUE do
                receive("messagecheck", msg);
                if IsModbus(msg.text) then
                    if msg.source = "trustnet_in" then 
                        mod1: send(untrustnet_out, [id|->msg.id, isValid|->TRUE, text|->msg.text]);
                    elsif (msg.source = "untrust_in") then 
                        mod2: send(trustnet_out, [id|->msg.id, isValid|->TRUE, text|->msg.text]);
                    end if;
                
                else
                    if msg.source = "trustnet_in" then
                        mod3: send(untrustnet_out, [id|->msg.id, isValid|->FALSE, text|->msg.text]);
                    elsif msg.source = "untrust_in" then
                        mod4: send(trustnet_out, [id|->msg.id, isValid|->FALSE, text|->msg.text]);
                    end if;
                end if;
            end while;
                
end process
\*=========================================

\*Check the validitity of the signature
process verify = "verify"

variables   msg = <<>>,
            bareMessage = <<>>,
            retreivedHMAC = <<>>,
            generatedHMAC = <<>>,
            result = FALSE,
            CompareHMAC \in BOOLEAN, \*since we dont model SHA2 this is random
            hmacsMatch = FALSE
begin
verify1:   while TRUE do
                receive("verify", msg);
                verify2: retreivedHMAC := GetHMAC(msg.text);
                verify3: generatedHMAC := HMAC(msg.text, PASSWORD);
                verify4: hmacsMatch := CompareHMAC;
                if hmacsMatch then
                    verify5: send(trustnet_out, [id|->msg.id, isValid|->TRUE]);
                else
                    verify6: send(trustnet_out, [id|->msg.id, isValid|->FALSE]);
                end if;
            end while;

end process
\*=========================================

\*Receive plaintext modbus from the trusted serial port
process trustnet_in = "trustnet_in"

variables   rxBuf = <<>>,
            guid = 0,
            msg = <<>>,
            msgid = <<>>,
            rx = FALSE,
            rxReg = <<>>,
            last2 = <<3,3>>, \*dummy numbers
            incMessage \in MessagesToSerialPort,
            incByte = <<>>,

begin
\* wait for something to appear in the buffer
trustnet_in1:   while TRUE do
                receive("trustnet_in", msg);
                start:  while Len(msg) > 0 do
                        if Len(rxBuf) = MAXMODBUSSIZE then
                            rxBuf := <<>>;
                            rxReg := <<>>;
                            incByte := <<>>;
                            incMessage := <<>>;
                            goto start;
                        end if;
                inc:    incByte :=  <<Head(msg)>>;
                        incMessage := Tail(msg);
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
                                check0: msgid := guid \o "trustnet_in";
                                check1: guid := guid + 1;
                                check2: send(messagecheck, [id|->msgid, text|->rxBuf, source|->trustnet_in]);
                                check3: send(sign, [id|->msgid, text|->rxBuf]);
                                check4: rxBuf := <<>>;
                                rxReg := <<>>;
                                incByte := <<>>;
                                incMessage := <<>>;
            end if;
        end while;
    end while;
            
end process;
\*=========================================

\*Receive signed messages from untrusted serial port
process untrustnet_in = "untrustnet_in"

variables   rxBuf = <<>>,
            guid = 0,
            msg = <<>>,
            msgid = <<>>,
            rx = FALSE,
            rxReg = <<>>,
            last2 = <<3,3>>, \*dummy numbers
            incMessage \in MessagesToSerialPort,
            incByte = <<>>,

begin
\* wait for something to appear in the buffer
untrustnet_in1:   while TRUE do
                receive("untrustnet_in", msg);
                start:  while Len(msg) > 0 do
                inc:    incByte :=  <<Head(msg)>>;
                        incMessage := Tail(msg);
                        if incByte = <<>> then 
                        else
                            rxReg := incByte;    
                        end if;

    
                receive:    \* a "!" character indicates the start of a new message
                            if rxReg = StrTupleToNumTuple(<<"!">>)
                                then rxBuf := <<>>;
                            end if;
                            r0: last2 := Tail(last2 \o rxReg);
                            r1: rxBuf := rxBuf \o rxReg; \* put the contents of the register into the buffer
                            \*empty the register
                            r2: rxReg := <<>>;
                check:     \*if we get the end of the modbus "/r/n" then ship it
                            if NumTupleToStrTuple(last2) = <<"\r","\n">> then \*convert back to ASCII before checking for end of packet
                                check0: msgid := guid \o "untrustnet_in";
                                check1: guid := guid + 1;
                                check2: send(messagecheck, [id|->msgid, text|->rxBuf, source|->untrustnet_in]);
                                check3: send(verify, [id|->msgid, text|->rxBuf]);
                                check4: rxBuf := <<>>;
                                rxReg := <<>>;
                                incByte := <<>>;
                                incMessage := <<>>;
            end if;
        end while;
    end while;
            
end process;
\*=========================================

\*process to send modbus out the trusted serial port
process trustnet_out = "trustnet_out"

variables   msg = <<>>,
            txBuf = <<>>,
            txReg = <<>>,
            adder = 0,
            validMessages = {}
            
begin
    to1: while TRUE do
        receive("trustnet_out", msg);
        if msg.isValid then \*if the message is valid then look for another message in the validMessages set with the same id.
            if \E x \in validMessages : x.id = msg.id then \*if one exists then both portions of the message were verified and the message can be sent
                txBuf := msg.text;
                transmit: if Len(txBuf) > 1 then
                    \*empty the buffer into the register
                    a: txReg := <<Head(txBuf)>>;
                    b: send(finished_trustnet, txReg);
                    c: txBuf := Tail(txBuf);
                    goto transmit;
                else
                    txReg := <<txBuf[1]>>;
                    send(finished_trustnet, txReg);
                end if;
                to2: validMessages := validMessages \ {x \in validMessages: x.id = msg.id}; \*remove sent message from set
            else
                validMessages := validMessages \union {msg}; \*if a message with the same id is not found then add this message to that set
            end if;
        end if;
        finished: txReg := <<>>;
        txBuf := <<>>;
    end while;
    
end process;
\*=========================================

\*process to send modbus out the trusted serial port
process untrustnet_out = "untrustnet_out"

variables   msg = <<>>,
            txBuf = <<>>,
            txReg = <<>>,
            adder = 0,
            validMessages = {}
            
begin
    uto1: while TRUE do
        receive("untrustnet_out", msg);
        if msg.isValid then \*if the message is valid then look for another message in the validMessages set with the same id.
            if \E x \in validMessages : x.id = msg.id then \*if one exists then both portions of the message were verified and the message can be sent
                txBuf := StrTupleToNumTuple(<<"!">>) \o msg.msg.text;
                transmit: if Len(txBuf) > 1 then
                    \*empty the buffer into the register
                    a: txReg := <<Head(txBuf)>>;
                    b: send(finished_trustnet, txReg);
                    c: txBuf := Tail(txBuf);
                    goto transmit;
                else
                    txReg := <<txBuf[1]>>;
                    send(finished_untrustnet, txReg);
                end if;
                uto2: validMessages := validMessages \ {x \in validMessages: x.id = msg.id}; \*remove sent message from set
            else
                validMessages := validMessages \union {msg}; \*if a message with the same id is not found then add this message to that set
            end if;
        end if;
        finished: txReg := <<>>;
        txBuf := <<>>;
    end while;
    
end process;

            


end algorithm;*)
\* BEGIN TRANSLATION
\* Label start of process trustnet_in at line 150 col 25 changed to start_
\* Label inc of process trustnet_in at line 158 col 25 changed to inc_
\* Label receive of process trustnet_in at line 167 col 29 changed to receive_
\* Label r0 of process trustnet_in at line 170 col 33 changed to r0_
\* Label r1 of process trustnet_in at line 171 col 33 changed to r1_
\* Label r2 of process trustnet_in at line 173 col 33 changed to r2_
\* Label check of process trustnet_in at line 175 col 29 changed to check_
\* Label check0 of process trustnet_in at line 176 col 41 changed to check0_
\* Label check1 of process trustnet_in at line 177 col 41 changed to check1_
\* Label check2 of process trustnet_in at line 55 col 9 changed to check2_
\* Label check3 of process trustnet_in at line 55 col 9 changed to check3_
\* Label check4 of process trustnet_in at line 180 col 41 changed to check4_
\* Label transmit of process trustnet_out at line 257 col 27 changed to transmit_
\* Label a of process trustnet_out at line 259 col 24 changed to a_
\* Label b of process trustnet_out at line 55 col 9 changed to b_
\* Label c of process trustnet_out at line 261 col 24 changed to c_
\* Label finished of process trustnet_out at line 272 col 19 changed to finished_
\* Process sign at line 66 col 1 changed to sign_
\* Process messagecheck at line 81 col 1 changed to messagecheck_
\* Process verify at line 108 col 1 changed to verify_
\* Process trustnet_in at line 134 col 1 changed to trustnet_in_
\* Process untrustnet_in at line 192 col 1 changed to untrustnet_in_
\* Process trustnet_out at line 243 col 1 changed to trustnet_out_
\* Process untrustnet_out at line 280 col 1 changed to untrustnet_out_
\* Process variable msg of process sign at line 68 col 13 changed to msg_
\* Process variable msg of process messagecheck at line 83 col 13 changed to msg_m
\* Process variable msg of process verify at line 110 col 13 changed to msg_v
\* Process variable rxBuf of process trustnet_in at line 136 col 13 changed to rxBuf_
\* Process variable guid of process trustnet_in at line 137 col 13 changed to guid_
\* Process variable msg of process trustnet_in at line 138 col 13 changed to msg_t
\* Process variable msgid of process trustnet_in at line 139 col 13 changed to msgid_
\* Process variable rx of process trustnet_in at line 140 col 13 changed to rx_
\* Process variable rxReg of process trustnet_in at line 141 col 13 changed to rxReg_
\* Process variable last2 of process trustnet_in at line 142 col 13 changed to last2_
\* Process variable incMessage of process trustnet_in at line 143 col 13 changed to incMessage_
\* Process variable incByte of process trustnet_in at line 144 col 13 changed to incByte_
\* Process variable msg of process untrustnet_in at line 196 col 13 changed to msg_u
\* Process variable msg of process trustnet_out at line 245 col 13 changed to msg_tr
\* Process variable txBuf of process trustnet_out at line 246 col 13 changed to txBuf_
\* Process variable txReg of process trustnet_out at line 247 col 13 changed to txReg_
\* Process variable adder of process trustnet_out at line 248 col 13 changed to adder_
\* Process variable validMessages of process trustnet_out at line 249 col 13 changed to validMessages_
CONSTANT defaultInitValue
VARIABLES trustnet_in, trustnet_out, sign, verify, messagecheck, 
          untrustnet_in, untrustnet_out, finished_trustnet, 
          finished_untrustnet, chan, pc, msg_, generated_hmac, msg_m, msg_v, 
          bareMessage, retreivedHMAC, generatedHMAC, result, CompareHMAC, 
          hmacsMatch, rxBuf_, guid_, msg_t, msgid_, rx_, rxReg_, last2_, 
          incMessage_, incByte_, rxBuf, guid, msg_u, msgid, rx, rxReg, last2, 
          incMessage, incByte, msg_tr, txBuf_, txReg_, adder_, validMessages_, 
          msg, txBuf, txReg, adder, validMessages

vars == << trustnet_in, trustnet_out, sign, verify, messagecheck, 
           untrustnet_in, untrustnet_out, finished_trustnet, 
           finished_untrustnet, chan, pc, msg_, generated_hmac, msg_m, msg_v, 
           bareMessage, retreivedHMAC, generatedHMAC, result, CompareHMAC, 
           hmacsMatch, rxBuf_, guid_, msg_t, msgid_, rx_, rxReg_, last2_, 
           incMessage_, incByte_, rxBuf, guid, msg_u, msgid, rx, rxReg, last2, 
           incMessage, incByte, msg_tr, txBuf_, txReg_, adder_, 
           validMessages_, msg, txBuf, txReg, adder, validMessages >>

ProcSet == {"sign"} \cup {"messagecheck"} \cup {"verify"} \cup {"trustnet_in"} \cup {"untrustnet_in"} \cup {"trustnet_out"} \cup {"untrustnet_out"}

Init == (* Global variables *)
        /\ trustnet_in = <<>>
        /\ trustnet_out = <<>>
        /\ sign = <<>>
        /\ verify = <<>>
        /\ messagecheck = defaultInitValue
        /\ untrustnet_in = <<>>
        /\ untrustnet_out = <<>>
        /\ finished_trustnet = <<>>
        /\ finished_untrustnet = <<>>
        /\ chan = <<trustnet_in, trustnet_out, sign, verify, messagecheck, untrustnet_in, untrustnet_out,finished_untrustnet,finished_trustnet>>
        (* Process sign_ *)
        /\ msg_ = <<>>
        /\ generated_hmac = <<>>
        (* Process messagecheck_ *)
        /\ msg_m = <<>>
        (* Process verify_ *)
        /\ msg_v = <<>>
        /\ bareMessage = <<>>
        /\ retreivedHMAC = <<>>
        /\ generatedHMAC = <<>>
        /\ result = FALSE
        /\ CompareHMAC \in BOOLEAN
        /\ hmacsMatch = FALSE
        (* Process trustnet_in_ *)
        /\ rxBuf_ = <<>>
        /\ guid_ = 0
        /\ msg_t = <<>>
        /\ msgid_ = <<>>
        /\ rx_ = FALSE
        /\ rxReg_ = <<>>
        /\ last2_ = <<3,3>>
        /\ incMessage_ \in MessagesToSerialPort
        /\ incByte_ = <<>>
        (* Process untrustnet_in_ *)
        /\ rxBuf = <<>>
        /\ guid = 0
        /\ msg_u = <<>>
        /\ msgid = <<>>
        /\ rx = FALSE
        /\ rxReg = <<>>
        /\ last2 = <<3,3>>
        /\ incMessage \in MessagesToSerialPort
        /\ incByte = <<>>
        (* Process trustnet_out_ *)
        /\ msg_tr = <<>>
        /\ txBuf_ = <<>>
        /\ txReg_ = <<>>
        /\ adder_ = 0
        /\ validMessages_ = {}
        (* Process untrustnet_out_ *)
        /\ msg = <<>>
        /\ txBuf = <<>>
        /\ txReg = <<>>
        /\ adder = 0
        /\ validMessages = {}
        /\ pc = [self \in ProcSet |-> CASE self = "sign" -> "sign1"
                                        [] self = "messagecheck" -> "modbus1"
                                        [] self = "verify" -> "verify1"
                                        [] self = "trustnet_in" -> "trustnet_in1"
                                        [] self = "untrustnet_in" -> "untrustnet_in1"
                                        [] self = "trustnet_out" -> "to1"
                                        [] self = "untrustnet_out" -> "uto1"]

sign1 == /\ pc["sign"] = "sign1"
         /\ Len(chan[sign]) > 0
         /\ msg_' = Head(chan[sign])
         /\ chan' = [chan EXCEPT ![sign] = Tail(chan[sign])]
         /\ pc' = [pc EXCEPT !["sign"] = "sign2"]
         /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                         untrustnet_in, untrustnet_out, finished_trustnet, 
                         finished_untrustnet, generated_hmac, msg_m, msg_v, 
                         bareMessage, retreivedHMAC, generatedHMAC, result, 
                         CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, msgid_, 
                         rx_, rxReg_, last2_, incMessage_, incByte_, rxBuf, 
                         guid, msg_u, msgid, rx, rxReg, last2, incMessage, 
                         incByte, msg_tr, txBuf_, txReg_, adder_, 
                         validMessages_, msg, txBuf, txReg, adder, 
                         validMessages >>

sign2 == /\ pc["sign"] = "sign2"
         /\ generated_hmac' = HMAC(msg_.text, PASSWORD)
         /\ pc' = [pc EXCEPT !["sign"] = "sign3"]
         /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                         untrustnet_in, untrustnet_out, finished_trustnet, 
                         finished_untrustnet, chan, msg_, msg_m, msg_v, 
                         bareMessage, retreivedHMAC, generatedHMAC, result, 
                         CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, msgid_, 
                         rx_, rxReg_, last2_, incMessage_, incByte_, rxBuf, 
                         guid, msg_u, msgid, rx, rxReg, last2, incMessage, 
                         incByte, msg_tr, txBuf_, txReg_, adder_, 
                         validMessages_, msg, txBuf, txReg, adder, 
                         validMessages >>

sign3 == /\ pc["sign"] = "sign3"
         /\ chan' = [chan EXCEPT ![untrustnet_out] = Append(chan[untrustnet_out], ([id|->msg_.id, hmac|->generated_hmac, isValid|->TRUE]))]
         /\ pc' = [pc EXCEPT !["sign"] = "sign1"]
         /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                         untrustnet_in, untrustnet_out, finished_trustnet, 
                         finished_untrustnet, msg_, generated_hmac, msg_m, 
                         msg_v, bareMessage, retreivedHMAC, generatedHMAC, 
                         result, CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, 
                         msgid_, rx_, rxReg_, last2_, incMessage_, incByte_, 
                         rxBuf, guid, msg_u, msgid, rx, rxReg, last2, 
                         incMessage, incByte, msg_tr, txBuf_, txReg_, adder_, 
                         validMessages_, msg, txBuf, txReg, adder, 
                         validMessages >>

sign_ == sign1 \/ sign2 \/ sign3

modbus1 == /\ pc["messagecheck"] = "modbus1"
           /\ Len(chan["messagecheck"]) > 0
           /\ msg_m' = Head(chan["messagecheck"])
           /\ chan' = [chan EXCEPT !["messagecheck"] = Tail(chan["messagecheck"])]
           /\ IF IsModbus(msg_m'.text)
                 THEN /\ IF msg_m'.source = "trustnet_in"
                            THEN /\ pc' = [pc EXCEPT !["messagecheck"] = "mod1"]
                            ELSE /\ IF (msg_m'.source = "untrust_in")
                                       THEN /\ pc' = [pc EXCEPT !["messagecheck"] = "mod2"]
                                       ELSE /\ pc' = [pc EXCEPT !["messagecheck"] = "modbus1"]
                 ELSE /\ IF msg_m'.source = "trustnet_in"
                            THEN /\ pc' = [pc EXCEPT !["messagecheck"] = "mod3"]
                            ELSE /\ IF msg_m'.source = "untrust_in"
                                       THEN /\ pc' = [pc EXCEPT !["messagecheck"] = "mod4"]
                                       ELSE /\ pc' = [pc EXCEPT !["messagecheck"] = "modbus1"]
           /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                           messagecheck, untrustnet_in, untrustnet_out, 
                           finished_trustnet, finished_untrustnet, msg_, 
                           generated_hmac, msg_v, bareMessage, retreivedHMAC, 
                           generatedHMAC, result, CompareHMAC, hmacsMatch, 
                           rxBuf_, guid_, msg_t, msgid_, rx_, rxReg_, last2_, 
                           incMessage_, incByte_, rxBuf, guid, msg_u, msgid, 
                           rx, rxReg, last2, incMessage, incByte, msg_tr, 
                           txBuf_, txReg_, adder_, validMessages_, msg, txBuf, 
                           txReg, adder, validMessages >>

mod1 == /\ pc["messagecheck"] = "mod1"
        /\ chan' = [chan EXCEPT ![untrustnet_out] = Append(chan[untrustnet_out], ([id|->msg_m.id, isValid|->TRUE, text|->msg_m.text]))]
        /\ pc' = [pc EXCEPT !["messagecheck"] = "modbus1"]
        /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                        untrustnet_in, untrustnet_out, finished_trustnet, 
                        finished_untrustnet, msg_, generated_hmac, msg_m, 
                        msg_v, bareMessage, retreivedHMAC, generatedHMAC, 
                        result, CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, 
                        msgid_, rx_, rxReg_, last2_, incMessage_, incByte_, 
                        rxBuf, guid, msg_u, msgid, rx, rxReg, last2, 
                        incMessage, incByte, msg_tr, txBuf_, txReg_, adder_, 
                        validMessages_, msg, txBuf, txReg, adder, 
                        validMessages >>

mod2 == /\ pc["messagecheck"] = "mod2"
        /\ chan' = [chan EXCEPT ![trustnet_out] = Append(chan[trustnet_out], ([id|->msg_m.id, isValid|->TRUE, text|->msg_m.text]))]
        /\ pc' = [pc EXCEPT !["messagecheck"] = "modbus1"]
        /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                        untrustnet_in, untrustnet_out, finished_trustnet, 
                        finished_untrustnet, msg_, generated_hmac, msg_m, 
                        msg_v, bareMessage, retreivedHMAC, generatedHMAC, 
                        result, CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, 
                        msgid_, rx_, rxReg_, last2_, incMessage_, incByte_, 
                        rxBuf, guid, msg_u, msgid, rx, rxReg, last2, 
                        incMessage, incByte, msg_tr, txBuf_, txReg_, adder_, 
                        validMessages_, msg, txBuf, txReg, adder, 
                        validMessages >>

mod3 == /\ pc["messagecheck"] = "mod3"
        /\ chan' = [chan EXCEPT ![untrustnet_out] = Append(chan[untrustnet_out], ([id|->msg_m.id, isValid|->FALSE, text|->msg_m.text]))]
        /\ pc' = [pc EXCEPT !["messagecheck"] = "modbus1"]
        /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                        untrustnet_in, untrustnet_out, finished_trustnet, 
                        finished_untrustnet, msg_, generated_hmac, msg_m, 
                        msg_v, bareMessage, retreivedHMAC, generatedHMAC, 
                        result, CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, 
                        msgid_, rx_, rxReg_, last2_, incMessage_, incByte_, 
                        rxBuf, guid, msg_u, msgid, rx, rxReg, last2, 
                        incMessage, incByte, msg_tr, txBuf_, txReg_, adder_, 
                        validMessages_, msg, txBuf, txReg, adder, 
                        validMessages >>

mod4 == /\ pc["messagecheck"] = "mod4"
        /\ chan' = [chan EXCEPT ![trustnet_out] = Append(chan[trustnet_out], ([id|->msg_m.id, isValid|->FALSE, text|->msg_m.text]))]
        /\ pc' = [pc EXCEPT !["messagecheck"] = "modbus1"]
        /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                        untrustnet_in, untrustnet_out, finished_trustnet, 
                        finished_untrustnet, msg_, generated_hmac, msg_m, 
                        msg_v, bareMessage, retreivedHMAC, generatedHMAC, 
                        result, CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, 
                        msgid_, rx_, rxReg_, last2_, incMessage_, incByte_, 
                        rxBuf, guid, msg_u, msgid, rx, rxReg, last2, 
                        incMessage, incByte, msg_tr, txBuf_, txReg_, adder_, 
                        validMessages_, msg, txBuf, txReg, adder, 
                        validMessages >>

messagecheck_ == modbus1 \/ mod1 \/ mod2 \/ mod3 \/ mod4

verify1 == /\ pc["verify"] = "verify1"
           /\ Len(chan["verify"]) > 0
           /\ msg_v' = Head(chan["verify"])
           /\ chan' = [chan EXCEPT !["verify"] = Tail(chan["verify"])]
           /\ pc' = [pc EXCEPT !["verify"] = "verify2"]
           /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                           messagecheck, untrustnet_in, untrustnet_out, 
                           finished_trustnet, finished_untrustnet, msg_, 
                           generated_hmac, msg_m, bareMessage, retreivedHMAC, 
                           generatedHMAC, result, CompareHMAC, hmacsMatch, 
                           rxBuf_, guid_, msg_t, msgid_, rx_, rxReg_, last2_, 
                           incMessage_, incByte_, rxBuf, guid, msg_u, msgid, 
                           rx, rxReg, last2, incMessage, incByte, msg_tr, 
                           txBuf_, txReg_, adder_, validMessages_, msg, txBuf, 
                           txReg, adder, validMessages >>

verify2 == /\ pc["verify"] = "verify2"
           /\ retreivedHMAC' = GetHMAC(msg_v.text)
           /\ pc' = [pc EXCEPT !["verify"] = "verify3"]
           /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                           messagecheck, untrustnet_in, untrustnet_out, 
                           finished_trustnet, finished_untrustnet, chan, msg_, 
                           generated_hmac, msg_m, msg_v, bareMessage, 
                           generatedHMAC, result, CompareHMAC, hmacsMatch, 
                           rxBuf_, guid_, msg_t, msgid_, rx_, rxReg_, last2_, 
                           incMessage_, incByte_, rxBuf, guid, msg_u, msgid, 
                           rx, rxReg, last2, incMessage, incByte, msg_tr, 
                           txBuf_, txReg_, adder_, validMessages_, msg, txBuf, 
                           txReg, adder, validMessages >>

verify3 == /\ pc["verify"] = "verify3"
           /\ generatedHMAC' = HMAC(msg_v.text, PASSWORD)
           /\ pc' = [pc EXCEPT !["verify"] = "verify4"]
           /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                           messagecheck, untrustnet_in, untrustnet_out, 
                           finished_trustnet, finished_untrustnet, chan, msg_, 
                           generated_hmac, msg_m, msg_v, bareMessage, 
                           retreivedHMAC, result, CompareHMAC, hmacsMatch, 
                           rxBuf_, guid_, msg_t, msgid_, rx_, rxReg_, last2_, 
                           incMessage_, incByte_, rxBuf, guid, msg_u, msgid, 
                           rx, rxReg, last2, incMessage, incByte, msg_tr, 
                           txBuf_, txReg_, adder_, validMessages_, msg, txBuf, 
                           txReg, adder, validMessages >>

verify4 == /\ pc["verify"] = "verify4"
           /\ hmacsMatch' = CompareHMAC
           /\ IF hmacsMatch'
                 THEN /\ pc' = [pc EXCEPT !["verify"] = "verify5"]
                 ELSE /\ pc' = [pc EXCEPT !["verify"] = "verify6"]
           /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                           messagecheck, untrustnet_in, untrustnet_out, 
                           finished_trustnet, finished_untrustnet, chan, msg_, 
                           generated_hmac, msg_m, msg_v, bareMessage, 
                           retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                           rxBuf_, guid_, msg_t, msgid_, rx_, rxReg_, last2_, 
                           incMessage_, incByte_, rxBuf, guid, msg_u, msgid, 
                           rx, rxReg, last2, incMessage, incByte, msg_tr, 
                           txBuf_, txReg_, adder_, validMessages_, msg, txBuf, 
                           txReg, adder, validMessages >>

verify5 == /\ pc["verify"] = "verify5"
           /\ chan' = [chan EXCEPT ![trustnet_out] = Append(chan[trustnet_out], ([id|->msg_v.id, isValid|->TRUE]))]
           /\ pc' = [pc EXCEPT !["verify"] = "verify1"]
           /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                           messagecheck, untrustnet_in, untrustnet_out, 
                           finished_trustnet, finished_untrustnet, msg_, 
                           generated_hmac, msg_m, msg_v, bareMessage, 
                           retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                           hmacsMatch, rxBuf_, guid_, msg_t, msgid_, rx_, 
                           rxReg_, last2_, incMessage_, incByte_, rxBuf, guid, 
                           msg_u, msgid, rx, rxReg, last2, incMessage, incByte, 
                           msg_tr, txBuf_, txReg_, adder_, validMessages_, msg, 
                           txBuf, txReg, adder, validMessages >>

verify6 == /\ pc["verify"] = "verify6"
           /\ chan' = [chan EXCEPT ![trustnet_out] = Append(chan[trustnet_out], ([id|->msg_v.id, isValid|->FALSE]))]
           /\ pc' = [pc EXCEPT !["verify"] = "verify1"]
           /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                           messagecheck, untrustnet_in, untrustnet_out, 
                           finished_trustnet, finished_untrustnet, msg_, 
                           generated_hmac, msg_m, msg_v, bareMessage, 
                           retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                           hmacsMatch, rxBuf_, guid_, msg_t, msgid_, rx_, 
                           rxReg_, last2_, incMessage_, incByte_, rxBuf, guid, 
                           msg_u, msgid, rx, rxReg, last2, incMessage, incByte, 
                           msg_tr, txBuf_, txReg_, adder_, validMessages_, msg, 
                           txBuf, txReg, adder, validMessages >>

verify_ == verify1 \/ verify2 \/ verify3 \/ verify4 \/ verify5 \/ verify6

trustnet_in1 == /\ pc["trustnet_in"] = "trustnet_in1"
                /\ Len(chan["trustnet_in"]) > 0
                /\ msg_t' = Head(chan["trustnet_in"])
                /\ chan' = [chan EXCEPT !["trustnet_in"] = Tail(chan["trustnet_in"])]
                /\ pc' = [pc EXCEPT !["trustnet_in"] = "start_"]
                /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                                messagecheck, untrustnet_in, untrustnet_out, 
                                finished_trustnet, finished_untrustnet, msg_, 
                                generated_hmac, msg_m, msg_v, bareMessage, 
                                retreivedHMAC, generatedHMAC, result, 
                                CompareHMAC, hmacsMatch, rxBuf_, guid_, msgid_, 
                                rx_, rxReg_, last2_, incMessage_, incByte_, 
                                rxBuf, guid, msg_u, msgid, rx, rxReg, last2, 
                                incMessage, incByte, msg_tr, txBuf_, txReg_, 
                                adder_, validMessages_, msg, txBuf, txReg, 
                                adder, validMessages >>

start_ == /\ pc["trustnet_in"] = "start_"
          /\ IF Len(msg_t) > 0
                THEN /\ IF Len(rxBuf_) = MAXMODBUSSIZE
                           THEN /\ rxBuf_' = <<>>
                                /\ rxReg_' = <<>>
                                /\ incByte_' = <<>>
                                /\ incMessage_' = <<>>
                                /\ pc' = [pc EXCEPT !["trustnet_in"] = "start_"]
                           ELSE /\ pc' = [pc EXCEPT !["trustnet_in"] = "inc_"]
                                /\ UNCHANGED << rxBuf_, rxReg_, incMessage_, 
                                                incByte_ >>
                ELSE /\ pc' = [pc EXCEPT !["trustnet_in"] = "trustnet_in1"]
                     /\ UNCHANGED << rxBuf_, rxReg_, incMessage_, incByte_ >>
          /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                          messagecheck, untrustnet_in, untrustnet_out, 
                          finished_trustnet, finished_untrustnet, chan, msg_, 
                          generated_hmac, msg_m, msg_v, bareMessage, 
                          retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                          hmacsMatch, guid_, msg_t, msgid_, rx_, last2_, rxBuf, 
                          guid, msg_u, msgid, rx, rxReg, last2, incMessage, 
                          incByte, msg_tr, txBuf_, txReg_, adder_, 
                          validMessages_, msg, txBuf, txReg, adder, 
                          validMessages >>

inc_ == /\ pc["trustnet_in"] = "inc_"
        /\ incByte_' = <<Head(msg_t)>>
        /\ incMessage_' = Tail(msg_t)
        /\ IF incByte_' = <<>>
              THEN /\ UNCHANGED rxReg_
              ELSE /\ rxReg_' = incByte_'
        /\ pc' = [pc EXCEPT !["trustnet_in"] = "receive_"]
        /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                        untrustnet_in, untrustnet_out, finished_trustnet, 
                        finished_untrustnet, chan, msg_, generated_hmac, msg_m, 
                        msg_v, bareMessage, retreivedHMAC, generatedHMAC, 
                        result, CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, 
                        msgid_, rx_, last2_, rxBuf, guid, msg_u, msgid, rx, 
                        rxReg, last2, incMessage, incByte, msg_tr, txBuf_, 
                        txReg_, adder_, validMessages_, msg, txBuf, txReg, 
                        adder, validMessages >>

receive_ == /\ pc["trustnet_in"] = "receive_"
            /\ IF rxReg_ = StrTupleToNumTuple(<<":">>)
                  THEN /\ rxBuf_' = <<>>
                  ELSE /\ TRUE
                       /\ UNCHANGED rxBuf_
            /\ pc' = [pc EXCEPT !["trustnet_in"] = "r0_"]
            /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                            messagecheck, untrustnet_in, untrustnet_out, 
                            finished_trustnet, finished_untrustnet, chan, msg_, 
                            generated_hmac, msg_m, msg_v, bareMessage, 
                            retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                            hmacsMatch, guid_, msg_t, msgid_, rx_, rxReg_, 
                            last2_, incMessage_, incByte_, rxBuf, guid, msg_u, 
                            msgid, rx, rxReg, last2, incMessage, incByte, 
                            msg_tr, txBuf_, txReg_, adder_, validMessages_, 
                            msg, txBuf, txReg, adder, validMessages >>

r0_ == /\ pc["trustnet_in"] = "r0_"
       /\ last2_' = Tail(last2_ \o rxReg_)
       /\ pc' = [pc EXCEPT !["trustnet_in"] = "r1_"]
       /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                       untrustnet_in, untrustnet_out, finished_trustnet, 
                       finished_untrustnet, chan, msg_, generated_hmac, msg_m, 
                       msg_v, bareMessage, retreivedHMAC, generatedHMAC, 
                       result, CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, 
                       msgid_, rx_, rxReg_, incMessage_, incByte_, rxBuf, guid, 
                       msg_u, msgid, rx, rxReg, last2, incMessage, incByte, 
                       msg_tr, txBuf_, txReg_, adder_, validMessages_, msg, 
                       txBuf, txReg, adder, validMessages >>

r1_ == /\ pc["trustnet_in"] = "r1_"
       /\ rxBuf_' = rxBuf_ \o rxReg_
       /\ pc' = [pc EXCEPT !["trustnet_in"] = "r2_"]
       /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                       untrustnet_in, untrustnet_out, finished_trustnet, 
                       finished_untrustnet, chan, msg_, generated_hmac, msg_m, 
                       msg_v, bareMessage, retreivedHMAC, generatedHMAC, 
                       result, CompareHMAC, hmacsMatch, guid_, msg_t, msgid_, 
                       rx_, rxReg_, last2_, incMessage_, incByte_, rxBuf, guid, 
                       msg_u, msgid, rx, rxReg, last2, incMessage, incByte, 
                       msg_tr, txBuf_, txReg_, adder_, validMessages_, msg, 
                       txBuf, txReg, adder, validMessages >>

r2_ == /\ pc["trustnet_in"] = "r2_"
       /\ rxReg_' = <<>>
       /\ pc' = [pc EXCEPT !["trustnet_in"] = "check_"]
       /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                       untrustnet_in, untrustnet_out, finished_trustnet, 
                       finished_untrustnet, chan, msg_, generated_hmac, msg_m, 
                       msg_v, bareMessage, retreivedHMAC, generatedHMAC, 
                       result, CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, 
                       msgid_, rx_, last2_, incMessage_, incByte_, rxBuf, guid, 
                       msg_u, msgid, rx, rxReg, last2, incMessage, incByte, 
                       msg_tr, txBuf_, txReg_, adder_, validMessages_, msg, 
                       txBuf, txReg, adder, validMessages >>

check_ == /\ pc["trustnet_in"] = "check_"
          /\ IF NumTupleToStrTuple(last2_) = <<"\r","\n">>
                THEN /\ pc' = [pc EXCEPT !["trustnet_in"] = "check0_"]
                ELSE /\ pc' = [pc EXCEPT !["trustnet_in"] = "start_"]
          /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                          messagecheck, untrustnet_in, untrustnet_out, 
                          finished_trustnet, finished_untrustnet, chan, msg_, 
                          generated_hmac, msg_m, msg_v, bareMessage, 
                          retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                          hmacsMatch, rxBuf_, guid_, msg_t, msgid_, rx_, 
                          rxReg_, last2_, incMessage_, incByte_, rxBuf, guid, 
                          msg_u, msgid, rx, rxReg, last2, incMessage, incByte, 
                          msg_tr, txBuf_, txReg_, adder_, validMessages_, msg, 
                          txBuf, txReg, adder, validMessages >>

check0_ == /\ pc["trustnet_in"] = "check0_"
           /\ msgid_' = guid_ \o "trustnet_in"
           /\ pc' = [pc EXCEPT !["trustnet_in"] = "check1_"]
           /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                           messagecheck, untrustnet_in, untrustnet_out, 
                           finished_trustnet, finished_untrustnet, chan, msg_, 
                           generated_hmac, msg_m, msg_v, bareMessage, 
                           retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                           hmacsMatch, rxBuf_, guid_, msg_t, rx_, rxReg_, 
                           last2_, incMessage_, incByte_, rxBuf, guid, msg_u, 
                           msgid, rx, rxReg, last2, incMessage, incByte, 
                           msg_tr, txBuf_, txReg_, adder_, validMessages_, msg, 
                           txBuf, txReg, adder, validMessages >>

check1_ == /\ pc["trustnet_in"] = "check1_"
           /\ guid_' = guid_ + 1
           /\ pc' = [pc EXCEPT !["trustnet_in"] = "check2_"]
           /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                           messagecheck, untrustnet_in, untrustnet_out, 
                           finished_trustnet, finished_untrustnet, chan, msg_, 
                           generated_hmac, msg_m, msg_v, bareMessage, 
                           retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                           hmacsMatch, rxBuf_, msg_t, msgid_, rx_, rxReg_, 
                           last2_, incMessage_, incByte_, rxBuf, guid, msg_u, 
                           msgid, rx, rxReg, last2, incMessage, incByte, 
                           msg_tr, txBuf_, txReg_, adder_, validMessages_, msg, 
                           txBuf, txReg, adder, validMessages >>

check2_ == /\ pc["trustnet_in"] = "check2_"
           /\ chan' = [chan EXCEPT ![messagecheck] = Append(chan[messagecheck], ([id|->msgid_, text|->rxBuf_, source|->trustnet_in]))]
           /\ pc' = [pc EXCEPT !["trustnet_in"] = "check3_"]
           /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                           messagecheck, untrustnet_in, untrustnet_out, 
                           finished_trustnet, finished_untrustnet, msg_, 
                           generated_hmac, msg_m, msg_v, bareMessage, 
                           retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                           hmacsMatch, rxBuf_, guid_, msg_t, msgid_, rx_, 
                           rxReg_, last2_, incMessage_, incByte_, rxBuf, guid, 
                           msg_u, msgid, rx, rxReg, last2, incMessage, incByte, 
                           msg_tr, txBuf_, txReg_, adder_, validMessages_, msg, 
                           txBuf, txReg, adder, validMessages >>

check3_ == /\ pc["trustnet_in"] = "check3_"
           /\ chan' = [chan EXCEPT ![sign] = Append(chan[sign], ([id|->msgid_, text|->rxBuf_]))]
           /\ pc' = [pc EXCEPT !["trustnet_in"] = "check4_"]
           /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                           messagecheck, untrustnet_in, untrustnet_out, 
                           finished_trustnet, finished_untrustnet, msg_, 
                           generated_hmac, msg_m, msg_v, bareMessage, 
                           retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                           hmacsMatch, rxBuf_, guid_, msg_t, msgid_, rx_, 
                           rxReg_, last2_, incMessage_, incByte_, rxBuf, guid, 
                           msg_u, msgid, rx, rxReg, last2, incMessage, incByte, 
                           msg_tr, txBuf_, txReg_, adder_, validMessages_, msg, 
                           txBuf, txReg, adder, validMessages >>

check4_ == /\ pc["trustnet_in"] = "check4_"
           /\ rxBuf_' = <<>>
           /\ rxReg_' = <<>>
           /\ incByte_' = <<>>
           /\ incMessage_' = <<>>
           /\ pc' = [pc EXCEPT !["trustnet_in"] = "start_"]
           /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                           messagecheck, untrustnet_in, untrustnet_out, 
                           finished_trustnet, finished_untrustnet, chan, msg_, 
                           generated_hmac, msg_m, msg_v, bareMessage, 
                           retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                           hmacsMatch, guid_, msg_t, msgid_, rx_, last2_, 
                           rxBuf, guid, msg_u, msgid, rx, rxReg, last2, 
                           incMessage, incByte, msg_tr, txBuf_, txReg_, adder_, 
                           validMessages_, msg, txBuf, txReg, adder, 
                           validMessages >>

trustnet_in_ == trustnet_in1 \/ start_ \/ inc_ \/ receive_ \/ r0_ \/ r1_
                   \/ r2_ \/ check_ \/ check0_ \/ check1_ \/ check2_
                   \/ check3_ \/ check4_

untrustnet_in1 == /\ pc["untrustnet_in"] = "untrustnet_in1"
                  /\ Len(chan["untrustnet_in"]) > 0
                  /\ msg_u' = Head(chan["untrustnet_in"])
                  /\ chan' = [chan EXCEPT !["untrustnet_in"] = Tail(chan["untrustnet_in"])]
                  /\ pc' = [pc EXCEPT !["untrustnet_in"] = "start"]
                  /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                                  messagecheck, untrustnet_in, untrustnet_out, 
                                  finished_trustnet, finished_untrustnet, msg_, 
                                  generated_hmac, msg_m, msg_v, bareMessage, 
                                  retreivedHMAC, generatedHMAC, result, 
                                  CompareHMAC, hmacsMatch, rxBuf_, guid_, 
                                  msg_t, msgid_, rx_, rxReg_, last2_, 
                                  incMessage_, incByte_, rxBuf, guid, msgid, 
                                  rx, rxReg, last2, incMessage, incByte, 
                                  msg_tr, txBuf_, txReg_, adder_, 
                                  validMessages_, msg, txBuf, txReg, adder, 
                                  validMessages >>

start == /\ pc["untrustnet_in"] = "start"
         /\ IF Len(msg_u) > 0
               THEN /\ pc' = [pc EXCEPT !["untrustnet_in"] = "inc"]
               ELSE /\ pc' = [pc EXCEPT !["untrustnet_in"] = "untrustnet_in1"]
         /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                         untrustnet_in, untrustnet_out, finished_trustnet, 
                         finished_untrustnet, chan, msg_, generated_hmac, 
                         msg_m, msg_v, bareMessage, retreivedHMAC, 
                         generatedHMAC, result, CompareHMAC, hmacsMatch, 
                         rxBuf_, guid_, msg_t, msgid_, rx_, rxReg_, last2_, 
                         incMessage_, incByte_, rxBuf, guid, msg_u, msgid, rx, 
                         rxReg, last2, incMessage, incByte, msg_tr, txBuf_, 
                         txReg_, adder_, validMessages_, msg, txBuf, txReg, 
                         adder, validMessages >>

inc == /\ pc["untrustnet_in"] = "inc"
       /\ incByte' = <<Head(msg_u)>>
       /\ incMessage' = Tail(msg_u)
       /\ IF incByte' = <<>>
             THEN /\ rxReg' = rxReg
             ELSE /\ rxReg' = incByte'
       /\ pc' = [pc EXCEPT !["untrustnet_in"] = "receive"]
       /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                       untrustnet_in, untrustnet_out, finished_trustnet, 
                       finished_untrustnet, chan, msg_, generated_hmac, msg_m, 
                       msg_v, bareMessage, retreivedHMAC, generatedHMAC, 
                       result, CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, 
                       msgid_, rx_, rxReg_, last2_, incMessage_, incByte_, 
                       rxBuf, guid, msg_u, msgid, rx, last2, msg_tr, txBuf_, 
                       txReg_, adder_, validMessages_, msg, txBuf, txReg, 
                       adder, validMessages >>

receive == /\ pc["untrustnet_in"] = "receive"
           /\ IF rxReg = StrTupleToNumTuple(<<"!">>)
                 THEN /\ rxBuf' = <<>>
                 ELSE /\ TRUE
                      /\ rxBuf' = rxBuf
           /\ pc' = [pc EXCEPT !["untrustnet_in"] = "r0"]
           /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                           messagecheck, untrustnet_in, untrustnet_out, 
                           finished_trustnet, finished_untrustnet, chan, msg_, 
                           generated_hmac, msg_m, msg_v, bareMessage, 
                           retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                           hmacsMatch, rxBuf_, guid_, msg_t, msgid_, rx_, 
                           rxReg_, last2_, incMessage_, incByte_, guid, msg_u, 
                           msgid, rx, rxReg, last2, incMessage, incByte, 
                           msg_tr, txBuf_, txReg_, adder_, validMessages_, msg, 
                           txBuf, txReg, adder, validMessages >>

r0 == /\ pc["untrustnet_in"] = "r0"
      /\ last2' = Tail(last2 \o rxReg)
      /\ pc' = [pc EXCEPT !["untrustnet_in"] = "r1"]
      /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                      untrustnet_in, untrustnet_out, finished_trustnet, 
                      finished_untrustnet, chan, msg_, generated_hmac, msg_m, 
                      msg_v, bareMessage, retreivedHMAC, generatedHMAC, result, 
                      CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, msgid_, 
                      rx_, rxReg_, last2_, incMessage_, incByte_, rxBuf, guid, 
                      msg_u, msgid, rx, rxReg, incMessage, incByte, msg_tr, 
                      txBuf_, txReg_, adder_, validMessages_, msg, txBuf, 
                      txReg, adder, validMessages >>

r1 == /\ pc["untrustnet_in"] = "r1"
      /\ rxBuf' = rxBuf \o rxReg
      /\ pc' = [pc EXCEPT !["untrustnet_in"] = "r2"]
      /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                      untrustnet_in, untrustnet_out, finished_trustnet, 
                      finished_untrustnet, chan, msg_, generated_hmac, msg_m, 
                      msg_v, bareMessage, retreivedHMAC, generatedHMAC, result, 
                      CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, msgid_, 
                      rx_, rxReg_, last2_, incMessage_, incByte_, guid, msg_u, 
                      msgid, rx, rxReg, last2, incMessage, incByte, msg_tr, 
                      txBuf_, txReg_, adder_, validMessages_, msg, txBuf, 
                      txReg, adder, validMessages >>

r2 == /\ pc["untrustnet_in"] = "r2"
      /\ rxReg' = <<>>
      /\ pc' = [pc EXCEPT !["untrustnet_in"] = "check"]
      /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                      untrustnet_in, untrustnet_out, finished_trustnet, 
                      finished_untrustnet, chan, msg_, generated_hmac, msg_m, 
                      msg_v, bareMessage, retreivedHMAC, generatedHMAC, result, 
                      CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, msgid_, 
                      rx_, rxReg_, last2_, incMessage_, incByte_, rxBuf, guid, 
                      msg_u, msgid, rx, last2, incMessage, incByte, msg_tr, 
                      txBuf_, txReg_, adder_, validMessages_, msg, txBuf, 
                      txReg, adder, validMessages >>

check == /\ pc["untrustnet_in"] = "check"
         /\ IF NumTupleToStrTuple(last2) = <<"\r","\n">>
               THEN /\ pc' = [pc EXCEPT !["untrustnet_in"] = "check0"]
               ELSE /\ pc' = [pc EXCEPT !["untrustnet_in"] = "start"]
         /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                         untrustnet_in, untrustnet_out, finished_trustnet, 
                         finished_untrustnet, chan, msg_, generated_hmac, 
                         msg_m, msg_v, bareMessage, retreivedHMAC, 
                         generatedHMAC, result, CompareHMAC, hmacsMatch, 
                         rxBuf_, guid_, msg_t, msgid_, rx_, rxReg_, last2_, 
                         incMessage_, incByte_, rxBuf, guid, msg_u, msgid, rx, 
                         rxReg, last2, incMessage, incByte, msg_tr, txBuf_, 
                         txReg_, adder_, validMessages_, msg, txBuf, txReg, 
                         adder, validMessages >>

check0 == /\ pc["untrustnet_in"] = "check0"
          /\ msgid' = guid \o "untrustnet_in"
          /\ pc' = [pc EXCEPT !["untrustnet_in"] = "check1"]
          /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                          messagecheck, untrustnet_in, untrustnet_out, 
                          finished_trustnet, finished_untrustnet, chan, msg_, 
                          generated_hmac, msg_m, msg_v, bareMessage, 
                          retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                          hmacsMatch, rxBuf_, guid_, msg_t, msgid_, rx_, 
                          rxReg_, last2_, incMessage_, incByte_, rxBuf, guid, 
                          msg_u, rx, rxReg, last2, incMessage, incByte, msg_tr, 
                          txBuf_, txReg_, adder_, validMessages_, msg, txBuf, 
                          txReg, adder, validMessages >>

check1 == /\ pc["untrustnet_in"] = "check1"
          /\ guid' = guid + 1
          /\ pc' = [pc EXCEPT !["untrustnet_in"] = "check2"]
          /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                          messagecheck, untrustnet_in, untrustnet_out, 
                          finished_trustnet, finished_untrustnet, chan, msg_, 
                          generated_hmac, msg_m, msg_v, bareMessage, 
                          retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                          hmacsMatch, rxBuf_, guid_, msg_t, msgid_, rx_, 
                          rxReg_, last2_, incMessage_, incByte_, rxBuf, msg_u, 
                          msgid, rx, rxReg, last2, incMessage, incByte, msg_tr, 
                          txBuf_, txReg_, adder_, validMessages_, msg, txBuf, 
                          txReg, adder, validMessages >>

check2 == /\ pc["untrustnet_in"] = "check2"
          /\ chan' = [chan EXCEPT ![messagecheck] = Append(chan[messagecheck], ([id|->msgid, text|->rxBuf, source|->untrustnet_in]))]
          /\ pc' = [pc EXCEPT !["untrustnet_in"] = "check3"]
          /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                          messagecheck, untrustnet_in, untrustnet_out, 
                          finished_trustnet, finished_untrustnet, msg_, 
                          generated_hmac, msg_m, msg_v, bareMessage, 
                          retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                          hmacsMatch, rxBuf_, guid_, msg_t, msgid_, rx_, 
                          rxReg_, last2_, incMessage_, incByte_, rxBuf, guid, 
                          msg_u, msgid, rx, rxReg, last2, incMessage, incByte, 
                          msg_tr, txBuf_, txReg_, adder_, validMessages_, msg, 
                          txBuf, txReg, adder, validMessages >>

check3 == /\ pc["untrustnet_in"] = "check3"
          /\ chan' = [chan EXCEPT ![verify] = Append(chan[verify], ([id|->msgid, text|->rxBuf]))]
          /\ pc' = [pc EXCEPT !["untrustnet_in"] = "check4"]
          /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                          messagecheck, untrustnet_in, untrustnet_out, 
                          finished_trustnet, finished_untrustnet, msg_, 
                          generated_hmac, msg_m, msg_v, bareMessage, 
                          retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                          hmacsMatch, rxBuf_, guid_, msg_t, msgid_, rx_, 
                          rxReg_, last2_, incMessage_, incByte_, rxBuf, guid, 
                          msg_u, msgid, rx, rxReg, last2, incMessage, incByte, 
                          msg_tr, txBuf_, txReg_, adder_, validMessages_, msg, 
                          txBuf, txReg, adder, validMessages >>

check4 == /\ pc["untrustnet_in"] = "check4"
          /\ rxBuf' = <<>>
          /\ rxReg' = <<>>
          /\ incByte' = <<>>
          /\ incMessage' = <<>>
          /\ pc' = [pc EXCEPT !["untrustnet_in"] = "start"]
          /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                          messagecheck, untrustnet_in, untrustnet_out, 
                          finished_trustnet, finished_untrustnet, chan, msg_, 
                          generated_hmac, msg_m, msg_v, bareMessage, 
                          retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                          hmacsMatch, rxBuf_, guid_, msg_t, msgid_, rx_, 
                          rxReg_, last2_, incMessage_, incByte_, guid, msg_u, 
                          msgid, rx, last2, msg_tr, txBuf_, txReg_, adder_, 
                          validMessages_, msg, txBuf, txReg, adder, 
                          validMessages >>

untrustnet_in_ == untrustnet_in1 \/ start \/ inc \/ receive \/ r0 \/ r1
                     \/ r2 \/ check \/ check0 \/ check1 \/ check2 \/ check3
                     \/ check4

to1 == /\ pc["trustnet_out"] = "to1"
       /\ Len(chan["trustnet_out"]) > 0
       /\ msg_tr' = Head(chan["trustnet_out"])
       /\ chan' = [chan EXCEPT !["trustnet_out"] = Tail(chan["trustnet_out"])]
       /\ IF msg_tr'.isValid
             THEN /\ IF \E x \in validMessages_ : x.id = msg_tr'.id
                        THEN /\ txBuf_' = msg_tr'.text
                             /\ pc' = [pc EXCEPT !["trustnet_out"] = "transmit_"]
                             /\ UNCHANGED validMessages_
                        ELSE /\ validMessages_' = (validMessages_ \union {msg_tr'})
                             /\ pc' = [pc EXCEPT !["trustnet_out"] = "finished_"]
                             /\ UNCHANGED txBuf_
             ELSE /\ pc' = [pc EXCEPT !["trustnet_out"] = "finished_"]
                  /\ UNCHANGED << txBuf_, validMessages_ >>
       /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                       untrustnet_in, untrustnet_out, finished_trustnet, 
                       finished_untrustnet, msg_, generated_hmac, msg_m, msg_v, 
                       bareMessage, retreivedHMAC, generatedHMAC, result, 
                       CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, msgid_, 
                       rx_, rxReg_, last2_, incMessage_, incByte_, rxBuf, guid, 
                       msg_u, msgid, rx, rxReg, last2, incMessage, incByte, 
                       txReg_, adder_, msg, txBuf, txReg, adder, validMessages >>

finished_ == /\ pc["trustnet_out"] = "finished_"
             /\ txReg_' = <<>>
             /\ txBuf_' = <<>>
             /\ pc' = [pc EXCEPT !["trustnet_out"] = "to1"]
             /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                             messagecheck, untrustnet_in, untrustnet_out, 
                             finished_trustnet, finished_untrustnet, chan, 
                             msg_, generated_hmac, msg_m, msg_v, bareMessage, 
                             retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                             hmacsMatch, rxBuf_, guid_, msg_t, msgid_, rx_, 
                             rxReg_, last2_, incMessage_, incByte_, rxBuf, 
                             guid, msg_u, msgid, rx, rxReg, last2, incMessage, 
                             incByte, msg_tr, adder_, validMessages_, msg, 
                             txBuf, txReg, adder, validMessages >>

transmit_ == /\ pc["trustnet_out"] = "transmit_"
             /\ IF Len(txBuf_) > 1
                   THEN /\ pc' = [pc EXCEPT !["trustnet_out"] = "a_"]
                        /\ UNCHANGED << chan, txReg_ >>
                   ELSE /\ txReg_' = <<txBuf_[1]>>
                        /\ chan' = [chan EXCEPT ![finished_trustnet] = Append(chan[finished_trustnet], txReg_')]
                        /\ pc' = [pc EXCEPT !["trustnet_out"] = "to2"]
             /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                             messagecheck, untrustnet_in, untrustnet_out, 
                             finished_trustnet, finished_untrustnet, msg_, 
                             generated_hmac, msg_m, msg_v, bareMessage, 
                             retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                             hmacsMatch, rxBuf_, guid_, msg_t, msgid_, rx_, 
                             rxReg_, last2_, incMessage_, incByte_, rxBuf, 
                             guid, msg_u, msgid, rx, rxReg, last2, incMessage, 
                             incByte, msg_tr, txBuf_, adder_, validMessages_, 
                             msg, txBuf, txReg, adder, validMessages >>

a_ == /\ pc["trustnet_out"] = "a_"
      /\ txReg_' = <<Head(txBuf_)>>
      /\ pc' = [pc EXCEPT !["trustnet_out"] = "b_"]
      /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                      untrustnet_in, untrustnet_out, finished_trustnet, 
                      finished_untrustnet, chan, msg_, generated_hmac, msg_m, 
                      msg_v, bareMessage, retreivedHMAC, generatedHMAC, result, 
                      CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, msgid_, 
                      rx_, rxReg_, last2_, incMessage_, incByte_, rxBuf, guid, 
                      msg_u, msgid, rx, rxReg, last2, incMessage, incByte, 
                      msg_tr, txBuf_, adder_, validMessages_, msg, txBuf, 
                      txReg, adder, validMessages >>

b_ == /\ pc["trustnet_out"] = "b_"
      /\ chan' = [chan EXCEPT ![finished_trustnet] = Append(chan[finished_trustnet], txReg_)]
      /\ pc' = [pc EXCEPT !["trustnet_out"] = "c_"]
      /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                      untrustnet_in, untrustnet_out, finished_trustnet, 
                      finished_untrustnet, msg_, generated_hmac, msg_m, msg_v, 
                      bareMessage, retreivedHMAC, generatedHMAC, result, 
                      CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, msgid_, 
                      rx_, rxReg_, last2_, incMessage_, incByte_, rxBuf, guid, 
                      msg_u, msgid, rx, rxReg, last2, incMessage, incByte, 
                      msg_tr, txBuf_, txReg_, adder_, validMessages_, msg, 
                      txBuf, txReg, adder, validMessages >>

c_ == /\ pc["trustnet_out"] = "c_"
      /\ txBuf_' = Tail(txBuf_)
      /\ pc' = [pc EXCEPT !["trustnet_out"] = "transmit_"]
      /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                      untrustnet_in, untrustnet_out, finished_trustnet, 
                      finished_untrustnet, chan, msg_, generated_hmac, msg_m, 
                      msg_v, bareMessage, retreivedHMAC, generatedHMAC, result, 
                      CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, msgid_, 
                      rx_, rxReg_, last2_, incMessage_, incByte_, rxBuf, guid, 
                      msg_u, msgid, rx, rxReg, last2, incMessage, incByte, 
                      msg_tr, txReg_, adder_, validMessages_, msg, txBuf, 
                      txReg, adder, validMessages >>

to2 == /\ pc["trustnet_out"] = "to2"
       /\ validMessages_' = validMessages_ \ {x \in validMessages_: x.id = msg_tr.id}
       /\ pc' = [pc EXCEPT !["trustnet_out"] = "finished_"]
       /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                       untrustnet_in, untrustnet_out, finished_trustnet, 
                       finished_untrustnet, chan, msg_, generated_hmac, msg_m, 
                       msg_v, bareMessage, retreivedHMAC, generatedHMAC, 
                       result, CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, 
                       msgid_, rx_, rxReg_, last2_, incMessage_, incByte_, 
                       rxBuf, guid, msg_u, msgid, rx, rxReg, last2, incMessage, 
                       incByte, msg_tr, txBuf_, txReg_, adder_, msg, txBuf, 
                       txReg, adder, validMessages >>

trustnet_out_ == to1 \/ finished_ \/ transmit_ \/ a_ \/ b_ \/ c_ \/ to2

uto1 == /\ pc["untrustnet_out"] = "uto1"
        /\ Len(chan["untrustnet_out"]) > 0
        /\ msg' = Head(chan["untrustnet_out"])
        /\ chan' = [chan EXCEPT !["untrustnet_out"] = Tail(chan["untrustnet_out"])]
        /\ IF msg'.isValid
              THEN /\ IF \E x \in validMessages : x.id = msg'.id
                         THEN /\ txBuf' = StrTupleToNumTuple(<<"!">>) \o msg'.msg.text
                              /\ pc' = [pc EXCEPT !["untrustnet_out"] = "transmit"]
                              /\ UNCHANGED validMessages
                         ELSE /\ validMessages' = (validMessages \union {msg'})
                              /\ pc' = [pc EXCEPT !["untrustnet_out"] = "finished"]
                              /\ txBuf' = txBuf
              ELSE /\ pc' = [pc EXCEPT !["untrustnet_out"] = "finished"]
                   /\ UNCHANGED << txBuf, validMessages >>
        /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                        untrustnet_in, untrustnet_out, finished_trustnet, 
                        finished_untrustnet, msg_, generated_hmac, msg_m, 
                        msg_v, bareMessage, retreivedHMAC, generatedHMAC, 
                        result, CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, 
                        msgid_, rx_, rxReg_, last2_, incMessage_, incByte_, 
                        rxBuf, guid, msg_u, msgid, rx, rxReg, last2, 
                        incMessage, incByte, msg_tr, txBuf_, txReg_, adder_, 
                        validMessages_, txReg, adder >>

finished == /\ pc["untrustnet_out"] = "finished"
            /\ txReg' = <<>>
            /\ txBuf' = <<>>
            /\ pc' = [pc EXCEPT !["untrustnet_out"] = "uto1"]
            /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                            messagecheck, untrustnet_in, untrustnet_out, 
                            finished_trustnet, finished_untrustnet, chan, msg_, 
                            generated_hmac, msg_m, msg_v, bareMessage, 
                            retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                            hmacsMatch, rxBuf_, guid_, msg_t, msgid_, rx_, 
                            rxReg_, last2_, incMessage_, incByte_, rxBuf, guid, 
                            msg_u, msgid, rx, rxReg, last2, incMessage, 
                            incByte, msg_tr, txBuf_, txReg_, adder_, 
                            validMessages_, msg, adder, validMessages >>

transmit == /\ pc["untrustnet_out"] = "transmit"
            /\ IF Len(txBuf) > 1
                  THEN /\ pc' = [pc EXCEPT !["untrustnet_out"] = "a"]
                       /\ UNCHANGED << chan, txReg >>
                  ELSE /\ txReg' = <<txBuf[1]>>
                       /\ chan' = [chan EXCEPT ![finished_untrustnet] = Append(chan[finished_untrustnet], txReg')]
                       /\ pc' = [pc EXCEPT !["untrustnet_out"] = "uto2"]
            /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, 
                            messagecheck, untrustnet_in, untrustnet_out, 
                            finished_trustnet, finished_untrustnet, msg_, 
                            generated_hmac, msg_m, msg_v, bareMessage, 
                            retreivedHMAC, generatedHMAC, result, CompareHMAC, 
                            hmacsMatch, rxBuf_, guid_, msg_t, msgid_, rx_, 
                            rxReg_, last2_, incMessage_, incByte_, rxBuf, guid, 
                            msg_u, msgid, rx, rxReg, last2, incMessage, 
                            incByte, msg_tr, txBuf_, txReg_, adder_, 
                            validMessages_, msg, txBuf, adder, validMessages >>

a == /\ pc["untrustnet_out"] = "a"
     /\ txReg' = <<Head(txBuf)>>
     /\ pc' = [pc EXCEPT !["untrustnet_out"] = "b"]
     /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                     untrustnet_in, untrustnet_out, finished_trustnet, 
                     finished_untrustnet, chan, msg_, generated_hmac, msg_m, 
                     msg_v, bareMessage, retreivedHMAC, generatedHMAC, result, 
                     CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, msgid_, 
                     rx_, rxReg_, last2_, incMessage_, incByte_, rxBuf, guid, 
                     msg_u, msgid, rx, rxReg, last2, incMessage, incByte, 
                     msg_tr, txBuf_, txReg_, adder_, validMessages_, msg, 
                     txBuf, adder, validMessages >>

b == /\ pc["untrustnet_out"] = "b"
     /\ chan' = [chan EXCEPT ![finished_trustnet] = Append(chan[finished_trustnet], txReg)]
     /\ pc' = [pc EXCEPT !["untrustnet_out"] = "c"]
     /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                     untrustnet_in, untrustnet_out, finished_trustnet, 
                     finished_untrustnet, msg_, generated_hmac, msg_m, msg_v, 
                     bareMessage, retreivedHMAC, generatedHMAC, result, 
                     CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, msgid_, 
                     rx_, rxReg_, last2_, incMessage_, incByte_, rxBuf, guid, 
                     msg_u, msgid, rx, rxReg, last2, incMessage, incByte, 
                     msg_tr, txBuf_, txReg_, adder_, validMessages_, msg, 
                     txBuf, txReg, adder, validMessages >>

c == /\ pc["untrustnet_out"] = "c"
     /\ txBuf' = Tail(txBuf)
     /\ pc' = [pc EXCEPT !["untrustnet_out"] = "transmit"]
     /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                     untrustnet_in, untrustnet_out, finished_trustnet, 
                     finished_untrustnet, chan, msg_, generated_hmac, msg_m, 
                     msg_v, bareMessage, retreivedHMAC, generatedHMAC, result, 
                     CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, msgid_, 
                     rx_, rxReg_, last2_, incMessage_, incByte_, rxBuf, guid, 
                     msg_u, msgid, rx, rxReg, last2, incMessage, incByte, 
                     msg_tr, txBuf_, txReg_, adder_, validMessages_, msg, 
                     txReg, adder, validMessages >>

uto2 == /\ pc["untrustnet_out"] = "uto2"
        /\ validMessages' = validMessages \ {x \in validMessages: x.id = msg.id}
        /\ pc' = [pc EXCEPT !["untrustnet_out"] = "finished"]
        /\ UNCHANGED << trustnet_in, trustnet_out, sign, verify, messagecheck, 
                        untrustnet_in, untrustnet_out, finished_trustnet, 
                        finished_untrustnet, chan, msg_, generated_hmac, msg_m, 
                        msg_v, bareMessage, retreivedHMAC, generatedHMAC, 
                        result, CompareHMAC, hmacsMatch, rxBuf_, guid_, msg_t, 
                        msgid_, rx_, rxReg_, last2_, incMessage_, incByte_, 
                        rxBuf, guid, msg_u, msgid, rx, rxReg, last2, 
                        incMessage, incByte, msg_tr, txBuf_, txReg_, adder_, 
                        validMessages_, msg, txBuf, txReg, adder >>

untrustnet_out_ == uto1 \/ finished \/ transmit \/ a \/ b \/ c \/ uto2

Next == sign_ \/ messagecheck_ \/ verify_ \/ trustnet_in_ \/ untrustnet_in_
           \/ trustnet_out_ \/ untrustnet_out_

Spec == Init /\ [][Next]_vars

\* END TRANSLATION


=============================================================================
\* Modification History
\* Last modified Tue Oct 09 19:08:59 EDT 2018 by mssabr01
\* Last modified Sat Oct 06 22:30:31 EDT 2018 by userMehdi
\* Created Tue Oct 02 17:14:28 EDT 2018 by mssabr01
