let rec fib n =
  if n = 0 then 0
  else if n = 1 then 1
  else fib (n - 1) + fib (n - 2)
;;

let fibTail number =
  let rec fibTail' n a b =
    if n = 0 then
      a
    else
      fibTail' (n - 1) b (a + b)
  in fibTail' number 0 1
;;

fib 45;;

fibTail 45;;