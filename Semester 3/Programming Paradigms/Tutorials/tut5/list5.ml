type 'a lazy_list = Cons of 'a * (unit -> 'a lazy_list)

let rec lrepeat k (Cons (x, xs)) =
  let rec repeatHelper n elem =
    if n = 0 then
      []
    else
      elem :: repeatHelper (n - 1) elem
  in
  lazy (
    repeatHelper k x @ lrepeat k (Lazy.force (xs ()))
  )
