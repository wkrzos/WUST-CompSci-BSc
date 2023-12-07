sealed trait Expression
case class Val(value: Double) extends Expression
case object Sum extends Expression
case object Diff extends Expression
case object Prod extends Expression
case object Div extends Expression

def evaluate(expression: List[Expression]): Option[Double] = {
  var stack: List[Double] = Nil

  def applyOperation(operation: Expression, val1: Double, val2: Double): Double =
    operation match {
      case Sum => val1 + val2
      case Diff => val1 - val2
      case Prod => val1 * val2
      case Div => if (val2 != 0) val1 / val2 else throw new IllegalArgumentException("Division by zero")
    }

  try {
    for (elem <- expression) {
      elem match {
        case Val(value) => stack = value :: stack
        case operator =>
          if (stack.length < 2)
            throw new IllegalArgumentException("Not enough list elements, expression invalid")

          val val1 = stack.head
          stack = stack.tail

          val val2 = stack.head
          stack = stack.tail

          val result = applyOperation(operator, val2, val1)
          stack = result :: stack
      }
    }

    if (stack.length == 1)
      Some(stack.head)
    else
      throw new IllegalArgumentException("Invalid expression")
  } catch {
    case _: IllegalArgumentException | _: ArithmeticException => None
  }
}

val list1 = List(Val(1.0), Val(3.5), Sum)
val list2 = List(Val(0.0), Val(1.0), Div)
val list3 = List(Val(1.0), Val(2.0), Val(2.0), Prod, Sum, Val(1.0), Sum)
val list4 = List(Val(1.0), Val(0.0), Prod)
val list5 = List(Val(1.0), Val(0.0), Div)
val list6 = List(Val(2.0), Val(2.0), Sum, Val(3.0), Prod)
val list7 = List(Val(2.0), Val(3.0), Sum, Val(4.0), Prod)
val list8 = List(Val(3.0), Val(7.0), Val(10.0), Prod, Sum)
val list9 = List(Val(3.0), Val(1.0), Sum, Val(3.0), Val(2.0), Sum, Prod)
val list10 = List(Val(3.0), Val(1.0), Sum, Val(4.0), Val(4.0), Sum, Div)


println(evaluate(list1)) // Some 4.5
println(evaluate(list2)) // Some 0.0
println(evaluate(list3)) // Some 6.0 = A + B * C + D
println(evaluate(list4)) // Some 0.0
println(evaluate(list5)) // None (Division by zero)
println(evaluate(list6)) // Some 12.0 = (A + B) * C
println(evaluate(list7)) // Some 20.0 = (A + B) * C
println(evaluate(list8)) // Some 73.0 = A + B * C
println(evaluate(list9)) // Some 20.0 = (A + B) * (C + D)
println(evaluate(list10)) // Some 0.5 = (A + B) / (C + D)
