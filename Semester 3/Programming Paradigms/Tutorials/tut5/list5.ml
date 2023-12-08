(* Exercise 1 *)

type 'a lazyList = Cons of 'a * (unit -> 'a lazyList);;

let rec repeatElement n y =
  if n = 0 then
    Cons (y, fun () -> repeatElement n y)
  else
    Cons (y, fun () -> repeatElement (n - 1) y)
;;

let rec lrepeat k (Cons (x, xs)) =
  let rec repeatKTimes m =
    if m = 0 then
      lrepeat k (xs ())
    else
      repeatElement k x :: repeatKTimes (m - 1)
  in
  lazy (List.fold_right (fun e acc -> Cons (e, fun () -> acc)) (repeatKTimes k) (lrepeat k (xs ())));;
;;

lrepeat 3 (repeatElement 2 1);;

(* Exercise 2 *)
  
