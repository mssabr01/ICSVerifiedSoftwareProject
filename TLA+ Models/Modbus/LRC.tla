-------------------------------- MODULE LRC --------------------------------

LOCAL INSTANCE Naturals
LOCAL INSTANCE Sequences
LOCAL INSTANCE TLC

RECURSIVE addSeq(_) 
addSeq(seq) == 
    IF seq = <<>>
    THEN 0
    ELSE Head(seq) + addSeq(Tail(seq))


\*Takes a decimal number and creates an 8-bit binary sequence. 8-bit is all that is necessary for LRC so that is all we do here
DecimalToBinarySeq(num) ==  <<num \div 128 % 2>>
                         \o <<num \div 64 % 2>>
                         \o <<num \div 32 % 2>>
                         \o <<num \div 16 % 2>>
                         \o <<num \div 8 % 2>>
                         \o <<num \div 4 % 2>>
                         \o <<num \div 2 % 2>>
                         \o <<num % 2>>

\*B2D and BinarySeqToDecimal operate in tandem to transform a sequence of 1's and 0's of arbitrary length to a decimal number
RECURSIVE B2D(_,_)
LOCAL B2D(num,seq) ==
    IF seq = <<>>
    THEN 0
    ELSE (seq[Len(seq)] * num) + B2D(2*num, SubSeq(seq,1,Len(seq)-1))

BinarySeqToDecimal(seq) == B2D(1,seq)

\*adds 1 to a binary sequence the "I don't feel like doing this in binary" way
BinaryAdd1(seq) == DecimalToBinarySeq(BinarySeqToDecimal(seq)+1)

\*XOR for 1's and 0's because TLA+ XOR only operates on TRUE/FALSE
XOR(a,b) == CASE a=1 /\ b=1 -> 0
              [] a=1 /\ b=0 -> 1
              [] a=0 /\ b=1 -> 1
              [] OTHER -> 0
              
\*takes a binary sequence and produces the 2s compliment
TwosComp(seq) == BinaryAdd1([x \in DOMAIN seq |-> XOR(seq[x],1)])

\*the reason this module exists
CalculateLRC(seq) == BinarySeqToDecimal(TwosComp(DecimalToBinarySeq((addSeq(seq) % 256)))) \*negative of all bytes added together mod 2^8

=============================================================================
\* Modification History
\* Last modified Thu Jun 13 12:27:36 EDT 2019 by mehdi
\* Last modified Wed May 02 18:01:26 EDT 2018 by SabraouM
\* Created Wed May 02 17:41:39 EDT 2018 by SabraouM