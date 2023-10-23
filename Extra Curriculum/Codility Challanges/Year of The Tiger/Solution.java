public class Solution2 {
    
    private static final int ALPHABET_SIZE = 26;

	public int solution(String[] T) {
		int maxOccurrences = 1;
		int occurrences[][][] = new int[ALPHABET_SIZE][ALPHABET_SIZE][ALPHABET_SIZE];

		for (int i = 0; i < T.length; i++) {

			char[] chars = T[i].toCharArray();

			chars[0] -= 'a';
			chars[1] -= 'a';
			chars[2] -= 'a';

			occurrences[chars[0]][chars[1]][chars[2]]++;

			if (chars[0] != chars[1]) {
				occurrences[chars[1]][chars[0]][chars[2]]++;
			}

			if (chars[1] != chars[2]) {
				occurrences[chars[0]][chars[2]][chars[1]]++;
			}
            
			maxOccurrences = Math.max(maxOccurrences, occurrences[chars[0]][chars[1]][chars[2]]);
			maxOccurrences = Math.max(maxOccurrences, occurrences[chars[1]][chars[0]][chars[2]]);
			maxOccurrences = Math.max(maxOccurrences, occurrences[chars[0]][chars[2]][chars[1]]);
		}

		return maxOccurrences;
	}
}