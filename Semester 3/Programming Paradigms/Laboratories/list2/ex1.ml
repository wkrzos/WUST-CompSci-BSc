(*err: first element is not included, has not be changed*)
let cutOut a b lst =
  let rec helper acc i = function
    | [] -> List.rev acc
    | hd :: tl when i >= a && i <= b ->
      helper (hd :: acc) (i + 1) tl
    | _ :: tl ->
      helper acc (i + 1) tl
  in
  helper [] 0 lst
;;

let cutOut15 = cutOut 1 5;;

let cutOut710 = cutOut 7 10;;
