---------------------------- MODULE auth_device ----------------------------
EXTENDS Sequences, FiniteSets, Naturals, TLC
LOCAL INSTANCE Modbus

LOCAL HMACSIZE == 64
LOCAL MINMESSAGESIZE == 1
LOCAL MINMACMESSAGESIZE == 65
LOCAL PASSWORD == "lolpassword"
LOCAL BareMessages == {<<":","1","1","0","3","0","0","6","B","0","0","0","3","7","E","C","R","L","F">>,
                        <<"D","9","2","8","D","9","2","8",
                           "7","5","3","0","7","5","3","0",
                           "9","8","5","C","9","8","5","C",
                           "E","B","B","A","E","B","B","A",
                           "D","9","2","8","D","9","2","8",
                           "7","5","3","0","7","5","3","0",
                           "9","8","5","C","9","8","5","C",
                           "E","B","B","A","E","B","B","A",
                           "9","8","5","C","9","8","5","C",
                           "E","B","B","A","E","B","B","A",
                           "D","9","2","8","D","9","2","8",
                           "7","5","3","0","7","5","3","0",
                           "9","8","5","C","9","8","5","C">>,
                           <<>>}
                       
HMAC(str, pass) == <<"l","o","l","h","m","a","c">> \*not concerned with the inner workings of SHA2

(* --algorithm auth_device

variables 
    trustnet_in = <<>>,
    trustnet_out = <<>>,
    sign = <<>>,
    verify = <<>>,
    messagecheck_in = <<>>,
    messagecheck_out = <<>>,
    untrustnet_in = <<>>,
    untrustnet_out = <<>>,
    chan = <<trustnet_in, trustnet_out, sign, verify, messagecheck_in, messagecheck_out, untrustnet_in, untrustnet_out>>;

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

\* Signing process. Uses _sign_ chan.
process sign = "sign"

variables   msg = <<>>,
            generated_hmac = <<>>;
begin
sign1:   while TRUE do
         
             receive(msg);
             sign2: generated_hmac := HMAC(msg.text, PASSWORD); \*hash it and the password
             sign3: send(untrustnet_out, [msg_id|->msg.id, hmac|->generated_hmac]);
         end while;
end process
\*=========================================

process modbus = "modbus"

variables   msg = <<>>,
            
begin
modbus1:    while TRUE do
        receive(msg);
        if IsModbus(msg.text) then
            if msg.source = "trustnet_in" then 
                send(untrustnet_out, [msg_id|->msg.id, isValid|->"true", text|->msg.text]);
            elsif (msg.source = "untrust_in")
                then send(trustnet_out, [msg_id|->msg.id, isValid|->"true", text|->msg.text]);
            end if;
        
        else
            if msg.source = "trustnet_in" then
                send(untrustnet_out, [msg_id|->msg.id, isValid|->"false", text|->msg.text]);
            elsif msg.source = "untrust_in" then
                send(trustnet_out, [msg_id|->msg.id, isValid|->"false", text|->msg.text]);
            end if;
        end if;
    end while
                
end process


end algorithm;*)

=============================================================================
\* Modification History
\* Last modified Wed Oct 03 18:57:58 EDT 2018 by mssabr01
\* Created Tue Oct 02 17:14:28 EDT 2018 by mssabr01
