let rec initSegment (list1, list2) =
  match (list1, list2) with
  | ([], _) -> true  (* If 'list1' is empty, it's an initial segment of any list. *)
  | (_, []) -> false  (* If 'list2' is empty, it's not an initial segment of 'list1'. *)
  | (x :: xs, y :: ys) when x = y -> initSegment (xs, ys)
  | _ -> false
;;

initSegment ([], [1; 2; 3]);;  (* Expect: true, an empty list is an initial segment of any list. *)
initSegment ([1; 2; 3], []);;  (* Expect: false, an empty list cannot be an initial segment of a non-empty list. *)
initSegment ([1], [1; 2; 3]);;  (* Expect: true, [1] is an initial segment of [1; 2; 3]. *)
initSegment ([1; 2; 3], [1]);;  (* Expect: false, [1; 2; 3] is not an initial segment of [1]. *)
initSegment ([1; 2], [1; 2; 3; 4]);;  (* Expect: true, [1; 2] is an initial segment of [1; 2; 3; 4]. *)
initSegment ([1; 2; 4], [1; 2; 3; 4]);;  (* Expect: false, [1; 2; 4] is not an initial segment of [1; 2; 3; 4]. *)
initSegment (["a"; "b"], ["a"; "b"; "c"]);;  (* Expect: true, ["a"; "b"] is an initial segment of ["a"; "b"; "c"]. *)
initSegment (["a"; "b"; "d"], ["a"; "b"; "c"]);;  (* Expect: false, ["a"; "b"; "d"] is not an initial segment of ["a"; "b"; "c"]. *)
initSegment (["x"; "y"; "z"], ["x"; "y"; "z"]);;  (* Expect: true, ["x"; "y"; "z"] is an initial segment of itself. *)
initSegment ([1; 2; 3; 4], [1; 2; 3; 4]);;  (* Expect: true, [1; 2; 3; 4] is an initial segment of itself. *)
initSegment ([1; 2; 3; 4], [1; 2; 3]);;  (* Expect: false, [1; 2; 3; 4] is not an initial segment


