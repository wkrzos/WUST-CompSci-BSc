import java.util.Arrays;

public class MainJavaRefinedNamesHelperMethods {

    // Solution: findMinimumOperations
    public static int solution(String initialString, String finalString) {

        // Create a 2D array to represent the allowed transitions between characters.
        // There are 26 letters in the english alphabet.
        boolean[][] allowedTransitions = createAllowedTransitions(initialString, finalString);

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
        int[] minOperations = new int[] { initialString.length() };

        // Call the DepthFirstSearch method to find the minimum number of operations to
        // transform the initial string into the final string and update the value of
        // minOperations[0]
        depthFirstSearch(remainingChars, 0, 0, allowedTransitions, numDiagonalChars, minOperations);

        System.out.println(minOperations[0]); // debug
        return minOperations[0];
    }

    private static boolean[][] createAllowedTransitions(String initialString, String finalString) {
        boolean[][] allowedTransitions = new boolean[26][26];
        int length = initialString.length();
        for (int i = 0; i < length; ++i) {
            int initialChar = initialString.charAt(i) - 'a';
            int finalChar = finalString.charAt(i) - 'a';
            allowedTransitions[initialChar][finalChar] = true;
            allowedTransitions[finalChar][initialChar] = true;
        }
        return allowedTransitions;
    }

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

    // Topological DFS sort
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