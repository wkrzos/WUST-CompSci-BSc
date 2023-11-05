let root3 a =
  let e = 1e-15 in  (* Precision constant *)
  if a < 0.0 then
    invalid_arg "Input number must be non-negative"
  else if a = 0.0 then
    0.0
  else
    let rec root3' x =
      let next_x = x +. ((a /. (x *. x) -. x) /. 3.0) in
      if abs_float (x *. x *. x -. a) <= e *. abs_float a then x
      else root3' next_x
    in
    root3' a
;;

root3 0.1;;
