module Trustnetin

open FStar.Char
open FStar.Seq

let MAXMODBUSSIZE = 515

(*str length 3, starts with :, e
nds with \r\n"*)
val IsComplete: s:string{(length s) <= MAXMODBUSSIZE} -> Tot bool
let IsComplete s = match s with 
  | str: length str < 3 -> falsse
  | hd :: tl -> if hd = ":" && Reverse tl = "\n\r" then true else false
