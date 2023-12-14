def modifiedPascalF(n: Int): List[Int] = {

  // HOF - addition or difference
  def operationOfList(a: List[Int], b: List[Int], op: (Int, Int) => Int): List[Int] =
    (a, b) match {
      case (Nil, _) => b
      case (_, Nil) => a
      case (x :: xs, y :: ys) => op(x, y) :: operationOfList(xs, ys, op)
    }

  def modifiedPascalIter(n: Int): List[Int] = {
    n match {
      case 0 => List(1)
      case _ =>
        val previous = modifiedPascalIter(n - 1)
        if n % 2 == 0 then
          1 :: operationOfList(previous, previous.drop(1), _ + _)
        else
          1 :: operationOfList(previous, previous.drop(1), _ - _)
    }
  }

  modifiedPascalIter(n)
}

println(modifiedPascalF(0)) // Should be List(1)
println(modifiedPascalF(1)) // Should be List(1, 1)
println(modifiedPascalF(2)) // Should be List(1, 2, 1)
println(modifiedPascalF(3)) // Should be List(1, -1, 1, 1)
println(modifiedPascalF(4)) // Should be List(1, 0, 0, 2, 1)
println(modifiedPascalF(5))

def modifiedPascalI(n: Int): Array[Int] = {
  if (n == 0) return Array(1)
  val arr = Array.fill(n + 1)(0)
  val arrHelper = Array.fill(n + 1)(0)
  arr(0) = 1
  arrHelper(0) = 1
  for (i <- 1 to n) {
    if (i % 2 == 0) {
      for (j <- 1 to i) {
        arrHelper(j) = arr(j - 1) + arr(j)
      }
      if (i != n) arrHelper.copyToArray(arr)
    } else {
      for (k <- 1 to i) {
        arr(k) = arrHelper(k - 1) - arrHelper(k)
      }
      if (i != n) arr.copyToArray(arrHelper)
    }
  }
  if (n % 2 == 0) arrHelper else arr
}

println(modifiedPascalI(0).mkString("Array(", ", ", ")"))
println(modifiedPascalI(1).mkString("Array(", ", ", ")"))
println(modifiedPascalI(2).mkString("Array(", ", ", ")"))
println(modifiedPascalI(3).mkString("Array(", ", ", ")"))
println(modifiedPascalI(4).mkString("Array(", ", ", ")"))
println(modifiedPascalI(5).mkString("Array(", ", ", ")"))
println(modifiedPascalI(6).mkString("Array(", ", ", ")"))
