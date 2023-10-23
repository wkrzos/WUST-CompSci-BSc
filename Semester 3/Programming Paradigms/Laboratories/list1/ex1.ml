(* Exercise 1 *)

let reverse4 = function (x, y, z, w) -> (w, z, y, x);;

let test_reverse4 () =
  (* Test 1: Standard element reversal *)
  let result1 = reverse4 (0, 1, 2, 3) in
  assert (result1 = (3, 2, 1, 0));;

  (* Test 2: Reversing elements with values of 0 *)
  let result2 = reverse4 (0, 0, 0, 0) in
  assert (result2 = (0, 0, 0, 0));;

  (* Test 3: Reversing elements with negative values *)
  let result3 = reverse4 (-1, -2, -3, -4) in
  assert (result3 = (-4, -3, -2, -1));;

  (* Test 4: Reversing elements with different types *)
  let result4 = reverse4 (1.0, true, 1, "A") in
  assert (result4 = ("A", 1, true, 1.0));;

  (* Test 5: Reversing elements with different types *)
  let result5 = reverse4 (1.5, "Hello", 'c', 42) in
  assert (result5 = (42, 'c', "Hello", 1.5));;

(* Running the tests *)
let () =
test_reverse4 ();;
print_endline "All tests passed.";;

(* Exercise 2 *)

let sumRange = fun (s, e) ->
  let rec aux acc current =
    if current > e - 1 then acc
    else aux (acc + current) (current + 1)
  in aux 0 s
;;

let prodRange = fun (s, e) ->
  let rec aux acc current =
    if current > e - 1 then acc
    else if s = 0 then 0
    else aux (acc * current) (current + 1)
  in
  if s = 0 then 0
  else aux 1 s
;;

let sumProd = fun (s, e) ->
  let sumOfRange = sumRange (s, e) in
  let prodOfRange = prodRange (s, e) in
  (sumOfRange, prodOfRange)
;;

let test_sumProd() = 
  (* Test 1: Positive numbers *)
  let result1 = sumProd (1, 5) in
  assert (result1 = (10, 24));;

  (* Test 2: Only zeros *)
  let result2 = sumProd (0, 0) in
  assert (result2 = (0, 0));;

  (* Test 3: Negative numbers with an even number of factors *)
  let result3 = sumProd (-4, -0) in
  assert (result3 = (-10, 24));;

  (* Test 4: Negative numbers with an odd number of factors *)
  let result4 = sumProd (-4, -1) in
  assert (result4 = (-9, -24));;

  (* Test 5: Range from negative to positive *)
  let result5 = sumProd (-4, 5) in
  assert (result5 = (0, 0));;

(* Run the tests *)
let () =
test_sumProd ();
print_endline "All tests passed.";;

(* Exercise 3 *)

let isPerfect n =
  let rec sum_divisors i sum =
    if i = 0 then sum
    else if n mod i = 0 then
      sum_divisors (i - 1) (sum + i)
    else
      sum_divisors (i - 1) sum
  in
  let sum = sum_divisors (n - 1) 0 in
  sum = n
;;

(* Tests *)

let test_isPerfect () =
  (* Test 1: 6 is a perfect number *)
  let result1 = isPerfect 6 in
  assert (result1 = true);;

  (* Test 2: 28 is a perfect number *)
  let result2 = isPerfect 28 in
  assert (result2 = true);;

  (* Test 3: 12 is not a perfect number *)
  let result3 = isPerfect 12 in
  assert (result3 = false);;

  (* Test 4: 496 is a perfect number *)
  let result4 = isPerfect 496 in
  assert (result4 = true);;

  (* Test 5: 7 is not a perfect number *)
  let result5 = isPerfect 7 in
  assert (result5 = false);;

(* Run the tests *)
let () =
test_isPerfect ();;
print_endline "All tests passed.";;

(* Exercise 4 *)

let insert = function (list, node, position) ->
  let rec aux lst elem pos =
    match lst, pos with
    | _, 0 -> elem :: lst
    | [], _ -> [elem]
    | hd :: tl, _ when pos <= 0 -> elem :: lst
    | hd :: tl, _ -> hd :: (aux tl elem (pos - 1))
  in aux list node position
;;

let test_insert() =
  (* Test 1: Inserting an element at the beginning of an empty list *)
  let result1 = insert ([], "A", 0) in
  assert (result1 = ["A"]);;

  (* Test 2: Inserting an element at the beginning of a non-empty list *)
  let result2 = insert (["B"; "C"], "A", 0) in
  assert (result2 = ["A"; "B"; "C"]);;

  (* Test 3: Inserting an element at the end of the list *)
  let result3 = insert (["A"; "B"], "C", 2) in
  assert (result3 = ["A"; "B"; "C"]);;

  (* Test 4: Inserting an element out of the list's range - it should land at the end *)
  let result4 = insert (["A"; "B"], "C", 10) in
  assert (result4 = ["A"; "B"; "C"]);;

  (* Test 5: Inserting an element at the first position (index 1) *)
  let result5 = insert (["A"; "B"; "C"], "X", 1) in
  assert (result5 = ["A"; "X"; "B"; "C"]);;

  (* Test 6: Inserting an element at the middle position (index 2) *)
  let result6 = insert (["A"; "B"; "C"], "Y", 2) in
  assert (result6 = ["A"; "B"; "Y"; "C"]);;

  (* Test 7: Inserting an element at the penultimate position (index 2) *)
  let result7 = insert (["A"; "B"; "C"], "Z", 2) in
  assert (result7 = ["A"; "B"; "Z"; "C"]);;

  (* Test 8: Inserting an element at the end of the list where the position equals the list's length *)
  let result8 = insert (["A"; "B"; "C"], "D", 3) in
  assert (result8 = ["A"; "B"; "C"; "D"]);;

  (* Test 9: Inserting an element at the beginning of the list when the position is negative *)
  let result9 = insert (["B"; "C"], "A", -1) in
  assert (result9 = ["A"; "B"; "C"]);;

  (* Test 10: Inserting an element at the second position when the position is negative *)
  let result10 = insert (["A"; "C"], "B", -2) in
  assert (result10 = ["B"; "A"; "C"]);;

  (* Test 11: Inserting an element at the end of the list when the position is highly negative *)
  let result11 = insert (["A"; "B"], "C", -10) in
  assert (result11 = ["C"; "A"; "B"]);;

(* Run the tests *)
let () =
test_insert ();;
print_endline "All tests passed.";;
