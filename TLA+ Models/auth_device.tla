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

macro receive(msg) 
    begin
        await Len(chan[self]) > 0;
        msg := Head(chan[self]);
        chan[self] := Tail(chan[self]);
    end macro;

\* Signing process.
process sign = "sign"

variables   msg = <<>>,
            generated_hmac = <<>>;
begin
sign1:   while TRUE do
         
             receive(msg);
             sign2: generated_hmac := HMAC(msg.text, PASSWORD); \*hash it and the password
             sign3: send(untrustnet_out, [id|->msg.id, hmac|->generated_hmac]);
         end while;
end process
\*=========================================

\*Check validitity of the underlying protocol. In this case Modbus
process messagecheck = "messagecheck"

variables   msg = <<>>
            
begin
modbus1:    while TRUE do
                receive(msg);
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
                receive(msg);
                verify2: generatedHMAC := HMAC(msg.text, PASSWORD);
                verify3: hmacsMatch := CompareHMAC;
                if hmacsMatch then
                    verify4: send(trustnet_out, [id|->msg.id, isValid|->TRUE]);
                else
                    verify5: send(trustnet_out, [id|->msg.id, isValid|->FALSE]);
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
                receive(msg);
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
                            if NumTupleToStrTuple(last2) == <<"\r","\n">> then \*convert back to ASCII before checking for end of packet
                                check0: msgid := guid \o "trustnet_in";
                                check1: guid := guid + 1;
                                check2: send(messagecheck, [id|->msgid, text|->rxBuf, source|->self]);
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
                receive(msg);
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
                            if NumTupleToStrTuple(last2) == <<"\r","\n">> then \*convert back to ASCII before checking for end of packet
                                check0: msgid := guid \o "untrustnet_in";
                                check1: guid := guid + 1;
                                check2: send(messagecheck, [id|->msgid, text|->rxBuf, source|->self]);
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
            msgBuf = [x \in {} |-> 0]
            
begin
    while TRUE do
        receive(msg);
        if msg.isValid then
            adder := 1;
        else adder := -1;
        end if;
        msgBuf := [x \in DOMAIN msgBuf |-> IF x == msg.id THEN msgBuf[x]+adder ELSE msgBuf[x]]
        \*If a message is waiting for its couterpart (ie the modbus was verified but we are still waiting for the crypto) then it will be at 1
        \*If both are verified then the value will be 2
        \*If one is verified and the other is not, it will be 0

        
        \*go through buffers looking for matching messages
        for
        txBuf := msg;
transmit:   if Len(txBuf) > 1
            then
                \*empty the buffer into the register
                a: txReg := <<Head(txBuf)>>;
                b: txBuf := Tail(txBuf);
                goto transmit;
            else
                txReg := <<txBuf[1]>>;
            end if;
            
finished: txReg:= <<>>;
          txBuf := <<>>;

end algorithm;*)


=============================================================================
\* Modification History
\* Last modified Sun Oct 07 12:51:57 EDT 2018 by mssabr01
\* Last modified Sat Oct 06 22:30:31 EDT 2018 by userMehdi
\* Created Tue Oct 02 17:14:28 EDT 2018 by mssabr01
