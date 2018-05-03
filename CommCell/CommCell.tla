------------------ MODULE CommCell ---------------------
(*https://elixir.bootlin.com/linux/v4.2/source/drivers/tty/serial/serial_core.c*)
(*http://www.modbus.org/docs/Modbus_over_serial_line_V1.pdf*)

(*
--algorithm RxTx
{
    \*tx is there is something to send, rx is there is something to receive
   variables 
        isIdle = TRUE, 
        startMsg = ":", 
        end1="CR",
        end2="LF",
        tx = FALSE, \*set by application if the buffer contains a message to send
        rx = FALSE, \* set by code below when we've received a full, valid frame ready to be processed
        txReg \in 0 ..255,
        rxReg \in 0 .. 255,
        rxBuffCount = 0;
        txBuffCount = 0,
        isValidCRC = TRUE;
        isValidModbus = TRUE;
            
    \* Station is idle
    \* can rx or tx
    \* tx ---------------------------------
    
    process (Serial = "Serial")
    {
        idle: while (TRUE)
        {
            isIdle := TRUE;
            \*if we have something to send and we are not receiving
            \*and if the buffer contains a valid Modbus frame (TODO)
            switchToTx: if(tx = TRUE && txBuffCount \= 0 && isValidModbus)
            { 
                \* we are no longer idle, put the start message 
                \* character, ";", into the send transmit register
                emission_start: isIdle  := FALSE;
                                txReg   := startMsg;
                \* while there is stuff to send, keep sending it byte by byte
                emission:   while ( l1: txBuffCount \= 0)
                            { 
                                l2: txReg := txBuff;
                                    txBuffCount := txBuffCount -1;
                            };
                \* when the register is empty send the CR/LF and go back to idle
                emission_end: txReg := end1;
                backToIdle: txReg := end2;
                              tx := FALSE;
                              goto idle;
            };
            \* if we are receiving something (there is a ":" in the rx register)
            switchToRx: if(rxReg = startMsg)
            {
                \*init reception: set idle to false, reset the receive buffer counter
                reception:  isIdle := FALSE;
                            rxBuffCount := 0;
                            \* if at any point before the message is complete we get another ":"
                            \* restart the process
                            r1: if(rxReg = startMsg) {goto reception}; \*can receive ":" multiple times
                            \*loop until we get the end of the message
                            r2: while( rxReg \= "CR" )
                                {
                                    if(rxReg = startMsg) {goto reception; };
                                    r3: rxBuffCount := rxBuffCount + 1;
                                        rxBuff[rxBuffCount] := rxReg;
                                };
                            \*handle end of frame, check if valid modbus (TODO)
                            \*handle CRC (TODO)
                endFrame:   if(rxReg = startMsg) { goto reception; };
                            r4: if(rxReg = end2 && isValidModbus && isValidCRC)
                                {
                                \*if we get LF\CR and the CRC is good and the frame is valid modbus
                                \*then signal to the application that the rx buffer is ready to process
                                    rx := TRUE;
                                };
                            
                            
            };
        };          
    }                            
     

    
}
*)
\* BEGIN TRANSLATION
VARIABLES isIdle, startMsg, end1, end2, tx, rx, txReg, rxReg, rxBuffCount, 
          txBuffCount, isValidCRC, isValidModbus, pc

vars == << isIdle, startMsg, end1, end2, tx, rx, txReg, rxReg, rxBuffCount, 
           txBuffCount, isValidCRC, isValidModbus, pc >>

ProcSet == {"Serial"}

Init == (* Global variables *)
        /\ isIdle = TRUE
        /\ startMsg = ":"
        /\ end1 = "CR"
        /\ end2 = "LF"
        /\ tx = FALSE
        /\ rx = FALSE
        /\ txReg \in 0 ..255
        /\ rxReg \in 0 .. 255
        /\ rxBuffCount = 0
        /\ txBuffCount = 0
        /\ isValidCRC = TRUE
        /\ isValidModbus = TRUE
        /\ pc = [self \in ProcSet |-> "idle"]

idle == /\ pc["Serial"] = "idle"
        /\ isIdle' = TRUE
        /\ pc' = [pc EXCEPT !["Serial"] = "switchToTx"]
        /\ UNCHANGED << startMsg, end1, end2, tx, rx, txReg, rxReg, 
                        rxBuffCount, txBuffCount, isValidCRC, isValidModbus >>

switchToTx == /\ pc["Serial"] = "switchToTx"
              /\ IF tx = TRUE && txBuffCount \= 0 && isValidModbus
                    THEN /\ pc' = [pc EXCEPT !["Serial"] = "emission_start"]
                    ELSE /\ pc' = [pc EXCEPT !["Serial"] = "switchToRx"]
              /\ UNCHANGED << isIdle, startMsg, end1, end2, tx, rx, txReg, 
                              rxReg, rxBuffCount, txBuffCount, isValidCRC, 
                              isValidModbus >>

emission_start == /\ pc["Serial"] = "emission_start"
                  /\ isIdle' = FALSE
                  /\ txReg' = startMsg
                  /\ pc' = [pc EXCEPT !["Serial"] = "emission"]
                  /\ UNCHANGED << startMsg, end1, end2, tx, rx, rxReg, 
                                  rxBuffCount, txBuffCount, isValidCRC, 
                                  isValidModbus >>

emission == /\ pc["Serial"] = "emission"
            /\ IF l1: txBuffCount \= 0
                  THEN /\ pc' = [pc EXCEPT !["Serial"] = "l2"]
                  ELSE /\ pc' = [pc EXCEPT !["Serial"] = "emission_end"]
            /\ UNCHANGED << isIdle, startMsg, end1, end2, tx, rx, txReg, rxReg, 
                            rxBuffCount, txBuffCount, isValidCRC, 
                            isValidModbus >>

l2 == /\ pc["Serial"] = "l2"
      /\ txReg' = txBuff
      /\ txBuffCount' = txBuffCount -1
      /\ pc' = [pc EXCEPT !["Serial"] = "emission"]
      /\ UNCHANGED << isIdle, startMsg, end1, end2, tx, rx, rxReg, rxBuffCount, 
                      isValidCRC, isValidModbus >>

emission_end == /\ pc["Serial"] = "emission_end"
                /\ txReg' = end1
                /\ pc' = [pc EXCEPT !["Serial"] = "backToIdle"]
                /\ UNCHANGED << isIdle, startMsg, end1, end2, tx, rx, rxReg, 
                                rxBuffCount, txBuffCount, isValidCRC, 
                                isValidModbus >>

backToIdle == /\ pc["Serial"] = "backToIdle"
              /\ txReg' = end2
              /\ tx' = FALSE
              /\ pc' = [pc EXCEPT !["Serial"] = "idle"]
              /\ UNCHANGED << isIdle, startMsg, end1, end2, rx, rxReg, 
                              rxBuffCount, txBuffCount, isValidCRC, 
                              isValidModbus >>

switchToRx == /\ pc["Serial"] = "switchToRx"
              /\ IF rxReg = startMsg
                    THEN /\ pc' = [pc EXCEPT !["Serial"] = "reception"]
                    ELSE /\ pc' = [pc EXCEPT !["Serial"] = "idle"]
              /\ UNCHANGED << isIdle, startMsg, end1, end2, tx, rx, txReg, 
                              rxReg, rxBuffCount, txBuffCount, isValidCRC, 
                              isValidModbus >>

reception == /\ pc["Serial"] = "reception"
             /\ isIdle' = FALSE
             /\ rxBuffCount' = 0
             /\ pc' = [pc EXCEPT !["Serial"] = "r1"]
             /\ UNCHANGED << startMsg, end1, end2, tx, rx, txReg, rxReg, 
                             txBuffCount, isValidCRC, isValidModbus >>

r1 == /\ pc["Serial"] = "r1"
      /\ IF rxReg = startMsg
            THEN /\ pc' = [pc EXCEPT !["Serial"] = "reception"]
            ELSE /\ pc' = [pc EXCEPT !["Serial"] = "r2"]
      /\ UNCHANGED << isIdle, startMsg, end1, end2, tx, rx, txReg, rxReg, 
                      rxBuffCount, txBuffCount, isValidCRC, isValidModbus >>

r2 == /\ pc["Serial"] = "r2"
      /\ IF rxReg \= "CR"
            THEN /\ IF rxReg = startMsg
                       THEN /\ pc' = [pc EXCEPT !["Serial"] = "reception"]
                       ELSE /\ pc' = [pc EXCEPT !["Serial"] = "r3"]
            ELSE /\ pc' = [pc EXCEPT !["Serial"] = "endFrame"]
      /\ UNCHANGED << isIdle, startMsg, end1, end2, tx, rx, txReg, rxReg, 
                      rxBuffCount, txBuffCount, isValidCRC, isValidModbus >>

r3 == /\ pc["Serial"] = "r3"
      /\ rxBuffCount' = rxBuffCount + 1
      /\ rxBuff' = [rxBuff EXCEPT ![rxBuffCount'] = rxReg]
      /\ pc' = [pc EXCEPT !["Serial"] = "r2"]
      /\ UNCHANGED << isIdle, startMsg, end1, end2, tx, rx, txReg, rxReg, 
                      txBuffCount, isValidCRC, isValidModbus >>

endFrame == /\ pc["Serial"] = "endFrame"
            /\ IF rxReg = startMsg
                  THEN /\ pc' = [pc EXCEPT !["Serial"] = "reception"]
                  ELSE /\ pc' = [pc EXCEPT !["Serial"] = "r4"]
            /\ UNCHANGED << isIdle, startMsg, end1, end2, tx, rx, txReg, rxReg, 
                            rxBuffCount, txBuffCount, isValidCRC, 
                            isValidModbus >>

r4 == /\ pc["Serial"] = "r4"
      /\ IF rxReg = end2 && isValidModbus && isValidCRC
            THEN /\ rx' = TRUE
            ELSE /\ TRUE
                 /\ rx' = rx
      /\ pc' = [pc EXCEPT !["Serial"] = "idle"]
      /\ UNCHANGED << isIdle, startMsg, end1, end2, tx, txReg, rxReg, 
                      rxBuffCount, txBuffCount, isValidCRC, isValidModbus >>

Serial == idle \/ switchToTx \/ emission_start \/ emission \/ l2
             \/ emission_end \/ backToIdle \/ switchToRx \/ reception \/ r1
             \/ r2 \/ r3 \/ endFrame \/ r4

Next == Serial

Spec == Init /\ [][Next]_vars

\* END TRANSLATION

==============================================================
