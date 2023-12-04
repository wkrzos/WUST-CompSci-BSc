(* Exercise 4 *)

let count_internal_nodes tree =
  let rec count_internal_nodes_aux t acc =
    match t with
    | Empty -> 0
    | Node (_, Empty, Empty) -> acc
    | Node (_, left, Empty) | Node (_, Empty, right) ->
        acc + count_internal_nodes_aux left (acc + 1)
    | Node (_, right, left) ->
        acc + count_internal_nodes_aux right (acc + 1) + count_internal_nodes_aux left (acc + 1)
  in
  count_internal_nodes_aux tree 0

let count_external_nodes tree =
  let rec count_external_nodes_aux t acc =
    match t with
    | Empty -> acc
    | Node (_, Empty, Empty) -> 2 * (acc + 1)
    | Node (_, left, Empty) | Node (_, Empty, right) ->
        count_external_nodes_aux left (acc + 1) + acc + 1 + count_external_nodes_aux right (acc + 1)
    | Node (_, left, right) ->
        count_external_nodes_aux left (acc + 1) + count_external_nodes_aux right (acc + 1)
  in
  count_external_nodes_aux tree 0

type 'a graph = Graph of ('a -> 'a list)

(* Exercise 5 *)

let depth_first_search (Graph graph) start_node =
  let rec dfs_aux visited = function
    | [] -> []
    | head :: tail ->
        if List.mem head visited then dfs_aux visited tail
        else head :: dfs_aux (head :: visited) (graph head @ tail)
  in
  dfs_aux [] [start_node]
