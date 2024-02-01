trait Low
trait LuxTorpeda extends Low
trait Super extends LuxTorpeda

type Permission = Low

trait User[+ReadPerm <: Permission, +WritePerm <: Permission] {
  def retrieveFromTerminal(retrieved: String): Unit
  def passToTerminal(): String
}

class Terminal[ReadPerm <: Permission, WritePerm <: ReadPerm](private var secret: String) {
  def read(user: User[ReadPerm, _]): Unit = {
    println(s"Terminal reading with user of permission: ${user.getClass.getSimpleName}")
    user.retrieveFromTerminal(secret)
    println(s"User retrieved secret: $secret")
  }

  def write(user: User[_, WritePerm]): Unit = {
    println(s"Terminal writing with user of permission: ${user.getClass.getSimpleName}")
    val newSecret = user.passToTerminal()
    println(s"User provided new secret: $newSecret")
    secret = newSecret
  }
}

class GenericUser[ReadPerm <: Permission, WritePerm <: Permission](var secret: String) extends User[ReadPerm, WritePerm] {
  override def retrieveFromTerminal(retrieved: String): Unit = {
    println(s"User (${this.getClass.getSimpleName}) retrieving secret from terminal.")
    secret = retrieved
    println(s"User secret updated to: $secret")
  }

  override def passToTerminal(): String = {
    println(s"User (${this.getClass.getSimpleName}) passing secret to terminal.")
    secret
  }
}

// User instances
val lowUser = new GenericUser[Low, Low]("chemtrails are real")
val highUser = new GenericUser[LuxTorpeda, LuxTorpeda]("there are reptilians living under the surface of the Earth")
val luxTorpedaUser = new GenericUser[Super, Super]("the Earth is flat but the other planets are spherical in nature")

// Terminal instances
val lowTerminal = new Terminal[Low, Low]("uno")
val highTerminal = new Terminal[LuxTorpeda, LuxTorpeda]("dos")
val luxTorpedaTerminal = new Terminal[Super, Super]("tres")

//============== TEST 1 ==============
lowUser.secret
highUser.secret
luxTorpedaUser.secret

//============== TEST 2 ==============
// Test Case 1: Reading from Terminal
println("Test Case 1: Reading from Terminal")
lowTerminal.read(lowUser)  // Should print permissions and update user secret

// Test Case 2: Writing to Terminal
println("\nTest Case 2: Writing to Terminal")
lowTerminal.write(lowUser)  // Should print permissions and update terminal secret

// Test Case 3: Reading with a higher permission user
println("\nTest Case 3: Reading with a higher permission user")
highTerminal.read(highUser)  // Should print permissions and update user secret

// Test Case 4: Writing with a higher permission user
println("\nTest Case 4: Writing with a higher permission user")
highTerminal.write(highUser)  // Should print permissions and update terminal secret

// Test Case 5: Reading with a super permission user
println("\nTest Case 5: Reading with a super permission user")
luxTorpedaTerminal.read(luxTorpedaUser)  // Should print permissions and update user secret

// Test Case 6: Writing with a super permission user
println("\nTest Case 6: Writing with a super permission user")
luxTorpedaTerminal.write(luxTorpedaUser)  // Should print permissions and update terminal secret

// Test Case 7
highTerminal.write(luxTorpedaUser)

// Test Case 8
//superTerminal.write(lowUser)

// Test Case 9
//highTerminal.write(lowUser)

