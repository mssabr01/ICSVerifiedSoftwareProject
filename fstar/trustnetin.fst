module Trustnetin

open FStar.Char
open FStar.Seq

let MAXMODBUSSIZE = 515

(*str length 3, starts with :, ends with \r\n"*)
//val IsComplete: s:string{length s <= MAXMODBUSSIZE} -> Tot bool
let IsComplete s = 
   if (head s) = ":" && (head (Reverse s)) = "\n" then true else false
