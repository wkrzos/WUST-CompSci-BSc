sealed trait Expression
  case class Val(value: Double)
  case object Sum extends Expression
  case object Diff extends Expression
  case object Prod extends Expression
  case object Div extends Expression

def evaluate(expression: List[Expression]): Option[Double] =

  var stack: List[Double] = Nil

  def applyOperation(operation: Expression, val1: Double, val2: Double): Double =
    operation match
      case Sum => val1 + val2
      case Diff => val1 - val2
      case Prod => val1 * val2
      case Div => val1 / val2

  try
    for (elem <- expression)
      elem match
        case Val(value) => stack = value :: stack
        case operator =>

          if (stack.length < 2)
            throw new IllegalArgumentException("Not enough list elements, expression invalid")

          val val2 = stack.head
          stack = stack.tail

          val1 = stack.head
          stack = stack.tail

          val result = applyOperation(operator, val1, val2)
          stack = result :: stack

    if (stack.length == 1)
      Some(stack.head)
    else
      throw new IllegalArgumemtException("i")

    catch
      case _: Throwable => None