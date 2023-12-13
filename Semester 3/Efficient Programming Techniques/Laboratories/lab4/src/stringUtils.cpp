#include <string>

// Splits a string into an array of words. Returns the array and updates the size.
std::string* splitStringIntoArray(const std::string& inputString, int* arraySize)
{
    std::string* wordArray = new std::string[inputString.length()]; // Allocate maximum possible size
    int wordCount = 0;
    std::string currentWord;

    for (char ch : inputString)
    {
        if (ch == ' ')
        {
            if (!currentWord.empty())
            {
                wordArray[wordCount++] = currentWord;
                currentWord.clear();
            }
        }
        else
        {
            currentWord += ch;
        }
    }

    if (!currentWord.empty())
    {
        wordArray[wordCount++] = currentWord;
    }

    *arraySize = wordCount;
    return wordArray;
}

// Joins an array of strings into a single string with spaces.
std::string joinArrayIntoString(const std::string* stringArray, int arraySize)
{
    std::string resultString;

    for (int i = 0; i < arraySize; ++i)
    {
        resultString += stringArray[i];

        if (i < arraySize - 1)
        {
            resultString += " ";
        }
    }

    return resultString;
}