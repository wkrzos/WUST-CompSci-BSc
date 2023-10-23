public class Solution {

	public static void main(String[] args) {
		int[] matrix = {0, 2, 3, 4, 1, 1, 1, 3, 1};
		int[] result = solution(matrix);
		for(int i = 0; i < result.length; i++){
			System.out.println(result[i]);
		}
	}

	public static int[] solution(int[] T) {
		int[] outputArray = T;
		int[] rowSumArray = new int[3];
		int[] colSumArray = new int[3];
		int maxSum = -1;

		for (int i = 0; i < 3; i++) {
			rowSumArray[i] = 0;
			colSumArray[i] = 0;

			for (int j = 0; j < 3; j++) {
				rowSumArray[i] += T[j + 3*i];
				colSumArray[i] += T[3*j + i];
			}

			maxSum = Math.max(maxSum, rowSumArray[i]);
			maxSum = Math.max(maxSum, colSumArray[i]);
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (rowSumArray[i] < maxSum && colSumArray[j] < maxSum) {
					int difference = maxSum - Math.max(rowSumArray[i], colSumArray[j]);
					outputArray[3*i + j] += difference;
					rowSumArray[i] += difference;
					colSumArray[j] += difference;
				}
			}
		}
		
		return outputArray;
	}
}