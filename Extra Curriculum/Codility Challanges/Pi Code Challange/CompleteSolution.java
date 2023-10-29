import java.util.Arrays;

public class CompleteSolution {

    public static void main(String[] args) {

        // Example 1
        int result1 = CompleteSolution.solution("abc", "bcd");
        System.out.println(result1); // expected output: 2

        // Example 2
        int result2 = CompleteSolution.solution("axxz", "yzwy");
        System.out.println(result2); // expected output: 2

        // Example 3
        int result3 = CompleteSolution.solution("bacad", "abada");
        System.out.println(result3); // expected output: 1

        // Example 4
        int result4 = CompleteSolution.solution("amz", "amz");
        System.out.println(result4); // expected output: 3

        // Example 5: "ab", "ba" => "ab" => 1
        int result5 = CompleteSolution.solution("ab", "ba");
        System.out.println(result5); // expected output: 1

        // Example 6
        int result = CompleteSolution.solution("aafsjkhflaskjhdflsafhlaksdhf", "asfewfwaefhvnxncvbxcbvexvbjq");
        System.out.println(result); // expected output: ?

        // Example 7
        int result7 = CompleteSolution.solution("aa", "bba");
        System.out.println(result7); // expected output: 1 ?
    }

    // Solution: findMinimumOperations
    public static int solution(String P, String Q) {

        // Create a 2D array to represent the allowed transitions between characters.
        // There are 26 letters in the english alphabet.
        boolean[][] allowedTransitions = createAllowedTransitions(P, Q);

        // Identify the diagonal characters (i.e., characters that don't need any
        // operation) and remove all transitions involving them from the
        // allowedTransitions array to simplify the search process
        int numDiagonalChars = removeDiagonalChars(allowedTransitions);

        // Calculate the set of remaining characters (i.e., characters that can
        // transition to at least one other character) and initialize an integer array
        // to store the minimum number of operations required to transform the initial
        // string into the final string
        int remainingChars = calculateRemainingChars(allowedTransitions);

        // Initialize an integer array to store the minimum number of operations
        int[] minOperations = new int[]{P.length()};

        // Call the DepthFirstSearch method to find the minimum number of operations to
        // transform the initial string into the final string and update the value of
        // minOperations[0]
        depthFirstSearch(remainingChars, 0, 0, allowedTransitions, numDiagonalChars, minOperations);

        //System.out.println(minOperations[0]); // debug
        return minOperations[0];
    }

    /**
     * The provided code snippet calculates the index of a character within the
     * English alphabet. Here's how it works:
     * 
     * 1. `initialString.charAt(i)` retrieves the character at the `i`th index of
     * the string `initialString`.
     * 2. `'a'` represents the character 'a' in the ASCII or Unicode character set.
     * 3. The expression `initialString.charAt(i) - 'a'` subtracts the ASCII or
     * Unicode value of the character at index `i` from the ASCII or Unicode value
     * of 'a'.
     * 4. The resulting value, stored in the `initialChar` variable, represents the
     * index of the character within the English alphabet. The character 'a'
     * corresponds to 0, 'b' corresponds to 1, 'c' corresponds to 2, and so on.
     * 
     * For example, if `initialString.charAt(i)` returns the character 'd', then
     * `initialChar` will be assigned the value 3 because the ASCII or Unicode value
     * of 'd' is three more than the ASCII or Unicode value of 'a'.
     */

    private static boolean[][] createAllowedTransitions(String initialString, String finalString) {

        boolean[][] allowedTransitions = new boolean[26][26];
        int length = initialString.length();

        for (int i = 0; i < length; ++i) {
            int initialChar = initialString.charAt(i) - 'a';
            int finalChar = finalString.charAt(i) - 'a';
            allowedTransitions[initialChar][finalChar] = true;
            allowedTransitions[finalChar][initialChar] = true;
        }

        /*
         * This line of code takes a character from a string called initialString at the
         * i-th index and converts it to an integer value based on its distance from the
         * lowercase letter 'a' in the ASCII character set. This is known as ASCII value
         * subtraction.
         * 
         * For example, if the character at the i-th index is 'b', then the value of
         * initialChar would be 1 because 'b' has an ASCII value of 98 and 'a' has an
         * ASCII value of 97. So, initialChar would be equal to 98 - 97, which is 1.
         * 
         * This code is commonly used when dealing with alphabets and performing
         * mathematical operations on them, such as in encryption or decryption
         * algorithms or when converting letters to numerical indices for use in arrays
         * or other data structures.
         */

        return allowedTransitions;
    }

    /**
     * This code is a method named `removeDiagonalChars` that takes a 2D boolean
     * array called `allowedTransitions` as a parameter. It iterates over the
     * diagonal elements of the array and checks if each element is `true`. If an
     * element on the diagonal is `true`, it sets all elements in the corresponding
     * row to `false` using `Arrays.fill()` and increments the count of diagonal
     * characters by 1.
     * 
     * Here's a step-by-step explanation of what the code does:
     * 
     * 1. It initializes a variable `numDiagonalChars` to keep track of the count of
     * diagonal characters, starting with 0.
     * 2. It enters a loop that iterates from 0 to 25 (inclusive). This assumes that
     * the array `allowedTransitions` has a size of 26x26 since it represents
     * characters of the alphabet (26 letters).
     * 3. Inside the loop, it checks if `allowedTransitions[i][i]` is `true`. This
     * condition checks if the current element on the diagonal (at index `[i][i]`)
     * is `true`.
     * 4. If the condition is `true`, it means that a diagonal character is present
     * at that position. It proceeds to the next step.
     * 5. It uses `Arrays.fill()` to set all elements in the `i`-th row of
     * `allowedTransitions` to `false`. This effectively removes the transitions or
     * connections from the diagonal character to other characters in the alphabet.
     * 6. It increments the count of diagonal characters by 1 using the
     * `++numDiagonalChars` statement.
     * 7. The loop continues until it has checked all diagonal elements of the
     * array.
     * 8. Finally, it returns the count of diagonal characters stored in
     * `numDiagonalChars`.
     * 
     * In summary, this method removes the diagonal characters from a 2D boolean
     * array `allowedTransitions` and returns the count of diagonal characters that
     * were removed.
     */

    private static int removeDiagonalChars(boolean[][] allowedTransitions) {

        int numDiagonalChars = 0;

        for (int i = 0; i < 26; ++i) {
            if (allowedTransitions[i][i]) {
                Arrays.fill(allowedTransitions[i], false);
                ++numDiagonalChars;
            }
        }

        return numDiagonalChars;
    }

    /**
     * In the given code snippet, the line `remainingChars |= 1 << i;` is inside a
     * method named `calculateRemainingChars`. This method takes a 2D boolean array
     * called `allowedTransitions` as a parameter.
     * 
     * Here's an explanation of the code in the context of the entire method:
     * 
     * 1. It initializes an integer variable `remainingChars` to 0. This variable
     * will be used to store a bitmask representing the remaining characters.
     * 2. It enters two nested loops. The outer loop iterates from 0 to 25,
     * representing the rows of the `allowedTransitions` array (assuming it is a
     * 26x26 matrix). This corresponds to the characters from 'a' to 'z' in the
     * English alphabet.
     * 3. Inside the outer loop, there is an inner loop that also iterates from 0 to
     * 25, representing the columns of the `allowedTransitions` array.
     * 4. The code checks if `allowedTransitions[i][j]` is `true`. This condition
     * checks if there is an allowed transition or connection between the character
     * at row `i` and the character at column `j` in the `allowedTransitions` array.
     * 5. If the condition is `true`, it means that there is an allowed transition
     * between the characters represented by the indices `i` and `j`. It proceeds to
     * the next step.
     * 6. It performs a bitwise OR operation and a bitwise left shift operation:
     * `remainingChars |= 1 << i;`. This line updates the `remainingChars` bitmask
     * by setting the bit at position `i` to 1.
     * - `1 << i` performs a bitwise left shift operation on the value 1, shifting
     * it `i` positions to the left. This effectively creates a bitmask with a
     * single bit set to 1 at position `i`.
     * - `remainingChars |= ...` is a bitwise OR assignment operation. It combines
     * the current value of `remainingChars` with the left-shifted bitmask,
     * effectively setting the bit at position `i` to 1 if it wasn't already set.
     * 7. After setting the bit for the current character `i`, it breaks out of the
     * inner loop using `break`. This is because the focus is on identifying at
     * least one allowed transition for each character, so if a transition is found,
     * there's no need to continue checking for further transitions for that
     * character.
     * 8. The loops continue until all the elements of the `allowedTransitions`
     * array have been checked.
     * 9. Finally, it returns the `remainingChars` bitmask that represents the
     * remaining characters with at least one allowed transition.
     * 
     * In summary, this method iterates through the `allowedTransitions` array and
     * builds a bitmask `remainingChars` where each bit represents whether a
     * character has at least one allowed transition. The method returns this
     * bitmask as the result.
     * 
     * A bitmask is a technique used to represent and manipulate sets of binary
     * flags or attributes. It is a binary pattern or a sequence of bits where each
     * bit corresponds to a specific flag or attribute.
     * 
     * What's a bitmask?
     * 
     * In the context of the code snippet you provided, remainingChars is a bitmask.
     * Each bit of the bitmask represents a character from 'a' to 'z' (assuming the
     * English alphabet is used). The presence or absence of a transition for each
     * character is indicated by the value of the corresponding bit in the bitmask.
     * 
     * For example, if remainingChars has a binary value of 0010010, it means that
     * the characters 'c', 'e', and 'f' have at least one allowed transition, while
     * the other characters have no allowed transitions.
     * 
     * By manipulating and examining the bits of a bitmask, you can efficiently
     * represent and perform operations on sets of flags or attributes. Bitwise
     * operations like bitwise OR (|), bitwise AND (&), and bitwise shifting
     * (<<, >>) are commonly used to manipulate and extract information from
     * bitmasks.
     */

    private static int calculateRemainingChars(boolean[][] allowedTransitions) {

        int remainingChars = 0;

        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                if (allowedTransitions[i][j]) {
                    remainingChars |= 1 << i;
                    break;
                }
            }
        }

        return remainingChars;
    }

    /**
     * Topological DFS sort https://en.wikipedia.org/wiki/Depth-first_search
     * 
     * DepthFirstSearch: This method takes several inputs: remainingChars (an
     * integer that represents the set of remaining characters), currentChar (an
     * integer that represents the current character being examined), currentState
     * (an integer that represents the current state of the string being
     * transformed), allowedTransitions (the 2D array that represents the allowed
     * transitions between characters), numOperations (the current number of
     * operations performed), and minOperations (an integer array that stores the
     * minimum number of operations required to transform initialString into
     * finalString). 
     * 
     * The method uses a depth-first search approach to examine all
     * possible combinations of transitions and operations. First, it checks if the
     * current number of operations is already greater than or equal to the minimum
     * number of operations found so far. If so, it returns without further
     * examination. 
     * 
     * Next, it checks if the current character is not in the set of
     * remaining characters. If so, it moves on to the next character. 
     * 
     * Otherwise, it examines the allowed transitions for the current character and counts the
     * number of possible transitions (numTransitions) and the set of transitions
     * (temp). It then calls itself twice recursively, once with the current
     * character removed from the set of remaining characters and the set of
     * transitions added to the current state, and once with the current character
     * added to the current state and the current number of operations incremented.
     * The method continues until all possible combinations of transitions and
     * operations have been examined. When the minimum number of operations required
     * to transform the initial string into the final string is found, it updates
     * the minOperations array.
     */
    public static void depthFirstSearch(int remainingChars, int currentChar, int currentState,
            final boolean[][] allowedTransitions, int numOperations, int[] minOperations) {

        // If the current number of operations is already greater than or equal to the
        // minimum number of operations found so far, return without further examination
        if (numOperations >= minOperations[0]) {
            return;
        }

        // basically a bit mask, XOR operand to check if the current character is in the
        // set of remaining characters
        int mask = 1 << currentChar;

        if (mask > remainingChars) {
            minOperations[0] = numOperations;
            return;
        }

        if ((mask & remainingChars) != 0) {

            int temp = 0;
            int numTransitions = 0;

            for (int i = currentChar + 1; i < 26; ++i) {
                if (allowedTransitions[i][currentChar]) {
                    if ((remainingChars & (1 << i)) > 0) {
                        // Set the bit corresponding to each character that has a valid transition from
                        // it
                        // bitwise OR
                        temp = temp | (1 << i);
                        ++numTransitions;
                    }
                }
            }

            /*
             * remainingChars ^ temp removes the current character from the set of
             * remaining
             * characters; bitwise XOR
             * 
             * currentState | temp combines the bits set in both currentState
             * and temp using a bitwise OR operation. This updates the currentState
             * bitmask
             * to include the bits representing the characters with valid transitions
             * from
             * the current character. The updated currentState is then passed in the
             * recursive calls to propagate the state information within the algorithm.
             */

            /*
             * The line `currentState | mask` performs a bitwise OR operation between the
             * `currentState` and `mask` variables. The purpose of this operation is to
             * update the `currentState` bitmask by combining the bits that are set in both
             * `currentState` and `mask`.
             * 
             * Here's an explanation of its purpose within the provided code:
             * 
             * - The `currentState` variable represents a bitmask that indicates the current
             * state or configuration.
             * - The `mask` variable is a bitmask that has only one bit set, corresponding
             * to the `currentChar`.
             * - The line `currentState | mask` is used to update the `currentState` bitmask
             * by combining the bits set in both `currentState` and `mask`.
             * - The `|` operator performs a bitwise OR operation between `currentState` and
             * `mask`.
             * - This operation sets the bits in the result bitmask to 1 if either the
             * corresponding bit in `currentState` or `mask` is set to 1.
             * - The resulting bitmask represents the updated state or configuration after
             * including the `currentChar` in the `currentState`.
             * - The updated `currentState` bitmask is passed as the `currentState` argument
             * in the recursive calls to maintain and propagate the state throughout the
             * algorithm.
             * 
             * In summary, `currentState | mask` combines the bits set in both
             * `currentState` and `mask` using a bitwise OR operation. This updates the
             * `currentState` bitmask to include the bit representing the `currentChar`. The
             * updated `currentState` is then passed in the recursive calls to propagate the
             * state information within the algorithm.
             */
            depthFirstSearch(remainingChars ^ temp, currentChar + 1, currentState | temp, allowedTransitions,
                    numOperations + numTransitions, minOperations);
            depthFirstSearch(remainingChars, currentChar + 1, currentState | mask, allowedTransitions,
                    numOperations + 1, minOperations);

        } else {
            depthFirstSearch(remainingChars, currentChar + 1, currentState, allowedTransitions, numOperations,
                    minOperations);
        }
    }
}

/*
 * This is a Java program that finds the minimum number of operations required
 * to transform one string (initialString) into another string (finalString)
 * using a specific set of allowed transitions between characters. The program
 * uses depth-first search to explore all possible combinations of transitions
 * and operations until the minimum number of operations required to transform
 * the initial string into the final string is found.
 * 
 * The program has two main methods:
 * 
 * findMinimumOperations: This method takes two strings as input (initialString
 * and finalString) and returns the minimum number of operations required to
 * transform initialString into finalString. The method first creates a 2D array
 * (allowedTransitions) to represent the allowed transitions between characters.
 * It then loops through the characters of initialString and finalString and
 * marks the allowed transitions between the corresponding characters in the
 * allowedTransitions array. Next, it identifies the diagonal characters (i.e.,
 * characters that can transition to themselves) and removes them from
 * allowedTransitions. Finally, it calculates the set of remaining characters
 * (i.e., characters that can transition to at least one other character) and
 * initializes an integer array (minOperations) to store the minimum number of
 * operations required to transform initialString into finalString. It then
 * calls the DepthFirstSearch method to find the minimum number of operations.
 * 
 * DepthFirstSearch: This method takes several inputs: remainingChars (an
 * integer that represents the set of remaining characters), currentChar (an
 * integer that represents the current character being examined), currentState
 * (an integer that represents the current state of the string being
 * transformed), allowedTransitions (the 2D array that represents the allowed
 * transitions between characters), numOperations (the current number of
 * operations performed), and minOperations (an integer array that stores the
 * minimum number of operations required to transform initialString into
 * finalString). The method uses a depth-first search approach to examine all
 * possible combinations of transitions and operations. First, it checks if the
 * current number of operations is already greater than or equal to the minimum
 * number of operations found so far. If so, it returns without further
 * examination. Next, it checks if the current character is not in the set of
 * remaining characters. If so, it moves on to the next character. Otherwise, it
 * examines the allowed transitions for the current character and counts the
 * number of possible transitions (numTransitions) and the set of transitions
 * (temp). It then calls itself twice recursively, once with the current
 * character removed from the set of remaining characters and the set of
 * transitions added to the current state, and once with the current character
 * added to the current state and the current number of operations incremented.
 * The method continues until all possible combinations of transitions and
 * operations have been examined. When the minimum number of operations required
 * to transform the initial string into the final string is found, it updates
 * the minOperations array.
 * 
 * Overall, the code is well-structured and easy to follow. The variable names
 * are clear and descriptive, making it easy to understand the purpose of each
 * variable. The comments could be more detailed, particularly in the
 * DepthFirstSearch method, to make it easier to understand how the recursion
 * works.
 */